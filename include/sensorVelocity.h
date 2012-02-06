// =============================================================================
//  SensorVelocity.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORVELOCITY_H__
#define __SENSORVELOCITY_H__
#include "sensor.h"

// forward declaration
class Joint;

class SensorVelocity : public Sensor<double, Joint>
{
	public:
		SensorVelocity(Joint* joint):Sensor(joint,"vel"){};
		~SensorVelocity(){};
	
		void update() { setValue(getDataclass()->getVelocity()); }		
};

 #endif