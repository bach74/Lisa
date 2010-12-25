// =============================================================================
//  TrajectoryQueue.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "trajectoryQueue.h"
#include "config.h"


/**-------------------------------------------------------------------------------
    go

    @brief
    @return
---------------------------------------------------------------------------------*/
void QueueElementType::go()
{

	NxD6JointDesc* desc;
	mActuator.getJoint()->getDesc((NxJointDesc**)&desc);
	desc->twistDrive.driveType = (mValue == "NX_D6JOINT_DRIVE_POSITION") ? NX_D6JOINT_DRIVE_POSITION : NX_D6JOINT_DRIVE_VELOCITY;
	mActuator.getJoint()->setDesc((NxJointDesc*)desc);

}

/**-------------------------------------------------------------------------------
    go

    @brief
    @return void
---------------------------------------------------------------------------------*/
void QueueElementForce::go()
{
	// test apply force - this force will stabilize the joint
	NxD6JointDesc* desc;
	mActuator.getJoint()->getDesc((NxJointDesc**)&desc);
	NxActor* a1 = desc->actor[mActor];
	float td = Config::Instance().getActuatorSteppingTime();
	NxForceMode type=(mForceType=="NX_IMPULSE")?NX_IMPULSE:NX_FORCE;
	a1->addForce(NxVec3(0, 0, 400)*td, type);
}