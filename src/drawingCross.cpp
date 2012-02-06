// =============================================================================
//  DrawingCross.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "drawingCross.h"

/**-------------------------------------------------------------------------------
	DrawingCross
	
	@brief
	@param sceneNode
	@param name
	@param color
	@param scale
	@return 
---------------------------------------------------------------------------------*/
DrawingCross::DrawingCross(Ogre::SceneNode* sceneNode, const std::string& name,
						   const Ogre::ColourValue& color, float scale):ManualObject(name)
{
	mRoot=sceneNode;
	Ogre::SceneNode* myManualObjectNode = sceneNode->createChildSceneNode(name + "_node");

	Ogre::MaterialManager& matMgr = Ogre::MaterialManager::getSingleton();
	Ogre::MaterialPtr myManualObjectMaterial = matMgr.create(name + "Material", OGRE_DEBUG_GROUP);
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(color);

	begin(name + "Material", Ogre::RenderOperation::OT_LINE_LIST);
	position(-2 * scale, 0, 0);
	position(2 * scale, 0, 0);
	position(0, -2 * scale, 0);
	position(0, 2 * scale, 0);
	position(0, 0, -2 * scale);
	position(0, 0, 2 * scale);
	end();
	setCastShadows(false);

	myManualObjectNode->attachObject(this);
}

/**-------------------------------------------------------------------------------
	~DrawingCross
	
	@brief
	@param 
	@return 
---------------------------------------------------------------------------------*/
DrawingCross::~DrawingCross(void)
{
	Ogre::MaterialManager::getSingleton().remove(mName + "Material");
	mRoot->removeAndDestroyChild(mName + "_node");

}
