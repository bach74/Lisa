#include "stdafx.h"
#include "jointRevolute.h"

/**-------------------------------------------------------------------------------
	JointRevolute

	@brief
	@param joint
	@return
---------------------------------------------------------------------------------*/
JointRevolute::JointRevolute(NxJoint* joint): Joint(joint)
{
}

/**-------------------------------------------------------------------------------
	~JointRevolute

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
JointRevolute::~JointRevolute(void)
{
}


/**-------------------------------------------------------------------------------
	getActorAngle

	@brief
	@param i
	@return NxReal
---------------------------------------------------------------------------------*/
NxReal JointRevolute::getActorAngle(int i)
{
	NxReal res;
	// TODO ovo nije dobro !!
	NxRevoluteJointDesc desc;
	((NxRevoluteJoint*)mJoint)->saveToDesc(desc);
	res = desc.actor[i]->getGlobalPosition().x;

	return res;
}

/**-------------------------------------------------------------------------------
	getActorVelocity

	@brief
	@param i
	@return NxReal
---------------------------------------------------------------------------------*/
NxReal JointRevolute::getActorVelocity(int i)
{
	NxReal res;

	NxRevoluteJointDesc desc;
	((NxRevoluteJoint*)mJoint)->saveToDesc(desc);
	res = desc.actor[i]->getAngularVelocity().z;


	return res;
}

/**-------------------------------------------------------------------------------
	getDesc

	@brief
	@param desc
	@return void
---------------------------------------------------------------------------------*/
void JointRevolute::getDesc(NxJointDesc** desc)
{
	NxRevoluteJointDesc* desc2 = new NxRevoluteJointDesc();
	dynamic_cast<NxRevoluteJoint*>(mJoint)->saveToDesc(*desc2);
	*desc = desc2;
}

/**-------------------------------------------------------------------------------
	setDesc
	
	@brief
	@param desc
	@return void
---------------------------------------------------------------------------------*/
void JointRevolute::setDesc( NxJointDesc* desc )
{
	NxRevoluteJointDesc* desc2 = dynamic_cast<NxRevoluteJointDesc*>(desc);
	dynamic_cast<NxRevoluteJoint*>(mJoint)->loadFromDesc(*desc2);
}

/**-------------------------------------------------------------------------------
	updateJoint

	@brief
	@param sampleTime
	@return void
---------------------------------------------------------------------------------*/
void JointRevolute::updateJoint(float sampleTime)
{

	mAngle = ((NxRevoluteJoint*)mJoint)->getAngle();
	mVelocity = ((NxRevoluteJoint*)mJoint)->getVelocity();
	mAcceleration = (sampleTime != 0) ? (mVelocityPrev - mVelocity) / sampleTime : 0;

	// Since we cannot get torque from the joint, the only way is to get the torque
	// applied to the body connected to the joint (actor[1])
	NxRevoluteJointDesc desc;
	((NxRevoluteJoint*)mJoint)->saveToDesc(desc);
	NxVec3 axis = desc.localAxis[1];
	NxMat33 rot = desc.actor[1]->getGlobalOrientation();
	// transform global frame moment to local frame moment so that we get
	// constant moments around the axes
	mAngularMomentum = desc.actor[1]->getAngularMomentum().dot(rot * axis);
	//Torque
	//tau=dL/dt or I*d(omega)/dt=I*alpha
	//mTorque = desc.actor[1]->getMassSpaceInertiaTensor().dot(rot * axis) * mAcceleration; --> mAcceleration_body[1]
	mTorque=(sampleTime!=0)?(mAngularMomentum-mAngularMomentumPrev)/sampleTime:0;

	mVelocity=(fabs(mVelocity)<1e-6)?0:mVelocity;
	mAcceleration=(fabs(mAcceleration)<1e-6)?0:mAcceleration;
	mTorque=(fabs(mTorque)<1e-5)?0:mTorque;		

	mVelocityPrev = mVelocity;
	mAngularMomentumPrev=mAngularMomentum;


	// test new angular momentum calculations
	// NxActor::getAngularMomentum() gets the angular momentum relative to world frame but with 
	// components resolved in instantaneous body frame. So these components naturally change all the time,
	// while the vector is still constant. The components in world frame, given by 
	// NxActor::getGlobalOrientation().multiplyByTranspose(L,L), are constant to within roundoff error.

	NxVec3 L = desc.actor[1]->getAngularMomentum();
	desc.actor[1]->getGlobalOrientation().multiplyByTranspose(L,L);
	//mAngularMomentum = L.dot(rot * axis_pocetni);
	mAngularMomentum = L.z;


	// difference between angular moments
	// TODO to bi trebalo biti na istoj osi ...!!!!
	// ne mozes samo tako oduzeti...
	NxVec3 axis0 = desc.localAxis[0];
	NxMat33 rot0 = desc.actor[0]->getGlobalOrientation();
	NxReal mAngularMomentum0 = desc.actor[0]->getAngularMomentum().dot(rot0 * axis0);
	
	mAngularMomentum=mAngularMomentum-mAngularMomentum0;
}