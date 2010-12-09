/** \file    NxOgreCharacterMovementModel.h
 *  \brief   Header for the CharacterMovementModel class.
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

#ifndef __NXOGRE_CHARACTER_MOVEMENT_MODEL_H__
#define __NXOGRE_CHARACTER_MOVEMENT_MODEL_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreHelpers.h"

namespace NxOgre {
namespace CharacterSystem {

	class NxPublicClass CharacterMovementModel {
		
		public:
			
			virtual void		enter(CharacterMovementModel* from, NxMat34 pose)	{mPose = pose;mMovement.zero();mOrientation.id();}
			virtual NxMat34		exit()												{return mPose;}
			
			virtual void		simulate(NxReal dTime)								{}
			virtual void		simulateAfter(NxReal dTime)							{}
			virtual void		reset(Character* c)									{mCharacter = c;}// mPose = c->getPose();}
			virtual void		forward()											{}
			virtual void		backward()											{}
			virtual void		left()												{}
			virtual void		right()												{}
			virtual void		up()												{}
			virtual void		down()												{}
			
			virtual void		setYaw(NxRadian yaw)								{
				// mOrientation
			}
			
			void				setPose(NxMat34 pose)								{mPose = pose;}
			virtual	void		setPitch(NxRadian pitch)							{}
			virtual void		setRoll(NxRadian roll)								{}
			
			virtual void		setOrientation(NxQuat orientation)					{}
			virtual NxQuat		getOrientation()									{	NxQuat quat; 
																						mPose.M.toQuat(quat);
																						return quat;}
			
			virtual NxString	getType()											{return NxString("Default");}
			
			virtual NxVec3		getGlobalMovementVector(NxReal dT) {
				return (mOrientation * mMovement) * dT;
			}
			
			virtual NxVec3		getMovementVector() {
				return mMovement;
			}
			
			virtual NxQuat		getGlobalOrientation() {
				return mOrientation;
			}
			
		protected:
			
			Character*	mCharacter;
			NxMat34		mPose;
			NxVec3		mMovement;
			NxQuat		mOrientation;
			
		private:
		
	};
		
	////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
#endif
