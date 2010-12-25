// =============================================================================
//  SimulationImputController.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "SimulationInputController.h"
#include "scene.h"


/**-------------------------------------------------------------------------------
    SimulationInputController - initialize and add a mouse
    and key event listener

    @brief
    @param simulation
    @return
---------------------------------------------------------------------------------*/
SimulationInputController::SimulationInputController(Simulation* simulation)
{
	mSimulation = simulation;
	mPaused = true;
	mLineGraphFactory = NULL;

	InputManager& inputMgr = InputManager::Instance();
	inputMgr.addMouseListener(this, typeid(this).name());
	inputMgr.addKeyListener(this, typeid(this).name());

	mMouseBtnDown = -1;
	mBtnControl = false;

	mDebugger = NULL;
	mHelpWindow = NULL;
}

/**-------------------------------------------------------------------------------
    ~SimulationInputController - remove listeners

    @brief
    @return
---------------------------------------------------------------------------------*/
SimulationInputController::~SimulationInputController()
{
	InputManager& inputMgr = InputManager::Instance();
	inputMgr.removeMouseListener(this);
	inputMgr.removeKeyListener(this);

	delete mDebugger;
	mDebugger = NULL;
	delete mHelpWindow;
	mHelpWindow = NULL;
	delete mLineGraphFactory;
	mLineGraphFactory = NULL;
}


/**-------------------------------------------------------------------------------
    mouse is moving

    \param evt (const OIS::MouseEvent &)
    \return (void)
-----------------------------------------------------------------------------*/
bool SimulationInputController::mouseMoved(const OIS::MouseEvent& evt)
{
	mSimulation->getScene()->getCamera().updateCamera((OIS::MouseButtonID)mMouseBtnDown, evt.state, mSelectedObject, mBtnControl);
	return true;
}

/**-------------------------------------------------------------------------------
    mouse button was pressed, handle events

    \param evt (const OIS::MouseEvent &)
    \param id (OIS::MouseButtonID)
    \return (void)
-----------------------------------------------------------------------------*/
bool SimulationInputController::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	mMouseBtnDown = id;

	switch (id)
	{
		case(OIS::MB_Left) :
			onLeftMouseClick(evt.state);
			break;
		case(OIS::MB_Middle) :
			onMiddleMouseClick(evt.state);
			break;
		case(OIS::MB_Right) :
			onRightMouseClick(evt.state);
			break;
	}

	return true;
}

/**-------------------------------------------------------------------------------
    mouse button was released

    \param evt (const OIS::MouseEvent &)
    \param id (OIS::MouseButtonID)
    \return (void)
-----------------------------------------------------------------------------*/
bool SimulationInputController::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	// Call mouseReleased of current state
	const OIS::MouseState& mouseState = evt.state;

	mMouseBtnDown = -1;

	switch (id)
	{
		case(OIS::MB_Left) :
			break;
		case(OIS::MB_Right) :
			break;
		case(OIS::MB_Middle) :
			break;
	}

	return true;
}

/**-------------------------------------------------------------------------------
    handle left mouse button click

    \param mstate (const OIS::MouseState &)
    \return (void)
-----------------------------------------------------------------------------*/
void SimulationInputController::onLeftMouseClick(const OIS::MouseState& mstate)
{
	float posX = 1.0f / mSimulation->getScene()->getWindow().getWidth() * mstate.X.abs;
	float posY = 1.0f / mSimulation->getScene()->getWindow().getHeight() * mstate.Y.abs;
	mSelectedObject = mSimulation->getScene()->getCamera().mousePick(posX, posY, mSelectedObject, false);
}

/**-------------------------------------------------------------------------------
    handle right mouse button click

    \param mstate (const OIS::MouseState &)
    \return (void)
-----------------------------------------------------------------------------*/
void SimulationInputController::onRightMouseClick(const OIS::MouseState& mstate)
{
	mSimulation->getScene()->getCamera().updateCamera(OIS::MB_Right, mstate, mSelectedObject, mBtnControl);
}


/**-------------------------------------------------------------------------------
    a key was pressed, handle locally required keys and then
    send them to the GUI

    \param evt (const OIS::KeyEvent &)
    \return (void)
-----------------------------------------------------------------------------*/
bool SimulationInputController::keyPressed(const OIS::KeyEvent& evt)
{
	// Call keyPressed of current state

	switch (evt.key)
	{
		case OIS::KC_ESCAPE :
			mSimulation->requestStateChange(Simulation::SHUTDOWN);
			break;
		case OIS::KC_LCONTROL:
			// when left control is pressed change camera movement type
			mBtnControl = true;
			break;
		case OIS::KC_F1:

			if (mHelpWindow)
			{
				delete mHelpWindow;
				mHelpWindow = NULL;
			}
			else
			{
				mHelpWindow = new ViewHelp(mSimulation);
			}

			break;
		case OIS::KC_F2:

			if (mDebugger)
			{
				delete mDebugger;
				mDebugger = NULL;
			}
			else
			{
				mDebugger = new ViewDebugger(mSimulation);
			}

			break;
		case OIS::KC_F3:

			if (mLineGraphFactory)
			{
				delete mLineGraphFactory;
				mLineGraphFactory = NULL;
			}
			else
			{
				mLineGraphFactory = new LineGraphFactory(mSimulation);
			}

			break;
		case OIS::KC_F4:
			mPaused = !mPaused;
			if (!mPaused) {
				mSimulation->requestStateChange(Simulation::SIMULATING);
			} else {
				mSimulation->requestStateChange(Simulation::PAUSED);
			}
			break;
		default:
			break;
	}

	return true;
}

/**-------------------------------------------------------------------------------
    a key was released

    \param evt (const OIS::KeyEvent &)
    \return (void)
-----------------------------------------------------------------------------*/
bool SimulationInputController::keyReleased(const OIS::KeyEvent& evt)
{
	// Call keyReleased of current state
	switch (evt.key)
	{
		case OIS::KC_LCONTROL:
			mBtnControl = false;
			break;
		default:
			break;
	}

	return true;
}
