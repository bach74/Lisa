/** \file    NxOgreJoint.h
 *  \brief   Header for the JointCallback, JointParams and Joint classes.
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

#ifndef __NXOGRE_JOINT_H__
#define __NXOGRE_JOINT_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

namespace NxOgre {

	class NxPublicClass JointParams : public Params {

		public:

			//////////////////////////////////////////////////////////////


			JointParams()					{
												setToDefault();
											}
			
			JointParams(const char* p)		{
												process(p);
											}

			JointParams(NxString p)			{
												process(p);
											}

			//////////////////////////////////////////////////////////////

			void							setToDefault();
			void							parse(Parameters);		
			void							fromNxJointDesc(NxJointDesc&);

			//////////////////////////////////////////////////////////////

			NxVec3							mNormalA;
			NxVec3							mNormalB;
			NxVec3							mAxisA;
			NxVec3							mAxisB;
			NxVec3							mAnchorA;
			NxVec3							mAnchorB;

			bool							mActorsCollidable;
			bool							mVisualiseJoint;

			JointCallback*					mBreakableCallback;
			NxReal							mBreakableMaxForce;
			NxReal							mBreakableMaxTorque;
	

			void							setLimits(Ogre::Radian upper, Ogre::Radian lower);
			void							setLimits(Ogre::Radian upper, NxReal upperRestitution, Ogre::Radian lower, NxReal lowerRestitution);
			bool							mHasLimits;
			NxReal							mUpperLimit; // Radian
			NxReal							mUpperLimitRestitution;
#if (NX_SDK_VERSION_NUMBER >= 272)
			NxReal							mUpperLimitHardness;
#endif
			NxReal							mLowerLimit; // Radian
			NxReal							mLowerLimitRestitution;
#if (NX_SDK_VERSION_NUMBER >= 272)
			NxReal							mLowerLimitHardness;
#endif

			void							setSpring(NxReal spring, NxReal target, NxReal damper);
			bool							mHasSpring;
			NxReal							mSpring;
			NxReal							mSpringTarget;
			NxReal							mSpringDamper;

			void							setMotor(NxReal maxForce, NxReal velocityTarget, bool freeSpin);
			bool							mHasMotor;
			bool							mMotorFreeSpin;
			NxReal							mMotorMaxForce;
			NxReal							mMotorVelocityTarget;


			void							setJointProjection(NxJointProjectionMode mode, Ogre::Radian angle, NxReal distance);
			NxJointProjectionMode			mJointProjectionMode;
			NxReal							mJointProjectionAngle;
			NxReal							mJointProjectionDistance;

			//	For:
			//		SphericalJoint		(swingAxis)
			NxVec3							mSwingAxis;

			//	For:
			//		SphericalJoint		SwingLimit Restitution
			//		SphericalJoint		SwingLimit Value
			//		SphericalJoint		SwingLimit Hardness
			bool							mHasSwingLimit;
			NxReal							mSwingLimit_Restitution;
			NxReal							mSwingLimit_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
			NxReal							mSwingLimit_Hardness;
#endif

			// For:
			//		SphericalJoint		SwingSpring	Damper
			//		SphericalJoint		SwingSpring	Spring
			//		SphericalJoint		SwingSpring TargetValue
			//		SphericalJoint		TwistLimit High/Low Restitution
			//		SphericalJoint		TwistLimit High/Low Value
			//		SphericalJoint		TwistLimit High/Low Hardness
 			bool							mHasTwistLimit;
 			NxReal							mTwistLimit_High_Restitution;
 			NxReal							mTwistLimit_High_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
			NxReal							mTwistLimit_High_Hardness;
#endif
 			NxReal							mTwistLimit_Low_Restitution;
 			NxReal							mTwistLimit_Low_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
			NxReal							mTwistLimit_Low_Hardness;
#endif
			
			// For:
			//		SphericalJoint		SwingSpring	Damper
			//		SphericalJoint		SwingSpring	Spring
			//		SphericalJoint		SwingSpring TargetValue
			bool							mHasTwistSpring;
			NxReal							mTwistSpring_Damper;
			NxReal							mTwistSpring_Spring;
			NxReal							mTwistSpring_Target;

			// For:
			//		SphericalJoint		SwingSpring	Damper
			//		SphericalJoint		SwingSpring	Spring
			//		SphericalJoint		SwingSpring TargetValue
			bool							mHasSwingSpring;
			NxReal							mSwingSpring_Damper;
			NxReal							mSwingSpring_Spring;
			NxReal							mSwingSpring_Target;

	};

	////////////////////////////////////////////////////////////////
	
	/** Joint
		Joints are used to connect two actors together, or a single actor and the World.

		Joints are sub-classes into x seperate joints
			- Spherical
			- Revolute
			- Prismatic
			- Cylindrical
			- Fixed
			- Distance
			- Point in Plane
			- Point on Line
			- Pully Joint
			- 6 Degrees of Freedom Joint

		All NxOgre joints have very similar constructors/creators:

			new RevoluteJoint(actorA, actorB, globalPosition, globalAxis, params);
			mScene->createRevoluteJoint(actorA, actorB, globalPosition, globalAxis, params);

	*/

	class NxPublicClass Joint {
		
	public:

		/** Joint Constructor (Two actors Joint)
			\note
				This is an "empty" class, use the correct constructor in the related joint you want.
		*/
		Joint(Actor*,Actor*);
		

		/** Joint Constructor (Actors/World Joint)
			\note
				This is an "empty" class, use the correct constructor in the related joint you want.
		*/
		Joint(Actor*);
		
		
		/** Joint Destructor

		*/
		virtual ~Joint();

		////////////////////////////////////////////////////////////////
	
		struct LimitPlane {

			LimitPlane(const NxVec3 & normal, NxReal planeD, NxReal restitution = 0.0f) {
				mNormal = normal;
				mD = planeD;
				mRestitution = restitution;
			}
			
			NxVec3 mNormal;
			NxReal mD, mRestitution;
		};

		////////////////////////////////////////////////////////////////
		
		
		/** getActorA
			Returns the Actor which is assigned to "A".
			\return Actor A
		*/
		Actor*						getActorA()							{
																			return mActorA;
																		}

		/** getActorB
			Returns the Actor which is assigned to "B".
			\note
				If there is no B, or the Joint is attached to the World. A NULL pointer is returned.
			\return Actor B
		*/
		Actor*						getActorB()							{
																			return mActorB;
																		}

		/** getScene
			Returns the Scene which Actor A is in.
		*/
		Scene*						getScene();
		
		/** getID
			Returns the unique ID of this joint.
			\return	The Joint ID
		*/
		NxJointID					getID()								{
																			return mID;
																		}
		/** setID
			Set's the ID of the Joint
			\note
				This will not update the container the joint is stored in.
		*/
		void						setID(NxJointID id)					{
																			mID = id;
																		}

		/** getNxJoint
			Returns the abstract NxJoint class.
			\return The NxJoint
		*/
		NxJoint*					getNxJoint()						{
																			return mJoint;
																		}


		/** setGlobalAnchor
			Sets the point where ActorA and ActorB are attached (in global coordinates).
			\param anchor	The point of attachment.
		*/
		void						setGlobalAnchor(const Ogre::Vector3 &anchor);
		

		/** setGlobalAnchor
			Sets the point where ActorA and ActorB are attached (in global coordinates).
			\param anchor	The point of attachment.
		*/
		void						setGlobalAnchor(const NxVec3 &anchor);


		/** setGlobalAxis
			Set the normalised direction of the joint axis.
			\param axis		The Joint axis
		*/
		void						setGlobalAxis(const Ogre::Vector3 &axis);


		/** setGlobalAxis
			Set the normalised direction of the joint axis.
			\param axis		The Joint axis
		*/
		void						setGlobalAxis(const NxVec3 &axis);

		
		/** getGlobalAnchor
			Gets the point where ActorA and ActorB are attached (in global coordinates).
			\return The point of attachment.
		*/
		Ogre::Vector3				getGlobalAnchor() const;
	
		
		/** getGlobalAnchor
			Gets the point where ActorA and ActorB are attached (in global coordinates).
			\return The point of attachment.
		*/
		NxVec3						getGlobalAnchorAsNxVec3() const;


		/** getGlobalAxis
			Get's the normalised direction of the joint axis.
			\param axis		The Joint axis
		*/
		Ogre::Vector3				getGlobalAxis() const;


		/** getGlobalAxis
			Get's the normalised direction of the joint axis.
			\param axis		The Joint axis
		*/
		NxVec3						getGlobalAxisAsNxVec3()	const;


		/** getGlobalAxis
			Get's the normalised direction of the joint axis.
			\param axis		The Joint axis
		*/
		NxJointState				getState();


		/** setBreakable
			Specifies the maximum force or torque before the Joint breaks.
		*/
		void						setBreakable(NxReal maxForce, NxReal maxTorque);


		/** getBreakableMaxForce
			Returns the maxmium force before the Joint breaks.
		*/
		NxReal						getBreakableMaxForce();


		/** getBreakableMaxTorque
			Returns the maxmium torque before the Joint breaks.
		*/
		NxReal						getBreakableMaxTorque();


		/** setLimitPoint
			Set's the limit point of the Joint
		*/
		void						setLimitPoint(const Ogre::Vector3& point, bool onActorB = true);


		/** setLimitPoint
			Set's the limit point of the Joint
		*/
		void						setLimitPoint(const NxVec3 &point, bool onActorB = true);


		/** getLimitPoint
			Get's the limit point of the Joint
			\return The Limit point 
		*/
		Ogre::Vector3				getLimitPoint() const;


		/** getLimitPoint
			Get's the limit point of the Joint
			\return The Limit point 
		*/
		NxVec3						getLimitPointAsNxVec3() const;


		/** addLimitPlane
			Get's the limit point of the Joint
			\param normal Normal for the limit plane in global coordinates.
			\param pointInPlane Point in the limit plane in global coordinates.
			\param restitution Restitution of the limit plane.
		*/
		void						addLimitPlane(const NxVec3 &normal, const NxVec3 & pointInPlane, NxReal restitution = 0.0f);
		
		
		/** clearLimitPlanes
			Removes all of the limit planes in this joint.
		*/
		void						clearLimitPlanes();

		
		/** getLimitPlanes
			Returns a list of all of the limit planes in this joint.
		*/
		std::vector<LimitPlane>		getLimitPlanes();

	

	protected:

		//////////////////////////////////////////////////////////////////////////////

		void ActorsToDescription(Actor*, Actor*, NxJointDesc&);
		void ActorToDescription(Actor*, NxJointDesc&);
		void ParamsToDescription(JointParams&, NxJointDesc&);

		//////////////////////////////////////////////////////////////////////////////

		Actor				*mActorA;
		Actor				*mActorB;
		Scene				*mScene;
		NxJoint*			 mJoint;
		NxJointID			 mID;

		JointCallback*		 mCallback;

	};

};

#endif
