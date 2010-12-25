// =============================================================================
//  actuatorPID.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach - All Rights Reserved
//
// =============================================================================
#ifndef __ACTUATORPID_H__
#define __ACTUATORPID_H__

#include "actuator.h"
#include "actuatorPID.h"


class ActuatorPID: public Actuator
{
	public:
		ActuatorPID(Joint* node, Controller<double>* controller, Sensor<double,Joint>* sensor);
		virtual ~ActuatorPID();

	private:

		/**-------------------------------------------------------------------------------
			Update controller internal values and states.
			Should be done each time sampling interval.

			\param      sample_time
			\return controller output
		--------------------------------------------------------------------------------*/
		virtual void update(double currentTime, double sampleTime);
};


 #endif