#pragma once

#include "simulation.h"
#include "sensorForce.h"


class ViewDebugger: public Ogre::FrameListener
{
	public:

		enum DebugView
		{
			VISUAL_NONE,
			VISUAL_BRIEF,
			VISUAL_BODIES,
			VISUAL_JOINTS,
			VISUAL_COLLISIONS,
			VISUAL_EVERYTHING,
			VISUAL_MOST,
			VISUAL_CONTACTS,
		};

		ViewDebugger(Simulation* simulation);
		~ViewDebugger();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		Simulation* getSimulation() const { return mSimulation; }

		void toggleVisible();

		std::string getDebugDescription() const { return mDebugDescription; }
		void setDebugDescription(std::string val) { mDebugDescription = val; }

		void setDebug(DebugView debugView);
		std::string getDebug();

		bool getExpandedText() const { return mExpandedText; }
		void setExpandedText(bool val) { mExpandedText = val; }

		SensorVectors* getForceVec() const { return mForceVec; }

	private:

		Simulation*                     mSimulation;
		OIS::KeyListener*               mController;

		std::string                     mDebugDescription;
		Ogre::Overlay*                  mOverlay;
		Ogre::OverlayElement*			mDebugOverlayText;
		Ogre::OverlayContainer*			mDebugOverlay;
		DebugView                       mDebugView;
		std::vector<NxParameter>        mShowDebuggers;
		unsigned int                    mShowDebuggersCurrent;
		bool							mExpandedText;
		SensorVectors*					mForceVec;

		ViewDebugger();

		void updateDebug();
		void showDebug(bool show);
		

};
