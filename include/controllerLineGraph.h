#pragma once
#include "linegraphwidget.h"
#include "controller.h"

class ControllerLineGraph : public LineGraphWidget, public Ogre::FrameListener
{
	public:
		ControllerLineGraph(Controller<double>* controller, const char* uniqueName, float parentTop, float parentLeft,
		                    float parentBottom, float parentRight, float xProp, float yProp, float width, float height,
							Ogre::SceneManager* sceneManager);
		~ControllerLineGraph();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);

	private:
		Controller<double>* mController;
};
