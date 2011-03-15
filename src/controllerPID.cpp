// =============================================================================
//  controllerPID.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "controller.h"
#include "controllerPID.h"

/**-------------------------------------------------------------------------------
	ctor
	initialize controller
--------------------------------------------------------------------------------*/
ControllerPID::ControllerPID(double Kp, double Ti, double Td, double out_max)
{
	mOutput = 0;
	mSetpoint = 0;
	mInput = 0;

	this->Kp = Kp;
	this->Ti = Ti;
	this->Td = Td;
	this->maxOutput = out_max;

	mStates.push_back(0); // uckm1=0;
	mStates.push_back(0); // errorkm1=0;
	mStates.push_back(0); // errorkm2=0;
	mStates.push_back(0); // pvkm1=0;
	mStates.push_back(0); // pvkm2=0;
}

/**-------------------------------------------------------------------------------
	Update controller internal values and mStates.

	\param      error
	\param      sample_time
	\return controller output
--------------------------------------------------------------------------------*/
double ControllerPID::calculate(float sample_time)
{
	return calculate(mSetpoint - mInput, sample_time);
}

/**-------------------------------------------------------------------------------
	calculate

	@brief
	@param error
	@param sample_time
	@return double
---------------------------------------------------------------------------------*/
double ControllerPID::calculate(double error, float sample_time)
{
	// better PID control response, with derivative output based on
	// process value (input) instead of set-point
	double PV = mInput;

	// calculate the proportional term
	double pTerm = Kp * (error - mStates[ERRORKM1]);

	// calculate the integral term (backward Euler)
	double iTerm = (Ti == 0) ? 0 : Kp / Ti * sample_time * error;

	// calculate the derivative term
	//double dTerm = (Td != 0) ? Kp * Td / sample_time * (error - 2 * mStates[ERRORKM1] + mStates[ERRORKM2]) : 0;
	double dTerm = (Td != 0) ? Kp * Td / sample_time * (PV - 2 * mStates[PVKM1] + mStates[PVKM2]) : 0;

	double uc = mStates[UCKM1] + pTerm + iTerm + dTerm;

	mStates[UCKM1] = uc;
	mStates[ERRORKM2] = mStates[ERRORKM1];
	mStates[ERRORKM1] = error;
	mStates[PVKM2] = mStates[PVKM1];
	mStates[PVKM1] = PV;

	// output limiter
	// this should be at the end of the block
	if (maxOutput != 0)
	{
		if (uc > maxOutput)
		{
			uc = maxOutput;
		}
		else if (uc < -maxOutput)
		{
			uc = -maxOutput;
		}
	}

	mOutput = uc;

	return uc;
}


/**-------------------------------------------------------------------------------
	getParameters

	@brief return controller parameters
	@param ret return value
	@return double
---------------------------------------------------------------------------------*/
void ControllerPID::getParameters( std::vector<double>& ret ) const
{
	ret.push_back(Kp);
	ret.push_back(Ti);
	ret.push_back(Td);
}