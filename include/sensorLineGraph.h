#pragma once
#include "lineGraphWidget.h"
#include "sensor.h"

class SensorLineGraph : public LineGraphWidget, public Ogre::FrameListener
{
	public:
		SensorLineGraph(SensorVectors* sensor, const char* uniqueName, float parentTop, float parentLeft,
				float parentBottom, float parentRight, float xProp, float yProp, float width, float height,
				Ogre::SceneManager* sceneManager);

		virtual ~SensorLineGraph();

		virtual bool frameEnded(const Ogre::FrameEvent& evt);

		void show();
		void hide();

	private:
		SensorVectors* mSensor;

};
