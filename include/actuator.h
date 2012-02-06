// =============================================================================
//  actuator.h   
//
//  Copyright (C) 2007-2012 by Bach - All Rights Reserved
//
// =============================================================================
#ifndef __ACTUATOR_H__
#define __ACTUATOR_H__


//forward declarations
template <typename T>
class Controller;
template <typename T, typename U>
class Sensor;
class Joint;

#include "logger.h"


/**-------------------------------------------------------------------------------
	Actuator template class wraps NxJoint class
	with a controller (double template specialization for now only) and
	a sensor
--------------------------------------------------------------------------------*/
class Actuator : public LoggerWriter<Actuator>
{
	public:

		Actuator(Joint* joint, Controller<double>* controller, Sensor<double, Joint>* sensor);
		
		virtual ~Actuator(){};

		void doOneStep(float currentTime, float sampleTime);;

		Controller<double>*		getController() const { return mController; }		
		Joint*					getJoint() const { return mJoint; }
		Sensor<double,Joint>*	getSensor() const { return mSensor; }

	protected:
		/**-------------------------------------------------------------------------------
			Update actuator internal values and states.
			Should be done each time sampling interval.

			\param      sample_time
			\return depends on implementation
		--------------------------------------------------------------------------------*/
		virtual void update(float currentTime, float sampleTime) = 0;

		/**-------------------------------------------------------------------------------
			Write values to the log file.

			\param      currentTime
			\param      desc
			\return     nothing
		--------------------------------------------------------------------------------*/
		void writeToLog(NxJointDesc* desc, float currentTime);

		Joint*					mJoint;
		Controller<double>*		mController;
		Sensor<double, Joint>*	mSensor;
};

 #endif