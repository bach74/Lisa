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
#include "stdafx.h"
#include "CritSectEx.h"

DWORD CritSectEx::s_dwProcessors = 0;

void CritSectEx::AllocateKernelSemaphore()
{
	if (!m_hSemaphore)
	{
		HANDLE hSemaphore = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
		TestSys(!hSemaphore);
		if (InterlockedCompareExchangePointer(&m_hSemaphore, hSemaphore, NULL))
			VERIFY(CloseHandle(hSemaphore)); // we're late
	}
}

bool CritSectEx::PerfLock(DWORD dwThreadID, DWORD dwTimeout)
{
	// Attempt spin-lock
	for (DWORD dwSpin = 0; dwSpin < m_dwSpinMax; dwSpin++)
	{
		if (PerfLockImmediate(dwThreadID))
			return true;

		YieldProcessor();
	}

	// Ensure we have the kernel event created
	AllocateKernelSemaphore();

	bool bVal = PerfLockKernel(dwThreadID, dwTimeout);
	WaiterMinus();

	return bVal;
}

bool CritSectEx::PerfLockKernel(DWORD dwThreadID, DWORD dwTimeout)
{
	bool bWaiter = false;

	for (DWORD dwTicks = GetTickCount(); ; )
	{
		if (!bWaiter)
			WaiterPlus();

		if (PerfLockImmediate(dwThreadID))
			return true;

		DWORD dwWait;
		if (INFINITE == dwTimeout)
			dwWait = INFINITE;
		else
		{
			dwWait = GetTickCount() - dwTicks; // how much time elapsed
			if (dwTimeout <= dwWait)
				return false;
			dwWait = dwTimeout - dwWait;
		}

		ASSERT(m_hSemaphore);
		switch (WaitForSingleObject(m_hSemaphore, dwWait))
		{
		case WAIT_OBJECT_0:
			bWaiter = false;
			break;
		case WAIT_TIMEOUT:
			bWaiter = true;
			break;
		default:
			TestSys(TRUE);
		}
	}

	// unreachable
}

void CritSectEx::SetSpinMax(DWORD dwSpinMax)
{
	if (!s_dwProcessors)
	{
		SYSTEM_INFO stSI;
		GetSystemInfo(&stSI);
		s_dwProcessors = stSI.dwNumberOfProcessors;
	}
	if (s_dwProcessors > 1)
		m_dwSpinMax = dwSpinMax;
}

