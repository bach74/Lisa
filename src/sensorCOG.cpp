// =============================================================================
//  SensorCOG.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "SensorCOG.h"
#include "link.h"
#include "linkIterator.h"
#include "simulation.h"


/**-------------------------------------------------------------------------------
	calculate

	@brief
	@return void
---------------------------------------------------------------------------------*/
void SensorCOG::update()
{
	// calculate center-of-gravity for each step
	Ogre::Vector3 cogPosition(0,0,0);
	double totalMass = 0;

	LinkIterator it = LinkIterator(getDataclass()->getLinks());

	for (; !it.end(); ++it)
	{
		Link& link=*it;
		if (link.isDynamic())
		{
			// calculate center of gravity
			// call to Ogre::Vector3 pos=body->getGlobalPosition() is wrong !
			// instead body->getCMassGlobalPosition() call should be used
			Ogre::Vector3 pos=link.getCMassGlobalPosition();
			float mass=link.getMass();
			totalMass+=mass;
			cogPosition+=pos*mass;
		}
	}

	if (totalMass>0)
	{
		// update drawings
		cogPosition=cogPosition/totalMass;
		cogPosition.y=0;
		std::vector<Ogre::Vector3> values;
		values.push_back(cogPosition);
		setValue(values);
		setDataValid(true);
	}
}