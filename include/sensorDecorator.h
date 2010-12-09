#pragma once
#include "sensor.h"


/**-------------------------------------------------------------------------------
    SensorDecorator
---------------------------------------------------------------------------------*/
template <typename T>
class SensorDecorator : public Sensor<T>
{
	public:
		SensorDecorator(Sensor* sensor): mSensor(sensor) {};
		virtual ~SensorDecorator() { delete mSensor; mSensor=NULL; };

		Simulation* getSimulation()			{ return mSensor->getDataclass(); }
		bool getDataValid()	const			{ return mSensor->getDataValid(); }		
		void setDataValid(bool dv)			{ mSensor->setDataValid(dv);}
		std::string getSensorName()	const	{ return mSensor->getSensorName(); }
		void getValue(T& val) const			{ mSensor->getValue(val); }			
		void setValue(const T& val)			{ mSensor->setValue(val); }
	
	protected:

		Sensor* mSensor;
};
