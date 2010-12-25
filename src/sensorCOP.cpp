// =============================================================================
//  SensorCOP.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "sensorCOP.h"
#include "contactReporter.h"
#include "simulation.h"
#include "math\ConvexHullGraham.h"
#include "config.h"
#include "NxMath.h"
#include "linkIterator.h"

/**-------------------------------------------------------------------------------
    SensorCOP

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
SensorCOP::SensorCOP(Simulation* simulation): Sensor(simulation, std::string("COP"))
{
	// get floor
	NxOgre::Actor* floor = getDataclass()->getPhyScene()->getActor(getDataclass()->getPhyScene()->getName() + ".floor");

	if (floor == NULL)
	{
		throw Exception("FLOOR actor must be created first", "sensorCOP.cpp");
	}

	// Create contact reporters for the bodies that have MY_AF_PRESSURE_SENSOR flag set
	// Contacts are reported when two bodies collide.
	// This is how we calculate center of pressure for the colliding body (with a floor).
	LinkIterator it = LinkIterator(getDataclass()->getLinks());

	for (; !it.end(); ++it)
	{
		Link& link = *it;

		bool ps = link.hasActorFlag((NxActorFlag)MY_AF_PRESSURE_SENSOR);

		if (ps)
		{
			NxU32 f = NX_NOTIFY_ON_START_TOUCH | NX_NOTIFY_ON_TOUCH | NX_NOTIFY_ON_END_TOUCH | NX_NOTIFY_FORCES;
			getDataclass()->getPhyScene()->getNxScene()->setActorPairFlags(*link.getNxActor(), *floor->getNxActor(), f);
			// link.clearActorFlag((NxActorFlag)MY_AF_PRESSURE_SENSOR);

			// All actors are by default in the "Default" actor group
			// Let's create a new actor group for each of our "pressure sensors"
			std::string groupName = link.getName() + "_PS";
			NxOgre::ActorGroup* group = getDataclass()->getPhyScene()->createActorGroup(groupName);
			link.setGroup(groupName);
			// create contact reporter for that group
			MyContactReporter* newContactReporter = new MyContactReporter(groupName);
			mContactReporters.push_back(boost::shared_ptr<MyContactReporter>(newContactReporter));

			// nxOgre does not own the callback, we will delete it ourselves
			group->setCallback(newContactReporter, false);
		}
	}
}

/**-------------------------------------------------------------------------------
    ~SensorCOP

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
SensorCOP::~SensorCOP(void)
{
	mContactReporters.clear();
}


/**-------------------------------------------------------------------------------
    calculate

    @brief
    @return void
---------------------------------------------------------------------------------*/
void SensorCOP::update()
{
	setDataValid(false);
	Ogre::Vector3 sumCOP(0, 0, 0);
	float sumForce = 0;
	std::vector<Ogre::Vector3> contactPoints;

	std::vector<boost::shared_ptr<MyContactReporter> >::iterator it = mContactReporters.begin();

	for (; it != mContactReporters.end(); ++it)
	{
		if ((*it)->hasContact())
		{
			NxVec3 pos = (*it)->getCOPpos();
			NxVec3 force = (*it)->getCOPforce();
			float f = force.magnitude();
			sumCOP += Ogre::Vector3(pos.x * f, pos.y * f, pos.z * f);
			sumForce += f;

			BOOST_FOREACH(NxVec3 v, (*it)->mContactPoints)
			{
				contactPoints.push_back(Ogre::Vector3(v.x, v.y, v.z));
			}
		}
	}

	if (sumForce > 0)
	{
		Ogre::Vector3 cop = Ogre::Vector3(sumCOP.x / sumForce, sumCOP.y / sumForce, sumCOP.z / sumForce);
		std::vector<Ogre::Vector3> values;
		values.push_back(cop);

		if (Config::Instance().getControllerZMP())
		{
			// create a convex hull, based on pressure sensor position
			// need at least two vertices
			if (contactPoints.size() > 1)
			{
				ConvexHullGraham g(contactPoints);

				g.partition_points();
				std::vector<Ogre::Vector3> ret = g.build_hull();

				// calculate maximum possible margins (that is, from the center of the convex hull to
				// the edges) and then normalize the current margins (from cop) so we end up with [-1,1]
				Ogre::Vector3 center = g.getCenter(ret);
				Ogre::Vector3 marginCenter = g.getMargins(ret, center);
				if (marginCenter.x < 0) { marginCenter.x = -marginCenter.x; }
				if (marginCenter.z < 0) { marginCenter.z = -marginCenter.z; }
				Ogre::Vector3 marginCOP = g.getMargins(ret, cop);

				values.push_back(center);
				// add (max) possible distances for the convex hull
				values.push_back(marginCenter);
				// add distances from the cop to the edges, to the sensor state
				values.push_back(marginCOP);

				// add convex hull created from sensor positions to the sensor state
				BOOST_FOREACH(Ogre::Vector3 v, ret)
				{
					values.push_back(v);
				}
			}
		}

		setValue(values);
		setDataValid(true);
	}

}
