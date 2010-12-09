// =============================================================================
//  phySimCreator.h   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#pragma once
#include "scenecreator.h"


/// physX simulation factory method
class PhySimCreator :	public SimulationCreator
{
public:
	PhySimCreator(void);
	~PhySimCreator(void);
	virtual SimulationImpl* CreateSim(void);
	virtual Camera*	CreateCamera(void);
};

