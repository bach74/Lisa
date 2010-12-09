/** \file    NxOgreUserAllocator.h
 *  \brief   Header for the UserAllocator class and NxCreateAllocator macro.
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

#ifndef __NXOGRE_USERALLOCATOR_H__
#define __NXOGRE_USERALLOCATOR_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

#if (NX_DEBUG == 1)
	
	#define NxCreateAllocator(s) new NxOgre::UserAllocator(s);

#if (NX_USE_OGRE == 1)
//#  include <OgreNoMemoryMacros.h>
#endif

	class NxPublicClass UserAllocator : public NxUserAllocator {
		
		public:
			
			UserAllocator(const NxString& name) : mName(name), m(0),md(0), r(0), f(0) {}
			
			~UserAllocator() {

				char buffer [255];
				sprintf (buffer, "Allocator '%s' destroyed. Stats; malloc: %i, dmalloc: %i, realloc: %i, free: %i", mName.c_str(), m, md, r, f);

				if ( int(m - f) != 0 || (md != 0 && int(md - f) != 0) ) {
					char sbuffer[255 + 15];
					sprintf(sbuffer, "%s - Leaks found!", buffer);
					NxDebug(NxString(sbuffer).c_str());
				}
				else {
					NxDebug(NxString(buffer).c_str());
				}
			}

			void *malloc(NxU32 size)
			{
				m++;
				return ::malloc(size);
			}
	

			void *mallocDEBUG(NxU32 size,const char *fileName, int line)
			{
				md++;
				return ::_malloc_dbg(size,_NORMAL_BLOCK, fileName, line);
			} 
	

			void * realloc(void * memory, NxU32 size)
			{
				r++;
				return ::realloc(memory,size);
			}

	
			void free(void * memory)
			{
				f++;
				::free(memory);
			}


			NxString mName;
			NxU32 m,md,r,f;

	};

#if (NX_USE_OGRE == 1)
//#  include <OgreMemoryMacros.h>
#endif

#else

	#define NxCreateAllocator(s) new NxOgre::UserAllocator();

	class NxPublicClass UserAllocator : public NxUserAllocator {
	
		public:
			
			UserAllocator() {}
			~UserAllocator() {}
			
			void *malloc(NxU32 size) {
				return ::malloc(size);
			}
			
			void *mallocDEBUG(NxU32 size,const char *fileName, int line) {
				return ::_malloc_dbg(size,_NORMAL_BLOCK, fileName, line);
			} 
			
			void * realloc(void * memory, NxU32 size) {
				return ::realloc(memory,size);
			}
			
			void free(void * memory) {
				::free(memory);
			}

	};
#endif

};

#endif
