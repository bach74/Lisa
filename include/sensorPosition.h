#pragma once
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
