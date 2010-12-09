// =============================================================================
//  simulation.h   version:  1.0
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
//
// =============================================================================
#pragma once
#include "simulation.h"
#include "SimulationInputController.h"
#include "trajectory.h"
#include "sensors.h"
#include "poseControl.h"
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

		// pose control
		PoseControl* mPoseControl;
};