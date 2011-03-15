// =============================================================================
//  Simulation.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SIMULATION_H__
#define __SIMULATION_H__


class Scene;
class Link;
class Links;
class Actuators;
class Actuator;
#include "CritSectEx.h"

class Simulation : public Ogre::FrameListener
{
	public:

		typedef enum eSimulationStates
		{
			STARTUP,
			LOADING,
			CANCEL_LOADING,
			PREPARE,
			SIMULATING,
			SHUTDOWN,
			PAUSED
		} SimulationState;

		Simulation();
		virtual ~Simulation();

		// state change functions
		virtual bool        requestStateChange(SimulationState state) = 0;
		SimulationState     getCurrentState() const { return mState; }
		bool                lockState(SimulationState newState);
		bool                unlockState();

		// frame listener events
		virtual bool        frameStarted(const Ogre::FrameEvent& evt) = 0;
		virtual bool        frameEnded(const Ogre::FrameEvent& evt) = 0;
		virtual void        capture() = 0;
		virtual void		simulate(float timeSinceLastFrame)=0;

		float               getFrameTime() const { return mFrameTime; }
		void                setFrameTime(float ms) { mFrameTime = ms; }
		float               getTimeSinceLastRenderFrame() const { return mTimeSinceLastRenderFrame; }
		void                setTimeSinceLastRenderFrame(float ms) { mTimeSinceLastRenderFrame = ms; }
		float				getTimeSinceLastPhysXFrame() const { return mTimeSinceLastPhysXFrame; }
		void				setTimeSinceLastPhysXFrame(float val) { mTimeSinceLastPhysXFrame = val; }

		// Current object manipulation
		virtual Link*		getSelectedObject() const = 0;

		Links*				getLinks() const { return mLinks.get(); }
		Actuators*			getActuators() const { return mActuators.get(); };

		NxOgre::World*		getWorld() const { return mWorld.get(); }
		Scene*				getScene() const { return mScene; }
		NxOgre::Scene*		getPhyScene() const { return mPhyScene.get(); }

		virtual std::string getDescription() = 0;

	protected:

		boost::shared_ptr<NxOgre::World>		mWorld;
		Scene*									mScene;
		boost::shared_ptr<NxOgre::Scene>		mPhyScene;

		// objects (actors) are represented as links
		boost::shared_ptr<Links>				mLinks;

		// link controllers (for joints)
		boost::shared_ptr<Actuators>			mActuators;


	private:
		float               mFrameTime;
		float               mTimeSinceLastRenderFrame;
		float               mTimeSinceLastPhysXFrame;
		SimulationState     mState;
		CritSectEx			myCs;
		bool                mLocked;
};

 #endif