#pragma once

#include "sensor.h"
#include "simulation.h"

/**----------------------------------------------------------------------------
   Maintain sensors

   \param simulation (Simulation *)
   \return ()
 -----------------------------------------------------------------------------*/
class Sensors
{
	public:
		Sensors(Simulation* simulation);
		~Sensors();

		void update();

		SensorVectors* getSensor(const std::string& sensorName) const;

	private:
		// A collection of vector sensors
		std::vector<boost::shared_ptr<SensorVectors> > mSensors;
};
