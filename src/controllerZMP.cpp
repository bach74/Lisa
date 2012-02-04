// =============================================================================
//  controllerZMP.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================

#include "stdafx.h"
#include "controllerZMP.h"
#include "controllerPID.h"
#include "config.h"

/**-------------------------------------------------------------------------------
	ControllerZMP

	@brief
	@param sensor
	@param actuators
	@param filename
	@return
---------------------------------------------------------------------------------*/
ControllerZMP::ControllerZMP(SensorVectors& sensorZMP, SensorVectors& sensorCOP, SensorVectors& sensorCOG,
                             std::vector<boost::shared_ptr<Actuator > >& actuators, const char* filename) :
	mSensorZMP(sensorZMP), mSensorCOP(sensorCOP), mSensorCOG(sensorCOG), mActuators(actuators)
{
	TCHAR path[MAX_PATH+1];
	GetCurrentDirectory(MAX_PATH, path);

	strcat_s(path, MAX_PATH, "\\resources\\");
	strcat_s(path, MAX_PATH, filename);

	mName = "logs\\controllerZMP.log";
}

/**-------------------------------------------------------------------------------
	~ControllerZMP

	@brief
	@param
	@return
---------------------------------------------------------------------------------*/
ControllerZMP::~ControllerZMP()
{
}

/**-------------------------------------------------------------------------------
	calculate

	@brief
	@param sampleTime
	@return double
---------------------------------------------------------------------------------*/
double ControllerZMP::calculate(double sampleTime)
{
	// sp (=try to stabilize)

	// TODO sensor fusion -> sensor ZMP
	if (mSensorZMP.getDataValid())
	{
		std::vector<Ogre::Vector3> values;
		mSensorZMP.getValue(values);
		Ogre::Vector3 zmp = values.front();
	}

	// pv COP
	if (mSensorCOP.getDataValid())
	{
		std::vector<Ogre::Vector3> values;
		mSensorCOP.getValue(values);
		Ogre::Vector3 cop = values[0];
		//Ogre::Vector3 copForce = values[1];

		std::vector<Ogre::Vector3> valuesCOG;
		mSensorCOG.getValue(valuesCOG);
		Ogre::Vector3 gcog = valuesCOG.front();

		if (values.size() > 2)
		{
			// get error (distance from COP convex hull center)
			Ogre::Vector3 centerCH = values[2];
			Ogre::Vector3 marginMax = values[3];
			Ogre::Vector3 marginCOP = values[4];
			static std::vector<Ogre::Vector3> convexHull;
			static Ogre::Vector3 errorPrev;

			Ogre::Vector3 error(0, 0, 0);

			if (convexHull.size() != values.size() - 5)
			{
				// probably loss of support on one edge
				// try to determine the edge by comparing with previous convex hull
				Ogre::Vector3 sumPrev = std::accumulate(convexHull.begin(), convexHull.end(), Ogre::Vector3::ZERO);
				Ogre::Vector3 sum = std::accumulate(values.begin() + 5, values.end(), Ogre::Vector3::ZERO);

				if (convexHull.size() != 0)
				{
					error.x = (sumPrev.x / convexHull.size() > sum.x) ? -1.0f : 1.0f;
					error.z = (sumPrev.z / convexHull.size() > sum.z) ? -1.0f : 1.0f;
				}
			}
			else
			{
				// calculate relative distance  (from the center to the edge)
				// Ogre::Vector3 error((cop.x-centerCH.x)/marginMax.x, 0.0f, (cop.z-centerCH.z)/marginMax.z);
				error.x = (fabs(marginMax.x) < 1e-3) ? errorPrev.x : (gcog.x - centerCH.x) / marginMax.x;
				error.z = (fabs(marginMax.z) < 1e-3) ? errorPrev.z : (gcog.z - centerCH.z) / marginMax.z;
			}

			// store current values to previous values
			convexHull.clear();
			std::copy(values.begin() + 5, values.end(), std::back_inserter<std::vector<Ogre::Vector3>>(convexHull));
			errorPrev = error;

			if (fabs(error.x) > 1000)
			{
				error.x = error.x + 1;
			}

			float t = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() / 1000.0f;

			double result = CalculateOutput(t, sampleTime);


			if (Config::Instance().getLoggingControllerZMP())
			{
				mLogBuffer.setf(std::ios::fixed);
				mLogBuffer.setf(std::ios::showpoint);

				mLogBuffer << std::setw(3) << Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() / 1000.0f << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << error.x << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << error.y << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << error.z << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << gcog.x << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << gcog.y << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << gcog.z << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << result << "\t";
				mLogBuffer << std::setw(4) << values.size() << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << marginMax.x << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << marginMax.y << "\t";
				mLogBuffer << std::setprecision(6) << std::setw(10) << marginMax.z << "\n";
			}
		}
	}

	return 0;
}

/**-------------------------------------------------------------------------------
	calculate

	@brief
	@param error
	@param sampleTime
	@return double
---------------------------------------------------------------------------------*/
double ControllerZMP::calculate(double error, double sampleTime)
{
	return calculate(0, sampleTime);
}

/**-------------------------------------------------------------------------------
	CalculateOutput

	@brief
	@param t
	@return double
---------------------------------------------------------------------------------*/
double ControllerZMP::CalculateOutput(float t, double sampleTime)
{
	double result = 0;

	//mController.setVariable("xpos", error.z);
	//mController.setVariable("xposchange", 5);
	//mController.evaluate();
	//result = mController.getValue("uc");

	return result;
}
