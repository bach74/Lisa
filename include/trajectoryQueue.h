// =============================================================================
//  trajectoryQueue.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __TRAJECTORYQUEUE_H__
#define __TRAJECTORYQUEUE_H__

class Actuator;

/**-------------------------------------------------------------------------------
	TrajectoryQueue
---------------------------------------------------------------------------------*/
class TrajectoryQueue
{
	public:
		TrajectoryQueue(const Actuator& actuator, double time): mActuator(actuator), mTime(time) {};
		~TrajectoryQueue() {};

		double mTime;
		virtual void go() = 0;

	protected:

		const Actuator& mActuator;
};

/**-------------------------------------------------------------------------------
	QueueElementSP
---------------------------------------------------------------------------------*/
class QueueElementSP : public TrajectoryQueue
{
	public:
		QueueElementSP(const Actuator& actuator, double time, double val):
			TrajectoryQueue(actuator, time), mValue(val) {};

		virtual void go();

	protected:
		double mValue;
};

/**-------------------------------------------------------------------------------
	QueueElementType
---------------------------------------------------------------------------------*/
class QueueElementType : public TrajectoryQueue
{
	public:
		QueueElementType(const Actuator& actuator, double time, const std::string& val):
			TrajectoryQueue(actuator, time), mValue(val) {};

		virtual void go();

	protected:
		std::string mValue;
};

/**-------------------------------------------------------------------------------
	QueueElementForce
---------------------------------------------------------------------------------*/
class QueueElementForce : public TrajectoryQueue
{
	public:
		QueueElementForce(const Actuator& actuator, double time, const NxVec3& val, const std::string& forceType, int actor):
			TrajectoryQueue(actuator, time), mValue(val), mForceType(forceType), mActor(actor) {};

		virtual void go();

	protected:
		NxVec3 mValue;
		std::string mForceType;
		int mActor;
};

 #endif