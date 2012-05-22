// =============================================================================
//  JointD6.cpp
//
//  Copyright (C) 2007-2012 by Bach
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================

#include "stdafx.h"
#include "jointD6.h"


JointD6::JointD6(NxJoint* joint): Joint(joint)
{
	NxD6JointDesc desc;
	dynamic_cast<NxD6Joint*>(mJoint)->saveToDesc(desc);

	mStartAngle=getAngleD6(desc);
}

/**-------------------------------------------------------------------------------
	getDesc

	@brief
	@param desc
	@return void
---------------------------------------------------------------------------------*/
void JointD6::getDesc(NxJointDesc** desc)
{
	NxD6JointDesc* desc2 = new NxD6JointDesc();
	dynamic_cast<NxD6Joint*>(mJoint)->saveToDesc(*desc2);
	*desc = desc2;
}


/**-------------------------------------------------------------------------------
	setDesc

	@brief
	@param desc
	@return void
---------------------------------------------------------------------------------*/
void JointD6::setDesc(NxJointDesc* desc)
{
	NxD6JointDesc* desc2 = dynamic_cast<NxD6JointDesc*>(desc);
	dynamic_cast<NxD6Joint*>(mJoint)->loadFromDesc(*desc2);
}

/**-------------------------------------------------------------------------------
	getInternalMotorSetpoint

	get currently set set-point for the velocity or position of PhysX internal motor.
	This is not the controller set-point.

	@brief
	@return NxReal
---------------------------------------------------------------------------------*/
NxReal JointD6::getInternalMotorSetpoint()
{
	float res = 0;

	NxD6JointDesc desc;
	NxD6Joint* joint = (NxD6Joint*)mJoint;
	joint->saveToDesc(desc);

	if (desc.twistDrive.driveType == NX_D6JOINT_DRIVE_POSITION) {
		NxQuat orientation = desc.driveOrientation;
		res=orientation.getAngle();
	} else {
		res = desc.driveAngularVelocity.x;
	}

	return res;
}

/**-------------------------------------------------------------------------------
	updateJoint

	@brief
	@param sampleTime
	@return void
---------------------------------------------------------------------------------*/
void JointD6::updateJoint(float sampleTime)
{
	NxD6JointDesc desc;
	dynamic_cast<NxD6Joint*>(mJoint)->saveToDesc(desc);

	// getAngle
	mAngle=getAngleD6(desc)-mStartAngle;

	NxActor* actor1=desc.actor[0];
	NxActor* actor2=desc.actor[1];

	// primary joint axis
	NxVec3 axis = desc.localAxis[1];

	// getVelocity
	// Retrieves the revolute joint angle's rate of change (angular velocity).
	// It is the angular velocity of body1 minus body2 projected along the axis.
	NxVec3 vel1_global = actor1->getAngularVelocity();
	NxVec3 vel2_global = actor2->getAngularVelocity();
	NxMat33 o1_global = actor1->getGlobalOrientation();
	NxMat33 o2_global = actor2->getGlobalOrientation();

	// Should be o1*trans(vel1), but there is no such function
	// instead we use
	NxVec3 vel1_local, vel2_local;
	o1_global.multiplyByTranspose(vel1_global, vel1_local);
	o2_global.multiplyByTranspose(vel2_global, vel2_local);
	NxVec3 vel = vel1_local - vel2_local;
	mVelocity = vel.dot(axis);

	mAcceleration = (sampleTime != 0) ? (mVelocityPrev - mVelocity) / sampleTime : 0;

	NxMat33 rot = actor2->getGlobalOrientation();
	// transform global frame moment to local frame moment so that we get
	// constant moments around the axes
	mAngularMomentum = actor2->getAngularMomentum().dot(rot * axis);

	//Torque
	//tau=dL/dt or I*d(omega)/dt=I*alpha
	//mTorque = desc.actor[1]->getMassSpaceInertiaTensor().dot(rot * axis) * mAcceleration; --> mAcceleration_body[1]
	mTorque=(sampleTime!=0)?(mAngularMomentum-mAngularMomentumPrev)/sampleTime:0;

	mVelocityPrev = mVelocity;
	mAngularMomentumPrev=mAngularMomentum;
}

/**-------------------------------------------------------------------------------
	getAngleD6

	@brief
	@return float
---------------------------------------------------------------------------------*/
float JointD6::getAngleD6(const NxD6JointDesc& desc) const
{
	NxActor* actor1=desc.actor[0];
	NxActor* actor2=desc.actor[1];
	NxQuat qaxis(desc.localAxis[0],0);

	// get angle difference between the objects adjusted
	// to the primary joint axis
	NxQuat q1 = actor1->getGlobalOrientationQuat();
	NxQuat q2i = actor2->getGlobalOrientationQuat();
	q2i.invert();
	qaxis.invert();
	NxQuat q = qaxis*q2i*q1;
	
	return q.getAngle();
}