/** \file    NxOgreNxActorController.h
 *  \brief   Header for the NxActorController class.
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


#ifndef __NXOGRE_NXACTOR_CONTROLLER_H__
#define __NXOGRE_NXACTOR_CONTROLLER_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreCharacterController.h"

namespace NxOgre {
namespace CharacterSystem {

	class NxPublicClass NxActorController : public CharacterController {
			
		friend class Character;
		
		protected:

			NxActorController(NxMat34 pose, SimpleShape*, Scene*, VoidPointer*);

		public:
			
			virtual ~NxActorController();
		
					
			NxActorGroup		getActorGroup();
			NxCollisionGroup	getCollisionGroup();

			void				setActorGroup(NxActorGroup);
			void				setCollisionGroup(NxCollisionGroup);
		
			NxActor*			getActor() {
				return mActor;
			}

			VoidPointer*	getUserData() {
				return mUserData;
			}

			NxShape*			getShape() {
				return mShape;
			}

		protected:
			
			void				init(NxMat34 pose)					{}

			void				move(const NxVec3& direction)		{}
			
			void				setPosition(const NxVec3& position)	{}
			NxVec3				getPosition() const					{return NxVec3(0,0,0);}
			
			void				setOrientation(const NxQuat& orientation)	{}
			NxQuat				getOrientation() const						{return NxVec3(0,0,0);}
						
			void				setSize(const NxVec3& size)					{}
			NxVec3				getSize() const								{return NxVec3(0,0,0);}
			
			void				setStepSize(NxReal stepSize)				{}
			NxReal				getStepSize() const							{return 0;}
			
			void				setSlopeLimit(NxRadian slopeLimit)			{}
			NxRadian			getSlopeLimit() const						{return 0;}
	
			void				setGravityEnabled(bool gravity)				{}
			bool				getGravityEnabled() const					{return false;}

			void				setUpDirection(NxVec3 upDirection)			{}
			NxVec3				getUpDirection() const						{return NxVec3(0,0,0);}

			virtual NxString	getType() const { return NxString("NxActorController"); };
		
		private:

			NxActor*			mActor;
			VoidPointer*	mUserData;
			NxShape*			mShape;

	};

	/////////////////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
#endif
