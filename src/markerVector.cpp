// =============================================================================
//  markerVector.cpp   version:  1.0
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "MarkerVector.h"

MarkerVector::MarkerVector(void)
{
}

MarkerVector::~MarkerVector(void)
{
}

/**----------------------------------------------------------------------------
	.

	\param name (const String &)
	\param color (ColourValue)
	\return (void)
 -----------------------------------------------------------------------------*/
void MarkerVector::addObjectVector(const Ogre::String& name, Ogre::ColourValue color)
{
	//ManualObject* myManualObject =  mSceneMgr->createManualObject(name);
	Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name+"_node");

	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create(name+"Material","debugger");
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(color);

	begin(name+"Material", Ogre::RenderOperation::OT_LINE_LIST);
	position(0,0,0);
	position(5,0,0);
	end();

	myManualObjectNode->attachObject(this);
}

// test line
/*ManualObject* myManualObject=new ManualObject("manual1");
SceneNode* myManualObjectNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node");
MaterialPtr myManualObjectMaterial=MaterialManager::getSingleton().create("manual1Material","debugger");
myManualObjectMaterial->setReceiveShadows(false);
myManualObjectMaterial->getTechnique(0)->setLightingEnabled(false);
myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0);
myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1);
myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);
myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
	myManualObject->position(0, -200, 0);
	myManualObject->position(0, 200, 0);
myManualObject->end();
myManualObjectNode->attachObject(myManualObject);*/
