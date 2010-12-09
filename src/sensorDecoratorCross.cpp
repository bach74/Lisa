#include "stdafx.h"
#include "sensorDecoratorCross.h"
#include "simulation.h"

/**-------------------------------------------------------------------------------
	SensorDecoratorCross
	
	@brief
	@param sensor
	@param color
	@param scale
	@return 
---------------------------------------------------------------------------------*/
SensorDecoratorCross::SensorDecoratorCross(Sensor* sensor, const Ogre::ColourValue& color, float scale): SensorDecorator(sensor)
{
	mDrawing=new DrawingCross(getSimulation()->getScene()->getSceneManager().getRootSceneNode(), sensor->getSensorName(), color, scale);
	mSensor->setDataValid(false);
}

/**-------------------------------------------------------------------------------
	~SensorDecoratorCross
	
	@brief
	@return void
---------------------------------------------------------------------------------*/
SensorDecoratorCross::~SensorDecoratorCross() {
	delete mDrawing;
	mDrawing=NULL;
}

/**-------------------------------------------------------------------------------
	update
	
	@brief
	@return void
---------------------------------------------------------------------------------*/
void SensorDecoratorCross::update()
{
	mSensor->update();
	if (getDataValid()) {

		std::vector<Ogre::Vector3> crossPosition;
		getValue(crossPosition);
		mDrawing->setPosition(crossPosition.front());		
		mDrawing->setVisible(true);
	} else {
		mDrawing->setVisible(false);
	}
}