// =============================================================================
//  SensorDecoratorCross.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORDECORATORCROSS_H__
#define __SENSORDECORATORCROSS_H__

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

 #endif