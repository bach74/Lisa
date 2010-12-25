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
		Ogre::Vector3 zmp=values.front();
	}

	// pv COP
	if (mSensorCOP.getDataValid())
	{
		std::vector<Ogre::Vector3> values;
		mSensorCOP.getValue(values);
		Ogre::Vector3 cop = values[0];

		std::vector<Ogre::Vector3> valuesCOG;
		mSensorCOG.getValue(valuesCOG);
		Ogre::Vector3 gcog=valuesCOG.front();

		if (values.size() > 2)
		{
			// get error (distance from COP convex hull center)
			Ogre::Vector3 centerCH = values[1];
			Ogre::Vector3 marginMax = values[2];
			Ogre::Vector3 marginCOP = values[3];
			static std::vector<Ogre::Vector3> convexHull;
			static Ogre::Vector3 errorPrev;

			Ogre::Vector3 error(0,0,0);
			if (convexHull.size()!=values.size()-4) {
				// probably loss of support on one edge
				// try to determine the edge by comparing with previous convex hull
				Ogre::Vector3 sumPrev=std::accumulate(convexHull.begin(),convexHull.end(),Ogre::Vector3::ZERO);
				Ogre::Vector3 sum=std::accumulate(values.begin()+4,values.end(),Ogre::Vector3::ZERO);
				if (convexHull.size()!=0) {
					error.x=(sumPrev.x/convexHull.size()>sum.x)?-1:1;
					error.z=(sumPrev.z/convexHull.size()>sum.z)?-1:1;
				}
			} else {
				// calculate relative distance  (from the center to the edge)			
				// Ogre::Vector3 error((cop.x-centerCH.x)/marginMax.x, 0.0f, (cop.z-centerCH.z)/marginMax.z);
				error.x=(fabs(marginMax.x)<1e-3)?errorPrev.x:(gcog.x-centerCH.x)/marginMax.x;
				error.z=(fabs(marginMax.z)<1e-3)?errorPrev.z:(gcog.z-centerCH.z)/marginMax.z;
			}				

			// store current values to previous values
			convexHull.clear();
			std::copy(values.begin()+4,values.end(), std::back_inserter<std::vector<Ogre::Vector3>>(convexHull));
			errorPrev=error;

			if (fabs(error.x)>1000) {
				error.x=error.x+1;
			}

			float t=Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds()/1000.0;					
			
			double result = CalculateOutput(t, sampleTime);


			// TODO debug
			std::stringstream s;
			s << Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() / 1000.0;
			s << "\t"<< error.x << "\t" << error.y << "\t" << error.z;
			s << "\t" << gcog.x << "\t" << gcog.y << "\t" << gcog.z;
			s << "\t" << result;
			s << "\t" << values.size();
			s << "\t" << marginMax.x << "\t" << marginMax.y << "\t" << marginMax.z;
			s << "\n";
			DebugLogger::Instance().write(s.str());
			// end

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