#pragma once

#include "joint.h"

class JointD6 : public Joint
{
	public:
		JointD6(NxJoint* joint);
		~JointD6(void) {};

		virtual NxReal getInternalMotorSetpoint();
		virtual void getDesc(NxJointDesc** desc);
		virtual void setDesc(NxJointDesc* desc);

		virtual void updateJoint(float sampleTime);
		
	private:

		float getAngleD6(const NxD6JointDesc& desc) const;

		float	mStartAngle;
};
