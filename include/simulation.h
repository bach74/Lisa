#pragma once

#include "scene.h"
#include "link.h"
#include "actuator.h"
#include "actuators.h"


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
		virtual Link*       getSelectedObject() const = 0;

		Links*              getLinks() const { return mLinks; }
		Actuators*          getActuators() const { return mActuators; };

		NxOgre::World*      getWorld() const { return mWorld; }
		Scene*              getScene() const { return mScene; }
		NxOgre::Scene*      getPhyScene() const { return mPhyScene; }

		virtual std::string getDescription() = 0;

	protected:

		NxOgre::World*      mWorld;
		Scene*              mScene;
		NxOgre::Scene*      mPhyScene;

		// objects (actors) are represented as links
		Links*              mLinks;

		// link controllers (for joints)
		Actuators*          mActuators;


	private:
		float               mFrameTime;
		float               mTimeSinceLastRenderFrame;
		float               mTimeSinceLastPhysXFrame;
		SimulationState     mState;
		CRITICAL_SECTION    mCS;
		bool                mLocked;
};