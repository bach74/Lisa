#pragma once

#include "controllerZMP.h"
class Sensors;

class PoseControl
{
	public:
		PoseControl(std::vector<boost::shared_ptr<Actuator > >& actuators, Sensors* sensors);
		~PoseControl();

		void update(float frameTime);

	private:
		ControllerZMP* controllerZMP;
		std::vector<boost::shared_ptr<Actuator > >& mActuators;
};
