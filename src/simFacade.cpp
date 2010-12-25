// =============================================================================
//  SimFacade.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "SimFacade.h"
#include "simulationImpl.h"
#include "exception.h"

/**----------------------------------------------------------------------------
	Get i-th body from the .
   
	\param i (USHORT)
	\return (NxOgre::Body&)
 -----------------------------------------------------------------------------*/
NxOgre::Actor* SimFacade::getLink(USHORT i) const
{
	NxOgre::Actor* ret=NULL;

	NxOgre::Scene* scene=getPhyScene();
	NxOgre::Actors::Iterator it=scene->getActors()->mItems.begin();
	// ignore floor
	++it;
	for (;it!=scene->getActors()->mItems.end();++it)
		++it;

	return ret;
}

/**----------------------------------------------------------------------------
	pause or unpause the simulation.
   
	\param pause (bool)
	\return (void)
 -----------------------------------------------------------------------------*/
void SimFacade::pauseSimulation(bool pause) const
{
	NxOgre::World * phyWorld=getPhyScene()->getWorld();
//TODO			(pause!=0)?phyWorld.pause():phyWorld.resume();
}

/**----------------------------------------------------------------------------
	get number of links.
   
	\return (int)
 -----------------------------------------------------------------------------*/
int SimFacade::getNumLinks() const
{
	return (getPhyScene()->getNbActors()-1);
}

/**----------------------------------------------------------------------------
	get i-th link name.
   
	\param i (int)
	\return (std::string)
 -----------------------------------------------------------------------------*/
std::string SimFacade::getLinkName(USHORT i) const
{
	NxOgre::Actor* link=getLink(i);
	return (link!=NULL)?link->getName():std::string();
}

/**----------------------------------------------------------------------------
	get current simulation time.
   
	\return (double)
 -----------------------------------------------------------------------------*/
double SimFacade::getCurrentTime() const
{
	return getSimulation()->getFrameTime();
}


/**----------------------------------------------------------------------------
	get mass of the i-th link.
   
	\param i (USHORT)				link number
	\return (double)
 -----------------------------------------------------------------------------*/
double SimFacade::getLinkMass(USHORT i) const
{
	return getLink(i)->getMass();
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th link.
   
	\param i (USHORT)				link number
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getLinkPosition(USHORT i) const
{
	return getLink(i)->getGlobalPositionAsOgreVector3();
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th link.
   
	\param linkName (std::string &)	link name
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getLinkPosition(const std::string& linkName) const
{
	NxOgre::Actor* body=getPhyScene()->getActor(linkName);
	return (body)?body->getGlobalPositionAsOgreVector3():Ogre::Vector3();
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th joint.
   
	\param i (USHORT)				joint number
	\return (Ogre::Vector3)			joint position
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getJointCoordinates(USHORT i) const
{			
	// Actuator* a=SimFacade::Instance().getActuator(i);
	// TODO return (a)?a->getJointCoordinates():Ogre::Vector3();
	//Ogre::Vector3 getJointCoordinates() { return NxOgre::NxConvert<Ogre::Vector3, NxVec3>(mJoint->getGlobalAnchor()); }
	return Ogre::Vector3();
}

/**----------------------------------------------------------------------------
	Get center of pressure (COP) position.
   
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getCOPPosition() const
{
	// see if there is contact reporter 
	// find first contact reporter and report COP
	//TODO			myContactReporter *mcp=(myContactReporter*)(*getPhyScene()->mContactReporter->mReporters.begin());
	//			return (mcp->hasContact())?Ogre::Vector3(mcp->mCOPpos.x,mcp->mCOPpos.y,mcp->mCOPpos.z):Ogre::Vector3();
	return Ogre::Vector3();
}

/**----------------------------------------------------------------------------
	Get center of pressure (COP) force.
   
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getCOPForce() const
{
	//TODO			myContactReporter *mcp=(myContactReporter*)(*getPhyScene()->mContactReporter->mReporters.begin());
	//			return (mcp->hasContact())?Ogre::Vector3(mcp->mCOPforce.x,mcp->mCOPforce.y,mcp->mCOPforce.z):Ogre::Vector3();
	return Ogre::Vector3();
}

/**----------------------------------------------------------------------------
	Send message to exit.
   
	\return (void)
 -----------------------------------------------------------------------------*/
void SimFacade::closeApplication() const
{
	LisaCore::Instance().stop();
}


/**----------------------------------------------------------------------------
	Loads a trajectory from a file.
   
	\param filename (std::string)
	\return (void)
 -----------------------------------------------------------------------------*/
void SimFacade::loadTrajectory(const TCHAR* filename) const
{
	//SimulationImpl* sim=(SimulationImpl*)getSimulation();

	//if (sim->getCurrentState()>=Simulation::PREPARE)
	//	sim->loadTrajectory(filename);

}

/**-------------------------------------------------------------------------------
	getActuator
	
	@brief
	@param n
	@return Actuator*
---------------------------------------------------------------------------------*/
/*Actuator* SimFacade::getActuator(UINT n) const
{
	ActuatorIterator it(LisaCore::Instance().getSimulation()->getActuators());

	for (UINT i = 0; i < n; ++i)
	{
		if (it.end()) { return NULL; }
	}
	return &(*it);
}*/

/**-------------------------------------------------------------------------------
	getGravity
	
	@brief
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getGravity()
{
	NxOgre::Scene *scene=getSimulation()->getPhyScene();
	if (scene) {
		NxVec3 gVec3;
		scene->getNxScene()->getGravity(gVec3);
		return NxOgre::NxConvert<Ogre::Vector3, NxVec3>(gVec3);
	} else {
		throw Exception("Must initialize scene member first","SimFacade.cpp");
	}
}

/**-------------------------------------------------------------------------------
	get number of controllers
	
	@brief
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
UINT SimFacade::getControllerNum(void)
{
	return getSimulation()->getActuators()->size();
}

/**-------------------------------------------------------------------------------
	get parameters of the i-th actuator. The order of parameters is dependent on the 
	actuator type
	
	@brief get parameters
	@return std::vector<double>
---------------------------------------------------------------------------------*/
std::vector<double> SimFacade::getActuatorParams(USHORT i)
{
	throw Exception("Not implemented!","simfacade.cpp");
}

/**-------------------------------------------------------------------------------
	set parameters of the i-th actuator. The order of parameters is dependent on the 
	actuator type
	
	@brief set parameters
	@return none
---------------------------------------------------------------------------------*/
void SimFacade::setActuatorParams(USHORT i, std::vector<double>& params)
{
	throw Exception("Not implemented!","simfacade.cpp");
}

/**-------------------------------------------------------------------------------
	set parameter of the i-th actuator. The order of parameters is dependent on the 
	actuator type
	
	@brief set parameters
	@return none
---------------------------------------------------------------------------------*/
void SimFacade::setActuatorParam(USHORT i, USHORT nParam, double valParam)
{
	throw Exception("Not implemented!","simfacade.cpp");
}


/**-------------------------------------------------------------------------------
	get i-th actuator position

	\param i	i-th actuator 
	\return		position (angle)
--------------------------------------------------------------------------------*/
double SimFacade::getJointAngle(USHORT i)
{
	//*pVal=SimFacade::Instance().getActuator(i);
	//jCtlr->getJoint()->getAngle();
	return 0;
}

/**-------------------------------------------------------------------------------
	set i-th actuator reference

	\param i		i-th actuator 
	\param numRef	numRef-th actuator 
	\param Val		set-point
--------------------------------------------------------------------------------*/
void SimFacade::setJointSetpoint(USHORT i, USHORT numRef, DOUBLE Val)
{
	//Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	//jCtlr->getController()->setSetpoint(Val);
}

/**-------------------------------------------------------------------------------
	get i-th actuator reference

	\param i		i-th actuator 
	\param numRef	i-th actuator 
	\return			reference value
--------------------------------------------------------------------------------*/
double SimFacade::getJointSetpoint(USHORT i, USHORT numRef)
{
	//Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	//jCtlr->getController()->getSetpoint(*retVal);
	return 0;
}

/**-------------------------------------------------------------------------------
	get i-th actuator velocity

	\param i	i-th actuator 
	\return		velocity 
--------------------------------------------------------------------------------*/
double SimFacade::getJointVelocity(USHORT i)
{ 
	//Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	//*pVal=jCtlr->getJoint()->getVelocity();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator torque

	\param i	i-th actuator 
	\return		torque
--------------------------------------------------------------------------------*/
double SimFacade::getJointTorque(USHORT i)
{ 
	//Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	//*pVal=jCtlr->getJoint()->getTorque();
	return 0;	
}
