#include "stdafx.h"
#include "SensorCOPGraph.h"

/**-------------------------------------------------------------------------------
    SensorCOPGraph

    @brief
    @param sensor
    @param uniqueName
    @param parentTop
    @param parentLeft
    @param parentBottom
    @param parentRight
    @param xProp
    @param yProp
    @param sceneManager
    @return
---------------------------------------------------------------------------------*/
SensorCOPGraph::SensorCOPGraph(SensorVectors* sensor, const char* uniqueName, float parentTop,
                               float parentLeft, float parentBottom, float parentRight, float xProp,
                               float yProp, float width, float height, Ogre::SceneManager* sceneManager)
	: LineGraphWidget(uniqueName, parentTop, parentLeft, parentBottom, parentRight, xProp, yProp, width, height, sceneManager)
{
	mSensor = sensor;

	if (mSensor == NULL)
	{
		throw Exception("Sensor parameter is NULL", "SensorCOPGraph");
	}

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

/**-------------------------------------------------------------------------------
    ~SensorCOPGraph

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
SensorCOPGraph::~SensorCOPGraph(void)
{
	// remove frame listener
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);
}

/**-------------------------------------------------------------------------------
     frameEnded is FrameListener callback

     @brief
     @param evt
     @return void
---------------------------------------------------------------------------------*/
bool SensorCOPGraph::frameEnded(const Ogre::FrameEvent& evt)
{
	float t = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() / 1000.0f;

	if (mSensor->getDataValid())
	{
		std::vector<Ogre::Vector3> points;
		mSensor->getValue(points);

		Ogre::Vector3 cop = points.front();

		// first vector3 is a current COP position, second one is remaining margin from the edge,
		// and remaining vectors are pressure sensor distribution
		if (points.size() > 1)
		{
			Ogre::Vector3 centerCH = points[1];
			Ogre::Vector3 marginMax = points[2];
			Ogre::Vector3 margin = points[3];

			// calculate relative distance  (from the center to the edge)
//			Ogre::Vector3 error((cop.x-centerCH.x)/marginMax.x, 0.0f, (cop.z-centerCH.z)/marginMax.z);

			std::vector<Ogre::Vector3> vertices;
			std::copy(points.begin() + 4, points.end(), std::back_inserter<std::vector<Ogre::Vector3> >(vertices));

			// delete all lines, and redraw a complete convex hull,
			// as each edge will be a different line
			freeLines();

			// create a convex hull, based on pressure sensor position
			// need at least two vertices
			if (vertices.size() > 1)
			{
				for (size_t i = 0; i < vertices.size() - 1; ++i)
				{
					createLine(1, 0, 0);
					addPointToLine(i, vertices[i].x, vertices[i].z);
					addPointToLine(i, vertices[i+1].x, vertices[i+1].z);
				}

				// draw margins
				createLine(0, 1, 0);
				addPointToLine(vertices.size() - 1, cop.x, cop.z);
				addPointToLine(vertices.size() - 1, cop.x + margin.x, cop.z);
				createLine(0, 0, 1);
				addPointToLine(vertices.size(), cop.x, cop.z);
				addPointToLine(vertices.size(), cop.x, cop.z + margin.z);
			}
		}
	}

	return true;
}
