// =============================================================================
//  DrawingCoord.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "drawingCoord.h"

/**-------------------------------------------------------------------------------
	DrawingCoord
	
	@brief
	@param sceneNode
	@param name
	@param color
	@param scale
	@return 
---------------------------------------------------------------------------------*/
DrawingCoord::DrawingCoord(Ogre::SceneNode* sceneNode, const std::string& name,
						   float scale, const Ogre::ColourValue& col/*=Ogre::ColourValue::Black*/):ManualObject(name)
{
	mRoot=sceneNode;
	Ogre::SceneNode* myManualObjectNode = sceneNode->createChildSceneNode(name + "_node");

	Ogre::ColourValue col1=col==Ogre::ColourValue::Black?Ogre::ColourValue::Red:col;
	Ogre::ColourValue col2=col==Ogre::ColourValue::Black?Ogre::ColourValue::Green:col;
	Ogre::ColourValue col3=col==Ogre::ColourValue::Black?Ogre::ColourValue::Blue:col;

	Ogre::MaterialManager& matMgr = Ogre::MaterialManager::getSingleton();
	Ogre::MaterialPtr myManualObjectMaterial = matMgr.create(name + "MaterialX", OGRE_DEBUG_GROUP);
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(col1);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(col1);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(col1);

	myManualObjectMaterial=matMgr.create(name + "MaterialY", OGRE_DEBUG_GROUP);
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(col2);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(col2);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(col2);

	myManualObjectMaterial=matMgr.create(name + "MaterialZ", OGRE_DEBUG_GROUP);
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(col3);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(col3);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(col3);

	begin(name + "MaterialX", Ogre::RenderOperation::OT_LINE_LIST);
		position(0, 0, 0);
		position(2 * scale, 0, 0);
	end();
	begin(name + "MaterialY", Ogre::RenderOperation::OT_LINE_LIST);
		position(0, 0, 0);
		position(0, 2 * scale, 0);
	end();
	begin(name + "MaterialZ", Ogre::RenderOperation::OT_LINE_LIST);
		position(0, 0, 0);
		position(0, 0, 2 * scale);
	end();
	setCastShadows(false);

	myManualObjectNode->attachObject(this);
}

/**-------------------------------------------------------------------------------
	~DrawingCoord
	
	@brief
	@param 
	@return 
---------------------------------------------------------------------------------*/
DrawingCoord::~DrawingCoord(void)
{
	Ogre::MaterialManager::getSingleton().remove(mName + "Material");
	mRoot->removeAndDestroyChild(mName + "_node");

}
