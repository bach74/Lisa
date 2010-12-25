// =============================================================================
//  phySimCreator.cpp   version:  1.0
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The project is licensed under MIT license.
// 
// =============================================================================
#include "phyExtendedCamera.h"
#include "phySimCreator.h"


/**----------------------------------------------------------------------------
	Creates a camera and set the orientation.
   
	\return (Camera*)
 -----------------------------------------------------------------------------*/
Camera* PhySimCreator::CreateCamera()
{
	//Camera *cam=new ExtendedCamera(name,mSceneMgr, mPhyScene);
	cam->getOgreCamera()->setPosition(Vector3(30,30,50));
	cam->getOgreCamera()->lookAt(Vector3(0,0,0));

	// adjust camera to the object
	/*	Entity* ent=mSceneMgr->getEntity(entityName);		
		cam->setNearClipDistance(0.5f);
		// Infinite far plane? 
		if (!Root::getSingleton ().getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE)) { 
			camera->setFarClipDistance(ent->getBoundingRadius()*2+camera->getNearClipDistance());
		}	
		
		// Adjust camera position/orientation
		//Vector3 realCentre = ent->getBoundingBox().getCenter();
		Vector3 pos=ent->getParentNode()->getPosition();
		Vector3 scale=ent->getParentNode()->getScale();
		Vector3 sum=scale*pos;
		float rad=ent->getBoundingRadius()*scale.x;
		camera->setPosition(pos.x+rad/2,pos.y+rad,pos.z+rad+camera->getNearClipDistance());
		camera->lookAt(pos);	
	*/
}

Simulation* PhySimCreator::CreateSim( void )
{

}
