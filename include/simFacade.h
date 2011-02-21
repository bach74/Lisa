// =============================================================================
//  SimFacade.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SIMFACADE_H__
#define __SIMFACADE_H__

#include "lisaCore.h"
#include "simulation.h"
#include "actuator.h"
#include "contactReporter.h"
#include "CritSectEx.h"

/**-------------------------------------------------------------------------------
	SimFacade is a monolith class that exposes internal variables to the external
	interface. The variables are guaranteed to be from the same sampling period.
	
	@brief
	@return int
---------------------------------------------------------------------------------*/
class SimFacade : public ::Singleton<SimFacade>
{
	public:

		friend ::Singleton<SimFacade>;

		/// external variables-> simulation variables
		void getStates();

		/// simulation variables -> state snapshot
		void setStates();

		/// object
		int getNumLinks() const;
		std::string getLinkName(USHORT i) const;
		double getLinkMass(USHORT i) const;
		Ogre::Vector3 getLinkPosition(USHORT i) const;
		Ogre::Vector3 getLinkPosition(const std::string& linkName) const;
		Ogre::Vector3 getJointCoordinates(USHORT i) const;
		
		/// sensors
		Ogre::Vector3 getCOPPosition() const;
		Ogre::Vector3 getCOPForce() const;

		/// application
		void closeApplication() const;
		void pauseSimulation(bool pause) const;
		double getCurrentTime() const;

		/// trajectory
		void loadTrajectory(const TCHAR* filename) const;

		/// controllers & actuators
		UINT getControllerNum(void);
		std::vector<double> getActuatorParams(USHORT i);
		void setActuatorParams(USHORT i, std::vector<double>& params);
		void setActuatorParam(USHORT i, USHORT nParam, double valParam);

		/// joints
		double	getJointAngle(USHORT i);
		double	getJointVelocity(USHORT i);
		double	getJointTorque(USHORT i);
		void	setJointSetpoint(USHORT i, USHORT nParam, double val);
		double	getJointSetpoint(USHORT i, USHORT nParam);

		/// simulation
		Ogre::Vector3 getGravity();

	private:
		/// hide constructor
		SimFacade(){};
		virtual ~SimFacade(){};

		/// get physX scene object
		NxOgre::Scene* getPhyScene() const
		{
			NxOgre::World* world = LisaCore::Instance().getSimulation()->getWorld();
			return (world) ? world->getScenes()->get(THE_WORLD) : NULL;
		}

		/// get simulation object
		Simulation* getSimulation() const
		{
			return LisaCore::Instance().getSimulation();
		}

		/// get body implementation
		NxOgre::Actor* SimFacade::getLink(USHORT i) const;


		std::vector<double> mJointTorques;
		std::vector<double> mJointVelocities;
		std::vector<double> mJointAngles;
		std::vector<double> mJointSetpoints;

		CritSectEx	myCs;
};

 #endif