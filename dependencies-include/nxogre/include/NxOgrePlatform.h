/** \file    NxOgrePlatform.h
 *  \brief   Specific platform configuration (Windows or Linux) and using
 *           macros to replace code for that specific to a platform.
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

#ifndef __NXOGRE_PLATFORM_H__
#define __NXOGRE_PLATFORM_H__


#include "NxVersionNumber.h"

/////////////////////////////////////////////////////////////

// Windows

#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#   define NX_PLATFORM_WINDOWS
#
#   if defined(NXOGRE_EXPORTS)
#       define NxPublicClass __declspec(dllexport)
#       define NxPublicFunction __declspec(dllexport)
#       define NxPublicFinalClass(K) \
        K; \
        namespace Private { class K { \
           private: \
             friend class ::K; \
             K() {} \
        };} \
        class __declspec(dllexport) K : private virtual Private::K
#	else
#       define NxPublicClass
#       define NxPublicFunction
#       define NxPublicFinal_Class(K) \
        K; \
        namespace Private { class K { \
           private: \
             friend class ::K; \
             K() {} \
        };} \
        class K : private virtual Private::K
#   endif
#
#   define NX_USE_CHARACTER_API 1
#
#   if (NX_SDK_VERSION_NUMBER >= 272)
#      define NX_USE_FORCEFIELD_API 1
#   else
#      define NX_USE_FORCEFIELD API 0
#   endif
#
#
#   if (NX_SDK_VERSION_NUMBER >= 270)
#      define NX_USE_SOFTBODY_API 1
#      define NX_USE_CLOTH_API 1
#   else
#      define NX_USE_SOFTBODY_API 0
#      define NX_USE_CLOTH_API 0
#   endif
#
#   if (NX_SDK_VERSION_NUMBER >= 260)
#      define NX_USE_FLUID_API 1
#   else
#      define NX_USE_FLUID_API 0
#   endif
#
#endif

/////////////////////////////////////////////////////////////

// Linux

#if defined LINUX
#
#   define NX_PLATFORM_LINUX
#
#   if (NX_SDK_VERSION_NUMBER >= 272)
#      define NX_USE_FORCEFIELD_API 1
#	else
#      define NX_USE_FORCEFIELD API 0
#   endif
#
#   if (NX_SDK_VERSION_NUMBER >= 270)
#      define NX_USE_SOFTBODY_API 1
#      define NX_USE_CLOTH_API 1
#   else
#      define NX_USE_SOFTBODY_API 0
#      define NX_USE_CLOTH_API 0
#   endif
#
#   if (NX_SDK_VERSION_NUMBER >= 260)
#      define NX_USE_FLUID_API 1
#   else
#      define NX_USE_FLUID_API 0
#   endif
#
#endif

/////////////////////////////////////////////////////////////

// Debug or Release

#if (defined DEBUG) || (defined _DEBUG)
#   define NX_DEBUG 1
#else
#   define NX_DEBUG 0
#endif

/////////////////////////////////////////////////////////////

// Visual Studio annoyances.

#if defined( _MSC_VER )

//  Visual studio template function export annoyance.
#   define NxTemplateFunction __forceinline

//  Disable Warning: warning C4267: conversion from 'size_t'
//  to 'unsigned int', possible loss of data
#   pragma warning(disable: 4267) 

#endif

/////////////////////////////////////////////////////////////

// Default macros (which may of not been defined by the above).

#ifndef NxTemplateFunction
#   define NxTemplateFunction inline
#endif

#ifndef NxPublicClass
#   define NxPublicClass
#endif

#ifndef NxPublicFunction
#   define NxPublicFunction
#endif

#ifndef NxPublicFinalClass
#       define NxPublicFinalClass(K) \
        K; \
        namespace Private { class K { \
           private: \
              friend class ::K; \
              K() {} \
        };} \
        class K : private virtual Private::K
#endif

/////////////////////////////////////////////////////////////

#endif
