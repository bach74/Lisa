#pragma once

#include "viewDebugger.h"

class SimulationInputControllerDebug : public OIS::KeyListener
{
	public:
		SimulationInputControllerDebug(ViewDebugger* simulation);
		~SimulationInputControllerDebug(void);

		bool keyPressed(const OIS::KeyEvent& evt);
		bool keyReleased(const OIS::KeyEvent &arg);

	private:
		ViewDebugger*     mViewDebugger;
		typedef enum eForceTypes
		{
			FORCE,
			MOMENTUM
		} ForceType;

		ForceType               mForceMode;
		float                   mForceStrength;
		NxForceMode             mForceType;

		void                    onChange();
		std::string             getForceType();
		std::string             getForceName() { return (mForceMode==FORCE)?Ogre::String("Force"):Ogre::String("Torque"); }
};
