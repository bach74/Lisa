#pragma once
#include "sensordecorator.h"

/**-------------------------------------------------------------------------------
    SensorDecoratorVector

    draws vector graphic representation in the 3D space at the value[0] coordinates
    with force (value[1])
    (representing current sensor vector value)
---------------------------------------------------------------------------------*/
class SensorDecoratorVector : public SensorDecorator<std::vector<Ogre::Vector3> >, public Ogre::ManualObject
{
	public:
		SensorDecoratorVector(Sensor* sensor, const Ogre::ColourValue& color, bool persistent);

		virtual ~SensorDecoratorVector();

		virtual void update();
	
	private:
		bool mPersistent;
};
