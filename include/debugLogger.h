// =============================================================================
//  DebugLogger.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __DEBUGLOGGER_H__
#define __DEBUGLOGGER_H__

#include "logger.h"
#include "singleton.h"

class DebugLogger : public Logger, public Singleton<DebugLogger>
{
	public:
		DebugLogger(void);
		~DebugLogger(void);

		void write(const NxVec3& vec);
		void write(const Ogre::Vector3& vec);
		void write(const NxQuat& vec);
		void write(float f);
		void write(const std::string& text);
};

 #endif