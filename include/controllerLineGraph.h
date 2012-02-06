// =============================================================================
//  ControllerLineGraph.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONTROLLERLINEGRAPH_H__
#define __CONTROLLERLINEGRAPH_H__

#include "linegraphwidget.h"
#include "controller.h"

class ControllerLineGraph : public LineGraphWidget, public Ogre::FrameListener
{
	public:
		ControllerLineGraph(Controller<double>* controller, const char* uniqueName, float parentTop, float parentLeft,
		                    float parentBottom, float parentRight, float xProp, float yProp, float width, float height,
							Ogre::SceneManager* sceneManager);
		~ControllerLineGraph();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);

	private:
		Controller<double>* mController;
};

 #endif