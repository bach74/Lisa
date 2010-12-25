// =============================================================================
//  SimulationImpl.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SIMULATIONIMPL_H__
#define __SIMULATIONIMPL_H__
#include "simulation.h"
#include "SimulationInputController.h"
#include "trajectory.h"
#include "sensors.h"
#include "../src/com/LisaCOM.h"


/**-------------------------------------------------------------------------------
	SimulationImpl class

---------------------------------------------------------------------------------*/
class SimulationImpl : public Simulation
{

	public:

		SimulationImpl(Scene* my_scene);
		virtual ~SimulationImpl();

		bool			requestStateChange(SimulationState state);
		void			loadScene(const std::string& filename);
		void			onPrepareSimulation();

		void			simulateZoom(short distance);

		// object manipulation
		void			moveObjects(const Ogre::Quaternion& q, const Ogre::Vector3& pos);

		virtual bool	frameStarted(const Ogre::FrameEvent& evt);			
		virtual bool	frameEnded(const Ogre::FrameEvent& evt);
		virtual void	capture();
		virtual void	simulate(float timeSinceLastFrame);

		virtual Link*	getSelectedObject() const;

		// TODO better ?
		Sensors*		getSensors() const { return mSensors; }

		std::string		getDescription();

	private:

		SimulationImpl();

		// input controllers - mouse, keyboard, etc...
		SimulationInputController*  mInputController;

		// trajectory
		Trajectory* mTrajectory;

		// sensors
		Sensors* mSensors;

};

 #endif