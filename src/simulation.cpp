// =============================================================================
//  Simulation.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "simulation.h"

/**-------------------------------------------------------------------------------
	Simulation

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
Simulation::Simulation(void)
{
	mWorld=NULL;
	mScene=NULL;
	mFrameTime=0;
	mTimeSinceLastPhysXFrame=0;
	mTimeSinceLastRenderFrame=0;
	mState=STARTUP;
	mLocked=false;
	mLinks=NULL;
	mActuators = NULL;

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

/**-------------------------------------------------------------------------------
	~Simulation

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
Simulation::~Simulation(void)
{
	delete mActuators;
	mActuators = NULL;

	// remove frame listener
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);
}

/**-------------------------------------------------------------------------------
	lock state

	\return (bool)
 -----------------------------------------------------------------------------*/
bool Simulation::lockState(SimulationState newState)
{
	bool ret=false;

	{
		CritSectEx::Scope scope(myCs);
	
		if (mLocked==false)
		{
			mState=newState;
			mLocked=true;
			ret=true;
		}
	}

	return ret;
}

/**-------------------------------------------------------------------------------
	unlock state

	\return (bool)
 -----------------------------------------------------------------------------*/
bool Simulation::unlockState()
{
	bool ret=false;

	{
		CritSectEx::Scope scope(myCs);
		if (mLocked==true)
		{
			mLocked=false;
			ret=true;
		}
	}

	return ret;
}
