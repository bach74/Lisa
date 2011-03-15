// =============================================================================
//  SimulationInputControllerDebug.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "simulationInputControllerDebug.h"
#include "InputManager.h"
#include "link.h"


/**-------------------------------------------------------------------------------
	SimulationInputControllerDebug - initialize and add a
	mouse and key event listener

	@brief
	@param simulation
	@return
---------------------------------------------------------------------------------*/
SimulationInputControllerDebug::SimulationInputControllerDebug(ViewDebugger* simulation):mViewDebugger(simulation),
		mForceMode(FORCE), mForceType(NX_FORCE), mForceStrength(1)
{
	InputManager& inputMgr=InputManager::Instance();
	inputMgr.addKeyListener(this,typeid(this).name());
}

/**-------------------------------------------------------------------------------
	~SimulationInputControllerDebug - remove listeners

	@brief
	@return
---------------------------------------------------------------------------------*/
SimulationInputControllerDebug::~SimulationInputControllerDebug()
{
	InputManager& inputMgr=InputManager::Instance();
	inputMgr.removeKeyListener(this);
}

/**-------------------------------------------------------------------------------
	onChange

	@brief
	@return void
---------------------------------------------------------------------------------*/
void SimulationInputControllerDebug::onChange()
{
	Ogre::String text="\n\rForce mode:"+getForceName()
					  +" type:"+getForceType()
					  +" strength:"+Ogre::StringConverter::toString(mForceStrength)+"\n\r";
	mViewDebugger->setDebugDescription(text);
}

/**-------------------------------------------------------------------------------
	a key was pressed, handle locally required keys and then
	send them to the GUI

	\param evt (const OIS::KeyEvent &)
	\return (bool)
-----------------------------------------------------------------------------*/
bool SimulationInputControllerDebug::keyPressed(const OIS::KeyEvent& evt)
{

	ViewDebugger::DebugView viewDebug=ViewDebugger::VISUAL_NONE;
	// Call keyPressed of current state
	switch (evt.key)
	{
		case OIS::KC_TAB:
			mForceMode=(ForceType)(mForceMode^1);
			break;

		case OIS::KC_LSHIFT:
			if (mForceType<5)
				mForceType=(NxForceMode)(mForceType+1);
			else
				mForceType=NX_FORCE;
			break;

		case OIS::KC_MINUS:
			mForceStrength-=10;
			break;

		case OIS::KC_EQUALS:
			mForceStrength+=10;
			break;

		case OIS::KC_BACK:
			mViewDebugger->setExpandedText(!mViewDebugger->getExpandedText());
			break;

		case OIS::KC_1:
			viewDebug=ViewDebugger::VISUAL_BRIEF;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_2:
			viewDebug=ViewDebugger::VISUAL_BODIES;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_3:
			viewDebug=ViewDebugger::VISUAL_JOINTS;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_4:
			viewDebug=ViewDebugger::VISUAL_COLLISIONS;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_5:
			viewDebug=ViewDebugger::VISUAL_CONTACTS;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_6:
			viewDebug=ViewDebugger::VISUAL_MOST;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_7:
			viewDebug=ViewDebugger::VISUAL_EVERYTHING;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_9:
			mViewDebugger->toggleVisible();
			break;
		case OIS::KC_0:
			viewDebug=ViewDebugger::VISUAL_NONE;
			mViewDebugger->setDebug(viewDebug);
			break;

		case OIS::KC_F11:
		{
			float scale=mViewDebugger->getSimulation()->getWorld()->getSDK()->getParameter(NX_VISUALIZATION_SCALE);
			mViewDebugger->getSimulation()->getWorld()->getSDK()->setParameter(NX_VISUALIZATION_SCALE, scale-0.1f);
		}
		break;

		case OIS::KC_F12:
		{
			float scale=mViewDebugger->getSimulation()->getWorld()->getSDK()->getParameter(NX_VISUALIZATION_SCALE);
			mViewDebugger->getSimulation()->getWorld()->getSDK()->setParameter(NX_VISUALIZATION_SCALE, scale+0.1f);
		}
		break;

		case OIS::KC_UP:
		case OIS::KC_DOWN:
		case OIS::KC_LEFT:
		case OIS::KC_RIGHT:
		case OIS::KC_Q:
		case OIS::KC_A:
		{
			Link* link=mViewDebugger->getSimulation()->getSelectedObject();

			Ogre::Vector3 vec(0,0,0);

			switch (evt.key)
			{
				case OIS::KC_UP:
					vec.z=-1;
					break;
				case OIS::KC_DOWN:
					vec.z=1;
					break;
				case OIS::KC_LEFT:
					vec.x=-1;
					break;
				case OIS::KC_RIGHT:
					vec.x=1;
					break;
				case OIS::KC_Q:
					vec.y=1;
					break;
				case OIS::KC_A:
					vec.y=-1;
					break;
			}
			if (link)
			{
				if (mForceMode==FORCE)
				{
					float deltaTime=mViewDebugger->getSimulation()->getTimeSinceLastPhysXFrame();
					Ogre::Vector3 force=vec*mForceStrength*deltaTime;
					link->addForce(force, mForceType);
					std::vector<Ogre::Vector3> forceVal;
					forceVal.push_back(NxOgre::NxConvert<Ogre::Vector3,NxVec3>(mViewDebugger->getSimulation()->getSelectedObject()->getNxActor()->getCMassGlobalPosition()));
					forceVal.push_back(force);
					mViewDebugger->getForceVec()->setValue(forceVal);
					mViewDebugger->getForceVec()->setDataValid(true);
				}
				else
				{
					link->addLocalTorque(vec*mForceStrength);
				}
			}
		}
		break;

		default:
			break;
	}

	onChange();

	return true;
}

/**----------------------------------------------------------------------------
	Returns string description of currently selected force mode

	\return (Ogre::String)
-----------------------------------------------------------------------------*/
std::string SimulationInputControllerDebug::getForceType()
{
	switch (mForceType)
	{
		case NX_FORCE:
			return std::string("Force");
			break;
		case NX_IMPULSE:
			return std::string("Impulse");
			break;
		case NX_VELOCITY_CHANGE:
			return std::string("velocity change");
			break;
		case NX_SMOOTH_IMPULSE:
			return std::string("Smooth Impulse");
			break;
		case NX_SMOOTH_VELOCITY_CHANGE:
			return std::string("Smooth velocity change");
			break;
		case NX_ACCELERATION:
			return std::string("Acceleration");
			break;
		default:
			return "undefined";
	}

	onChange();
}

/**-------------------------------------------------------------------------------
	keyReleased

	@brief
	@param arg
	@return bool
---------------------------------------------------------------------------------*/
bool SimulationInputControllerDebug::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}
