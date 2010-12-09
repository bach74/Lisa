#pragma once

#include "controller.h"

class ControllerPID : public Controller<double>
{
	private:
		double Kp;          // integral gain
		double Ti;          // proportional gain
		double Td;          // derivative gain
		double maxOutput;     // maximum_output

		enum
		{
			UCKM1 = 0,      // Uc(k-1) , controller output (k-1)
			ERRORKM1,       // error(k-1)
			ERRORKM2,       // error(k-2)
			PVKM1,          // process value (k-1)
			PVKM2           // process value (k-2)
		};

	public:
		ControllerPID(double Kp, double Ti, double Td, double out_max);

		virtual ~ControllerPID() {};

		double calculate(double sample_time);
		double calculate(double error, double sample_time);

};
