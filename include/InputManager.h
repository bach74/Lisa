// =============================================================================
//  InputManager.h   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "singleton.h"


/**-------------------------------------------------------------------------------
	Input manager class	
	Keyboard, Mouse and joystick manipulation
---------------------------------------------------------------------------------*/
class InputManager : private OIS::KeyListener, OIS::MouseListener, OIS::JoyStickListener, public ::Singleton<InputManager> {
public:

	friend ::Singleton<InputManager>;

	void initialise(Ogre::RenderWindow *renderWindow);
	void capture();

	void addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName);
	void addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName);
	void addJoystickListener(OIS::JoyStickListener *joystickListener, const std::string& instanceName);

	void removeKeyListener(const std::string& instanceName);
	void removeKeyListener(OIS::KeyListener *keyListener);

	void removeMouseListener(const std::string& instanceName);
	void removeMouseListener(OIS::MouseListener *mouseListener);

	void removeJoystickListener(const std::string& instanceName);
	void removeJoystickListener(OIS::JoyStickListener *joystickListener);

	void removeAllListeners();
	void removeAllKeyListeners();
	void removeAllMouseListeners();
	void removeAllJoystickListeners();

	void setWindowExtents(int width, int height);
	int getNumOfJoysticks();

	/**----------------------------------------------------------------------------
		Return mouse.   
		\return (OIS::Mouse*)
	 -----------------------------------------------------------------------------*/
	OIS::Mouse* InputManager::getMouse()
	{
		return mMouse;
	}
	/**----------------------------------------------------------------------------
		return keyboard.  
		\return (OIS::Keyboard*)
	 -----------------------------------------------------------------------------*/
	OIS::Keyboard* InputManager::getKeyboard()
	{
		return mKeyboard;
	}
	/**----------------------------------------------------------------------------
		return joystick.  
		\param index (unsigned int)
		\return (OIS::JoyStick*)
	 -----------------------------------------------------------------------------*/
	OIS::JoyStick* InputManager::getJoystick(unsigned int index)
	{
		return (index<mJoysticks.size())?mJoysticks[index]:0;
	}


private:

	InputManager():mMouse(0), mKeyboard(0), mInputSystem(0) {};
	virtual ~InputManager();

	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool povMoved(const OIS::JoyStickEvent &e, int pov);
	bool axisMoved(const OIS::JoyStickEvent &e, int axis);
	bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
	bool buttonPressed(const OIS::JoyStickEvent &e, int button);
	bool buttonReleased(const OIS::JoyStickEvent &e, int button);

	OIS::InputManager *mInputSystem;
	OIS::Mouse        *mMouse;
	OIS::Keyboard     *mKeyboard;
	std::vector<OIS::JoyStick*> mJoysticks;

	std::map<std::string, OIS::KeyListener*> mKeyListeners;
	std::map<std::string, OIS::MouseListener*> mMouseListeners;
	std::map<std::string, OIS::JoyStickListener*> mJoystickListeners;

};

#endif