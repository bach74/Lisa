#pragma once
#include "lisaCore.h"
#include "simulation.h"
#include "actuator.h"
#include "contactReporter.h"

class SimFacade : public ::Singleton<SimFacade>
{
	public:

		friend ::Singleton<SimFacade>;

		// object
		int getNumLinks() const;
		std::string getLinkName(unsigned short i) const;
		double getLinkMass(unsigned short i) const;
		Ogre::Vector3 getLinkPosition(unsigned short i) const;
		Ogre::Vector3 getLinkPosition(const std::string& linkName) const;
		Ogre::Vector3 getJointCoordinates(unsigned short i) const;
		Ogre::Vector3 getCOPPosition() const;
		Ogre::Vector3 getCOPForce() const;

		// application
		void closeApplication() const;
		void pauseSimulation(bool pause) const;
		double getCurrentTime() const;

		// trajectory
		void loadTrajectory(const TCHAR* filename) const;

		/// get simulation object
		Simulation* getSimulation() const
		{
			return LisaCore::Instance().getSimulation();
		}

		/// getActuator
		Actuator* getActuator(int n) const;


	private:
		/// hide constructor
		SimFacade() {};
		virtual ~SimFacade() {};

		/// get physX scene object
		NxOgre::Scene* getPhyScene() const
		{
			NxOgre::World* world = LisaCore::Instance().getSimulation()->getWorld();
			return (world) ? world->getScenes()->get(THE_WORLD) : NULL;
		}

		/// get body implementation
		NxOgre::Actor* SimFacade::getLink(unsigned short i) const;
};
