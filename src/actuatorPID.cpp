// =============================================================================
//  ActuatorPID.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "actuatorPID.h"
#include "JointRevolute.h"
#include "jointD6.h"
#include "Controller.h"

/**-------------------------------------------------------------------------------
	ActuatorPID

	@brief
	@param node
	@param controller
	@return
---------------------------------------------------------------------------------*/
ActuatorPID::ActuatorPID(Joint* node, Controller<double>* controller, Sensor<double, Joint>* sensor) : Actuator(node, controller, sensor)
{
	// copy set-point from collada file set as angular velocity set-point
	// to the controller set-point
	// in case of revolute joints set point is ALWAYS set as VelocityTarget
	// regardless of position. velocity or torque joint type
	if (mJoint->getType() == NX_JOINT_REVOLUTE)
	{
		JointRevolute* revJoint = ((JointRevolute*)mJoint);
		NxMotorDesc motorDesc;
		revJoint->getMotor(motorDesc);
		controller->setSetpoint(motorDesc.velTarget);
	}
	else if (mJoint->getType() == NX_JOINT_D6)
	{
		// In case of D6 joint the set-point can be either as VelocityTarget
		// or as positionTarget -- depending on the joint type
		NxReal Sp = dynamic_cast<JointD6*>(mJoint)->getInternalMotorSetpoint();
		controller->setSetpoint(Sp);
	}
}


/**-------------------------------------------------------------------------------
		dtor
		clear all structures and release the memory
--------------------------------------------------------------------------------*/
ActuatorPID::~ActuatorPID()
{

}


/**-------------------------------------------------------------------------------
	Update controller internal values and states.
	Should be done each time sampling interval.

	\param      sample_time
	\return controller output
--------------------------------------------------------------------------------*/
void ActuatorPID::update(float currentTime, float sampleTime)
{
	if (mJoint->getType() == NX_JOINT_REVOLUTE)
	{
		double out = mController->calculate(sampleTime);
		// PhysX motor
		NxMotorDesc motorDesc;
		JointRevolute* revJoint = dynamic_cast<JointRevolute*>(mJoint);
		revJoint->getMotor(motorDesc);
		motorDesc.velTarget = (NxReal)out; // [rad/s]
		revJoint->setMotor(motorDesc);
	}
	else if (mJoint->getType() == NX_JOINT_D6)
	{
		// Use internal constraint solver for the controller
		// internal constraint solver can be compared to PD controller
		// double out = mController->calculate(sampleTime);

		// if reference is changed transfer it to the internal motor ref
		double sp;
		mController->getSetpoint(sp);
		NxJointDesc* desc = NULL;
		mJoint->getDesc(&desc);
		NxD6JointDesc* descD6 = dynamic_cast<NxD6JointDesc*>(desc);

		if (descD6->twistDrive.driveType == NX_D6JOINT_DRIVE_POSITION)
		{
			descD6->driveOrientation.fromAngleAxisFast((NxReal)sp,NxVec3(1,0,0));			
		}
		else
		{
			descD6->driveAngularVelocity.x=(NxReal)sp;
		}
		mJoint->setDesc(descD6);
	}
	else
	{
		throw Exception("Joint type unsupported", "ActuatorPID.cpp");
	}

}
