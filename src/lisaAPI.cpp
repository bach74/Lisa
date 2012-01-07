// =============================================================================
//  SimFacade.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================

#include "stdafx.h"
#include "lisaAPI.h"
#include "simulationImpl.h"
#include "exception.h"
#include "lisaCore.h"
#include "link.h"
#include "linkIterator.h"
#include "actuators.h"
#include "Controller.h"
#include "config.h"
#include "sensors.h"
#include "joint.h"

/**----------------------------------------------------------------------------
	LisaAPI constructor
 -----------------------------------------------------------------------------*/
LisaAPI::LisaAPI() : mFrameTime(0)
{
	const Simulation* sim = LisaCore::Instance().getSimulation();

	LinkIterator itLink = LinkIterator(sim->getLinks());

	for (; !itLink.end(); ++itLink)
	{
		if (itLink->isDynamic())
		{
			mLinkNames.push_back(itLink->getName());
			mLinkMass.push_back(itLink->getMass());
		}
	}
}

/**----------------------------------------------------------------------------
	pause or resume the simulation.

	\param pause (bool)
	\return (void)
 -----------------------------------------------------------------------------*/
void LisaAPI::pauseSimulation(bool pause) const
{
	Simulation* sim = const_cast<Simulation*>(LisaCore::Instance().getSimulation());

	sim->getLinks();

	if (pause)
	{
		sim->requestStateChange(Simulation::SIMULATING);
	}
	else
	{
		sim->requestStateChange(Simulation::PAUSED);
	}
}

/**----------------------------------------------------------------------------
	check if simulation is paused

	\return false is simulation is in the "simulating" state
 -----------------------------------------------------------------------------*/
short LisaAPI::isSimulationPaused() const
{
	const Simulation* sim = LisaCore::Instance().getSimulation();
	return !(sim->getCurrentState() == Simulation::SIMULATING);
}

/**----------------------------------------------------------------------------
	get number of links.

	\return (int)
 -----------------------------------------------------------------------------*/
int LisaAPI::getNumLinks() const
{
	return mLinkNames.size();
}

/**----------------------------------------------------------------------------
	get i-th link name.

	\param i (int)
	\return (std::string)
 -----------------------------------------------------------------------------*/
std::string LisaAPI::getLinkName(size_t i) const
{
	return mLinkNames.at(i);
}

/**----------------------------------------------------------------------------
	get current simulation time.

	\return (double)
 -----------------------------------------------------------------------------*/
double LisaAPI::getCurrentTime() const
{
	return mFrameTime;
}


/**----------------------------------------------------------------------------
	get mass of the i-th link.

	\param i (size_t)             link number
	\return (double)
 -----------------------------------------------------------------------------*/
double LisaAPI::getLinkMass(size_t i) const
{
	return mLinkMass.at(i);
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th link.

	\param i (size_t)             link number
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getLinkPosition(size_t i) const
{
	return mLinkPositions.at(i);
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th link.

	\param linkName (std::string &) link name
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getLinkPosition(const std::string& linkName) const
{
	auto it = std::find(mLinkNames.begin(), mLinkNames.end(), linkName);
	return (it != mLinkNames.end()) ? mLinkPositions[it-mLinkNames.begin()] : Ogre::Vector3(0, 0, 0);
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th joint.

	\param i (size_t)             joint number
	\return (Ogre::Vector3)         joint position
 -----------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getJointCoordinates(size_t i) const
{
	return mJointCoordinates.at(i);
}

/**----------------------------------------------------------------------------
	Get center of pressure (COP) position.

	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getCOPPosition() const
{
	Ogre::Vector3 ret(0, 0, 0);

	// see if there is a contact sensor
	if (Config::Instance().getControllerZMP())
	{
		// find contact sensor and report COP
		SensorVectors* sensorCOP = dynamic_cast<const SimulationImpl*>(getSimulation())->getSensors()->getSensor("COP");

		if (sensorCOP->getDataValid())
		{
			std::vector<Ogre::Vector3> val;
			sensorCOP->getValue(val);
			ret = val.front();
		}
	}

	return ret;
}

/**----------------------------------------------------------------------------
	Get center of pressure (COP) force.

	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getCOPForce() const
{
	Ogre::Vector3 ret(0, 0, 0);

	// see if there is contact sensor
	if (Config::Instance().getControllerZMP())
	{
		// find contact sensor and report COP
		SensorVectors* sensorCOP = dynamic_cast<const SimulationImpl*>(getSimulation())->getSensors()->getSensor("COP");

		if (sensorCOP->getDataValid())
		{
			std::vector<Ogre::Vector3> val;
			sensorCOP->getValue(val);
			ret = val.at(1);
		}
	}

	return ret;
}

/**----------------------------------------------------------------------------
	Send message to exit.

	\return (void)
 -----------------------------------------------------------------------------*/
void LisaAPI::closeApplication() const
{
	LisaCore::Instance().stop();
}


/**----------------------------------------------------------------------------
	Loads a trajectory from a file.

	\param filename (std::string)
	\return (void)
 -----------------------------------------------------------------------------*/
void LisaAPI::loadTrajectory(const TCHAR* filename) const
{
//	SimulationImpl* sim=(SimulationImpl*)getSimulation();

	//if (sim->getCurrentState()>=Simulation::PREPARE)
	//  sim->loadTrajectory(filename);

}

/**-------------------------------------------------------------------------------
	getGravity

	@brief
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
Ogre::Vector3 LisaAPI::getGravity()
{
	NxOgre::Scene* scene = getSimulation()->getPhyScene();

	if (scene)
	{
		NxVec3 gVec3;
		scene->getNxScene()->getGravity(gVec3);
		return NxOgre::NxConvert<Ogre::Vector3, NxVec3>(gVec3);
	}
	else
	{
		throw Exception("Must initialize scene member first", "SimFacade.cpp");
	}
}

/**-------------------------------------------------------------------------------
	get number of controllers

	@brief
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
UINT LisaAPI::getControllerNum(void)
{
	return getSimulation()->getActuators()->size();
}

/**-------------------------------------------------------------------------------
	get parameters of the i-th actuator. The order of parameters is dependent on the
	actuator type

	@brief get parameters
	@return std::vector<double>
---------------------------------------------------------------------------------*/
std::vector<double> LisaAPI::getActuatorParams(size_t i)
{
	return mActuatorParams.at(i);
}

/**-------------------------------------------------------------------------------
	set parameters of the i-th actuator. The order of parameters is dependent on the
	actuator type

	@brief set parameters
	@return none
---------------------------------------------------------------------------------*/
void LisaAPI::setActuatorParams(size_t i, std::vector<double>& params)
{
	const Simulation* sim = LisaCore::Instance().getSimulation();

	// iterate through the actuators and add the states to member variables
	ActuatorIterator itAct(sim->getActuators());

	for (size_t j=0; (!itAct.end()&&(j<i)); ++itAct, ++j) {};
	if (!itAct.end()) {
		Actuator& a = *itAct;
		a.getController()->setParameters(params);
	}
}

/**-------------------------------------------------------------------------------
	set parameter of the i-th actuator. The order of parameters is dependent on the
	actuator type

	@brief set parameters
	@return none
---------------------------------------------------------------------------------*/
void LisaAPI::setActuatorParam(size_t i, size_t nParam, double valParam)
{
	throw Exception("Not implemented!", "simfacade.cpp");
}


/**-------------------------------------------------------------------------------
	get i-th actuator position

	\param i    i-th actuator
	\return     position (angle)
--------------------------------------------------------------------------------*/
double LisaAPI::getJointAngle(size_t i)
{
	return mJointAngles.at(i);
}

/**-------------------------------------------------------------------------------
	set i-th actuator reference

	\param i        i-th actuator
	\param numRef   numRef-th actuator (IGNORED)
	\param Val      set-point
--------------------------------------------------------------------------------*/
void LisaAPI::setJointSetpoint(size_t i, size_t numRef, DOUBLE Val)
{
	const Simulation* sim = LisaCore::Instance().getSimulation();

	// iterate through the actuators and add the states to member variables
	ActuatorIterator itAct(sim->getActuators());

	// will protect the entire scope (until destroyed)
	CritSectEx::Scope scope(myCs);

	for (size_t j=0; (!itAct.end()&&(j<i)); ++itAct, ++j) {};
	if (!itAct.end()) {
		Actuator& a = *itAct;
		a.getController()->setSetpoint(Val);
	}
}

/**-------------------------------------------------------------------------------
	get i-th actuator reference

	\param i        i-th actuator
	\param numRef   i-th actuator
	\return         reference value
--------------------------------------------------------------------------------*/
double LisaAPI::getJointSetpoint(size_t i, size_t numRef)
{
	return mJointSetpoints.at(i);
}

/**-------------------------------------------------------------------------------
	get i-th actuator velocity

	\param i    i-th actuator
	\return     velocity
--------------------------------------------------------------------------------*/
double LisaAPI::getJointVelocity(size_t i)
{
	return mJointVelocities.at(i);
}

/**-------------------------------------------------------------------------------
	get i-th actuator torque

	\param i    i-th actuator
	\return     torque
--------------------------------------------------------------------------------*/
double LisaAPI::getJointTorque(size_t i)
{
	return mJointTorques.at(i);
}


/**-------------------------------------------------------------------------------
	setStates

	@brief

	Make a snapshot of simulation variables. This values will then be returned
	to the caller of getJointXXX() and getXxx() functions;
---------------------------------------------------------------------------------*/
void LisaAPI::setStates()
{
	const Simulation* sim = LisaCore::Instance().getSimulation();
	mFrameTime = sim->getFrameTime();

	// iterate through the actuators and add the states to member variables
	ActuatorIterator itAct(sim->getActuators()); 

	// will protect the entire scope (until destroyed)
	CritSectEx::Scope scope(myCs);

	// clear all old values
	mJointTorques.clear();
	mJointVelocities.clear();
	mJointAngles.clear();
	mJointSetpoints.clear();
	mJointCoordinates.clear();
	mActuatorParams.clear();

	for (; !itAct.end(); ++itAct)
	{
		Actuator& a = *itAct;
		Joint* j = a.getJoint();
		mJointAngles.push_back(j->getAngle());
		mJointTorques.push_back(j->getTorque());
		mJointVelocities.push_back(j->getVelocity());
		double val;
		a.getController()->getSetpoint(val);
		mJointSetpoints.push_back(val);
		mJointCoordinates.push_back(NxOgre::NxConvert<Ogre::Vector3, NxVec3>(j->getGlobalAnchor()));

		mActuatorParams.push_back(std::vector<double>());
		std::vector<double> cp;
		a.getController()->getParameters(cp);
		BOOST_FOREACH(double d, cp)
		{
			mActuatorParams.back().push_back(d);
		}
	}

	// clear link variables
	mLinkPositions.clear();

	// iterate through the actors and add the states to member variables
	LinkIterator itLink = LinkIterator(sim->getLinks());

	for (; !itLink.end(); ++itLink)
	{
		if (itLink->isDynamic())
		{
			mLinkPositions.push_back(itLink->getCMassGlobalPosition());
		}
	}
}

/**-------------------------------------------------------------------------------
	Get PhysX scene

	@brief
---------------------------------------------------------------------------------*/
NxOgre::Scene* LisaAPI::getPhyScene() const
{
	NxOgre::World* world = LisaCore::Instance().getSimulation()->getWorld();
	return (world) ? world->getScenes()->get(THE_WORLD) : NULL;
}

/**-------------------------------------------------------------------------------
	get simulation object

	@brief
---------------------------------------------------------------------------------*/
const Simulation* LisaAPI::getSimulation() const
{
	return LisaCore::Instance().getSimulation();
}
