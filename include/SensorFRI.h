// =============================================================================
//  SensorFRI.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORFRI_H__
#define __SENSORFRI_H__
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

 #endif