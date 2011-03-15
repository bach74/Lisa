/** \file    NxOgreJointSet1.cpp
 *  \see     NxOgreJointSet1.h
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

#include "NxOgreStable.h"
#include "NxOgreJointSet1.h"
#include "NxOgreJoint.h"			// For: These joints inherit Joint
#include "NxOgreActor.h"			// For: a::getNxActor, b::getNxActor
#include "NxOgreHelpers.h"			// For: Vector3 to NxVec3 conversion
#include "NxOgreScene.h"			// For: mScene::getNxScene()
#include "NxOgreJointCallback.h"	// For: Joint callbacks.

namespace NxOgre {


// SphericalJoint



////////////////////////////////////////////////////////////////////////////////////

SphericalJoint::SphericalJoint(Actor *a ,Actor *b, const Ogre::Vector3 &anchor, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(anchor,jp);
}

////////////////////////////////////////////////////////////////////////////////////

SphericalJoint::SphericalJoint(Actor *a, const Ogre::Vector3 &anchor, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(anchor, jp);
}

////////////////////////////////////////////////////////////////////////////////////

void SphericalJoint::__createJoint(const Ogre::Vector3 &anchor, JointParams& jp) {
	
	mCallback = 0;
	mDescription.setGlobalAnchor(NxConvert<NxVec3, Ogre::Vector3>(anchor));
	mDescription.userData = this;
	
	if (jp.mHasSpring) {
		mDescription.jointSpring.damper = jp.mSpringDamper;
		mDescription.jointSpring.spring = jp.mSpring;
		mDescription.jointSpring.targetValue = jp.mSpringTarget;
		mDescription.flags |= NX_SJF_JOINT_SPRING_ENABLED;
	}

	mDescription.swingAxis						= jp.mSwingAxis;
	
	if (jp.mHasSwingLimit) {
		mDescription.swingLimit.restitution		= jp.mSwingLimit_Restitution;
		mDescription.swingLimit.value			= jp.mSwingLimit_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
		mDescription.swingLimit.hardness		= jp.mSwingLimit_Hardness;
#endif
		mDescription.flags |= NX_SJF_SWING_LIMIT_ENABLED;
	}
	
	if (jp.mHasSwingSpring) {
		mDescription.swingSpring.damper			= jp.mSwingSpring_Damper;
		mDescription.swingSpring.spring			= jp.mSwingSpring_Spring;
		mDescription.swingSpring.targetValue	= jp.mSwingSpring_Target;
		mDescription.flags |= NX_SJF_SWING_SPRING_ENABLED;
	}
	
	if (jp.mHasTwistLimit) {
		mDescription.twistLimit.high.restitution	= jp.mTwistLimit_High_Restitution;
		mDescription.twistLimit.high.value			= jp.mTwistLimit_High_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
		mDescription.twistLimit.high.hardness		= jp.mTwistLimit_High_Hardness;
#endif
		mDescription.twistLimit.low.restitution		= jp.mTwistLimit_Low_Restitution;
		mDescription.twistLimit.low.value			= jp.mTwistLimit_Low_Value;
#if (NX_SDK_VERSION_NUMBER >= 272)
		mDescription.twistLimit.low.hardness		= jp.mTwistLimit_Low_Hardness;
#endif

		mDescription.flags |= NX_SJF_TWIST_LIMIT_ENABLED;
	}

	if (jp.mHasTwistSpring) {
		mDescription.twistSpring.damper				= jp.mTwistSpring_Damper;
		mDescription.twistSpring.spring				= jp.mTwistSpring_Spring;
		mDescription.twistSpring.targetValue		= jp.mTwistSpring_Target;
		mDescription.flags |= NX_SJF_TWIST_SPRING_ENABLED;
	}

	
	////////////////////////////////////////////////////
	
	if (mDescription.swingAxis.magnitudeSquared() < 0.9f) 
		std::cout << "magnitudeSquared" << std::endl;
	if (mDescription.projectionDistance < 0.0f) 
		std::cout << "projectionDistance" << std::endl;

	if (!mDescription.twistLimit.isValid()) 
		std::cout << "twistLimit" << std::endl;
	if (!mDescription.swingLimit.isValid()) 
		std::cout << "swingLimit" << std::endl;
	if (!mDescription.swingSpring.isValid()) 
		std::cout << "swingSpring" << std::endl;
	if (!mDescription.twistSpring.isValid()) 
		std::cout << "twistSpring" << std::endl;
	if (!mDescription.jointSpring.isValid()) 
		std::cout << "jointSpring" << std::endl;


	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mSphericalJoint = static_cast<NxSphericalJoint*>(mJoint);

}

////////////////////////////////////////////////////////////////////////////////////

SphericalJoint::~SphericalJoint() {

	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mSphericalJoint = 0;
	if (mCallback)
		delete mCallback;
}



// RevoluteJoint




////////////////////////////////////////////////////////////////////////////////////

RevoluteJoint::RevoluteJoint(Actor *a ,Actor *b, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor,jp);
}

////////////////////////////////////////////////////////////////////////////////////

RevoluteJoint::RevoluteJoint(Actor *a, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor, jp);
}

////////////////////////////////////////////////////////////////////////////////////

void RevoluteJoint::__createJoint(const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams& jp) {
	
	mCallback = 0;
	mDescription.setGlobalAnchor(NxConvert<NxVec3, Ogre::Vector3>(anchor));
	mDescription.setGlobalAxis(NxConvert<NxVec3, Ogre::Vector3>(axis));
	mDescription.userData = this;
	
	if (jp.mHasLimits) {
		mDescription.limit.high.setToDefault();
		mDescription.limit.high.restitution = jp.mUpperLimitRestitution;
		mDescription.limit.high.value = jp.mUpperLimit;
#if (NX_SDK_VERSION_NUMBER >= 272)
		mDescription.limit.high.hardness = jp.mUpperLimitHardness;
#endif
		mDescription.limit.low.restitution = jp.mLowerLimitRestitution;
		mDescription.limit.low.value = jp.mLowerLimit;
#if (NX_SDK_VERSION_NUMBER >= 272)
		mDescription.limit.low.hardness = jp.mLowerLimitHardness;
#endif
		mDescription.flags |= NX_RJF_LIMIT_ENABLED;
	}

	if (jp.mHasSpring && !jp.mHasMotor) {
		mDescription.spring.damper = jp.mSpringDamper;
		mDescription.spring.spring = jp.mSpring;
		mDescription.spring.targetValue = jp.mSpringTarget;
		mDescription.flags |= NX_RJF_SPRING_ENABLED;
	}

	if (jp.mHasMotor && !jp.mHasSpring) {
		mDescription.motor.freeSpin = jp.mMotorFreeSpin;
		mDescription.motor.maxForce = jp.mMotorMaxForce;
		mDescription.motor.velTarget = jp.mMotorVelocityTarget;
		mDescription.flags |= NX_RJF_MOTOR_ENABLED;
	}
	
	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mRevoluteJoint = static_cast<NxRevoluteJoint*>(mJoint);

}

////////////////////////////////////////////////////////////////////////////////////

RevoluteJoint::~RevoluteJoint() {

	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mRevoluteJoint = 0;
	if (mCallback)
		delete mCallback;
}

////////////////////////////////////////////////////////////////////////////////////





// PrismaticJoint




////////////////////////////////////////////////////////////////////////////////////

PrismaticJoint::PrismaticJoint(Actor *a ,Actor *b, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor,jp);
}

////////////////////////////////////////////////////////////////////////////////////

PrismaticJoint::PrismaticJoint(Actor *a, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor, jp);
}

////////////////////////////////////////////////////////////////////////////////////

void PrismaticJoint::__createJoint(const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams& jp) {
	
	mCallback = 0;
	mDescription.setGlobalAnchor(NxConvert<NxVec3, Ogre::Vector3>(anchor));
	mDescription.setGlobalAxis(NxConvert<NxVec3, Ogre::Vector3>(axis));
	mDescription.userData = this;

	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mPrismaticJoint = static_cast<NxPrismaticJoint*>(mJoint);
	

}

////////////////////////////////////////////////////////////////////////////////////

PrismaticJoint::~PrismaticJoint() {

	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mPrismaticJoint = 0;
	if (mCallback)
		delete mCallback;
}

////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
