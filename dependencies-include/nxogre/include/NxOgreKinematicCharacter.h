/** \file    NxOgreKinematicCharacter.h
 *  \brief   Header for the KinematicCharacter class.
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

#ifndef __NXOGRE_KINEMATIC_CHARACTER_H__
#define __NXOGRE_KINEMATIC_CHARACTER_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreCharacterController.h"

namespace NxOgre {
namespace CharacterSystem {

	/** \brief Kinematic based Character.
	*/
	class NxPublicClass KinematicCharacter : public CharacterController {

		friend class Character;

		protected:

			KinematicCharacter(NxMat34 pose, SimpleShape*, Scene*, VoidPointer*);	
		
		public:

			virtual ~KinematicCharacter();
		
					
			NxActorGroup		getActorGroup()							{return 0;}
			NxCollisionGroup	getCollisionGroup()						{return 0;}

			void				setActorGroup(NxActorGroup)				{}
			void				setCollisionGroup(NxCollisionGroup)		{}
		
			NxActor*            getActor() {
				return mActor;
			}

			VoidPointer*         getUserData() {
				return mUserData;
			}

		protected:

			void				init(NxMat34 pose);

			void				move(const NxVec3& direction);
			
			void				setPosition(const NxVec3& position);
			NxVec3				getPosition() const;
			
			void				setOrientation(const NxQuat& orientation);
			NxQuat				getOrientation() const;
			
			NxMat34				getPose() const;

			void				setSize(const NxVec3& size);
			NxVec3				getSize() const;
			
			void				setStepSize(NxReal stepSize);
			NxReal				getStepSize() const;
			
			void				setSlopeLimit(NxRadian slopeLimit);
			NxRadian			getSlopeLimit() const;

			void				setGravityEnabled(bool gravity);
			bool				getGravityEnabled() const;

			void				setUpDirection(NxVec3 upDirection);
			NxVec3				getUpDirection() const;

			virtual NxString	getType() const { return NxString("NxActorController"); };
		
		private:

			NxActor*            mActor;
			VoidPointer*        mUserData;
			VoidPointer*        mShapeUserData;
			NxVec3              mUpDirection;

	};

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
#endif
