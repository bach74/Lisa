// =============================================================================
//  sensorCOG.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORCOG_H__
#define __SENSORCOG_H__

#include "sensor.h"

class SensorCOG : public SensorVectors
{
	public:
		SensorCOG(Simulation* simulation):Sensor(simulation,"COG"){};
		~SensorCOG(void){};

	protected:
		virtual void update();

};

 #endif