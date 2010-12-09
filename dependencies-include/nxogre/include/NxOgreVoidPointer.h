/** \file    NxOgreVoidPointer.h
 *  \brief   Header for the VoidPointer class.
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


#ifndef __NXOGRE_VOIDPOINTER_H__
#define __NXOGRE_VOIDPOINTER_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	class NxPublicClass VoidPointer {

		public:

			VoidPointer(void* ptr, NxOgreClassType type, RenderableSource* render_ptr = 0)
			   : Ptr(ptr),
			     Type(type),
			     RenderPtr(render_ptr)
			     {}

			NxOgreClassType getType() {
				return (NxOgreClassType) Type;
			}

			Actor* toActor() {
				return static_cast<Actor*>(Ptr);
			}

			SimpleActor* toSimpleActor() {
				return static_cast<SimpleActor*>(Ptr);
			}

			CharacterSystem::Character* toCharacter() {
				return static_cast<CharacterSystem::Character*>(Ptr);
			}

			Trigger* toTrigger() {
				return static_cast<Trigger*>(Ptr);
			}

			Shape* toShape() {
				return static_cast<Shape*>(Ptr);
			}

			void*                   Ptr;

			/** \brief Type of class according to the enum NxOgreClassType.
			*/
			unsigned int            Type;

			RenderableSource*       RenderPtr;

	};
	
};

#endif
