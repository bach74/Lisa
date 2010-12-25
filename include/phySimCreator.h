// =============================================================================
//  phySimCreator.h   version:  1.0
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The project is licensed under MIT license.
// 
// =============================================================================
#ifndef __PHYSIMCREATOR_H__
#define __PHYSIMCREATOR_H__
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


 #endif