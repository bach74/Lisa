#pragma once
#include "sensor.h"

class SensorCOG : public SensorVectors
{
	public:
		SensorCOG(Simulation* simulation):Sensor(simulation,"COG"){};
		~SensorCOG(void){};

	protected:
		virtual void update();

};
