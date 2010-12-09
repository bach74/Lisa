#pragma once
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
