#pragma once
#include "sensor.h"

class SensorFRI : public SensorVectors
{
	public:
		SensorFRI(Simulation* simulation) : Sensor(simulation,"FRI"){}
		~SensorFRI(void);

	protected:
		virtual void update();

	private:
};