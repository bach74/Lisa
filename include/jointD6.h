// =============================================================================
//  JointD6.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __JOINTD6_H__
#define __JOINTD6_H__

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

 #endif