#include "stdafx.h"
#include "poseControl.h"
#include "config.h"
#include "sensors.h"


/**-------------------------------------------------------------------------------
	PoseControl
	
	@brief
	@return 
---------------------------------------------------------------------------------*/
PoseControl::PoseControl(std::vector<boost::shared_ptr<Actuator > >& actuators, Sensors* sensors):mActuators(actuators)
{
	if (Config::Instance().getControllerZMP())
	{
		SensorVectors* sensorZMP = sensors->getSensor("ZMP");
		SensorVectors* sensorCOP = sensors->getSensor("COP");
		SensorVectors* sensorCOG = sensors->getSensor("COG");
		controllerZMP = new ControllerZMP(*sensorZMP, *sensorCOP, *sensorCOG, mActuators, "singleton.fcl");
	}
}

/**-------------------------------------------------------------------------------
	~PoseControl
	
	@brief
	@return 
---------------------------------------------------------------------------------*/
PoseControl::~PoseControl()
{
	mActuators.clear();
}

/**-------------------------------------------------------------------------------
	update
	
	@brief
	@param frameTime
	@return void
---------------------------------------------------------------------------------*/
void PoseControl::update(float frametime)
{
	if (controllerZMP) {
		float td = Config::Instance().getActuatorSteppingTime();
		controllerZMP->calculate(td);
	}
}
