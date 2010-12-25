// =============================================================================
//  MySceneController.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __MYSCENECONTROLLER_H__
#define __MYSCENECONTROLLER_H__
#include "NxOgrePrerequisites.h"
#include <NxOgreSceneController.h>

class MySceneController : public NxOgre::SceneController
{
		friend class Scene;

	public:

		MySceneController::MySceneController(NxOgre::Scene* scene);
		virtual ~MySceneController(void);

		virtual Ogre::String getType() const {return Ogre::String("Accumulator");}
		virtual void setTiming(NxSceneDesc& desc, NxReal maxTimestep, NxU32 maxIter, NxU32 numSubSteps);
		virtual void setTiming(NxReal maxTimestep, NxU32 maxIter, NxU32 numSubSteps);
		virtual void init(NxScene*);
		virtual NxOgre::TimeStep Simulate(NxReal);

	private:
		Ogre::Timer* mTimer;


		NxF64     mMaxStep;
		NxF64     mAccumulator;
		NxReal    mAlpha;
		NxU32     mPreviousTime;

};

 #endif