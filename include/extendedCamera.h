// =============================================================================
//  extendedCamera.h   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================
#ifndef __EXTENDEDCAMERA_H__
#define __EXTENDEDCAMERA_H__

#include "InputManager.h"


/// ExtendedCamera base class
class ExtendedCamera {

protected:

	// TODO
	Ogre::SceneNode *mTargetNode;		// The camera target
	Ogre::SceneNode *mCameraNode;		// The camera itself
	Ogre::Camera *mCamera;				// Ogre camera
	Ogre::String mName;					// camera name
	bool mAutoTracking;					// autotrack node?

	Ogre::SceneManager			*mSceneMgr;
	//Ogre::RaySceneQuery*		mRaySceneQuery;			// mouse picking

private:
	StencilOpQueueListener * mStencilOpFrameListener;

public:

	ExtendedCamera(Ogre::String name, Ogre::SceneManager *sceneMgr, bool autoTrack=false);
	virtual ~ExtendedCamera();

	Ogre::SceneNode*	getCameraNode() {	return mCameraNode;	}
	Ogre::SceneNode*	getTargetNode() {	return mTargetNode;	}
	Ogre::Camera*		getOgreCamera() {	return mCamera;	}

	void				updateCamera(const OIS::MouseButtonID& mbtn, const OIS::MouseState& mstate, Ogre::String& currentObject, bool ctrlHold);
	
	virtual std::string mousePick(float x, float y, std::string& currentObject, bool moveObject);
	std::string			selectObject(Ogre::Entity* entity);
	void				unselectObject(Ogre::Entity* entity);

};

 #endif