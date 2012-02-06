// =============================================================================
//  JointFactory.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __JOINTFACTORY_H__
#define __JOINTFACTORY_H__

#include "joint.h"

class JointFactory
{
	public:
		static Joint* createJoint(NxJoint* joint);
		~JointFactory(void);
	private:
		JointFactory();
};

 #endif