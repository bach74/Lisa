/** \file    NxOgreConfig.h
*  \brief   Configuration file of the NxOgre library, using macros to
*           switch on and off features of NxOgre.
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

#ifndef __NXOGRE_CONFIG_H__
#define __NXOGRE_CONFIG_H__

namespace NxOgre {


// Core
/////////////////////////////////////


/** \brief Report any possible leaks arising in the use of containers.
 
Stored variables that are not "locked" as possible leaks as thrown 
Errors, see log or your own Error Reporter for details.

0 - Disallow, 1 - Allow (Default)
*/
#define NX_TREAT_POSSIBLE_LEAKS_AS_LEAKS 1

/** \brief Compile with some of the unstable parts of the NxOgre API.

0 - Disallow (Default), 1 - Allow
*/
#define NX_UNSTABLE 1


// Debugging
/////////////////////////////////////


/** \brief Print any Reported Errors, Debug messages or Warnings to the Console.
	
	0 - Disallow (Default) 1 - Allow
*/
#define NX_CONSOLE_CHATTER 1

/** \brief Allow the DebugRenderer to be used.
	
	0 - Disallow (Default), 1 - Allow
*/
#define NX_USE_DEBUG_RENDERER_API 1

/** \brief Use allocator macros to track down leaks (NxNew, NxWatch and NxDelete)
	\note  This feature is only available in debug mode.
	
	0 - Disallow (Default), 1 - Allow
*/
#define NX_USE_ALLOCATOR_MACROS 1


// Serialisation and Cooking
/////////////////////////////////////


/** \brief Use JSON import/export fileformat. Requires JSONCPP dependency.
	\note Remember to add or remove jsoncpp.lib/jsoncppD.lib in the linker settings!
	
	0 - Disallow (Default) 1 - Allow
*/
#define NX_USE_JSON 0

/** \brief Use NxuStream serialisation system by Ageia. Requires NxuStream dependency.
	\note Remember to add or remove nxustream.lib/nxustream.lib in the linker settings!
	
	0 - Disallow (Default) 1 - Allow
*/
#define NX_USE_NXUSTREAM 0


// Ogre (Deprecated in NxOgre 1.5)
/////////////////////////////////////

/** \brief Use Ogre. Deprecated in NxOgre 1.5

	0 - Don't use Ogre, 1 - Use Ogre (default).
*/
#define NX_USE_OGRE 1


// Bleeding/0.9 changes
/////////////////////////////////////

/** \brief Use Legacy Character Controller from NxOgre 0.9
*/
#define NX_USE_LEGACY_NXCONTROLLER 0


};

#endif
