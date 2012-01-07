// =============================================================================
//  ControllerPID.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONTROLLERPID_H__
#define __CONTROLLERPID_H__

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

		double calculate(float sample_time);
		double calculate(double error, float sample_time);

		void getParameters(std::vector<double>& ret) const;
		void setParameters(const std::vector<double>& val);

};

 #endif