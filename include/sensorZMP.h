// =============================================================================
//  SensorZMP.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORZMP_H__
#define __SENSORZMP_H__

#include "sensor.h"

class SensorZMP : public SensorVectors
{
	public:
		SensorZMP(Simulation* simulation) : Sensor(simulation,"ZMP"){}
		~SensorZMP(void){};

	protected:
		virtual void update();

	private:
};

 #endif