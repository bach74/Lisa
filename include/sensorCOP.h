// =============================================================================
//  seosorCOP.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSORCOP_H__
#define __SENSORCOP_H__

#include "sensor.h"
#include "contactReporter.h"

/**-------------------------------------------------------------------------------
	SensorCOP

	First vector is COP position, following vectors are support polygon extremes
---------------------------------------------------------------------------------*/
class SensorCOP : public SensorVectors
{
	public:
		SensorCOP(Simulation* simulation);
		~SensorCOP(void);

	protected:
		virtual void update();

	private:
		std::vector<boost::shared_ptr<MyContactReporter> >  mContactReporters;		
};

 #endif