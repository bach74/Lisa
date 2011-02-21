#pragma once
// =============================================================================
//  CritSectEx.cpp  
//  
//  Copyright (C) Vladislav Gelfer (http://www.codeproject.com/KB/threads/CritSectEx.aspx)
//
//
//  This source and header files are licensed under The Code Project Open License (CPOL).
//
//  This file is included in the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#ifndef WINVER 
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT 0x0501
#endif

//#include <windows.h>
//#include <tchar.h>
#include <intrin.h>
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

inline void InlDebugBreak() { __asm { int 3 }; }

#ifdef _DEBUG
#	ifndef ASSERT
#		define ASSERT(x) do { if (!(x)) InlDebugBreak(); } while (false)
#	endif // ASSERT
#	ifndef VERIFY
#		define VERIFY(x) ASSERT(x)
#	endif
#else // _DEBUG
#	ifndef ASSERT
#		define ASSERT(x)
#	endif // ASSERT
#	ifndef VERIFY
#		define VERIFY(x) (x)
#	endif
#endif // _DEBUG

inline void TestSys(BOOL bFailed)
{
	if (bFailed)
	{
		// error handling. Do whatever is necessary in your implementation.
		// The following is an example:
		ULONG_PTR nErrCode = GetLastError();
		RaiseException(0xC20A018E, EXCEPTION_NONCONTINUABLE_EXCEPTION, 1, &nErrCode);
	}
}

class CritSectEx {

	static DWORD s_dwProcessors;

	// Declare all variables volatile, so that the compiler won't
	// try to optimize something important.
	volatile DWORD	m_nLocker;
	volatile DWORD	m_dwSpinMax;
	volatile HANDLE	m_hSemaphore;
	volatile long	m_nWaiters;

	// disable copy constructor and assignment
	CritSectEx(const CritSectEx&);
	void operator = (const CritSectEx&);

	inline bool PerfLockImmediate(DWORD dwThreadID)
	{
		return !_InterlockedCompareExchange((long*) &m_nLocker, dwThreadID, 0);
	}
	inline void WaiterPlus()
	{
		_InterlockedIncrement(&m_nWaiters);
	}
	inline void WaiterMinus()
	{
		_InterlockedDecrement(&m_nWaiters);
	}

	bool PerfLock(DWORD dwThreadID, DWORD dwTimeout);
	bool PerfLockKernel(DWORD dwThreadID, DWORD dwTimeout);

	void PerfUnlock()
	{
		_WriteBarrier(); // changes done to the shared resource are committed.

		m_nLocker = 0;

		_ReadWriteBarrier(); // The CS is released.

		if (m_nWaiters > 0) // AFTER it is released we check if there're waiters.
		{
			WaiterMinus();

			ASSERT(m_hSemaphore);
			TestSys(!ReleaseSemaphore(m_hSemaphore, 1, NULL));
		}
	}

public:
	// Constructor/Destroctor
	CritSectEx()
	{
		ZeroMemory(this, sizeof(*this));
	}
	CritSectEx(DWORD dwSpinMax)
	{
		ZeroMemory(this, sizeof(*this));
		SetSpinMax(dwSpinMax);
	}
	~CritSectEx()
	{
		if (m_hSemaphore)
			VERIFY(CloseHandle(m_hSemaphore));
	}

	// Lock/Unlock
	bool Lock(bool& bUnlockFlag, DWORD dwTimeout = INFINITE)
	{
		DWORD dwThreadId = GetCurrentThreadId();
		if (dwThreadId == m_nLocker)
			bUnlockFlag = false;
		else
			if ((!m_nLocker && PerfLockImmediate(dwThreadId)) ||
				(dwTimeout && PerfLock(dwThreadId, dwTimeout)))
				bUnlockFlag = true;
			else
				return false;

		return true;
	}
	void Unlock(bool bUnlockFlag)
	{
		if (bUnlockFlag)
			PerfUnlock();
	}

	// Some extra
	void SetSpinMax(DWORD dwSpinMax);
	void AllocateKernelSemaphore();

	// Scope
	class Scope {

		// disable copy constructor and assignment
		Scope(const Scope&);
		void operator = (const Scope&);

		CritSectEx* m_pCs;
		bool m_bLocked;
		bool m_bUnlockFlag;

		void InternalUnlock()
		{
			if (m_bUnlockFlag)
			{
				ASSERT(m_pCs);
				m_pCs->PerfUnlock();
			}
		}
		void InternalLock(DWORD dwTimeout)
		{
			ASSERT(m_pCs);
			m_bLocked = m_pCs->Lock(m_bUnlockFlag, dwTimeout);
		}
		void InternalLock(CritSectEx& cs, DWORD dwTimeout)
		{
			m_bUnlockFlag = false;
			m_pCs = &cs;
			InternalLock(dwTimeout);
		}

	public:
		Scope()
			:m_bLocked(false)
			,m_bUnlockFlag(false)
			,m_pCs(NULL)
		{
		}
		Scope(CritSectEx& cs, DWORD dwTimeout = INFINITE)
		{
			InternalLock(cs, dwTimeout);
		}
		~Scope()
		{
			InternalUnlock();
		}

		bool Lock(CritSectEx& cs, DWORD dwTimeout = INFINITE)
		{
			if (&cs == m_pCs)
				return Lock(dwTimeout);

			InternalUnlock();
			InternalLock(cs, dwTimeout);
			return m_bLocked;
		}
		bool Lock(DWORD dwTimeout = INFINITE)
		{
			ASSERT(m_pCs);
			if (!m_bLocked)
				InternalLock(dwTimeout);
			return m_bLocked;
		}
		void Unlock()
		{
			InternalUnlock();
			m_bUnlockFlag = false;
			m_bLocked = false;
		}

		bool IsLocked() const { return m_bLocked; }
		operator bool () const { return m_bLocked; }
	};
	friend class Scope;
};

// Classical critical sections, with internal support for recursive locks counter.
class CritSectRec {
	CritSectEx m_cs;
	long m_nRecursion;

	// disable copy constructor and assignment
	CritSectRec(const CritSectRec&);
	void operator = (const CritSectRec&);

public:
	CritSectRec()
		:m_nRecursion(0)
	{
	}

	bool Enter(DWORD dwTimeout = INFINITE)
	{
		bool bUnlockFlag;
		if (!m_cs.Lock(bUnlockFlag, dwTimeout))
			return false;

		ASSERT(bUnlockFlag ? !m_nRecursion : (m_nRecursion > 0));
		m_nRecursion++;
		return true;
	}
	bool TryEnter()
	{
		return Enter(0);
	}
	void Leave()
	{
		ASSERT(m_nRecursion > 0);
		if (! --m_nRecursion)
			m_cs.Unlock(true);
	}

	// Some extra
	void SetSpinMax(DWORD dwSpinMax) { m_cs.SetSpinMax(dwSpinMax); }
	void AllocateKernelSemaphore() { m_cs.AllocateKernelSemaphore(); }

	struct Scope {

		// disable copy constructor and assignment
		Scope(const Scope&);
		void operator = (const Scope&);

		CritSectRec* m_pCs;
		bool m_bLocked;

		void InternalLeave()
		{
			if (m_bLocked)
			{
				ASSERT(m_pCs);
				m_pCs->Leave();
			}
		}
		void InternalEnter(DWORD dwTimeout)
		{
			ASSERT(m_pCs);
			m_bLocked = m_pCs->Enter(dwTimeout);
		}
		void InternalEnter(CritSectRec& cs, DWORD dwTimeout)
		{
			m_pCs = &cs;
			InternalEnter(dwTimeout);
		}

	public:
		Scope()
			:m_bLocked(false)
			,m_pCs(NULL)
		{
		}
		Scope(CritSectRec& cs, DWORD dwTimeout = INFINITE)
		{
			InternalEnter(cs, dwTimeout);
		}
		~Scope()
		{
			InternalLeave();
		}

		bool Enter(CritSectRec& cs, DWORD dwTimeout = INFINITE)
		{
			if (&cs == m_pCs)
				return Enter(dwTimeout);

			InternalLeave();
			InternalEnter(cs, dwTimeout);
			return m_bLocked;
		}
		bool Enter(DWORD dwTimeout = INFINITE)
		{
			ASSERT(m_pCs);
			if (!m_bLocked)
				InternalEnter(dwTimeout);
			return m_bLocked;
		}
		void Leave()
		{
			InternalLeave();
			m_bLocked = false;
		}

		bool IsLocked() const { return m_bLocked; }
		operator bool () const { return m_bLocked; }
	};
};

