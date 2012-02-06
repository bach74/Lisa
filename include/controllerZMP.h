// =============================================================================
//  ControllerZMP.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONTROLLERZMP_H__
#define __CONTROLLERZMP_H__

#include "controller.h"
#include "sensor.h"
#include "actuator.h"

class ControllerZMP : public Controller<double>, public LoggerWriter<ControllerZMP>
{
	public:
		ControllerZMP(SensorVectors& sensorZMP, SensorVectors& sensorCOP, SensorVectors& sensorCOG,
					std::vector<boost::shared_ptr<Actuator > >& actuators, const char* filename);
		~ControllerZMP();

		virtual double calculate(double sampleTime);
		virtual double calculate(double error, double sampleTime);

		double CalculateOutput(float t, double sampleTime);

	private:
		SensorVectors& mSensorZMP;
		SensorVectors& mSensorCOP;
		SensorVectors& mSensorCOG;
		std::vector<boost::shared_ptr<Actuator > >& mActuators;

};

 #endif