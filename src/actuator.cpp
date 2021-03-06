// =============================================================================
//  Actuator.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "actuator.h"
#include "config.h"
#include "Controller.h"
#include "sensor.h"
#include "joint.h"


/**-------------------------------------------------------------------------------
	Constructor
	Creates Actuator and sets its name
--------------------------------------------------------------------------------*/
Actuator::Actuator( Joint* joint, Controller<double>* controller, Sensor<double, Joint>* sensor ) : mController(controller), mJoint(joint), mSensor(sensor)
{
	mName = "logs\\" + mJoint->getName() + ".log";
}

/**-------------------------------------------------------------------------------
	Prepare inputs for update, set outputs afterwards
	Should be done each time sampling interval.

	\param      sample_time
	\return depends on implementation
--------------------------------------------------------------------------------*/
void Actuator::doOneStep(float currentTime, float sampleTime)
{
	mJoint->updateJoint(sampleTime);

	mSensor->update();
	double Pv;
	mSensor->getValue(Pv);
	mController->setInput(Pv);

	update(currentTime, sampleTime);

	// update log files
	if (Config::Instance().getLoggingControllers())
	{
		NxJointDesc* desc = NULL;
		mJoint->getDesc(&desc);
		writeToLog(desc, currentTime);
		delete desc;
		desc = NULL;
	}
}

/**-------------------------------------------------------------------------------
	writeToLog

	@brief
	@param desc
	@return void
---------------------------------------------------------------------------------*/
void Actuator::writeToLog(NxJointDesc* desc, float currentTime)
{
	mLogBuffer.setf(std::ios::fixed);
	mLogBuffer.setf(std::ios::showpoint);
	mLogBuffer.width(6);
	mLogBuffer << currentTime << "\t";
	double val;
	mController->getSetpoint(val);
	mLogBuffer << val<<"\t";
	mController->getInput(val);
	mLogBuffer << val<<"\t";
	mController->getOutput(val);
	mLogBuffer << val<<"\t";

	for (int i = 0; i < 2; i++)
	{
		NxVec3 angM = desc->actor[i]->getAngularMomentum();
		NxVec3 angV = desc->actor[i]->getAngularVelocity();
		NxVec3 linM = desc->actor[i]->getLinearMomentum();
		NxVec3 linV = desc->actor[i]->getLinearVelocity();
		mLogBuffer << "\t" << angM.x << "\t" << angM.y << "\t" << angM.z
				   << "\t" << angV.x << "\t" << angV.y << "\t" << angV.z
				   << "\t" << linM.x << "\t" << linM.y << "\t" << linM.z
				   << "\t" << linV.x << "\t" << linV.y << "\t" << linV.z;
	}

	mLogBuffer << "\n";
}