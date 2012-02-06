// =============================================================================
//  Sensor.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SENSOR_H__
#define __SENSOR_H__

// forward declaration
class Simulation;

/**-------------------------------------------------------------------------------
	Interface for Sensor class 
---------------------------------------------------------------------------------*/
template <typename T, class U=Simulation>
class Sensor
{
	public:
	
		Sensor(U* dataclass, const std::string& name):mDataclass(dataclass),mSensorName(name),mDataValid(false){}
		virtual ~Sensor() {}

		// classes implementing this interface must define these functions
		virtual void update()=0;

		// optional implementation
		virtual void getValue(T& val) const	{val=mValue;}			
		virtual void setValue(const T& val) { mValue=val; }
		virtual bool getDataValid() const	{ return mDataValid; }
		virtual void setDataValid(bool dv)	{ mDataValid=dv;}
		virtual std::string getSensorName() const { return mSensorName; }
		virtual U* getDataclass() const { return mDataclass; }		

	protected:
		// default constructor only available to sensor decorator so that
		// the same interface can be implemented
		Sensor():mDataclass(NULL),mDataValid(false){};		

	private:

		U*			mDataclass;
		std::string	mSensorName;
		T			mValue;
		bool		mDataValid;		
};

#include "OgreVector3.h"
typedef Sensor<std::vector<Ogre::Vector3> > SensorVectors;

 #endif