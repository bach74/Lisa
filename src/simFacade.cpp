#include "stdafx.h"
#include "SimFacade.h"
#include "simulationImpl.h"

/**----------------------------------------------------------------------------
	Get i-th body from the .
   
	\param i (unsigned short)
	\return (NxOgre::Body&)
 -----------------------------------------------------------------------------*/
NxOgre::Actor* SimFacade::getLink(unsigned short i) const
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
std::string SimFacade::getLinkName(unsigned short i) const
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
   
	\param i (unsigned short)				link number
	\return (double)
 -----------------------------------------------------------------------------*/
double SimFacade::getLinkMass(unsigned short i) const
{
	return getLink(i)->getMass();
}

/**----------------------------------------------------------------------------
	get position (x,y,z) of the i-th link.
   
	\param i (unsigned short)				link number
	\return (Ogre::Vector3)
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getLinkPosition(unsigned short i) const
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
   
	\param i (unsigned short)				joint number
	\return (Ogre::Vector3)			joint position
 -----------------------------------------------------------------------------*/
Ogre::Vector3 SimFacade::getJointCoordinates(unsigned short i) const
{			
	Actuator* a=SimFacade::Instance().getActuator(i);
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
Actuator* SimFacade::getActuator( int n ) const
{
	ActuatorIterator it(LisaCore::Instance().getSimulation()->getActuators());

	for (int i = 0; i < n; ++i)
	{
		if (it.end()) { return NULL; }
	}
	return &(*it);
}