#include "stdafx.h"
#include "..\include\logger.h"

/**-------------------------------------------------------------------------------
	Logger - create stream buffer

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
Logger::Logger(void)
{
}

/**-------------------------------------------------------------------------------
	~Logger - delete stream buffer

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
Logger::~Logger(void)
{
	if (!mName.empty())
	{
		std::ofstream output(mName.c_str());
		output<<mLogBuffer.rdbuf();
		output.close();
	}
	else
	{
		throw Exception("output logger filename not defined!","Logger.cpp");
	}
}
