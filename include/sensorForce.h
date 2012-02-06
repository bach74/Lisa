// =============================================================================
//  SensorForce.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORFORCE_H__
#define __SENSORFORCE_H__

#include "sensor.h"

/**-------------------------------------------------------------------------------
    SensorForce has two parameters: position and strength
---------------------------------------------------------------------------------*/
class SensorForce : public SensorVectors
{
	public:
		SensorForce(Simulation* simulation): Sensor(simulation, "ForceSensor") { setDataValid(false); };
		~SensorForce(){};
	private:
		virtual void update(){};
};

 #endif