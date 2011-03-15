/** \file    NxOgreSceneController.cpp
 *  \see     NxOgreSceneController.h
 *  \version 1.0-20
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *           version 2.1 of the License, or (at your option) any later version.
 *           
 *           This library is distributed in the hope that it will be useful,
 *           but WITHOUT ANY WARRANTY; without even the implied warranty of
 *           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received a copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "NxOgreStable.h"
#include "NxOgreSceneController.h"
#include "NxOgreScene.h"
#include "NxOgreTimeStep.h"

#include "NxOgreTimer.h"

#include "Nx.h"

#ifdef WIN32 
	#define NOMINMAX
	#include <windows.h>
#endif

namespace NxOgre {

///////////////////////////////////////////////////////////////////////

SceneController::SceneController(Scene* scene) : mScene(scene) {}

///////////////////////////////////////////////////////////////////////

SceneController::~SceneController() {}

///////////////////////////////////////////////////////////////////////

void SceneController::setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {

}

///////////////////////////////////////////////////////////////////////

void SceneController::setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {

}

///////////////////////////////////////////////////////////////////////

void SceneController::init(NxScene* nxscene) {
	NxDebug("SceneController Initalised");
}

///////////////////////////////////////////////////////////////////////

TimeStep SceneController::Simulate(NxReal deltaTime) {

	mNxScene->simulate(deltaTime);
	mNxScene->flushStream();

	while (!mNxScene->fetchResults(NX_RIGID_BODY_FINISHED, false))
		;

	TimeStep ts;
	ts.Delta = deltaTime;
	ts.Alpha = 1.0f;

	return ts;
}

///////////////////////////////////////////////////////////////////////

VariableSceneController::VariableSceneController(Scene* scene) : SceneController(scene) {}


///////////////////////////////////////////////////////////////////////

VariableSceneController::~VariableSceneController() {}

///////////////////////////////////////////////////////////////////////

void VariableSceneController::init(NxScene* nxscene) {
	NxDebug("VariableSceneController Initalised");
	mNxScene = nxscene;
}
///////////////////////////////////////////////////////////////////////

void VariableSceneController::setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {

}

///////////////////////////////////////////////////////////////////////

void VariableSceneController::setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {
	desc.maxIter = matIter;
	desc.timeStepMethod = NX_TIMESTEP_VARIABLE;
}

///////////////////////////////////////////////////////////////////////

TimeStep VariableSceneController::Simulate(NxReal deltaTime) {

	mNxScene->simulate(deltaTime);
	mNxScene->flushStream();

	while (!mNxScene->fetchResults(NX_RIGID_BODY_FINISHED, false))
		;

	TimeStep ts;
	ts.Delta = deltaTime;
	ts.Alpha = 1.0f;

	return ts;
}

///////////////////////////////////////////////////////////////////////

FixedSceneController::FixedSceneController(Scene* scene) : SceneController(scene) {
}


///////////////////////////////////////////////////////////////////////

FixedSceneController::~FixedSceneController() {

}

///////////////////////////////////////////////////////////////////////

void FixedSceneController::init(NxScene* nxscene) {

#if (NX_DEBUG == 1)
	NxDebug("FixedSceneController Initalised");
#endif
	mNxScene = nxscene;

}

///////////////////////////////////////////////////////////////////////

void FixedSceneController::setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {
	
	mTiming_MaxStep = maxTimestep;
	mTiming_CurrentStep = 0.0f;

}

///////////////////////////////////////////////////////////////////////

void FixedSceneController::setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {
	
	mTiming_MaxStep = maxTimestep;
	mTiming_CurrentStep = 0.0f;

	desc.maxTimestep = mTiming_MaxStep;
	desc.maxIter = matIter;
	desc.timeStepMethod = NX_TIMESTEP_FIXED;

}

///////////////////////////////////////////////////////////////////////

TimeStep FixedSceneController::Simulate(NxReal deltaTime) {

	mTiming_CurrentStep += deltaTime;

	if (mTiming_CurrentStep < mTiming_MaxStep) {
		TimeStep ts;ts.Delta = 0;
		return ts;
	}

	TimeStep ts;
	ts.Delta = mTiming_MaxStep - (mTiming_MaxStep - mTiming_CurrentStep);

	mNxScene->simulate(ts.Delta);
	mNxScene->flushStream();

	while(!mNxScene->checkResults(NX_RIGID_BODY_FINISHED, false))
		;

	mNxScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	
	mTiming_CurrentStep=0;

	return ts;
}

///////////////////////////////////////////////////////////////////////

AccumulatorSceneController::AccumulatorSceneController(Scene* scene) : SceneController(scene) {
	mTimer = new Timer();
}

///////////////////////////////////////////////////////////////////////

AccumulatorSceneController::~AccumulatorSceneController() {
	delete mTimer;
}

///////////////////////////////////////////////////////////////////////

void AccumulatorSceneController::init(NxScene* nxscene) {
	mNxScene = nxscene;
	mTimer->reset();
}

///////////////////////////////////////////////////////////////////////


void AccumulatorSceneController::setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {
	mMaxStep = maxTimestep;
}

///////////////////////////////////////////////////////////////////////

void AccumulatorSceneController::setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps) {

	desc.maxTimestep = maxTimestep;
	desc.maxIter = matIter;
	desc.timeStepMethod = NX_TIMESTEP_FIXED;
	mMaxStep = maxTimestep;
	mAccumulator = 0;

}

///////////////////////////////////////////////////////////////////////

TimeStep AccumulatorSceneController::Simulate(NxReal) {

	double deltaTime = mTimer->micro() * 1.0e-6;
	if( deltaTime > 0.2 ) // 5hz
	{
		mTimer->reset();
		deltaTime = 0.2;
	}

	mAccumulator += deltaTime;

	while (mAccumulator >= mMaxStep) {
		mNxScene->simulate(mMaxStep);
		mNxScene->flushStream();
		mNxScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		mAccumulator -= mMaxStep;
	}

	mAlpha = mAccumulator / mMaxStep;
	mTimer->reset();

	TimeStep ts;
	ts.Delta = mMaxStep;
	ts.Alpha = mAlpha;

	return ts;

}

///////////////////////////////////////////////////////////////////////


}; //End of NxOgre namespace.
