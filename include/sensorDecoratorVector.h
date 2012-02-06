// =============================================================================
//  SensorDecoratorVector.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORDECORATORVECTOR_H__
#define __SENSORDECORATORVECTOR_H__

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

 #endif