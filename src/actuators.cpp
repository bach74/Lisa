// =============================================================================
//  Actuators.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "actuators.h"
#include "config.h"
#include "actuatorPID.h"
#include "jointFactory.h"
#include "controllerPID.h"
#include "sensorVelocity.h"
#include "sensorPosition.h"
#include "sensorTorque.h"
#include "sensors.h"


/**-------------------------------------------------------------------------------
	Actuators

	@brief
	@param phyScene
	@return
---------------------------------------------------------------------------------*/
Actuators::Actuators(NxOgre::Scene* phyScene, Sensors* sensors)
{
	phyScene->getNxScene()->resetJointIterator();
	NxJoint* nxJoint = NULL;

	while ((nxJoint = phyScene->getNxScene()->getNextJoint()) != NULL)
	{
		Joint* joint = JointFactory::createJoint(nxJoint);

		if (joint != NULL)
		{
			addActuator(joint);
		}
	}
}

/**-------------------------------------------------------------------------------
	~Actuators

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
Actuators::~Actuators(void)
{
	mActuators.clear();
}

/**-------------------------------------------------------------------------------
	update

	@brief
	@return
---------------------------------------------------------------------------------*/
void Actuators::update(float frameTime)
{
	float td = Config::Instance().getActuatorSteppingTime();
	// set actuator inputs and calculate the output
	// afterwards set it to the PhysX nxJoint
	std::vector<boost::shared_ptr<Actuator > >::iterator it;

	for (it = mActuators.begin(); it != mActuators.end(); ++it)
	{
		(*it)->doOneStep(frameTime, td);
	}
}


/**----------------------------------------------------------------------------
	Add nxJoint actuator to the scene

	\param nxJoint (NxRevoluteJoint *)
	\return (void)
-----------------------------------------------------------------------------*/
void Actuators::addActuator(Joint* joint)
{
	double Kp = 0, Ti = 0, Td = 0;
	int type = 0;

	// get controller data from userData
	NxJointDesc* desc = NULL;
	joint->getDesc(&desc);

	//if (joint->getFlags()&NX_RJF_MOTOR_ENABLED)
	if (desc->userData != NULL)
	{
		Ogre::StringVector s = Ogre::StringConverter::parseStringVector(Ogre::String((char*)desc->userData));
		s.size() > 0 ? Kp = Ogre::StringConverter::parseReal(s[0]) : Kp = 0.1;
		s.size() > 1 ? Ti = Ogre::StringConverter::parseReal(s[1]) : Ti = 0;
		s.size() > 2 ? Td = Ogre::StringConverter::parseReal(s[2]) : Td = 0.1;
		s.size() > 3 ? type = Ogre::StringConverter::parseInt(s[3]) : type = 0;
	}
	else
	{
		if (joint->getType() == NX_JOINT_D6)
		{
			NxD6JointDesc* descD6 = dynamic_cast<NxD6JointDesc*>(desc);

			if (descD6->twistDrive.driveType == NX_D6JOINT_DRIVE_POSITION)
			{
				type = 1;
			}
		}

	}

	Sensor<double, Joint>* sensor;

	switch (type)
	{
		case 0:
			sensor = new SensorVelocity(joint);
			break;
		case 1:
			sensor = new SensorPosition(joint);
			break;
		case 2:
			sensor = new SensorTorque(joint);
			break;
		default:
			throw Exception("Unknown sensor for controller", "actuators");
	}


	Controller<double>* controllerPID = new ControllerPID(Kp, Ti, Td, 0);
	boost::shared_ptr<Actuator > actuator(new ActuatorPID(joint, controllerPID, sensor));
	mActuators.push_back(actuator);

}

/**-------------------------------------------------------------------------------
	begin

	@brief
	@return ActuatorIterator&
---------------------------------------------------------------------------------*/
ActuatorIterator& ActuatorIterator::begin()
{
	if (mActuators != NULL)
	{
		mNode = mActuators->begin();
	}

	return *this;
}

/**-------------------------------------------------------------------------------
	end

	@brief
	@return bool
---------------------------------------------------------------------------------*/
bool ActuatorIterator::end()
{
	if (mActuators)
	{
		return mNode == mActuators->end();
	}
	else
	{
		return true;
	}
}

/**-------------------------------------------------------------------------------
	equal

	@brief
	@param other
	@return bool
---------------------------------------------------------------------------------*/
bool ActuatorIterator::equal(ActuatorIterator const& other) const
{
	return mNode == other.mNode && mActuators == other.mActuators;
}
