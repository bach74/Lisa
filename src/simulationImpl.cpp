// =============================================================================
//  simulation.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================

#include "stdafx.h"
#include "colladafile.h"
#include "config.h"
#include "extendedCamera.h"
#include "linkIterator.h"
#include "misc.h"
#include "mySceneController.h"
#include "simulationInputController.h"
#include "simulationImpl.h"
#include "sensors.h"
#include "trajectory.h"
#include "scene.h"
#include "actuators.h"
#include "Controller.h"
#include "joint.h"


/**----------------------------------------------------------------------------
   create Scene
	initialize critical section used for changing states
	register mouse and key listeners

   \param my_scene (Scene *)
   \return ()
 -----------------------------------------------------------------------------*/
SimulationImpl::SimulationImpl(Scene* _scene)
{
	// setup Scene pointer
	mScene = _scene;

	requestStateChange(Simulation::STARTUP);

	mInputController = boost::shared_ptr<SimulationInputController>(new SimulationInputController(this));

	// create "physical" world
	NxOgre::PhysXParams worldParams;
	worldParams.setToDefault();
	worldParams.mUseLog = true;
	worldParams.mFlags.parse("FrameListener: no");
	//worldParams.mInitResources=false;
	mWorld = boost::shared_ptr<NxOgre::World>(new NxOgre::World(worldParams));

	// create scene
	NxOgre::SceneParams sceneParams;
	sceneParams.setToDefault();
	sceneParams.mFloor = false;
	NxOgre::SceneParams::SceneFlags sceneFlags;
	sceneFlags.toDefault();
	sceneFlags.mForceConeFriction=true; // NX_SF_FORCE_CONE_FRICTION
	sceneParams.mSceneFlags=sceneFlags;
	// create our custom scene controller
	sceneParams.mController = NxOgre::SceneParams::CN_PTR;
	sceneParams.mRenderer = NxOgre::SceneParams::RN_OGRE;
	sceneParams.mGravity = NxVec3(0, -9.80665f, 0);
	mPhyScene = boost::shared_ptr<NxOgre::Scene>(mWorld->createScene(THE_WORLD, &mScene->getSceneManager(), sceneParams));

	// void setTiming(NxReal maxTimestep=1.0f/60.0f, NxU32 maxIter=8, NxTimeStepMethod method=NX_TIMESTEP_FIXED);

	// Timing parameters can also be set in the scene descriptor prior to scene construction.
	// The default settings are appropriate for most applications.

	// Using fixed time sub steps is very important to ensure a stable and reproducible simulation and is recommended
	// for most applications, specified using NX_TIMESTEP_FIXED.
	// Recommended Time Stepping Method
	// The recommended time stepping method for a typical application is fixed time steps where maxTimestep
	// is an exact multiple of elapsedTime and elapsedTime is a constant.
	// This way, the user knows the number of sub steps taken, which do not vary. (elapsedTime is the parameter passed to simulate())

	// The advantage is that the behavior, when applying forces and moving kinematic actors, is deterministic.
	// If the user executes a variable number of sub steps on each call to simulate, then the time period over
	// which forces are applied and kinematic actors move will vary (causing the velocity of kinematic actors to vary).
	// When accounting for variable frame rates, the user can make multiple calls to simulate, with new values supplied
	// to moveGlobalPose() and addForce(), etc.

	// Example
	// NxScene* gScene;
	// NxReal myTimestep = 1.0f/60.0f;
	// gScene->setTiming(myTimestep / 4.0f, 4, NX_TIMESTEP_FIXED);

	// setup custom scene controller - it will be deleted automatically by NxOgre
	MySceneController* sceneController = new MySceneController(mPhyScene.get());
	sceneController->setTiming(1.0f/100.0f, 250, 0);
	mPhyScene->setSceneController(sceneController);

	NxScene* pScene = mPhyScene->getNxScene();
	if (pScene)
	{
		// get timing parameters
		NxTimeStepMethod method;
		NxU32   maxIter, numSubs;
		NxReal  maxStep;
		pScene->getTiming(maxStep, maxIter, method, &numSubs);
		std::stringstream ss;
		ss << "Max step: " << maxStep << " Max Iterations: " << maxIter << " Method" << method << "  numSubsteps: " << numSubs << std::endl;
		NxOgre::NxDebug(ss.str().c_str());
	}
	else
	{
		MessageBox(NULL, _T("Scene cannot be created!"), _T("Error in SimulationImpl::SimulationImpl"), MB_ICONEXCLAMATION);
	}

}

/**-------------------------------------------------------------------------------
	destroy objects created in the constructor
--------------------------------------------------------------------------------*/
SimulationImpl::~SimulationImpl()
{
	mWorld->destroyScene(THE_WORLD);
}


/**-------------------------------------------------------------------------------
	loads a new scene

	\param filename (std::string &)
	\return (void)
 -----------------------------------------------------------------------------*/
void SimulationImpl::loadScene(const std::string& filename)
{
	requestStateChange(LOADING);

	// try loading collada file
	NxuOgre* file = new NxuOgre(mWorld->getSDK(), mPhyScene->getNxScene());

	bool loaded = false;

	try
	{
		// add floor (physical level, visual level is defined elsewhere)
		// we have to add NX_SF_POINT_CONTACT_FORCE to the floor
		NxOgre::ShapeParams params;
		params.mFlags |= NX_SF_POINT_CONTACT_FORCE;
		NxOgre::Ground* shp = new NxOgre::Ground(0, NxVec3(0, 1, 0), params);
		/*NxOgre::Actor* floor =*/ mPhyScene->createActor(mPhyScene->getName() + ".floor", shp, NxOgre::Pose(), "static: yes");

		// load a scene and create "all things beneath the sun"
		loaded = file->LoadScene(mWorld.get(), filename.c_str());

		if (loaded)
		{
			// TODO:: this should be loaded from the .dae file
			//mPhyScene->hasGravity();

			// create Links structure from nxOgre::Actors
			mLinks = boost::shared_ptr<Links>(new Links());
			// iterate through actors
			NxOgre::Actors::Iterator it = mPhyScene->getActors()->mItems.begin();

			for (; it != mPhyScene->getActors()->mItems.end(); ++it)
			{
				NxOgre::Actor* body = it->second.t;
				boost::shared_ptr<Link> link(new Link(body));
				mLinks->add(link);
			}

			// create trajectory instance
			// trajectory description is contained in the same collada file
			mTrajectory=boost::shared_ptr<Trajectory>(new Trajectory(filename));

			// done loading - prepare scene is a next step
			requestStateChange(PREPARE);
			// done preparing
		}
		else
		{
			throw Exception(filename + std::string(" was not found!"), "SimulationImpl::LoadScene()");
		}
	}
	catch (Exception& ex)
	{
		MessageBox(NULL, ex.getDescription(), _T("Error loading scene"), MB_ICONERROR);
	}

	delete file;
	file = NULL;

}

/**-------------------------------------------------------------------------------
	prepare simulation event
	this is normally done after the scene loading so user can initialize
	new bodies and setup the initial positions

	\return (void)
 -----------------------------------------------------------------------------*/
void SimulationImpl::onPrepareSimulation()
{
	mScene->getCamera().getOgreCamera()->setPosition(28, 44, 42);

	//LogManager::getSingleton().logMessage(Ogre::LML_NORMAL,DumpNodes(mSceneMgr->getRootSceneNode()).c_str());
	
	// Create sensors according to the config file
	mSensors = boost::shared_ptr<Sensors>(new Sensors(this));

	// create jointControllers
	mActuators = boost::shared_ptr<Actuators>(new Actuators(mPhyScene.get(), mSensors.get()));

	// create pose controller
	std::vector<boost::shared_ptr<Actuator > >* actuators=new std::vector<boost::shared_ptr<Actuator>>();
	ActuatorIterator it(mActuators.get());
	for (;!it.end();++it) {
		actuators->push_back(it.get());
	}

	// load trajectory now after the actuators have been instantiated
	mTrajectory->load(*actuators);
}

/**-------------------------------------------------------------------------------
	frame started event

	\return (void)
 -----------------------------------------------------------------------------*/
bool SimulationImpl::frameStarted(const Ogre::FrameEvent& evt)
{
	getWorld()->render(evt.timeSinceLastFrame);
	return true;
}

/**-------------------------------------------------------------------------------
	frame ended event

	\param deltaTime (float)
	\return (void)
 -----------------------------------------------------------------------------*/
bool SimulationImpl::frameEnded(const Ogre::FrameEvent& evt)
{
	//getWorld()->getPhysXDriver()->frameEnded(evt);
	return true;
}

/**-------------------------------------------------------------------------------
	simulate
	
	@brief
	@param timeSinceLastFrame
	@return void
---------------------------------------------------------------------------------*/
void SimulationImpl::simulate(float timeSinceLastFrame)
{
	setTimeSinceLastPhysXFrame(timeSinceLastFrame);

	// call nxOgre frame started (physX simulate)
	if (getCurrentState() == SIMULATING)
	{
		float t=getFrameTime();

		// get data from trajectory planner
		// trajectory set-point
		mTrajectory->setTime(t);
		mTrajectory->update();

		mActuators->update(t);

		if (Config::Instance().getKeepAlive())
		{
			NxOgre::Actors::Iterator it = mPhyScene->getActors()->mItems.begin();
			for (; it != mPhyScene->getActors()->mItems.end(); ++it)
			{
				((NxOgre::Actor*)(it->second.t))->wakeUp();
			}
		}

		getWorld()->simulate(timeSinceLastFrame);

		mSensors->update();

		// set link values for the next step
		Links::iterator itLink(mLinks.get());
		Ogre::Vector3 pos;
		for (;!itLink.end();++itLink)
		{	
			Link& l=*itLink;
			if (l.isDynamic()) {
				l.setPrevVelocity(l.getLinearVelocity());
				l.setPrevAngularMomentum(l.getAngularMomentum());
			}
		}
	}

}

/**-------------------------------------------------------------------------------
	capture input devices

	The reason "capture" is a separate function and should not called within the frameEnded
	or frameStarted method is that if it were so it would not be possible to
	remove frame-listeners when the corresponding key is pressed. During the framestart
	and frame-ended event iterator (that is frame-listener iterator) cannot be changed
	and removal is postponed for the subsequent call.

	As the debug, info and graph windows are frame-listeners, removing/adding them in the
	key-press handling becomes more cumbersome if capture is not called after the render pass.

	@brief
	@return void
---------------------------------------------------------------------------------*/
void SimulationImpl::capture()
{
	// capture input devices every frame
	mInputController->capture();
}


/**-------------------------------------------------------------------------------
	simulateZoom

	@brief
	@param distance
	@return void
---------------------------------------------------------------------------------*/
void SimulationImpl::simulateZoom(short distance)
{
	OIS::MouseState ms;
	ms.Z.rel = (int)(Config::Instance().getCameraZoomSpeed()*(distance));
	mInputController->onRightMouseClick(ms);
}

/**-------------------------------------------------------------------------------
	return controller values

	@brief
	@return std::string
---------------------------------------------------------------------------------*/
std::string SimulationImpl::getDescription()
{
	ActuatorIterator it = ActuatorIterator(mActuators.get());

	std::stringstream text;
	int i = 0;

	for (; !it.end(); ++it, ++i)
	{
		Actuator& actuator = *it;
		double ret = 0;
		actuator.getController()->getSetpoint(ret);
		text << "Ref[" << i << "]: " << ret
			 << "  Theta[" << i << "]: " << (Ogre::Real)actuator.getJoint()->getAngle()
			 << "  Omega[" << i << "]: " << (Ogre::Real)actuator.getJoint()->getVelocity()
			 << "  L[" << i << "]: " << (Ogre::Real) - actuator.getJoint()->getAngularMomentum()
			 << "\r\n";
	}

	return text.str();
}

/**-------------------------------------------------------------------------------
	change state

	\param newState (SimulationState)
	\return (bool)
 -----------------------------------------------------------------------------*/
bool SimulationImpl::requestStateChange(SimulationState newState)
{
	bool ret = false;

	if ((newState != getCurrentState()) && (getCurrentState() != SHUTDOWN))
	{
		if (lockState(newState))
		{
			switch (newState)
			{
				case SHUTDOWN:
					// this state cannot be changed once initiated
					break;
				case SIMULATING:
					break;
				case LOADING:
				case CANCEL_LOADING:
					break;
				case PREPARE:
					onPrepareSimulation();
					break;
				case STARTUP:
					break;
				case PAUSED:
					break;
			}

			unlockState();
			ret = true;
		}
		else
		{
			throw new Exception("State cannot be locked!","simulationImpl.cpp");
		}
	}

	return ret;
}

/**-------------------------------------------------------------------------------
	getSelectedObject

	@brief
	@return Link*
---------------------------------------------------------------------------------*/
Link* SimulationImpl::getSelectedObject() const
{
	Link* link = NULL;

	LinkIterator it = LinkIterator(mLinks.get());

	for (; !it.end(); ++it)
	{
		if (it->getName() + "-entity" == mInputController->getSelectedObject())
		{
			link = &(*it);
			break;
		}
	}

	return link;
}
