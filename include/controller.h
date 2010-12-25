// =============================================================================
//  controller.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "logger.h"

template <typename T>
class Controller
{
	public:

		Controller() {};
		virtual ~Controller() {};

		void setInput(const T& val) { mInput=val; }
		void getInput(T& ret) { ret=mInput; }

		void getOutput(T& ret) { ret=mOutput; }

		void setSetpoint(const T& val) { mSetpoint=val; }
		void getSetpoint(T& ret) { ret=mSetpoint; }

		/**-------------------------------------------------------------------------------
			Calculate controller internal values and mStates.
			Should be done each time sampling interval.

			\param      sample_time
			\return depends on implementation
		--------------------------------------------------------------------------------*/
		virtual double calculate(double sample_time) = 0;
		virtual double calculate(double error, double sample_time) = 0;


	protected:

		T mInput;
		T mOutput;
		T mSetpoint;

		std::vector<double> mStates;

};

 #endif