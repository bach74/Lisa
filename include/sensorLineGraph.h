// =============================================================================
//  SensorLineGraph.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORLINEGRAPH_H__
#define __SENSORLINEGRAPH_H__

#include "lineGraphWidget.h"
#include "sensor.h"

class SensorLineGraph : public LineGraphWidget, public Ogre::FrameListener
{
	public:
		SensorLineGraph(SensorVectors* sensor, const char* uniqueName, float parentTop, float parentLeft,
				float parentBottom, float parentRight, float xProp, float yProp, float width, float height,
				Ogre::SceneManager* sceneManager);

		virtual ~SensorLineGraph();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		void show();
		void hide();

	private:
		SensorVectors* mSensor;

};

 #endif