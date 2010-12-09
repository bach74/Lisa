// =============================================================================
//  simCreator.h   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#pragma once
#include "simulation.h"


/// Factory method for creating SimulationImpl classes
class SimCreator
{
public:
	SimCreator(void);
	virtual ~SimCreator(void);
	virtual SimulationImpl* Create(void)=0;
};
