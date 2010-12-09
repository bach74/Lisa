#pragma once
#include "controller.h"
#include "jFuzzyQt.h"
#include "sensor.h"
#include "actuator.h"

class ControllerZMP : public Controller<double>
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
		jfuzzyqt::JFuzzyQt mController;
		std::vector<boost::shared_ptr<Actuator > >& mActuators;
};
