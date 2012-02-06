// =============================================================================
//  SensorTorque.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORTORQUE_H__
#define __SENSORTORQUE_H__

#include "sensor.h"

// forward declaration
class Joint;

class SensorTorque : public Sensor<double, Joint>
{
	public:
		SensorTorque(Joint* joint):Sensor(joint,"torque"){};
		~SensorTorque(){};
	
		void update() { setValue(getDataclass()->getTorque()); }		
};

 #endif