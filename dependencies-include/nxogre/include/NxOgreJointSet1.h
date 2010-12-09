/** \file    NxOgreJointSet1.h
 *  \brief   Header for the SphericalJoint, RevoluteJoint and Prismatic-
 *           Joint classes.
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

#ifndef __NXOGRE_JOINTSET1_H__
#define __NXOGRE_JOINTSET1_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreJoint.h"

namespace NxOgre {


	/** Spherical Joints
		A spherical joint is the simplest kind of joint. It constrains two points on two different bodies 
		from coinciding. This point, located in world space, is the only parameter that has to be specified 
		(the other parameters are optional). Specifying the anchor point (point that is forced to coincide) 
		in world space guarantees that the point in the local space of each body will coincide when the 
		point is transformed back from local into world space. 
	
		\note Params specific to SphericalJoint

		- Limits

			- Swing Axis
			  Defines the center of the swing limit cone, attached to actorA;
			  -> JointParams::mSwingAxis

		    - Swing Limit
			  Defines the angle which the joint can rotate away from the swing axis.
			  -> JointParams::mHasSwingLimit
			  -> JointParams::mSwingLimit_Restitution
			  -> JointParams::mSwingLimit_Value

			- Twist Limit
			  Defines the high and low limits for twist around the joint axis.
			  -> JointParams::mHasTwistLimit
			  -> JointParams::mTwistLimit_High_Restitution
			  -> JointParams::mTwistLimit_High_Value
			  -> JointParams::mTwistLimit_Low_Restitution
			  -> JointParams::mTwistLimit_Low_Value
		
		- Springs

			- Twist Spring
			  Spring which attempts to return the twist to the target value.
			  -> JointParams::mHasTwistSpring
			  -> JointParams::mTwistSpring_Damper
			  -> JointParams::mTwistSpring_Spring
			  -> JointParams::mTwistSpring_Target
		    
			- Swing Spring
			  Spring which attempts to return the joint axis to the swingAxis. 
			  -> JointParams::mHasSwingSpring
			  -> JointParams::mSwingSpring_Damper
			  -> JointParams::mSwingSpring_Spring
			  -> JointParams::mSwingSpring_Target
		    
			- Joint Spring
			  Specifies how much the joint can be pulled apart if joint spring is enabled. 
			  -> JointParams::mHasSpring
			  -> JointParams::mSpringDamper
			  -> JointParams::mSpring
			  -> JointParams::mSpringTarget

	*/

	class NxPublicClass SphericalJoint : public Joint {
		
	public:

		SphericalJoint(Actor*, Actor*, const Ogre::Vector3 &anchor, JointParams = JointParams());
		SphericalJoint(Actor*, const Ogre::Vector3 &anchor, JointParams = JointParams());
		~SphericalJoint();

		NxSphericalJoint* getJoint() {return mSphericalJoint;}

	protected:

		void __createJoint(const Ogre::Vector3 &anchor, JointParams&);

		NxSphericalJoint*		mSphericalJoint;
		NxSphericalJointDesc	mDescription;

	};

	/** Revolute Joints
		A spherical joint is the simplest kind of joint. It constrains two points on two different bodies 
		from coinciding. This point, located in world space, is the only parameter that has to be specified 
		(the other parameters are optional). Specifying the anchor point (point that is forced to coincide) 
		in world space guarantees that the point in the local space of each body will coincide when the 
		point is transformed back from local into world space. 
	
		\note Params specific to RevoluteJoint

		- Limit
		  Defines a lower and upper limit on the angle of rotation for the joint.
			-> JointParams::mHasLimits
			-> JointParams::mUpperLimitRestitution
			-> JointParams::mUpperLimit
			-> JointParams::mLowerLimitRestitution
			-> JointParams::mLowerLimit

		- Spring, Cannot be used with the Motor.
		  Defines an angular spring which will try and rotate the joint to the springs target value 
			-> JointParams::mHasSpring
			-> JointParams::mSpringDamper
			-> JointParams::mSpring
			-> JointParams::mSpringTarget

		- Motor, Cannot be used with the Spring.
		  Defines an angular motor to apply to the joint.
			-> JointParams::mMotorFreeSpin
			-> JointParams::mMotorMaxForce
			-> JointParams::mMotorVelocityTarget

	*/
	class NxPublicClass RevoluteJoint : public Joint {
		
	public:

		RevoluteJoint(Actor*, Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams = JointParams());
		RevoluteJoint(Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams = JointParams());
		~RevoluteJoint();

		NxRevoluteJoint* getJoint() {return mRevoluteJoint;}

	protected:

		void __createJoint(const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams&);

		NxRevoluteJoint*	mRevoluteJoint;
		NxRevoluteJointDesc mDescription;

	};


	/** PrismaticJoint
		A prismatic joint permits relative translational movement between two bodies along an axis,
		but no relative rotational movement at all. It is usually necessary to add joint limits to
		prevent the bodies from getting too far from each other along the joint axis. If the distance
		becomes too great, then the SDK can have difficulty maintaining the joint constraints. 

		\note Params Specific to PrismaticJoint
	*/
	class NxPublicClass PrismaticJoint : public Joint {
		
	public:

		PrismaticJoint(Actor*, Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams = JointParams());
		PrismaticJoint(Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams = JointParams());
		~PrismaticJoint();

		NxPrismaticJoint* getJoint() {return mPrismaticJoint;}

	protected:

		void __createJoint(const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams&);

		NxPrismaticJoint*	mPrismaticJoint;
		NxPrismaticJointDesc mDescription;

	};
};

#endif
