// =============================================================================
//  extendedCamera.cpp
//
//  Copyright (C) 2007-2012 by Bach
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "ExtendedCamera.h"
#include "config.h"


/**----------------------------------------------------------------------------
   Extended camera constructor.

   \param name (Ogre::String)
   \param sceneMgr (Ogre::SceneManager *)
   \param autoTrack (bool)
   \return ()
 -----------------------------------------------------------------------------*/
ExtendedCamera::ExtendedCamera(Ogre::String name, Ogre::SceneManager* sceneMgr, bool autoTrack/*=false*/)
{
	// Basic member references setup
	mName = name;
	mSceneMgr = sceneMgr;
	mTargetNode = NULL;
	mCameraType = FREE_MOUSE;
	mTightness = 0.01f;

	mAutoTracking = autoTrack;
	// Create the camera's node structure
	mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);

	if (mAutoTracking)
	{
		mTargetNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName + "_target");

		// The camera will always look at the camera target
		mCameraNode->setAutoTracking(true, mTargetNode);
		// Needed because of auto tracking
		mCameraNode->setFixedYawAxis(true);
		// Register a framelistener when autotracking is enabled
		Ogre::Root::getSingletonPtr()->addFrameListener(this);
	}
	else
	{
		mCameraNode->setFixedYawAxis(false);
	}

	// Create our camera if it wasn't passed as a parameter
	mCamera = mSceneMgr->createCamera(mName);

	// attach the Ogre camera to the camera node
	mCameraNode->attachObject(mCamera);

	//  mCamera->setPolygonMode(Ogre::PolygonMode::PM_WIREFRAME);
	//  mCamera->setLodBias(0.3);

	mCamera->setNearClipDistance(0.1f);

	// Infinite far plane?
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
	{
		mCamera->setFarClipDistance(0); // performance hit ?
	}
	else
	{
		mCamera->setFarClipDistance(1000.f);
	}

	// Create RaySceneQuery
	//mRaySceneQuery=mSceneMgr->createRayQuery(Ogre::Ray());

	mStencilOpFrameListener = new StencilOpQueueListener();
}

/**----------------------------------------------------------------------------
   Extended camera destructor.

   \return ()
 -----------------------------------------------------------------------------*/
ExtendedCamera::~ExtendedCamera()
{
	//delete mRaySceneQuery;
	//mRaySceneQuery=NULL;

	Ogre::Root::getSingleton().removeFrameListener(this);

	mCameraNode->detachAllObjects();
	mSceneMgr->destroySceneNode(mName);
	mSceneMgr->destroyCamera(mCamera);

	if (mAutoTracking)
	{
		mSceneMgr->destroySceneNode(mTargetNode);
	}

	delete mStencilOpFrameListener;
}


/**-------------------------------------------------------------------------------
	update camera position

	\param mbtn (const OIS::MouseButtonID &)
	\param mstate (const OIS::MouseState &)
	\param currentObject (Ogre::String &)
	\param ctrlHold (bool)
	\return (void)
 -----------------------------------------------------------------------------*/
void ExtendedCamera::updateCamera(const OIS::MouseButtonID& mbtn, const OIS::MouseState& mstate, Ogre::String& currentObject, bool ctrlHold)
{
	float rotateSpeed = Config::Instance().getCameraRotateSpeed();
	float translateSpeed = Config::Instance().getCameraTranslateSpeed();

	switch (mCameraType)
	{
		case FREE_MOUSE:
			updateFreeMouseCamera(mbtn, ctrlHold, mstate, rotateSpeed, currentObject, translateSpeed);
			break;
	}
}

/**-------------------------------------------------------------------------------
	handle mouse picking

	\param x (float)
	\param y (float)
	\param currentObject (std::string &)
	\param moveObject (bool)
	\return (void)
 -----------------------------------------------------------------------------*/
std::string ExtendedCamera::mousePick(float x, float y, std::string& currentObject, bool moveObject)
{
	return "";
}

/**-------------------------------------------------------------------------------
	selected object
		get actual mesh from the nxOgre's body and perform some
		visualization so that user can perceive that this object
		is selected
		\return object name
--------------------------------------------------------------------------------*/
std::string ExtendedCamera::selectObject(Ogre::Entity* entity)
{
	if (Config::Instance().getSelectedObjectGlows())
	{
		// full glow alpha glow
		Ogre::Entity* alphaFullGlowEntity = entity->clone(entity->getName() + "_alphaGlow");
		alphaFullGlowEntity->setRenderQueueGroup(90);
		alphaFullGlowEntity->setMaterialName("cg/alpha_glow");
		Ogre::SceneNode* alphaFullGlowNode = entity->getParentSceneNode()->createChildSceneNode(entity->getParentSceneNode()->getName() + "_alphaGlow");
		alphaFullGlowNode->attachObject(alphaFullGlowEntity);

		// full glow alpha glow
		Ogre::Entity* glowFullGlowEntity = entity->clone(entity->getName() + "_alphaGlowGlow");
		glowFullGlowEntity->setRenderQueueGroup(91);
		glowFullGlowEntity->setMaterialName("cg/no_depth_check_glow");
		Ogre::SceneNode* glowFullGlowNode = entity->getParentSceneNode()->createChildSceneNode(entity->getParentSceneNode()->getName() + "_alphaGlowGlow");
		glowFullGlowNode->attachObject(glowFullGlowEntity);

		mSceneMgr->addRenderQueueListener(mStencilOpFrameListener);
	}

	return entity->getName();
}

/**-------------------------------------------------------------------------------
	unselected previously selected object

	\param entity (Ogre::Entity *)
	\return (void)
 -----------------------------------------------------------------------------*/
void ExtendedCamera::unselectObject(Ogre::Entity* entity)
{
	if (Config::Instance().getSelectedObjectGlows())
	{
		mSceneMgr->removeRenderQueueListener(mStencilOpFrameListener);

		Ogre::SceneNode* high = (Ogre::SceneNode*)entity->getParentSceneNode()->getChild(entity->getParentSceneNode()->getName() + "_alphaGlow");
		high->detachObject(entity->getName() + "_alphaGlow");
		mSceneMgr->destroySceneNode(high->getName());
		mSceneMgr->destroyEntity(entity->getName() + "_alphaGlow");
		high = (Ogre::SceneNode*)entity->getParentSceneNode()->getChild(entity->getParentSceneNode()->getName() + "_alphaGlowGlow");
		high->detachObject(entity->getName() + "_alphaGlowGlow");
		mSceneMgr->destroySceneNode(high->getName());
		mSceneMgr->destroyEntity(entity->getName() + "_alphaGlowGlow");
	}
}

/**-------------------------------------------------------------------------------
	updateFreeMouseCamera

	@brief
	@param mbtn
	@param ctrlHold
	@param mstate
	@param rotateSpeed
	@param currentObject
	@param translateSpeed
	@return void
---------------------------------------------------------------------------------*/
void ExtendedCamera::updateFreeMouseCamera(const OIS::MouseButtonID& mbtn, bool ctrlHold, const OIS::MouseState& mstate, float rotateSpeed, Ogre::String& currentObject, float translateSpeed)
{
	switch (mbtn)
	{
		case(OIS::MB_Left) :
		{
			if (ctrlHold)
			{
				// if left control is held then change camera's view
				// otherwise rotate camera around an object or coordinate system's center
				mCamera->yaw((Ogre::Radian)(-mstate.X.rel * rotateSpeed));
				mCamera->pitch((Ogre::Radian)(-mstate.Y.rel * rotateSpeed));
			}
			else
			{
				Ogre::SceneNode* sc = mCamera->getParentSceneNode();
				Ogre::Vector3 vw(0, 0, 0);

				// if object is selected, rotate around it
				if (mSceneMgr->hasEntity(currentObject))
				{
					Ogre::SceneNode* node = mSceneMgr->getEntity(currentObject)->getParentSceneNode();
					vw = node->_getDerivedPosition();
					Ogre::Matrix4 m4 = sc->_getFullTransform();
					// rotation around selected object
					vw = m4.inverse() * vw;
				}

				sc->translate(vw, Ogre::Node::TS_LOCAL);
				// this transformation will "ignore" camera's orientation
				Ogre::Quaternion qOri = mCamera->getRealOrientation();
				Ogre::Quaternion q(static_cast<Ogre::Radian>(mstate.X.rel * rotateSpeed), Ogre::Vector3(0, 1, 0));
				sc->rotate(qOri * q * qOri.Inverse(), Ogre::Node::TS_WORLD);
				Ogre::Quaternion q2(static_cast<Ogre::Radian>(-mstate.Y.rel * rotateSpeed), Ogre::Vector3(1, 0, 0));
				sc->rotate(qOri * q2 * qOri.Inverse(), Ogre::Node::TS_WORLD);
				sc->translate(-vw, Ogre::Node::TS_LOCAL);
			}
		}
		break;
		case(OIS::MB_Middle) :
			break;
		case(OIS::MB_Right) :
		{
			// get current camera
			Ogre::Real transSpeed = mCamera->getRealPosition().length() * translateSpeed;
			Ogre::Vector3 offs(static_cast<Ogre::Real>(mstate.X.rel * transSpeed),
			                   static_cast<Ogre::Real>(-mstate.Y.rel * transSpeed), static_cast<Ogre::Real>(mstate.Z.rel));
			mCamera->moveRelative(offs);
		}
		break;
	}
}

/**-------------------------------------------------------------------------------
	changeCameraType

	@brief
	@param val
	@param selectedObject
	@return void
---------------------------------------------------------------------------------*/
void ExtendedCamera::changeCameraType(CameraType val, const std::string& selectedObject)
{
	if (mSceneMgr->hasEntity(selectedObject))
	{
		switch (mCameraType)
		{
			case FREE_MOUSE:
				break;
		}

		mCameraType = val;
	}
}

/**-------------------------------------------------------------------------------
	changeTargetNode
	If autotracking is enabled, targetnode will be tracked. Instead of tracking
	a original node

	@brief
	@param target
	@return void
---------------------------------------------------------------------------------*/
void ExtendedCamera::changeTargetNode(const std::string& target)
{
	if (mSceneMgr->hasSceneNode(target))
	{
		mTargetName = target;
		Ogre::SceneNode* newTargetNode = mSceneMgr->getSceneNode(target);

		mCamera->setAutoTracking(false);
		mSceneMgr->destroySceneNode(mTargetNode);
		mTargetNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(newTargetNode->getName() + "_target");
		mCamera->setAutoTracking(true, mTargetNode);
	}
	else
	{
		throw Exception("Auto-tracking object cannot be found in scene.\n Please check config.ini!", "scene.cpp");
	}
}


/**-------------------------------------------------------------------------------
	frameStarted

	@brief
	@param evt
	@return bool
---------------------------------------------------------------------------------*/
bool ExtendedCamera::frameStarted(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 target = mSceneMgr->getSceneNode(mTargetName)->_getDerivedPosition();
	mTargetNode->_setDerivedPosition(Ogre::Vector3(target.x, 0, target.y));

	return true;
}