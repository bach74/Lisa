/** \file    NxOgreCharacter.h
 *  \brief   Header for the CharacterParams and Character classes.
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

#ifndef __NXOGRE_CHARACTER_H__
#define __NXOGRE_CHARACTER_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreParams.h"
#include "NxOgrePose.h"

namespace NxOgre {
namespace CharacterSystem {


	class NxPublicClass CharacterParams : public Params {
		
		public:
		
			CharacterParams()					{	
													setToDefault();
												}
			
			CharacterParams(const char* p)		{	
													process(p);
												}

			CharacterParams(NxString p)			{	
													process(p);
												}

			void								setToDefault();

			enum ControllerType {
#if (NX_USE_CHARACTER_API == 1)
				CT_KINEMATIC,
#endif
				CT_NXACTOR,
				CT_PTR
			};

			ControllerType					mControllerType;
			CharacterController*			mControllerPtr;

			NxReal							mStepOffset;
			NxRadian						mSlopeLimit;
			NxAxisType						mUpDirection;
			NxGroupsMask					mGroupMask;

			/** \brief Collision shape for NxActor and NxCharacter controllers.
				\note The function "setToDefault" sets the pointer to zero. You
					  have to assign one after setting the basic params using
					  the new operator or the SimpleShape::createShapeFromString method

				\see Controllers for what shapes they can and cannot use
				\see SimpleShape::createShapeFromString
					

			*/

			SimpleShape*					mControllerCollisionShape;
		

	 };
		
	/////////////////////////////////////////////////////////
		
	/** Character

	*/
	class NxPublicClass Character {
		
		public:

			enum LocalMovementDirection {
				LMD_FORWARD		= 0,
				LMD_BACKWARD	= 1,
				LMD_LEFT		= 2,
				LMD_RIGHT		= 3,
				LMB_UP			= 4,
				LMB_DOWN		= 5
			};
		
			Character(const NxString& identifier, Pose, CharacterModel*, CharacterParams, Scene*);
			virtual ~Character();
			
			NxString getName() const {return mName;}
			
			virtual void simulate(const TimeStep&);
			
			CharacterController*		getController() const {
				return mController;
			}

			CharacterModel*				getModel() const {
				return mModel;
			}

			CharacterMovementModel*		getCurrentMovementModel() const {
				return mCurrentMovement;
			}

			void setModel(CharacterModel* newModel) {
				mModel = newModel;
				resetMovement();
			}
			
			void resetMovement()										{}
			void setMovement(NxString movement);
			void setMovement(Ogre::Vector3 movementVector);
			void setLocalMovement(Ogre::Vector3 movementVector);

			inline void forward();
			inline void backward();
			inline void left();
			inline void right();
			inline void up();
			inline void down();
			
			void injectMovement(LocalMovementDirection);
			void setDirection(const NxQuat& orientation);
			void setDirection(const Ogre::Quaternion& orientation);
			void moveTowards(Ogre::Vector3 globalPosition, NxReal force);
			void setYaw(NxRadian Yaw);
			void setYaw(Ogre::Radian Yaw);
			void setPitch(NxRadian Pitch);
			void setPitch(Ogre::Radian Pitch);
			void setRoll(NxRadian Roll);
			void setRoll(Ogre::Radian Roll);

			
			/** \brief Forces height to a new one, without a transitional movement period.
				Forces the local height of the character shape to a new one whilst moving
				the character to half-height below.
				
				\param height Height of the character
			*/
			void setHeight(NxReal height);

			
			/** \brief Forces height to a new one, with a transitional movement period.
				Forces the local height of the character shape to a new one whilst leaving it
				at the existing position. Naturaly gravity or a custom vector will kick in and
				move the character into the correct new position over the upcoming frames.

				\param height Height of the character
			*/
			void changeHeight(NxReal height);

			void setSize(const NxVec3& size);
			void setSize(const float2& size);

			void setGravityEnabled(bool);
			bool isGravityEnabled();

			bool isDead() const {return mDead;}

		protected:
		
			CharacterController*		mController;
			CharacterModel*				mModel;
			CharacterMovementModel*		mCurrentMovement;
		
			NxString		mName;
			Scene*			mOwner;
			VoidPointer*	mVoidPointer;

		private:

			bool		mDead;
		
	};
		
	////////////////////////////////////////////
};// End of CharacterSystem
};// End of namespace

#endif
#endif
