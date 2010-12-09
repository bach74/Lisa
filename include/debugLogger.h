#pragma once

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
