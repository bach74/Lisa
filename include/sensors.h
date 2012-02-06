// =============================================================================
//  Sensors.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORS_H__
#define __SENSORS_H__

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

 #endif