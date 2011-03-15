// =============================================================================
//  ViewDebugger.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "viewDebugger.h"
#include "actuator.h"
#include "simulationInputControllerDebug.h"
#include "config.h"
#include "sensorDecoratorVector.h"
#include "scene.h"
#include "link.h"


/**-------------------------------------------------------------------------------
	ViewDebugger
	Create debug mOverlay and connect to a debug renderer

	@brief
	@param simulation
	@return
---------------------------------------------------------------------------------*/
ViewDebugger::ViewDebugger(Simulation* simulation)
{
	mSimulation = simulation;
	mController = NULL;
	mDebugView = VISUAL_NONE;
	mShowDebuggersCurrent = 0;
	mExpandedText = false;
	mForceVec = new SensorDecoratorVector(new SensorForce(mSimulation), Ogre::ColourValue(1, 1, 0),false);

	//Initialize debug GUI system
	float halfHeight = mSimulation->getScene()->getWindow().getHeight()/2.0f;
	float halfWidth = mSimulation->getScene()->getWindow().getWidth()/2.0f;

	mOverlay = Ogre::OverlayManager::getSingleton().create("Simulation.Debug");

	mDebugOverlay = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement(
						"Panel", "Simulation.WorldDebug"));

	mOverlay->add2D(mDebugOverlay);

	mDebugOverlayText = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "Simulation.WorldDebugText");
	mDebugOverlayText->setMetricsMode(Ogre::GMM_PIXELS);
	mDebugOverlayText->setLeft(10);
	mDebugOverlayText->setTop(10);
	mDebugOverlayText->setWidth(halfWidth);
	mDebugOverlayText->setHeight(halfHeight);
	mDebugOverlayText->setParameter("font_name", "Lucida");
	mDebugOverlayText->setParameter("char_height", "12");
	mDebugOverlayText->setParameter("horz_align", "left");
	mDebugOverlayText->setCaption("");
	mDebugOverlayText->setColour(Ogre::ColourValue(0, 0.8f, 0));

	mDebugOverlay->addChild(mDebugOverlayText);

	// show debug info mOverlay
	mOverlay->show();
	mSimulation->getWorld()->createDebugRenderer(&mSimulation->getScene()->getSceneManager());
	NxPhysicsSDK* physicsSDK = mSimulation->getWorld()->getSDK();
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_FORCE, 1);
	physicsSDK->setParameter(NX_VISUALIZATION_SCALE, Config::Instance().getVisualDebugScale());
	mSimulation->getWorld()->getPhysXDriver()->createDebuggerConnection("127.0.0.1");

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);

	mController = new SimulationInputControllerDebug(this);

	setDebug(VISUAL_BRIEF);
}

/**-------------------------------------------------------------------------------
	~ViewDebugger

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
ViewDebugger::~ViewDebugger(void)
{
	delete mForceVec;
	mForceVec = NULL;

	mShowDebuggers.clear();

	delete mController;
	mController = NULL;

	// remove frame listener
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);

	// delete debug info mOverlay
	mOverlay->hide();
	mSimulation->getWorld()->destroyDebugRenderer();
	mSimulation->getWorld()->getPhysXDriver()->destroyDebuggerConnection();

	Ogre::OverlayManager::getSingleton().destroyOverlayElement(mDebugOverlayText);
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(mDebugOverlay);
	Ogre::OverlayManager::getSingleton().destroy(mOverlay);
}

/**-------------------------------------------------------------------------------
	Frame started event
	update debug info

	\param deltaTime (float)
	\return (void)
-----------------------------------------------------------------------------*/
bool ViewDebugger::frameEnded(const Ogre::FrameEvent& evt)
{
	// show forces applied (with arrows)
	mForceVec->update();

	// update debug window info
	updateDebug();
	return true;
}


/**----------------------------------------------------------------------------
	Updates debug window with useful information

	\return (void)
 -----------------------------------------------------------------------------*/
void ViewDebugger::updateDebug()
{
	Link* selected = mSimulation->getSelectedObject();
	std::stringstream objectInfo;

	const char* simulationStatesText[] = {"STARTUP", "LOADING", "CANCEL LOADING", "PREPARING", "SIMULATING", "SHUTDOWN", "PAUSED"};
	objectInfo << "[" << simulationStatesText[mSimulation->getCurrentState()] << "] " <<
			   "Time: " << std::setw(8) << std::setprecision(4) << std::setfill(' ')  << mSimulation->getFrameTime() <<
			   " FPS: " << std::setw(6) << std::setprecision(4) << std::setfill(' ') << (1 / mSimulation->getTimeSinceLastRenderFrame()) <<
			   "  Td (PhysX): " << std::setw(6) << std::setprecision(3) << std::setfill(' ') <<  mSimulation->getTimeSinceLastPhysXFrame() << " ms";

	if (mExpandedText)
	{
		objectInfo << "\r\nShowing: " << getDebug();

		if (selected)
		{
			Ogre::SceneNode* node = mSimulation->getScene()->getSceneManager().getSceneNode(selected->getName());
			Ogre::Vector3 p = node->getPosition();
			Ogre::Vector3 axis;
			Ogre::Degree angle;
			node->getOrientation().ToAngleAxis(angle, axis);
			objectInfo << "\r\nSelected: " << selected->getName()
					   << "\n\rPosition: " << p << "\n\rOrientation: " << angle << " around " << axis;
		}

		objectInfo << mDebugDescription + mSimulation->getDescription();
	}

	mDebugOverlayText->setCaption(objectInfo.str());
}

/**-------------------------------------------------------------------------------
	setDebug

	@brief
	@param debugView
	@param show
	@return void
---------------------------------------------------------------------------------*/
void ViewDebugger::setDebug(DebugView debugView)
{
	mDebugView = debugView;

	NxPhysicsSDK* physicsSDK = mSimulation->getWorld()->getSDK();
	// clear all
	physicsSDK->setParameter(NX_VISUALIZE_WORLD_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_BODY_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_BODY_MASS_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 0);
	physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_VELOCITY, 0);
	physicsSDK->setParameter(NX_VISUALIZE_BODY_JOINT_GROUPS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_JOINT_LOCAL_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_JOINT_WORLD_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_JOINT_LIMITS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_FORCE_FIELDS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 0);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 0);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_ERROR, 0);
	physicsSDK->setParameter(NX_VISUALIZE_CONTACT_FORCE, 0);
	physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_AABBS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_AXES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_COMPOUNDS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_VNORMALS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_FNORMALS, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SPHERES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_STATIC, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_DYNAMIC, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_FREE, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_EDGES, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_CCD, 0);
	physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SKELETONS, 0);
	mShowDebuggers.clear();
	mShowDebuggersCurrent = 0;

	switch (mDebugView)
	{
		case VISUAL_NONE:
			break;
		case VISUAL_BRIEF:
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_POINT);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LOCAL_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SHAPES);
			break;

		case  VISUAL_EVERYTHING:
			mShowDebuggers.push_back(NX_VISUALIZE_WORLD_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_MASS_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_LIN_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_ANG_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_JOINT_GROUPS);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LOCAL_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_WORLD_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LIMITS);
			mShowDebuggers.push_back(NX_VISUALIZE_FORCE_FIELDS);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_POINT);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_NORMAL);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_ERROR);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_FORCE);
			mShowDebuggers.push_back(NX_VISUALIZE_ACTOR_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AABBS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SHAPES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_COMPOUNDS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_VNORMALS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_FNORMALS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SPHERES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_STATIC);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_DYNAMIC);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_FREE);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_EDGES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_CCD);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SKELETONS);
			break;

		case  VISUAL_BODIES:
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_MASS_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_LIN_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_ANG_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_JOINT_GROUPS);
			mShowDebuggers.push_back(NX_VISUALIZE_ACTOR_AXES);
			break;

		case  VISUAL_MOST:
			mShowDebuggers.push_back(NX_VISUALIZE_WORLD_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_LIN_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_ANG_VELOCITY);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LOCAL_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LIMITS);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_POINT);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_NORMAL);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AABBS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_COMPOUNDS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_STATIC);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_DYNAMIC);
			break;

		case  VISUAL_COLLISIONS:
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AABBS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SHAPES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_COMPOUNDS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_VNORMALS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_FNORMALS);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SPHERES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_STATIC);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_DYNAMIC);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_FREE);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_EDGES);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_CCD);
			mShowDebuggers.push_back(NX_VISUALIZE_COLLISION_SKELETONS);
			break;

		case  VISUAL_JOINTS:
			mShowDebuggers.push_back(NX_VISUALIZE_BODY_JOINT_GROUPS);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LOCAL_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_WORLD_AXES);
			mShowDebuggers.push_back(NX_VISUALIZE_JOINT_LIMITS);
			break;
		case  VISUAL_CONTACTS:
			mShowDebuggers.push_back(NX_VISUALIZE_FORCE_FIELDS);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_POINT);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_NORMAL);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_ERROR);
			mShowDebuggers.push_back(NX_VISUALIZE_CONTACT_FORCE);
	}

	std::for_each(mShowDebuggers.begin(), mShowDebuggers.end(), boost::bind(boost::mem_fn(&NxPhysicsSDK::setParameter), physicsSDK, _1, 1.0f));
}

/**-------------------------------------------------------------------------------
	getDebugDescription

	@brief
	@return std::string
---------------------------------------------------------------------------------*/
std::string ViewDebugger::getDebug()
{
	std::stringstream out;

	switch (mDebugView)
	{
		case VISUAL_NONE:
			out << "Nothing - ";
			break;
		case  VISUAL_BRIEF:
			out << "Brief - ";
			break;
		case  VISUAL_EVERYTHING:
			out << "Everything - ";
			break;

		case  VISUAL_BODIES:
			out << "Bodies - ";
			break;

		case  VISUAL_MOST:
			out << "Most - ";
			break;
		case VISUAL_CONTACTS:
			out << "Contacts - ";
			break;

		case  VISUAL_COLLISIONS:
			out << "Collisions - ";
			break;

		case  VISUAL_JOINTS:
			out << "Joints - ";
			break;
		default:
			out << "unknown - ";
	}

	NxPhysicsSDK* physicsSDK = mSimulation->getWorld()->getSDK();

	if (physicsSDK->getParameter(NX_VISUALIZE_WORLD_AXES) == 1.0) { out << "WORLD_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_BODY_AXES) == 1.0) { out << "BODY_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_BODY_MASS_AXES) == 1.0) { out << "BODY_MASS_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_BODY_LIN_VELOCITY) == 1.0) { out << "BODY_LIN_VELOCITY "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_BODY_ANG_VELOCITY) == 1.0) { out << "BODY_ANG_VELOCITY "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_BODY_JOINT_GROUPS) == 1.0) { out << "BODY_JOINT_GROUPS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_JOINT_LOCAL_AXES) == 1.0) { out << "JOINT_LOCAL_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_JOINT_WORLD_AXES) == 1.0) { out << "JOINT_WORLD_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_JOINT_LIMITS) == 1.0) { out << "JOINT_LIMITS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_FORCE_FIELDS) == 1.0) { out << "FORCE_FIELDS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_CONTACT_POINT) == 1.0) { out << "CONTACT_POINT "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_CONTACT_NORMAL) == 1.0) { out << "CONTACT_NORMAL "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_CONTACT_ERROR) == 1.0) { out << "CONTACT_ERROR "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_CONTACT_FORCE) == 1.0) { out << "CONTACT_FORCE "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_ACTOR_AXES) == 1.0) { out << "ACTOR_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_AABBS) == 1.0) { out << "COLLISION_AABBS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_SHAPES) == 1.0) { out << "COLLISION_SHAPES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_AXES) == 1.0) { out << "COLLISION_AXES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_COMPOUNDS) == 1.0) { out << "COLLISION_COMPOUNDS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_VNORMALS) == 1.0) { out << "COLLISION_VNORMALS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_FNORMALS) == 1.0) { out << "COLLISION_FNORMALS "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_SPHERES) == 1.0) { out << "COLLISION_SPHERES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_STATIC) == 1.0) { out << "COLLISION_STATIC "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_DYNAMIC) == 1.0) { out << "COLLISION_DYNAMIC "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_FREE) == 1.0) { out << "COLLISION_FREE "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_EDGES) == 1.0) { out << "COLLISION_EDGES "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_CCD) == 1.0) { out << "COLLISION_CCD "; }

	if (physicsSDK->getParameter(NX_VISUALIZE_COLLISION_SKELETONS) == 1.0) { out << "COLLISION_SKELETONS "; }

	return out.str();
}


/**-------------------------------------------------------------------------------
	toggle visible debuggers

	@brief
	@return void
---------------------------------------------------------------------------------*/
void ViewDebugger::toggleVisible()
{
	NxPhysicsSDK* physicsSDK = mSimulation->getWorld()->getSDK();
	std::for_each(mShowDebuggers.begin(), mShowDebuggers.end(), boost::bind(boost::mem_fn(&NxPhysicsSDK::setParameter), physicsSDK, _1, 0.0f));

	if (++mShowDebuggersCurrent >= mShowDebuggers.size())
	{
		mShowDebuggersCurrent = 0;
	}
	else
	{
		physicsSDK->setParameter(mShowDebuggers[mShowDebuggersCurrent], 1.0f);
	}
}
