#pragma once

#include "joint.h"

class JointRevolute : public Joint
{
	public:
		JointRevolute(NxJoint* joint);
		~JointRevolute(void);

		virtual NxReal	getActorAngle(int i);
		virtual NxReal	getActorVelocity(int i);
		virtual void	getDesc(NxJointDesc** desc);
		virtual void	setDesc(NxJointDesc* desc);

		virtual void	updateJoint(float sampleTime);

		void getMotor(NxMotorDesc& desc) {((NxRevoluteJoint*)mJoint)->getMotor(desc); }
		void setMotor(NxMotorDesc desc) { ((NxRevoluteJoint*)mJoint)->setMotor(desc); }
};
