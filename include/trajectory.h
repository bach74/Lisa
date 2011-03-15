// =============================================================================
//  Trajectory.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __TRAJECTORY_H__
#define __TRAJECTORY_H__

// fwd declaration
class TrajectoryQueue;
class Actuator;

class Trajectory
{
	public:

		Trajectory(const std::string& filename);
		~Trajectory();

		double	getTime()				{return mTime;}
		void	setTime(double time)	{ mTime = time; }
		void	update();				// should be call every step

		void	addQueue(boost::shared_ptr<TrajectoryQueue> q);
		void	load(const std::vector<boost::shared_ptr<Actuator > >& actuators);

	private:
		std::string mFilename;
		double mTime;                                                 // mTime in ms
		std::deque<boost::shared_ptr<TrajectoryQueue> > mQueue;       // SORTED queue of the pending set-point changes		
};

 #endif