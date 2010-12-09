/** \file    NxOgreActors.h
 *  \brief   Header for the Actors classes.
 *  \version 1.0-20
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


#ifndef __NXOGRE_ACTORS_H__
#define __NXOGRE_ACTORS_H__

#if 0

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"

namespace NxOgre {

	class NxPublicClass Actors : public Container<NxString, Actor*> {

		public:

			void Each(void (Type::*MethodPtr)()) {

				for(Actor* actor = begin(); actor = next();) {
					Actor->*MethodPtr();
				}

			}

			template <typename ReturnType>
			ReturnType Each(ReturnType (Type::*MethodPtr)()) {

				for(Actor* actor = begin(); actor = next();) {
					Actor->*MethodPtr();
				}

			}

			// 
			template <typename ReturnType, typename _Arg1>
			ReturnType each(ReturnType Actor::(*methodPtr)(_Arg1), _Arg1 argument1);

			// and so on ...
			void moveTowards(float3); // ...

	};

}; // End of NxOgre namespace.

#endif

#endif
