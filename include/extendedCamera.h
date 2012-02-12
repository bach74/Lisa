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
/// When autotracking, framelistener will be registered
class ExtendedCamera : public Ogre::FrameListener
{
	public:

		enum CameraType
		{
			FREE_MOUSE,
		};

		ExtendedCamera(Ogre::String name, Ogre::SceneManager* sceneMgr, bool autoTrack = false);
		virtual ~ExtendedCamera();

		Ogre::Camera*		getOgreCamera() { return mCamera; }

		Ogre::SceneNode*	getCameraNode() { return mCameraNode; }
		Ogre::SceneNode*	getTargetNode() { return mTargetNode; }
		void				changeTargetNode(const std::string& target);
		void				setTargetNodePosition(const Ogre::Vector3& position) {	mTargetNode->_setDerivedPosition(position); }		

		CameraType			getCameraType() const { return mCameraType; }
		void				changeCameraType(CameraType val, const std::string& selectedObject);

		void				updateCamera(const OIS::MouseButtonID& mbtn, const OIS::MouseState& mstate, Ogre::String& currentObject, bool ctrlHold);
		void				updateCamera(Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);
		void				instantUpdateCamera(Ogre::Vector3 cameraPosition, Ogre::Vector3 targetPosition);

		virtual std::string mousePick(float x, float y, std::string& currentObject, bool moveObject);
		std::string			selectObject(Ogre::Entity* entity);
		void				unselectObject(Ogre::Entity* entity);

		virtual bool		frameStarted(const Ogre::FrameEvent& evt);

	protected:


		Ogre::SceneNode* mTargetNode;		// The camera target
		Ogre::SceneNode* mCameraNode;		// The camera itself
		Ogre::Camera* mCamera;				// Ogre camera
		Ogre::String mName;					// camera name
		bool mAutoTracking;					// autotrack node?
		std::string mTargetName;			// autotrack node name

		CameraType mCameraType;
		float mTightness;

		Ogre::SceneManager*			mSceneMgr;
		//Ogre::RaySceneQuery*		mRaySceneQuery;			// mouse picking

	private:
		StencilOpQueueListener* mStencilOpFrameListener;		
		void updateFreeMouseCamera(const OIS::MouseButtonID& mbtn, bool ctrlHold, const OIS::MouseState& mstate, float rotateSpeed, Ogre::String& currentObject, float translateSpeed);
		Ogre::Vector3 getObjectWorldPosition(const std::string& currentObject); // TODO - refactor to another class

};

#endif