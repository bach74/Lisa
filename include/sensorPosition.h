// =============================================================================
//  SensorPosition.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORPOSITION_H__
#define __SENSORPOSITION_H__
#include "sensor.h"

// forward declaration
class Joint;

class SensorPosition : public Sensor<double, Joint>
{
	public:
		SensorPosition(Joint* joint):Sensor(joint,"pos"){};
		~SensorPosition(){};
	
		// note that returned angle is in range (-3.14,3.14)
		void update() { setValue(getDataclass()->getAngle()); }		
};

 #endif