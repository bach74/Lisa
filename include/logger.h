#pragma once

/**-------------------------------------------------------------------------------
	A logger class
	It will writeLog data into the memory and upon destruction dump it
	into the file
---------------------------------------------------------------------------------*/

class Logger
{
	public:
		Logger(void);
		virtual ~Logger(void);

		//virtual void writeLog()=0;

	protected:
		std::string         mName;
		std::stringstream   mLogBuffer;
};

/**-------------------------------------------------------------------------------
	Logger writer algorithm
---------------------------------------------------------------------------------*/
template <class ConcreteDerived>
class LoggerWriter : public Logger
{
	public:
		ConcreteDerived* self()
		{
			return static_cast<ConcreteDerived*>(this);
		}

		/*void writeLog()
		{
			mLogBuffer<<self()->updateLog();
		}*/
};
