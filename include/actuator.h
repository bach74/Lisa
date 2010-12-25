// =============================================================================
//  actuator.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach - All Rights Reserved
//
// =============================================================================
#ifndef __ACTUATOR_H__
#define __ACTUATOR_H__

#include "controller.h"
#include "joint.h"
#include "sensor.h"

/**-------------------------------------------------------------------------------
	Actuator template class wraps NxJoint class
	with a controller (double template specialization for now only) and
	a sensor
--------------------------------------------------------------------------------*/
class Actuator : public LoggerWriter<Actuator>
{
	public:

		Actuator(Joint* joint, Controller<double>* controller, Sensor<double, Joint>* sensor): mController(controller), mJoint(joint), mSensor(sensor)  {
			mName = "logs\\" + mJoint->getName() + ".log";
		}
		
		virtual ~Actuator() {
			delete mJoint;
			mJoint = NULL;
			delete mController;
			mController = NULL;
			delete mSensor;
			mSensor=NULL;
		}

		void doOneStep(double currentTime, double sampleTime);;

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
		virtual void update(double currentTime, double sampleTime) = 0;

		/**-------------------------------------------------------------------------------
			Write values to the log file.

			\param      currentTime
			\param      desc
			\return     nothing
		--------------------------------------------------------------------------------*/
		void writeToLog(NxJointDesc* desc, double currentTime);

		Joint*					mJoint;
		Controller<double>*		mController;
		Sensor<double, Joint>*	mSensor;
};

 #endif