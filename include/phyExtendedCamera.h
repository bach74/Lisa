// =============================================================================
//  phyExtendedCamera.h   
//  
//	ExtendedCamera specialization class
//	use physX functions to pick an object with mouse click, instead of Ogre's
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================
#ifndef __PHYEXTENDEDCAMERA_H__
#define __PHYEXTENDEDCAMERA_H__

#include "extendedCamera.h"


class PhyExtendedCamera : public ExtendedCamera {
protected:

	NxOgre::Scene*							mPhyScene;
	boost::shared_ptr<NxOgre::RayCaster>	mRayCaster;

public:

	PhyExtendedCamera(Ogre::String name, Ogre::SceneManager *sceneMgr, NxOgre::Scene* phyScene, bool autoTrack=false):
				ExtendedCamera(name,sceneMgr,autoTrack), mPhyScene(phyScene) 
		{
			mRayCaster=boost::shared_ptr<NxOgre::RayCaster>(
				new NxOgre::RayCaster(Ogre::Vector3::ZERO, Ogre::Vector3::ZERO, 200, NxOgre::RayCaster::RCT_CLOSEST, mPhyScene)
		);
	}

				virtual ~PhyExtendedCamera(){};
	
	std::string mousePick(float x, float y, std::string& currentObject, bool moveObject);
};

 #endif