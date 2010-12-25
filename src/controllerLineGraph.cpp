// =============================================================================
//  ControllerLineGraph.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "ControllerlineGraph.h"

/**-------------------------------------------------------------------------------
	ControllerLineGraph
	
	@brief
	@param controller
	@param uniqueName
	@param parentTop
	@param parentLeft
	@param parentBottom
	@param parentRight
	@param xProp
	@param yProp
	@param sceneManager
	@return 
---------------------------------------------------------------------------------*/
ControllerLineGraph::ControllerLineGraph(Controller<double>* controller,const char* uniqueName, float parentTop,
										float parentLeft, float parentBottom, float parentRight, float xProp,
										float yProp, float width, float height, Ogre::SceneManager* sceneManager):
					LineGraphWidget(uniqueName,parentTop,parentLeft,parentBottom,parentRight,xProp,yProp,width,height,sceneManager)
{
	mController = controller;

	if (mController == NULL)
	{
		throw Exception("Controller parameter is NULL", "ControllerLineGraph");
	}

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

/**-------------------------------------------------------------------------------
	~ControllerLineGraph
	
	@brief
	@param 
	@return 
---------------------------------------------------------------------------------*/
ControllerLineGraph::~ControllerLineGraph(void)
{
	// remove frame listener
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);
}

/**-------------------------------------------------------------------------------
     frameEnded is FrameListener callback

     @brief
     @param evt
     @return void
---------------------------------------------------------------------------------*/
bool ControllerLineGraph::frameEnded(const Ogre::FrameEvent& evt)
{
	float t = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()/1000.0f;

	double Sp;
	double Pv;
	double Uc;
	mController->getSetpoint(Sp);
	mController->getInput(Pv);
	mController->getOutput(Uc);
	addPointToLine(0, t, Sp);
	addPointToLine(1, t, Pv);
	//double err = Sp - Pv;
	//addPointToLine(2, t, Uc);

	return true;
}