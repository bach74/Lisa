/** \file    NxOgreJointSet2.cpp
 *  \see     NxOgreJointSet2.h
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
#include "NxOgreJointSet2.h"
#include "NxOgreJoint.h"			// For: These joints inherit Joint
#include "NxOgreActor.h"			// For: a::getNxActor, b::getNxActor
#include "NxOgreHelpers.h"			// For: Vector3 to NxVec3 conversion
#include "NxOgreScene.h"			// For: mScene::getNxScene()
#include "NxOgreJointCallback.h"

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////





// CylindricalJoint




////////////////////////////////////////////////////////////////////////////////////

CylindricalJoint::CylindricalJoint(Actor *a ,Actor *b, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor,jp);
}

////////////////////////////////////////////////////////////////////////////////////

CylindricalJoint::CylindricalJoint(Actor *a, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(axis,anchor, jp);
}

////////////////////////////////////////////////////////////////////////////////////

void CylindricalJoint::__createJoint(const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, JointParams& jp) {
	
	mCallback = 0;
	mDescription.setGlobalAnchor(NxConvert<NxVec3, Ogre::Vector3>(anchor));
	mDescription.setGlobalAxis(NxConvert<NxVec3, Ogre::Vector3>(axis));
	mDescription.userData = this;

	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mCylindricalJoint = static_cast<NxCylindricalJoint*>(mJoint);
	

}

////////////////////////////////////////////////////////////////////////////////////

CylindricalJoint::~CylindricalJoint() {

	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mCylindricalJoint = 0;
	if (mCallback)
		delete mCallback;
}

////////////////////////////////////////////////////////////////////////////////////





// FixedJoint




////////////////////////////////////////////////////////////////////////////////////

FixedJoint::FixedJoint(Actor *a ,Actor *b, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp);
}

////////////////////////////////////////////////////////////////////////////////////

FixedJoint::FixedJoint(Actor *a, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp);
}

////////////////////////////////////////////////////////////////////////////////////

void FixedJoint::__createJoint(JointParams& jp) {
	
	mCallback = 0;

	mDescription.userData = this;

	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mFixedJoint = static_cast<NxFixedJoint*>(mJoint);
	

}

////////////////////////////////////////////////////////////////////////////////////

FixedJoint::~FixedJoint() {
	
	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mFixedJoint = 0;
	if (mCallback)
		delete mCallback;
}

////////////////////////////////////////////////////////////////////////////////////





// DistanceJoint




////////////////////////////////////////////////////////////////////////////////////

DistanceJoint::DistanceJoint(Actor* a, Actor* b, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp,0,0);
}

////////////////////////////////////////////////////////////////////////////////////

DistanceJoint::DistanceJoint(Actor* a, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp,0,0);
}

////////////////////////////////////////////////////////////////////////////////////

DistanceJoint::DistanceJoint(Actor* a, Actor* b, NxReal maxDistance, NxReal minDistance, JointParams jp) : Joint(a,b){
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorsToDescription(a, b, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp,maxDistance, minDistance);
}

////////////////////////////////////////////////////////////////////////////////////

DistanceJoint::DistanceJoint(Actor* a, NxReal maxDistance, NxReal minDistance, JointParams jp) : Joint (a) {
	mDescription.setToDefault();
	mDescription.jointFlags = 0;
	ActorToDescription(a, mDescription);
	ParamsToDescription(jp, mDescription);
	__createJoint(jp,maxDistance, minDistance);
}

////////////////////////////////////////////////////////////////////////////////////

void DistanceJoint::__createJoint(JointParams& jp, NxReal maxD, NxReal minD) {
	
	mCallback = 0;

	mDescription.userData = this;

	if (maxD) {
		mDescription.maxDistance = maxD;
		mDescription.flags |= NX_DJF_MIN_DISTANCE_ENABLED;
	}

	if (minD) {
		mDescription.minDistance = minD;
		mDescription.flags |= NX_DJF_MAX_DISTANCE_ENABLED;
	}

	if (jp.mHasSpring) {
		mDescription.spring.spring = jp.mSpring;
		mDescription.spring.damper = jp.mSpringDamper;
		mDescription.spring.targetValue = jp.mSpringTarget;
		mDescription.flags |= NX_DJF_SPRING_ENABLED;
	}

	mCallback = jp.mBreakableCallback;
	mJoint = mScene->getNxScene()->createJoint(mDescription);
	mDistanceJoint = static_cast<NxDistanceJoint*>(mJoint);
	
}

////////////////////////////////////////////////////////////////////////////////////

DistanceJoint::~DistanceJoint() {
	
	if (mJoint)
		mScene->getNxScene()->releaseJoint(*mJoint);

	mDistanceJoint = 0;
	if (mCallback)
		delete mCallback;
}

////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
