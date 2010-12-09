/** \file    NxOgreStable.h
 *  \brief   NxOgre pre-compiled header and common headers include used by 
 *           all NxOgre source (cpp) files with no exceptions.
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

#ifndef __NXOGRE_STABLE_H__
#define __NXOGRE_STABLE_H__

#include "NxOgreConfig.h"
#include "NxOgrePlatform.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>

#include "NxOgreAllocator.h"

#define Nx_Version_Major    1
#define Nx_Version_Minor    0
#define Nx_Version_Commit   21
#define Nx_Version_Codename "Bleeding Edge"

#if (NX_DEBUG == 0)
#   define Nx_Version_Full "NxOgre 1.0.20 Bleeding Edge"
#else
#   define Nx_Version_Full "NxOgre 1.0.20 Bleeding Edge (Debug)"
#endif

#if NX_USE_OGRE
#   include "OgrePrerequisites.h"
#endif

#if NX_USE_OGRE
//#   include <OgreNoMemoryMacros.h>
#endif

#include <Nx.h>
#include <NxPhysics.h>

#if NX_USE_OGRE
//#   include <OgreMemoryMacros.h>
#endif

#endif
