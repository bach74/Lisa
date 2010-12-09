#pragma once
#include "sensor.h"

class SensorZMP : public SensorVectors
{
	public:
		SensorZMP(Simulation* simulation) : Sensor(simulation,"ZMP"){}
		~SensorZMP(void);

	protected:
		virtual void update();

	private:
};