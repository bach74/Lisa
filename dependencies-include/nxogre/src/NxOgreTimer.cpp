/** \file    NxOgreTimer.cpp
 *  \see     NxOgreTimer.h
 *  \version 1.0-21
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *           version 2.1 of the License, or (at your option) any later version.
 *           
 *           This library is distributed in the hope that it will be useful,
 *           but WITHOUT ANY WARRANTY; without even the implied warranty of
 *           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received a copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NxOgreStable.h"
#include "NxOgreTimer.h"

// This page was left somewhat blank.

namespace NxOgre {

#ifdef NX_PLATFORM_WINDOWS

/////////////////////////////////////////////////////////////

Timer::Timer() {
	reset();
}

/////////////////////////////////////////////////////////////

Timer::~Timer() {
	
}
/////////////////////////////////////////////////////////////

void Timer::reset() {

    zeroClock = clock();

    QueryPerformanceFrequency(&mFrequency);
    QueryPerformanceCounter(&mStartTime);
    mStartTick = GetTickCount();
    mLastTime = 0;
    mQueryCount = 0;

    // Save the current process
    HANDLE mProc = GetCurrentProcess();

    // Get the current Affinity
#if _MSC_VER >= 1400 && defined (_M_X64)
    GetProcessAffinityMask(mProc, (PDWORD_PTR)&mProcMask, (PDWORD_PTR)&mSysMask);
#else
    GetProcessAffinityMask(mProc, &mProcMask, &mSysMask);
#endif

    mThread = GetCurrentThread();
}

/////////////////////////////////////////////////////////////

unsigned long Timer::milli() {

    LARGE_INTEGER curTime;

    // Set affinity to the first core
    SetThreadAffinityMask(mThread, 1);

    // Query the timer
    QueryPerformanceCounter(&curTime);

    // Reset affinity
    SetThreadAffinityMask(mThread, mProcMask);

	// Resample the frequency
    mQueryCount++;
    if(mQueryCount == frequency_resample_rate)
    {
        mQueryCount = 0;
        QueryPerformanceFrequency(&mFrequency);
    }

    LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
    
    // scale by 1000 for milliseconds
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);

    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;

        // Re-calculate milliseconds
        newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
    }

    // Record last time for adjust
    mLastTime = newTime;

    return newTicks;
}

/////////////////////////////////////////////////////////////

unsigned long Timer::micro() {

    LARGE_INTEGER curTime;
    QueryPerformanceCounter(&curTime);
    LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
    
    // get milliseconds to check against GetTickCount
    unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
    
    // detect and compensate for performance counter leaps
    // (surprisingly common, see Microsoft KB: Q274323)
    unsigned long check = GetTickCount() - mStartTick;
    signed long msecOff = (signed long)(newTicks - check);
    if (msecOff < -100 || msecOff > 100)
    {
        // We must keep the timer running forward :)
        LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
        mStartTime.QuadPart += adjust;
        newTime -= adjust;
    }

    // Record last time for adjust
    mLastTime = newTime;

    // scale by 1000000 for microseconds
    unsigned long newMicro = (unsigned long) (1000000 * newTime / mFrequency.QuadPart);

    return newMicro;
}

/////////////////////////////////////////////////////////////

#endif

#ifdef NX_PLATFORM_LINUX
// Code goes here.
#endif

}; // End of NxOgre namespace.