#include "stdafx.h"
#include "debugLogger.h"

DebugLogger::DebugLogger(void)
{
	mName = "logs\\debug.log";
	mLogBuffer.setf(std::ios::fixed);
	mLogBuffer.setf(std::ios::showpoint);
}

DebugLogger::~DebugLogger(void)
{
}

void DebugLogger::write(const NxVec3& vec)
{
	mLogBuffer << vec.x << "\t" << vec.y << "\t" << vec.z << "\t";
}

void DebugLogger::write(const Ogre::Vector3& vec)
{
	mLogBuffer << vec.x << "\t" << vec.y << "\t" << vec.z << "\t";
}

void DebugLogger::write(const NxQuat& q)
{
	mLogBuffer << "x=" << q.x << "\ty=" << q.y << "\tz=" << q.z << "\tw=" << q.w;
}

void DebugLogger::write(const std::string& text)
{
	mLogBuffer << text;
}

void DebugLogger::write(float f)
{
	mLogBuffer << f;
}
