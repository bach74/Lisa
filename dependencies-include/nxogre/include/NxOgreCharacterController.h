/** \file    NxOgreCharacterController.h
 *  \brief   Header for the CharacterController class.
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


#ifndef __NXOGRE_CHARACTER_CONTROLLER_H__
#define __NXOGRE_CHARACTER_CONTROLLER_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

namespace NxOgre {
namespace CharacterSystem {

	class NxPublicClass CharacterController {
			
		friend class Character;

		public:
			
			CharacterController(Scene*, VoidPointer*);
			virtual ~CharacterController();
		
			virtual NxActorGroup		getActorGroup()							{return 0;}
			virtual NxCollisionGroup	getCollisionGroup()						{return 0;}

			virtual void				setActorGroup(NxActorGroup)				{}
			virtual void				setCollisionGroup(NxCollisionGroup)		{}
		
			virtual void				init(NxMat34 pose)						{}

			virtual void				move(const NxVec3& direction)			{}
			
			virtual void				setPosition(const NxVec3& position)		{}
			virtual NxVec3				getPosition() const						{return NxVec3(0,0,0);}
			
			virtual void				setOrientation(const NxQuat& orientation) {}
			virtual NxQuat				getOrientation() const					{NxQuat quat;quat.id();return quat;}
						
			virtual NxMat34				getPose() const							{NxMat34 m;m.id();return m;}

			virtual void				setSize(const NxVec3& size)				{}
			virtual void				getSize(NxVec3& size)					{}	

			virtual void				setSize(const float2& size)				{}
			virtual void				getSize(float2& size)					{}
			
			virtual void				setStepSize(NxReal stepSize)			{}
			virtual NxReal				getStepSize() const						{return 0;}
			
			virtual void				setSlopeLimit(NxRadian slopeLimit)		{}
			virtual NxRadian			getSlopeLimit() const					{return 0;}

			virtual void				setGravityEnabled(bool gravity)			{}
			virtual bool				getGravityEnabled() const				{return false;}

			virtual void				setUpDirection(NxVec3 upDirection)		{}
			virtual NxVec3				getUpDirection() const					{return NxVec3(0,0,0);}


			virtual NxString			getType() { return NxString("CharacterController"); };
		
			/////////////////////////////////////////////////

			Scene*						mScene;

		private:
	

	};
		
	////////////////////////////////////////////

};// End of CharacterSystem namespace.
};// End of NxOgre namespace.

#endif
#endif
