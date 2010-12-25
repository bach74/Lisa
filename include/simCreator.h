// =============================================================================
//  simCreator.h   version:  1.0
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The project is licensed under MIT license.
// 
// =============================================================================
#ifndef __SIMCREATOR_H__
#define __SIMCREATOR_H__
#include "simulation.h"


/// Factory method for creating SimulationImpl classes
class SimCreator
{
public:
	SimCreator(void);
	virtual ~SimCreator(void);
	virtual SimulationImpl* Create(void)=0;
};

 #endif