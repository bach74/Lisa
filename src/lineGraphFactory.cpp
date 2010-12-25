// =============================================================================
//  LineGraphFactory.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "lineGraphFactory.h"
#include "simulation.h"
#include "controllerLineGraph.h"
#include "sensorLineGraph.h"
#include "sensorCOPGraph.h"
#include "config.h"
#include "simulationImpl.h"


#define N_GRAPHS 5

/**-------------------------------------------------------------------------------
    LineGraphFactory

    @brief
    @param simulation
    @return
---------------------------------------------------------------------------------*/
LineGraphFactory::LineGraphFactory(Simulation* simulation)
{
	mSimulation = simulation;

	if (mSimulation == NULL)
	{
		throw Exception("Simulation is NULL", "LineGraphFactory");
	}

	float height = mSimulation->getScene()->getWindow().getHeight() - 1;
	float width = mSimulation->getScene()->getWindow().getWidth() - 1;

	float graphWidth = width/2.4f ;
	float graphHeight = height / N_GRAPHS*0.98f;
	float sizeY = 1.0f / N_GRAPHS;
	float sizeX = (width-graphWidth)/width;

	// for every actuator create a separate graph, and position it on the canvas
	ActuatorIterator it(mSimulation->getActuators());

	for (; !it.end(); ++it)
	{
		Controller<double>* c = it->getController();
		Actuator& a = *it;
		std::string sensorName = a.getSensor()->getSensorName();

		float x = sizeX;
		float y = sizeY * mGraphs.size();
		std::string jointName = a.getJoint()->getName();
		boost::shared_ptr<LineGraphWidget> gw(new ControllerLineGraph(c, jointName.c_str(), 1, 1, height, width, x, y,
		                                      graphWidth, graphHeight, &mSimulation->getScene()->getSceneManager()));

		gw->setGraphTitle(jointName.c_str());
		gw->setXAxisTitle("t[s]");
		gw->setYAxisTitle(sensorName.c_str());
		gw->setXAxisMax(5);
		gw->setYAxisMax(1);
		gw->setXAxisMin(0);
		gw->setYAxisMin(0);
		gw->createLine(1, 0, 0);
		gw->createLine(0, 1, 0);
		gw->createLine(0, 0, 1);
		gw->setXAxisScroll(true);
		gw->show();

		mGraphs.push_back(gw);
	}

	// if ZMP controller is active create ZMP controller graph
	if (Config::Instance().getControllerZMP())
	{
		{
			SensorVectors* sensorZMP = dynamic_cast<SimulationImpl*>(mSimulation)->getSensors()->getSensor("ZMP");
			std::string sensorName = sensorZMP->getSensorName();

			float x = sizeX;
			float y = sizeY * mGraphs.size();
			boost::shared_ptr<LineGraphWidget> gw(new SensorLineGraph(sensorZMP, sensorName.c_str(), 1, 1, height, width, x,
			                                      y, graphWidth, graphHeight, &mSimulation->getScene()->getSceneManager()));

			gw->setGraphTitle(sensorName.c_str());
			gw->setXAxisTitle("t[s]");
			gw->setYAxisTitle("x-pos");
			gw->setXAxisMin(0);
			gw->setXAxisMax(5);
			gw->setYAxisMin(-10);
			gw->setYAxisMax(10);
			gw->createLine(1, 0, 0);
			gw->createLine(0, 1, 0);
			gw->createLine(0, 0, 1);
			gw->setXAxisScroll(true);
			gw->setYAxisAutoScale(false);
			gw->show();

			mGraphs.push_back(gw);
		}
		// create a drawing of a supporting polygon
		{
			SensorVectors* sensorCOP = dynamic_cast<SimulationImpl*>(mSimulation)->getSensors()->getSensor("COP");
			std::string sensorName = sensorCOP->getSensorName();			

			float x = sizeX;
			float y = sizeY * mGraphs.size();
			boost::shared_ptr<LineGraphWidget> gw(new SensorCOPGraph(sensorCOP, sensorName.c_str(), 1, 1, height, width, x,
			                                      y, graphWidth, graphHeight, &mSimulation->getScene()->getSceneManager()));

			gw->setGraphTitle(sensorName.c_str());
			gw->setXAxisTitle("x-pos");
			gw->setYAxisTitle("y-pos");
			gw->setXAxisMin(0);
			gw->setXAxisMax(0);
			gw->setYAxisMin(0);
			gw->setYAxisMax(0);
			gw->setXAxisScroll(true);
			gw->setYAxisAutoScale(true);
			gw->setKeepBoxAspectRation(true);
			gw->setShowAxes(false);
			gw->show();

			mGraphs.push_back(gw);
		}
	}

}

/**-------------------------------------------------------------------------------
    ~LineGraphFactory

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
LineGraphFactory::~LineGraphFactory()
{
	mGraphs.clear();
}
