// =============================================================================
//  SimulationImpl.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SIMULATIONIMPL_H__
#define __SIMULATIONIMPL_H__
#include "simulation.h"

class SimulationInputController;
class Trajectory;
class Sensors;

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
		Sensors*		getSensors() const { return mSensors.get(); }

		std::string		getDescription();

	private:

		SimulationImpl();

		// input controllers - mouse, keyboard, etc...
		boost::shared_ptr<SimulationInputController>  mInputController;

		// trajectory
		boost::shared_ptr<Trajectory> mTrajectory;

		// sensors
		boost::shared_ptr<Sensors> mSensors;

};

 #endif