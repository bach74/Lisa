#pragma once
#include "sensordecorator.h"
#include "drawingCross.h"

/**-------------------------------------------------------------------------------
    SensorDecoratorCross

	draws cross symbol in the 3D space at the mValue coordinates
	(representing current sensor value)
---------------------------------------------------------------------------------*/
class SensorDecoratorCross : public SensorDecorator<std::vector<Ogre::Vector3> >
{
	public:
		SensorDecoratorCross(Sensor* sensor, const Ogre::ColourValue& color, float scale);		
		virtual ~SensorDecoratorCross();

		virtual void update();

	private:

		DrawingCross* mDrawing;
};
