// =============================================================================
//  JointFactory.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "jointFactory.h"
#include "jointRevolute.h"
#include "jointD6.h"

Joint* JointFactory::createJoint(NxJoint* joint)
{
	NxJointType jointType = joint->getType();

	if (jointType == NX_JOINT_REVOLUTE)
	{
		NxRevoluteJoint* revJoint = (NxRevoluteJoint*)joint;
		// if motor is not enabled, don't add a controller
		NxMotorDesc mot;

		if (revJoint->getMotor(mot))
		{
			// enable joint TODO
		}

		return new JointRevolute(joint);
	}
	else if (jointType == NX_JOINT_D6)
	{
		return new JointD6(joint);

		/* The joint springs themselves act as PD controllers in PhysX
		(the targetValue in the spring descriptor). It is a very useful feature for motion control.
		It seems to be pretty accurate than normal PD.
		I guess its using some acceleration constraints than torques like in traditional PD? */

	}
	else if (jointType != NX_JOINT_FIXED)
	{
		throw Exception("Joint type not supported", "joint.cpp");
	}

	return NULL;
}

JointFactory::~JointFactory(void)
{
}
