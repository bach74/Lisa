// =============================================================================
//  InputManager.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "InputManager.h"


/**----------------------------------------------------------------------------
	.

	\return ()
 -----------------------------------------------------------------------------*/
InputManager::~InputManager()
{
	if (mInputSystem)
	{
		if (mMouse)
		{
			mInputSystem->destroyInputObject(mMouse);
			mMouse=NULL;
		}

		if (mKeyboard)
		{
			mInputSystem->destroyInputObject(mKeyboard);
			mKeyboard=NULL;
		}

		if (mJoysticks.size() > 0)
		{
			std::vector<OIS::JoyStick*>::iterator itJoystick=mJoysticks.begin();

			for (; itJoystick!=mJoysticks.end(); ++itJoystick)
			{
				mInputSystem->destroyInputObject(*itJoystick);
			}
			mJoysticks.clear();
		}

		// Clear Listeners
		mKeyListeners.clear();
		mMouseListeners.clear();
		mJoystickListeners.clear();

		OIS::InputManager::destroyInputSystem(mInputSystem);
		mInputSystem=NULL;
	}
}

/**----------------------------------------------------------------------------
	Initialize input manager (keyboard, mouse and joystick)

	\param renderWindow (Ogre::RenderWindow *)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::initialise(Ogre::RenderWindow *renderWindow)
{
	if (!mInputSystem)
	{
		// Setup basic variables
		OIS::ParamList paramList;
		size_t windowHnd=0;
		std::ostringstream windowHndStr;

		// Get window handle
		renderWindow->getCustomAttribute("WINDOW", &windowHnd);

		// Fill parameter list
		windowHndStr<<windowHnd;
		paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		// Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

		// Create inputsystem
		mInputSystem = OIS::InputManager::createInputSystem(paramList);

		// If possible create a buffered keyboard
		if (mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0)
		{
			mKeyboard = static_cast<OIS::Keyboard*>(mInputSystem->createInputObject(OIS::OISKeyboard, true));
			mKeyboard->setEventCallback(this);
		}

		// If possible create a buffered mouse
		if (mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0)
		{
			mMouse = static_cast<OIS::Mouse*>(mInputSystem->createInputObject(OIS::OISMouse, true));
			mMouse->setEventCallback(this);

			// Get window size
			UINT width, height, depth;
			int left, top;
			renderWindow->getMetrics(width, height, depth, left, top);

			// Set mouse region
			setWindowExtents(width, height);
		}

		// If possible create all joysticks in buffered mode
		if (mInputSystem->getNumberOfDevices(OIS::OISJoyStick) > 0)
		{
			mJoysticks.resize(mInputSystem->getNumberOfDevices(OIS::OISJoyStick));
			std::vector<OIS::JoyStick*>::iterator itJoystick=mJoysticks.begin();
			for (; itJoystick != mJoysticks.end(); ++itJoystick)
			{
				(*itJoystick) = static_cast<OIS::JoyStick*>(mInputSystem->createInputObject(OIS::OISJoyStick, true));
				(*itJoystick)->setEventCallback(this);
			}
		}
	}
}

/**----------------------------------------------------------------------------
	Need to capture / update each device every frame.

	\param  (void)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::capture(void)
{
	if (mMouse)
		mMouse->capture();

	if (mKeyboard)
		mKeyboard->capture();

	std::for_each(mJoysticks.begin(),mJoysticks.end(),std::mem_fun(&OIS::JoyStick::capture));
}

/**----------------------------------------------------------------------------
	Add key listener to the input manager.

	\param keyListener (OIS::KeyListener *)
	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName)
{
	if (mKeyboard)
	{
		// Check for duplicate items
		if (mKeyListeners.find(instanceName)==mKeyListeners.end())
		{
			mKeyListeners[instanceName ]=keyListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}

/**----------------------------------------------------------------------------
	Add mouse listener to input manager.

	\param mouseListener (OIS::MouseListener *)
	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName)
{
	if (mMouse)
	{
		// Check for duplicate items
		if (mMouseListeners.find(instanceName)==mMouseListeners.end())
		{
			mMouseListeners[instanceName]=mouseListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}

/**----------------------------------------------------------------------------
	Add joystick listener to input manager.

	\param joystickListener (OIS::JoyStickListener *)
	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::addJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName)
{
	if (mJoysticks.size()>0)
	{
		if (mJoystickListeners.find(instanceName)==mJoystickListeners.end())
		{
			mJoystickListeners[instanceName]=joystickListener;
		}
		else
		{
			// Duplicate Item
		}
	}
}


/**----------------------------------------------------------------------------
	Remove keylistener from input manager.

	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeKeyListener(const std::string& instanceName)
{
	// Check if item exists
	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener=mKeyListeners.find(instanceName);

	if (itKeyListener!=mKeyListeners.end())
	{
		mKeyListeners.erase(itKeyListener);
	}
	else
	{
		// Doesn't Exist
	}
}

/**----------------------------------------------------------------------------
	Remove mouse listener from input manager.

	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeMouseListener(const std::string& instanceName)
{
	// Check if item exists
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener=mMouseListeners.find(instanceName);

	if (itMouseListener!=mMouseListeners.end())
	{
		mMouseListeners.erase(itMouseListener);
	}
	else
	{
		// Doesn't Exist
	}
}

/**----------------------------------------------------------------------------
	Remove joystick listener from input manager.

	\param instanceName (const std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeJoystickListener(const std::string& instanceName)
{
	// Check if item exists
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.find(instanceName);

	if (itJoystickListener!=mJoystickListeners.end())
	{
		mJoystickListeners.erase(itJoystickListener);
	}
	else
	{
		// Doesn't Exist
	}
}

/**----------------------------------------------------------------------------
	Remove key listener from input manager.

	\param keyListener (OIS::KeyListener *)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeKeyListener(OIS::KeyListener *keyListener)
{
	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener=mKeyListeners.begin();

	for (; itKeyListener!=mKeyListeners.end(); ++itKeyListener)
	{
		if (itKeyListener->second==keyListener)
		{
			mKeyListeners.erase(itKeyListener);
			break;
		}
	}
}

/**----------------------------------------------------------------------------
	Remove mouse listener from input manager.

	\param mouseListener (OIS::MouseListener *)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeMouseListener(OIS::MouseListener *mouseListener)
{
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener=mMouseListeners.begin();

	for (; itMouseListener!=mMouseListeners.end(); ++itMouseListener)
	{
		if (itMouseListener->second==mouseListener)
		{
			mMouseListeners.erase(itMouseListener);
			break;
		}
	}
}

/**----------------------------------------------------------------------------
	Remove joystick listener from input manager.

	\param joystickListener (OIS::JoyStickListener *)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeJoystickListener(OIS::JoyStickListener *joystickListener)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		if (itJoystickListener->second == joystickListener)
		{
			mJoystickListeners.erase(itJoystickListener);
			break;
		}
	}
}

/**----------------------------------------------------------------------------
	Remove all registered listeners from input manager.

	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeAllListeners()
{
	mKeyListeners.clear();
	mMouseListeners.clear();
	mJoystickListeners.clear();
}

/**----------------------------------------------------------------------------
	Remove all registered keylisteners from input manager..

	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeAllKeyListeners()
{
	mKeyListeners.clear();
}

/**----------------------------------------------------------------------------
	Remove all registered mouselisteners from input manager..

	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeAllMouseListeners()
{
	mMouseListeners.clear();
}

/**----------------------------------------------------------------------------
	Remove all registered Joysticklisteners from input manager..

	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::removeAllJoystickListeners()
{
	mJoystickListeners.clear();
}

/**----------------------------------------------------------------------------
	Set mouse region (if window resizes, we should alter this to reflect as well).

	\param width (int)
	\param height (int)
	\return (void)
 -----------------------------------------------------------------------------*/
void InputManager::setWindowExtents(int width, int height)
{
	const OIS::MouseState &mouseState=mMouse->getMouseState();

	mouseState.width=width;
	mouseState.height=height;
}

/**----------------------------------------------------------------------------
	get number of joysticks.

	\return (int)
 -----------------------------------------------------------------------------*/
int InputManager::getNumOfJoysticks()
{
	// Cast to keep compiler happy ^^
	return (int) mJoysticks.size();
}

/**----------------------------------------------------------------------------
	forward key pressed event to all registered key listeners.

	\param e (const OIS::KeyEvent &)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::keyPressed(const OIS::KeyEvent &e)
{
	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener=mKeyListeners.begin();

	for (; itKeyListener!=mKeyListeners.end(); ++itKeyListener)
	{
		itKeyListener->second->keyPressed(e);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward key release event to all registered key listeners.

	\param e (const OIS::KeyEvent &)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::keyReleased(const OIS::KeyEvent &e)
{
	std::map<std::string, OIS::KeyListener*>::iterator itKeyListener=mKeyListeners.begin();

	for (; itKeyListener!=mKeyListeners.end(); ++itKeyListener)
	{
		itKeyListener->second->keyReleased(e);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward mouse moved event to all registered mouse listeners.

	\param e (const OIS::MouseEvent &)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::mouseMoved(const OIS::MouseEvent &e)
{
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener=mMouseListeners.begin();

	for (; itMouseListener!=mMouseListeners.end(); ++itMouseListener)
	{
		itMouseListener->second->mouseMoved(e);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward mouse pressed event to all registered mouse listeners.

	\param e (const OIS::MouseEvent &)
	\param id (OIS::MouseButtonID)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener=mMouseListeners.begin();

	for (; itMouseListener!=mMouseListeners.end(); ++itMouseListener)
	{
		itMouseListener->second->mousePressed(e, id);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward mouse released event to all registered mouse listeners.

	\param e (const OIS::MouseEvent &)
	\param id (OIS::MouseButtonID)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	std::map<std::string, OIS::MouseListener*>::iterator itMouseListener=mMouseListeners.begin();

	for (; itMouseListener!=mMouseListeners.end(); ++itMouseListener)
	{
		itMouseListener->second->mouseReleased(e, id);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward pov moved event to all registered joystick listeners.

	\param e (const OIS::JoyStickEvent &)
	\param pov (int)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::povMoved(const OIS::JoyStickEvent &e, int pov)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		itJoystickListener->second->povMoved(e, pov);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward axis moved event to all registered joystick listeners.

	\param e (const OIS::JoyStickEvent &)
	\param axis (int)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		itJoystickListener->second->axisMoved(e, axis);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward slider moved event to all registered joystick listeners.

	\param e (const OIS::JoyStickEvent &)
	\param sliderID (int)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		itJoystickListener->second->sliderMoved(e, sliderID);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward button pressed event to all registered joystick listeners.

	\param e (const OIS::JoyStickEvent &)
	\param button (int)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::buttonPressed(const OIS::JoyStickEvent &e, int button)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		itJoystickListener->second->buttonPressed(e, button);
	}
	return true;
}

/**----------------------------------------------------------------------------
	forward button released event to all registered joystick listeners.

	\param e (const OIS::JoyStickEvent &)
	\param button (int)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool InputManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
{
	std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener=mJoystickListeners.begin();

	for (; itJoystickListener!=mJoystickListeners.end(); ++itJoystickListener)
	{
		itJoystickListener->second->buttonReleased(e, button);
	}
	return true;
}
