#pragma once
#include "lineGraphWidget.h"
#include "sensor.h"

class SensorCOPGraph : public LineGraphWidget, public Ogre::FrameListener
{
	public:
		SensorCOPGraph(SensorVectors* sensor, const char* uniqueName, float parentTop, float parentLeft,
				float parentBottom, float parentRight, float xProp, float yProp, float width, float height,
				Ogre::SceneManager* sceneManager);

		virtual ~SensorCOPGraph();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		void show();
		void hide();

	private:
		SensorVectors* mSensor;

};
