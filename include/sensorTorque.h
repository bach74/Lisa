#pragma once
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
