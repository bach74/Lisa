// =============================================================================
//  LineGraphWidgetFactory.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __LINEGRAPHFACTORY_H__
#define __LINEGRAPHFACTORY_H__

#include "simulation.h"
#include "lineGraphWidget.h"

class LineGraphFactory
{
	public:
		LineGraphFactory(Simulation* simulation);
		~LineGraphFactory(void);

		bool getVisible() { return mVisible; }
		void hide();
		void show();

	private:
		Simulation* mSimulation;
		bool		mVisible;

		std::vector<boost::shared_ptr<LineGraphWidget> > mGraphs;
};

 #endif