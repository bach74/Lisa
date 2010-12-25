// =============================================================================
//  Trajectory.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "trajectory.h"
#include "..\dependencies-include\tinyxml\tinyxml.h"
#include "..\dependencies-include\tinyxml\tinyxml.cpp"
#include "..\dependencies-include\tinyxml\tinyxmlparser.cpp"
#include "..\dependencies-include\tinyxml\tinyxmlerror.cpp"
#include "..\dependencies-include\tinyxml\tinystr.cpp"



/**-------------------------------------------------------------------------------
    Trajectory

    @brief
    @param filename
    @return
---------------------------------------------------------------------------------*/
Trajectory::Trajectory(const std::string& filename)
{
	TiXmlDocument doc(filename.c_str());

	if (doc.LoadFile())
	{
		TiXmlHandle hDoc(&doc);
		TiXmlElement* el = hDoc.FirstChild("TRAJECTORY").Element();

		if (el)
		{
			mFilename = (el->Attribute("filename")) ? el->Attribute("filename") : "";
		}
	}
}

/**-------------------------------------------------------------------------------
    ~Trajectory

    @brief
    @return
---------------------------------------------------------------------------------*/
Trajectory::~Trajectory()
{
}

/**-------------------------------------------------------------------------------
    addQueue

    @brief
    @param q
    @return void
---------------------------------------------------------------------------------*/
void Trajectory::addQueue(boost::shared_ptr<TrajectoryQueue> q)
{
	mQueue.push_back(q);

	std::sort(mQueue.begin(), mQueue.end(), boost::bind(
	              std::less<double>(),
	              boost::bind(&TrajectoryQueue::mTime, _1),
	              boost::bind(&TrajectoryQueue::mTime, _2)));

}

/**-------------------------------------------------------------------------------
    update

    @brief
    @return void
---------------------------------------------------------------------------------*/
void Trajectory::update()
{
	if (!mQueue.empty())
	{
		// get first set-point from the queue
		// the set-point should be sorted
		boost::shared_ptr<TrajectoryQueue> el = mQueue.front();

		while (mTime >= el->mTime)
		{
			el->go();

			// remove this set-point from the queue
			mQueue.pop_front();

			if (mQueue.empty()) { break; }

			// get next set-point
			el = mQueue.front();
		}
	}
}

/**-------------------------------------------------------------------------------
    load actuator trajectory from XML file

    @brief
    @param actuators
    @param filename
    @return void
---------------------------------------------------------------------------------*/
void Trajectory::load(const std::vector<boost::shared_ptr<Actuator > >& actuators)
{
	if (!mFilename.empty())
	{
		TCHAR path[MAX_PATH+1];
		GetCurrentDirectory(MAX_PATH, path);

		strcat_s(path, MAX_PATH, "\\resources\\");
		strcat_s(path, MAX_PATH, mFilename.c_str());

		TiXmlDocument doc(path);

		if (doc.LoadFile())
		{
			TiXmlHandle hDoc(&doc);
			TiXmlElement* el = hDoc.FirstChildElement().Element();

			if (el)
			{
				TiXmlHandle hRoot = TiXmlHandle(el);

				TiXmlHandle hJoint = hRoot.FirstChild("joint");
				TiXmlElement* elemJoint = hJoint.Element();

				for (elemJoint; elemJoint; elemJoint = elemJoint->NextSiblingElement())
				{
					Actuator* actuator = NULL;
					BOOST_FOREACH(boost::shared_ptr<Actuator> a, actuators)
					{
						if (elemJoint->Attribute("name") == a->getJoint()->getName())
						{
							actuator = a.get();
							break;
						}
					}

					if (actuator)
					{
						TiXmlElement* elemItem = elemJoint->FirstChildElement();

						for (elemItem; elemItem; elemItem = elemItem->NextSiblingElement())
						{
							double time = 0;

							if (elemItem->Attribute("time"))
							{
								elemItem->QueryDoubleAttribute("time", &time);

								if (elemItem->Attribute("type"))
								{
									// controller type change
									std::string type = elemItem->Attribute("type");
									boost::shared_ptr<TrajectoryQueue> q(new QueueElementType(*actuator, time, type));
									addQueue(q);
								}

								if (elemItem->Attribute("setPoint"))
								{
									// set-point change
									double val = 0;
									elemItem->QueryDoubleAttribute("setPoint", &val);
									boost::shared_ptr<TrajectoryQueue> q(new QueueElementSP(*actuator, time, val));
									addQueue(q);
								}

								if (elemItem->Attribute("force"))
								{
									int actor;
									elemItem->QueryIntAttribute("actor", &actor);
									std::string forceType = elemItem->Attribute("force_type");
									NxVec3 val = NxOgre::NxFromString<NxVec3>(elemItem->Attribute("value"));
									boost::shared_ptr<TrajectoryQueue> q(new QueueElementForce(*actuator, time, val, forceType, actor));
									addQueue(q);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			throw Exception(doc.ErrorDesc(), "Trajectory.cpp");
		}
	}
}
