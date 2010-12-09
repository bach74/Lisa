#pragma once

#include "trajectoryQueue.h"

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
