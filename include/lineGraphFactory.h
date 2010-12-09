#pragma once

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
