// =============================================================================
//  mySceneController.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "mySceneController.h"


/**-------------------------------------------------------------------------------
    MySceneController

    @brief
    @param scene
    @return
---------------------------------------------------------------------------------*/
MySceneController::MySceneController(NxOgre::Scene* scene) : NxOgre::SceneController(scene)
{
	mTimer = new Ogre::Timer();
	mNxScene = scene->getNxScene();
}

/**-------------------------------------------------------------------------------
    ~MySceneController

    @brief
    @return
---------------------------------------------------------------------------------*/
MySceneController::~MySceneController()
{
	delete mTimer;
}

/**-------------------------------------------------------------------------------
    init

    @brief
    @param nxscene
    @return void
---------------------------------------------------------------------------------*/
void MySceneController::init(NxScene* nxscene)
{
	mNxScene = nxscene;
	mTimer->reset();
}

/**-------------------------------------------------------------------------------
    setTiming

    @brief
    @param maxTimestep
    @param matIter
    @param numSubSteps
    @return void
---------------------------------------------------------------------------------*/
void MySceneController::setTiming(NxReal maxTimestep, NxU32 maxIter, NxU32 numSubSteps)
{
	mMaxStep = maxTimestep;
	mAccumulator = 0;
	mNxScene->setTiming(maxTimestep, maxIter, NX_TIMESTEP_VARIABLE);
}

/**-------------------------------------------------------------------------------
    setTiming

    @brief
    @param desc
    @param maxTimestep
    @param matIter
    @param numSubSteps
    @return void
---------------------------------------------------------------------------------*/
void MySceneController::setTiming(NxSceneDesc& desc, NxReal maxTimestep, NxU32 maxIter, NxU32 numSubSteps)
{
	setTiming(maxTimestep, maxIter, numSubSteps);
}

/**-------------------------------------------------------------------------------
    Simulate

	ideal asynchronous 
	while(1) {
		scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		fewCalcs();
		scene->flushStream();
		scene->simulate(deltaTime);
		moreCalcs();
	}

    @brief
    @param
    @return NxOgre::TimeStep
---------------------------------------------------------------------------------*/
NxOgre::TimeStep MySceneController::Simulate(NxReal)
{
	double deltaTime = mTimer->getMicroseconds() * 1.0e-6;

	if (deltaTime > 0.2)  // 5hz
	{
		mTimer->reset();
		deltaTime = 0.2;
	}

	mAccumulator += deltaTime;

	while (mAccumulator >= mMaxStep)
	{
		mNxScene->simulate(mMaxStep);
		mNxScene->flushStream();
		mNxScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		mAccumulator -= mMaxStep;
	}

	mAlpha = mAccumulator / mMaxStep;
	mTimer->reset();

	NxOgre::TimeStep ts;
	ts.Delta = mMaxStep;
	ts.Alpha = mAlpha;

	return ts;
}
