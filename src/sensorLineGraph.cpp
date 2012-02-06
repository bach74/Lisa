// =============================================================================
//  SensorLineGraph.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "sensorLineGraph.h"

/**-------------------------------------------------------------------------------
    SensorLineGraph

    @brief
    @param sensor
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
SensorLineGraph::SensorLineGraph(SensorVectors* sensor, const char* uniqueName, float parentTop,
                                 float parentLeft, float parentBottom, float parentRight, float xProp,
								 float yProp, float width, float height, Ogre::SceneManager* sceneManager)
	: LineGraphWidget(uniqueName, parentTop, parentLeft, parentBottom, parentRight, xProp, yProp, width, height, sceneManager)
{
	mSensor = sensor;

	if (mSensor == NULL)
	{
		throw Exception("Sensor parameter is NULL", "SensorLineGraph");
	}

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

/**-------------------------------------------------------------------------------
    ~SensorLineGraph

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
SensorLineGraph::~SensorLineGraph(void)
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
bool SensorLineGraph::frameEnded(const Ogre::FrameEvent& evt)
{
	float t = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() / 1000.0f;

	if (mSensor->getDataValid())
	{
		std::vector<Ogre::Vector3> values;
		mSensor->getValue(values);
		Ogre::Vector3 val(values.front());
		//addPointToLine(0, t, val[0]);
		addPointToLine(1, t, val[2]);
	}

	return true;
}
