/** \file    NxOgreJoint.cpp
 *  \see     NxOgreJoint.h
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

#include "NxOgreStable.h"
#include "NxOgreJoint.h"
#include "NxOgreActor.h"		// For a::getScene()
#include "NxOgreHelpers.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////////////

Joint::Joint(Actor* a, Actor* b)
: mActorA(a),
  mActorB(b),
  mScene(a->getScene()),
  mID(0),
  mJoint(0)
{
}


Joint::Joint(Actor* a)
: mActorA(a),
  mActorB(0),
  mScene(a->getScene()),
  mID(0),
  mJoint(0)
{
}

/////////////////////////////////////////////////////////////////////

Joint::~Joint() {
}

/////////////////////////////////////////////////////////////////////

void Joint::ActorsToDescription(Actor* a, Actor* b, NxJointDesc& jd) {
	jd.actor[0] = a->getNxActor();
	jd.actor[1] = b->getNxActor();
}

/////////////////////////////////////////////////////////////////////

void Joint::ActorToDescription(Actor* a, NxJointDesc& jd) {
	jd.actor[0] = a->getNxActor();
	jd.actor[1] = NULL;
}

/////////////////////////////////////////////////////////////////////

void Joint::ParamsToDescription(JointParams& jp, NxJointDesc& jd) {
	
	jd.maxForce = jp.mBreakableMaxForce;
	jd.maxTorque = jp.mBreakableMaxTorque;

	if (jp.mActorsCollidable)
		jd.jointFlags |= NX_JF_COLLISION_ENABLED;

	if (jp.mVisualiseJoint)
		jd.jointFlags |= NX_JF_VISUALIZATION;

	jd.localAxis[0]   = jp.mAxisA;
	jd.localAxis[1]	  = jp.mAxisB;
	jd.localNormal[0] = jp.mNormalA;
	jd.localNormal[1] = jp.mNormalB;
	jd.localAnchor[0] = jp.mAnchorA;
	jd.localAnchor[1] = jp.mAnchorB;

}

/////////////////////////////////////////////////////////////////////

void JointParams::setToDefault() {

	mAxisA.set(0,0,1);
	mAxisB.set(0,0,1);
	mNormalA.set(1,0,0);
	mNormalB.set(1,0,0);
	mAnchorA.zero();
	mAnchorB.zero();

	mActorsCollidable = false;
	mVisualiseJoint = true;

	mBreakableCallback = 0;
	mBreakableMaxForce = NX_MAX_REAL;
	mBreakableMaxTorque = NX_MAX_REAL;

	mHasLimits = false;
	mUpperLimit = 0;
	mUpperLimitRestitution = 0 ;
#if (NX_SDK_VERSION_NUMBER >= 272)
	mUpperLimitHardness = 1;
#endif
	mLowerLimit = 0;
	mLowerLimitRestitution = 0;
#if (NX_SDK_VERSION_NUMBER >= 272)
	mLowerLimitHardness = 1;
#endif

	mHasSpring = false;
	mSpring = 0;
	mSpringTarget = 0;
	mSpringDamper = 0;

	mHasMotor = false;
	mMotorFreeSpin = false;
	mMotorMaxForce = 0;
	mMotorVelocityTarget = NX_MAX_REAL;

	mJointProjectionMode = NX_JPM_NONE;
	mJointProjectionAngle = 0.0872f;	//about 5 degrees in radians.
	mJointProjectionDistance = 1.0f;


	mSwingAxis.set(0,0,1);


	mHasSwingLimit = false;
	mSwingLimit_Restitution = 0;
	mSwingLimit_Value = 0;

#if (NX_SDK_VERSION_NUMBER >= 272)
	mSwingLimit_Hardness = 1;
#endif

	mHasSwingSpring = false;
	mSwingSpring_Damper = 0;
	mSwingSpring_Spring = 0;
	mSwingSpring_Target = 0;

 	mHasTwistLimit = false;
 	mTwistLimit_High_Restitution = 0;
 	mTwistLimit_High_Value = 0;
#if (NX_SDK_VERSION_NUMBER >= 272)
	mTwistLimit_High_Hardness = 1;
#endif
	mTwistLimit_Low_Restitution = 0;
	mTwistLimit_Low_Value = 0;
#if (NX_SDK_VERSION_NUMBER >= 272)
	mTwistLimit_Low_Hardness = 1;
#endif

	
	mHasTwistSpring = false;
	mTwistSpring_Damper = 0;
	mTwistSpring_Spring = 0;
	mTwistSpring_Target = 0;

}

/////////////////////////////////////////////////////////////////////

void JointParams::parse(Parameters) {

}

/////////////////////////////////////////////////////////////////////

void JointParams::fromNxJointDesc(NxJointDesc& jd) {
	
	if (jd.jointFlags && NX_JF_COLLISION_ENABLED)
			mActorsCollidable = true;

	if (jd.jointFlags && NX_JF_VISUALIZATION)
		mVisualiseJoint = true;

	mBreakableMaxForce = jd.maxForce;
	mBreakableMaxTorque = jd.maxTorque;

}

/////////////////////////////////////////////////////////////////////

Scene* Joint::getScene() {
	return mActorA->getScene();
}

/////////////////////////////////////////////////////////////////////

void Joint::setGlobalAnchor(const Ogre::Vector3& a) {
	mJoint->setGlobalAnchor(NxConvert<NxVec3, Ogre::Vector3>(a));
}

/////////////////////////////////////////////////////////////////////

void Joint::setGlobalAnchor(const NxVec3 & a) {
	mJoint->setGlobalAnchor(a);
}

/////////////////////////////////////////////////////////////////////

void Joint::setGlobalAxis(const Ogre::Vector3& a) {
	mJoint->setGlobalAxis(NxConvert<NxVec3, Ogre::Vector3>(a));
}

/////////////////////////////////////////////////////////////////////

void Joint::setGlobalAxis(const NxVec3 &a) {
	mJoint->setGlobalAxis(a);
}

/////////////////////////////////////////////////////////////////////

Ogre::Vector3 Joint::getGlobalAnchor() const {
	return NxConvert<Ogre::Vector3, NxVec3>(mJoint->getGlobalAnchor());
}

/////////////////////////////////////////////////////////////////////

NxVec3 Joint::getGlobalAnchorAsNxVec3()	const {
	return mJoint->getGlobalAnchor();
}

/////////////////////////////////////////////////////////////////////

Ogre::Vector3 Joint::getGlobalAxis() const {
	return NxConvert<Ogre::Vector3, NxVec3>(mJoint->getGlobalAxis());
}

/////////////////////////////////////////////////////////////////////

NxVec3 Joint::getGlobalAxisAsNxVec3()	const {
	return mJoint->getGlobalAxis();
}

/////////////////////////////////////////////////////////////////////

NxJointState Joint::getState() {
	return mJoint->getState();
}

/////////////////////////////////////////////////////////////////////

void Joint::setBreakable(NxReal maxForce, NxReal maxTorque) {
	mJoint->setBreakable(maxForce, maxTorque);
}

/////////////////////////////////////////////////////////////////////

NxReal Joint::getBreakableMaxForce() {
	NxReal mF, mT;
	mJoint->getBreakable(mF,mT);
	return mF;
}

/////////////////////////////////////////////////////////////////////

NxReal Joint::getBreakableMaxTorque() {
	NxReal mF, mT;
	mJoint->getBreakable(mF,mT);
	return mT;
}

/////////////////////////////////////////////////////////////////////

void Joint::setLimitPoint(const Ogre::Vector3& point, bool onActorB) {
	mJoint->setLimitPoint(NxConvert<NxVec3, Ogre::Vector3>(point), onActorB);
}

/////////////////////////////////////////////////////////////////////

void Joint::setLimitPoint(const NxVec3 &point, bool onActorB) {
	mJoint->setLimitPoint(point, onActorB);
}

////////////////////////////////////////////////////////////////////////////////////

Ogre::Vector3 Joint::getLimitPoint() const {
	NxVec3 point;
	mJoint->getLimitPoint(point);
	return NxConvert<Ogre::Vector3, NxVec3>(point);
}

/////////////////////////////////////////////////////////////////////

NxVec3 Joint::getLimitPointAsNxVec3() const {
	NxVec3 point;
	mJoint->getLimitPoint(point);
	return point;
}

/////////////////////////////////////////////////////////////////////

void Joint::addLimitPlane(const NxVec3 &normal, const NxVec3 & pointInPlane, NxReal restitution) {
	mJoint->addLimitPlane(normal, pointInPlane, restitution);
}

/////////////////////////////////////////////////////////////////////

void Joint::clearLimitPlanes() {
	mJoint->purgeLimitPlanes();
}

/////////////////////////////////////////////////////////////////////

std::vector<Joint::LimitPlane> Joint::getLimitPlanes() {

	mJoint->resetLimitPlaneIterator();
	std::vector<Joint::LimitPlane> planes;

	while(mJoint->hasMoreLimitPlanes()) {
		NxVec3 normal;
		NxReal pd, res = 0;
		mJoint->getNextLimitPlane(normal, pd);
		planes.push_back(LimitPlane(normal, pd, res));
	}

	return planes;
}

}; //End of NxOgre namespace.
