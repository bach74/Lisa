#pragma once
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
