// =============================================================================
//  SimulationInputController.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SIMULATIONINPUTCONTROLLER_H__
#define __SIMULATIONINPUTCONTROLLER_H__

#include "inputManager.h"

class Simulation;
class ViewDebugger;
class ViewHelp;
class LineGraphFactory;

class SimulationInputController : public OIS::KeyListener, OIS::MouseListener
{
	public:
		SimulationInputController(Simulation* simulation);

		virtual ~SimulationInputController(void);

		bool keyPressed(const OIS::KeyEvent& evt);
		bool keyReleased(const OIS::KeyEvent& evt);

		bool mouseMoved(const OIS::MouseEvent& evt);
		bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

		void onLeftMouseClick(const OIS::MouseState& mstate);
		void onRightMouseClick(const OIS::MouseState& mstate);
		void onMiddleMouseClick(const OIS::MouseState& mstate) {};

		void capture() { InputManager::Instance().capture(); }

		std::string getSelectedObject() const { return mSelectedObject; }

	protected:
		std::string			mSelectedObject;

	private:

		Simulation*         mSimulation;
		ViewDebugger*		mDebugger;
		ViewHelp*			mHelpWindow;
		LineGraphFactory*	mLineGraphFactory;
		int                 mMouseBtnDown;
		bool                mBtnControl;
		bool				mPaused;

		SimulationInputController::SimulationInputController() {};

};

 #endif