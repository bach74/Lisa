#include "stdafx.h"
#include "SensorFRI.h"
#include "config.h"
#include "simulation.h"
#include "globals.h"

SensorFRI::~SensorFRI(void)
{
}

/**-------------------------------------------------------------------------------
    update - calculate Foot Rotation Index (FRI)

    @brief
    @return void
---------------------------------------------------------------------------------*/
void SensorFRI::update()
{

	float deltaT = getDataclass()->getTimeSinceLastPhysXFrame();
	Ogre::Vector3 g=Globals::Instance().getGravity();


	std::deque<Ogre::Vector3> a;
	std::deque<float> m;
	std::deque<Ogre::Vector3> pos;
	std::deque<Ogre::Vector3> tau;


	LinkIterator it = LinkIterator(getDataclass()->getLinks());
	for (; !it.end(); ++it)
	{
		Link& link = *it;

		// ignore floor, and other static items
		if (link.isDynamic())
		{
			Ogre::String name = link.getName();

			// By construction a link with pressure sensors is a foot link
			// which by convention should be removed from FRI calculations,
			// i.e. set as the first element
			// we don't care about ordering the rest of the elements
			bool ps = link.hasActorFlag((NxActorFlag)MY_AF_PRESSURE_SENSOR);
			if (ps) {
				pos.push_front(link.getCMassGlobalPosition());
				m.push_front(link.getMass());
				tau.push_front(link.getAngularMomentumDelta(deltaT));
				a.push_front(link.getLinerAcceleration(deltaT));
			} else {
				pos.push_back(link.getCMassGlobalPosition());
				m.push_back(link.getMass());
				tau.push_back(link.getAngularMomentumDelta(deltaT));
				a.push_back(link.getLinerAcceleration(deltaT));
			}
		}
	}


	double sum_FG=0;
	double sum_PzFG=0;
	double sum_PxFG=0;
	double sum_mPyaz=0;
	double sum_mPyax=0;
	double sum_Taux=0;
	double sum_Tauz=0;

	// calculate FRI
	for (unsigned int i=1;i<a.size();++i) {
		double FG=m[i]*(-a[i].y+g.y);
		double mPy=-m[i]*pos[i].y;
		sum_FG+=FG;
		sum_PzFG+=pos[i].z*FG;
		sum_PxFG+=pos[i].x*FG;
		sum_mPyaz+=mPy*a[i].z;
		sum_mPyax+=mPy*a[i].x;
		sum_Taux+=tau[i].x;
		sum_Tauz+=tau[i].z;
	}

	double m0g=m[0]*g.y;
	double DEN=m0g+sum_FG;
	double NUM1=m0g*pos[0].x+sum_PxFG-sum_mPyax-sum_Tauz;
	double NUM2=m0g*pos[0].z+sum_PzFG-sum_mPyaz+sum_Taux;	

	setDataValid(false);
	if (DEN!=0)
	{
		setDataValid(true);
		Ogre::Vector3 v(NUM1/DEN,0,NUM2/DEN);
		std::vector<Ogre::Vector3> values;
		values.push_back(v);
		setValue(values);
	}
}
