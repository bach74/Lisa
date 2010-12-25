// =============================================================================
//  phyExtendedCamera.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "phyExtendedCamera.h"
#include "OgreIteratorWrappers.h"



/**----------------------------------------------------------------------------
	dtor

	\return ()
 -----------------------------------------------------------------------------*/
PhyExtendedCamera::~PhyExtendedCamera()
{
	delete mRayCaster;
	mRayCaster=NULL;
}


/**-------------------------------------------------------------------------------
	handle mouse picking

	\param x (float)
	\param y (float)
	\param currentObject (std::string &)
	\param moveObject (bool)
	\return (void)
 -----------------------------------------------------------------------------*/
std::string PhyExtendedCamera::mousePick( float x, float y, std::string& currentObject, bool moveObject )
{
	std::string selectedObject;

	// Setup the ray Scene query
	Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(x, y);

	// find if the object is still in the Scene
	// if so unselect it
	if (mSceneMgr->hasEntity(currentObject))
	{
		unselectObject(mSceneMgr->getEntity(currentObject));
		currentObject="";
	}

	mRayCaster->setOrigin(mouseRay.getOrigin());
	mRayCaster->setDirection(mouseRay.getDirection());

	if (mRayCaster->castShape(NxOgre::RayCaster::AF_NONE))
	{
		NxOgre::Body *targetBody=static_cast<NxOgre::Body*>(mRayCaster->getClosestActor());
		// Move it TODO:
		if ((moveObject)&&(currentObject!=""))
		{
			Ogre::Plane p;
			p.normal=mouseRay.getDirection();
			//p.d=-mRayCaster->mHitPos.dotProduct(p.normal);
			p.d=-mRayCaster->getClosestRaycastHit().mWorldImpact.dotProduct(p.normal);

			std::pair<bool, Ogre::Real> res;
			res=mouseRay.intersects(p);
			Ogre::Vector3 objPoint;

			if (res.first)
			{
				Ogre::Vector3 force=mouseRay.getPoint(res.second)-targetBody->getGlobalPose();
				force*=10;
				force-= NxOgre::NxConvert<Ogre::Vector3, NxVec3>(targetBody->getNxActor()->getPointVelocity(targetBody->getGlobalPositionAsNxVec3()));
				targetBody->addForceAtPos(force, targetBody->getGlobalPose());
			}
		}
		else
		{
			// Pick it
			if (targetBody->isDynamic())
			{
				NxOgre::OgreNodeRenderable* target = static_cast<NxOgre::OgreNodeRenderable*>(targetBody->getRenderable());
				Ogre::SceneNode::ObjectIterator it=target->getOffsetNode()->getAttachedObjectIterator();

				if (it.hasMoreElements())
				{
					Ogre::Entity *entity=static_cast<Ogre::Entity*>(it.getNext());
					selectedObject=selectObject(entity);
				}
			}

		}
	}
	
	return selectedObject;
}
