/** \file    NxOgreSimpleActor.h
 *  \brief   Header for the SimpleActor class.
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

#ifndef __NXOGRE_SIMPLE_ACTOR_H__
#define __NXOGRE_SIMPLE_ACTOR_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"


namespace NxOgre {

	/** \brief SimpleActor is another representation of the NxActor class, unlike the
			   NxOgre Actor class, SimpleActors do not have names, they are never rendered,
			   or designed to be anything but a rigid body and do not use the extensive
			   Shape system.
	*/
	class NxPublicClass SimpleActor {

		protected:

			SimpleActor(Scene*);

		public:

			virtual ~SimpleActor();


			void setGlobalPose(const Pose&);
			Pose getGlobalPose() const;

			NxActor* getNxActor();
			Scene*   getScene();

			/** \brief Unique class hash identifier
			*/
			virtual NxShortHashIdentifier getType() const {
			  return NxOgreClass_SimpleActor; /* "NxOgre-SimpleActor" */
			}

			/** \brief Unique class identifier.
			*/
			virtual NxString getStringType() const {
			  return "NxOgre-SimpleActor";
			}

		protected:

			virtual void _addShapeToDescription(SimpleShape*, NxActorDesc*, bool ShapePoseIsActorPose);

			NxActor*     mActor;
			Scene*       mScene;
			VoidPointer*  mUserData;
	};

};

#endif
