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

	if (desc.twistDrive.driveType == NX_D6JOINT_DRIVE_POSITION)
	{
		NxQuat orientation = desc.driveOrientation;
		res=orientation.getAngle();
	}
	else
	{
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

	// getVelocity
	// Retrieves the revolute joint angle's rate of change (angular velocity).
	// It is the angular velocity of body1 minus body2 projected along the axis.
	NxVec3 vel1 = desc.actor[0]->getAngularVelocity();
	NxVec3 vel2 = desc.actor[1]->getAngularVelocity();
	NxMat33 o1 = desc.actor[0]->getGlobalOrientation();
	NxMat33 o2 = desc.actor[1]->getGlobalOrientation();

	// Should be o1*trans(vel1), but there is no such function
	// instead we use
	NxVec3 vel1_1, vel2_2;
	o1.multiplyByTranspose(vel1, vel1_1);
	o2.multiplyByTranspose(vel2, vel2_2);
	NxVec3 vel = vel1_1 - vel2_2;
	mVelocity = vel.z;

	mAcceleration = (sampleTime != 0) ? (mVelocityPrev - mVelocity) / sampleTime : 0;

	NxVec3 axis = desc.localAxis[1];
	NxMat33 rot = desc.actor[1]->getGlobalOrientation();
	// transform global frame moment to local frame moment so that we get
	// constant moments around the axes
	mAngularMomentum = desc.actor[1]->getAngularMomentum().dot(rot * axis);

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
	NxQuat q1 = desc.actor[0]->getGlobalOrientationQuat();
	NxQuat q2 = desc.actor[1]->getGlobalOrientationQuat();
	float angle1=q1.getAngle();
	float angle2=q2.getAngle();
	//q1.invert();
	//NxQuat q = q2 * q1;
	//return q.getAngle();
	return angle1-angle2;
}