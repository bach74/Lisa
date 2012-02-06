// =============================================================================
//  LisaAPI.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __LisaAPI_H__
#define __LisaAPI_H__

#include "singleton.h"
#include "CritSectEx.h"
#include "logger.h"

class Simulation;
class Actuator;


/**-------------------------------------------------------------------------------
	LisaAPI is a monolith class that exposes internal variables to the external
	interface. The variables are guaranteed to be from the same sampling period.
	
	The simulation variables can be persisted to a log file by using the loggerwritter
	interface.

	@brief
	@return int
---------------------------------------------------------------------------------*/
class LisaAPI : public ::Singleton<LisaAPI>, public LoggerWriter<LisaAPI>
{
	public:

		friend ::Singleton<LisaAPI>;

		/// simulation variables -> state snapshot
		void setStates();

		/// object
		int getNumLinks() const;
		std::string getLinkName(size_t i) const;
		double getLinkMass(size_t i) const;
		Ogre::Vector3 getLinkPosition(size_t i) const;
		Ogre::Vector3 getLinkPosition(const std::string& linkName) const;
		Ogre::Vector3 getJointCoordinates(size_t i) const;
		
		/// sensors
		Ogre::Vector3 getCOPPosition() const;
		Ogre::Vector3 getCOPForce() const;

		/// application
		void closeApplication() const;
		void pauseSimulation(bool pause) const;
		short isSimulationPaused() const;
		double getCurrentTime() const;

		/// trajectory
		void loadTrajectory(const TCHAR* filename) const;

		/// controllers & actuators
		UINT getControllerNum(void);
		std::vector<double> getActuatorParams(size_t i);
		void setActuatorParams(size_t i, std::vector<double>& params);
		void setActuatorParam(size_t i, size_t nParam, double valParam);

		/// joints
		double	getJointAngle(size_t i);
		double	getJointVelocity(size_t i);
		double	getJointTorque(size_t i);
		void	setJointSetpoint(size_t i, size_t nParam, double val);
		double	getJointSetpoint(size_t i, size_t nParam);
		void	setJointSetpoints(const std::vector<double>& setpoints);
		std::vector<double> getJointAngles();

		/// simulation
		Ogre::Vector3 getGravity();

		///logging
		void updateLog();

	private:
		/// hide constructor
		LisaAPI();
		virtual ~LisaAPI(){};

		/// get physX scene object
		NxOgre::Scene* getPhyScene() const;

		/// get simulation object
		const Simulation* getSimulation() const;

		/// get body implementation
		//NxOgre::Actor* LisaAPI::getLink(size_t i) const;


		std::vector<double>			mJointTorques;
		std::vector<double>			mJointVelocities;
		std::vector<double>			mJointAngles;
		std::vector<double>			mJointSetpoints;
		std::vector<std::vector<double>> mActuatorParams;

		std::vector<Ogre::Vector3>	mLinkPositions;
		std::vector<Ogre::Vector3>	mJointCoordinates;
		std::vector<std::string>	mLinkNames;
		std::vector<double>			mLinkMass;

		double mFrameTime;

		CritSectEx	myCs;
};

 #endif