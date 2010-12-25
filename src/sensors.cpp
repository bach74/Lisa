// =============================================================================
//  Sensors.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "sensors.h"
#include "config.h"
#include "sensorCOG.h"
#include "sensorCOP.h"
#include "sensorZMP.h"
#include "sensorDecorator.h"
#include "sensorDecoratorCross.h"
#include "SensorFRI.h"


/**-------------------------------------------------------------------------------
    Sensors

    @brief
    @param simulation
    @return
---------------------------------------------------------------------------------*/
Sensors::Sensors(Simulation* simulation)
{
	if (Config::Instance().getShowCOG())
	{
		// create center-of-gravity (COG) sensor
		SensorVectors* s = new SensorCOG(simulation);
		boost::shared_ptr<SensorVectors> cog(
			new SensorDecoratorCross(s, Ogre::ColourValue(0, 0, 1), Config::Instance().getDrawingScaleCOG()));
		mSensors.push_back(cog);
	}
	else
	{
		boost::shared_ptr<SensorVectors> cog(new SensorCOG(simulation));
		mSensors.push_back(cog);
	}


	// create center-of-pressure (COP) sensor	
	if (Config::Instance().getShowCOP())
	{
		SensorVectors* s = new SensorCOP(simulation);
		boost::shared_ptr<SensorVectors> cop(
			new SensorDecoratorCross(s, Ogre::ColourValue(0, 1, 0), Config::Instance().getDrawingScaleCOP()));
		mSensors.push_back(cop);
	}
	else
	{
		boost::shared_ptr<SensorVectors> cop(new SensorCOP(simulation));
		mSensors.push_back(cop);
	}

	// create (Zero-moment-point) ZMP sensor	
	if (Config::Instance().getShowZMP())
	{
		SensorVectors* s = new SensorZMP(simulation);
		boost::shared_ptr<SensorVectors> zmp(
			new SensorDecoratorCross(s, Ogre::ColourValue(1, 0, 1), Config::Instance().getDrawingScaleZMP()));
		mSensors.push_back(zmp);
	}
	else
	{
		boost::shared_ptr<SensorVectors> zmp(new SensorZMP(simulation));
		mSensors.push_back(zmp);
	}

	// create (Foot-rotation-index) FRI sensor	
	if (Config::Instance().getShowFRI())
	{
		SensorVectors* s = new SensorFRI(simulation);
		boost::shared_ptr<SensorVectors> fri(
			new SensorDecoratorCross(s, Ogre::ColourValue(0.42, 0.5624, 0.8492), Config::Instance().getDrawingScaleFRI()));
		mSensors.push_back(fri);
	}
	else
	{
		boost::shared_ptr<SensorVectors> fri(new SensorFRI(simulation));
		mSensors.push_back(fri);
	}

}

/**-------------------------------------------------------------------------------
    ~Sensors

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
Sensors::~Sensors(void)
{
	mSensors.clear();
}

/**-------------------------------------------------------------------------------
    update

    @brief
    @return void
---------------------------------------------------------------------------------*/
void Sensors::update()
{
	BOOST_FOREACH(boost::shared_ptr<SensorVectors> s, mSensors)
	{
		s->update();
	}
}

/**-------------------------------------------------------------------------------
    getVectorVectorSensor

    @brief
    @param sensorName
    @return SensorVectors*
---------------------------------------------------------------------------------*/
SensorVectors* Sensors::getSensor(const std::string& sensorName) const
{
	BOOST_FOREACH(boost::shared_ptr<SensorVectors> s, mSensors)
	{
		if (s->getSensorName() == sensorName)
		{
			return s.get();
		}
	}
	return NULL;
}