// =============================================================================
//  SensorZMP.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "sensorZMP.h"
#include "config.h"
#include "lisaAPI.h"
#include "simulation.h"
#include "linkIterator.h"
#include "links.h"
#include "sensor.h"


/**-------------------------------------------------------------------------------
	update
	
	@brief
	@return void
---------------------------------------------------------------------------------*/
void SensorZMP::update()
{
	NxReal mz=0, mx=0;

	NxReal sum1=0;
	NxReal sum2=0;
	NxReal sum3=0;
	NxReal sum4=0;
	NxReal sum5=0;

	NxReal deltaT = getDataclass()->getTimeSinceLastPhysXFrame();
	Ogre::Vector3 g=LisaAPI::Instance().getGravity();

	LinkIterator it = LinkIterator(getDataclass()->getLinks());

	for (; !it.end(); ++it)
	{
		Link& link=*it;
		// ignore floor, and other static items
		if (link.isDynamic())
		{
			/*
			Re: Getting accumulated forces for an actor
			IMHO, exposing computed values can be invaluable asset for developers, since we can use it instead of compute new values in order to add
			additional optimizations. if developers knew what kind of values it can get for free, planning the optimization would be much easier.
				What I'm saying is that the kind of values you get "for free" are not necessarily even close to the computed force (and not free
			as you will see below).
			If everything were working and set up perfectly, then perhaps we could do this. But to quickly resolve things in a stable manner,
			we often have to make changes to the simulation that work outside of the normal constraint solver/impulse mechanism.
			Since these fixups can be radically different than the impulse values, anything we report could be dramatically incorrect.
				For example, let's consider one potential CCD implementation. I'm not exactly certain how it is resolved internally
			(and it could be different in other versions of the SDK, anyway, but this example serves to illustrate my point),
			but one possible method would be to sweep the shape before the actual simulation step to compute the first point of contact,
			and then simply decrease the actor's velocity before actually executing the normal PhysX pipeline. The velocity would be cut
			as much as is needed to force this contact to be generated during the current time step. This (possibly dramatic) cutting of
			the velocity has no definitive physical meaning or corollary (though you could attribute it to the apparently random loss of
			energy due to plastic impact deformation), and is not an impulse maintained internal to the solver--since it has already been "pre-integrated".
			If you were to then request the impulse applied by the solver during the normal integration, it may actually be almost zero, or pointed sideways
			(due to a glancing blow)--rather than the huge impulse counter to the direction of motion you would have expected, because the solver
			only knows about the reduced velocity of the object.
				But, by calculating it yourself after the step is fully complete, you can capture not only the integrated impulse,
			but also the non-integrated (pre or post)impulses. Besides CCD, other algorithms such as penetration resolution, joint projection,
			character controller collision callback forces, and others may have similar effects.
				If your question is, "well, why doesn't the engine do this calculation for me?" the answer is, "because you are one of the only ones
			who has requested this information, you can calculate it by yourself if needed, and there's otherwise no reason to slow down everyone else's
			simulation for something they don't need". Even simply adding a convenience function would be a cost, because we would then have to store
			the last frame's velocity of every object on the off-chance that someone would want to call this function (which would need to be called
			after fetchResults, and thus after the last frame's data has been blown away).
			*/
		
			// Calculate zmp

			// The correct way to determine body position
			Ogre::Vector3 pos=link.getCMassGlobalPosition();
			NxReal m=link.getMass();
			Ogre::Vector3 tau = link.getAngularMomentumDelta(deltaT);
			Ogre::Vector3 a=link.getLinerAcceleration(deltaT);
			Ogre::Vector3 force=m*a;
			Ogre::Vector3 G=m*g;

			mz+=tau.z;
			mx+=tau.x;

			NxReal FG=-force.y+G.y;
			sum1+=FG*pos.x;
			sum2+=pos.y*force.x;
			sum3+=FG;

			sum4+=FG*pos.z;
			sum5+=pos.y*force.z;
		}
	}

	setDataValid(false);
	if (getDataclass()->getLinks()->size()>0)
	{
		if (sum3!=0)
		{
			setDataValid(true);
			Ogre::Vector3 v((sum1+sum2-mz)/sum3,0,(sum4+sum5+mx)/sum3);
			std::vector<Ogre::Vector3> values;
			values.push_back(v);
			setValue(values);
		}
	}
}
