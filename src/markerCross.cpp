#include "stdafx.h"
#include "markerCross.h"

MarkerCross::MarkerCross(void)
{
}

MarkerCross::~MarkerCross(void)
{
}

/**----------------------------------------------------------------------------
		.

		\param name (const String &)
		\param color (ColourValue)
		\param scale (float)
		\return (void)
	 -----------------------------------------------------------------------------*/
void MarkerCross::addObjectCross(const Ogre::String& name, Ogre::ColourValue color, float scale)
{
	//ManualObject* myManualObject =  mSceneMgr->createManualObject(name);
	Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name+"_node");

	Ogre::MaterialManager& matMgr=Ogre::MaterialManager::getSingleton();
	Ogre::MaterialPtr myManualObjectMaterial = matMgr.create(name+"Material","debugger");
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(color);

	begin(name+"Material", Ogre::RenderOperation::OT_LINE_LIST);
	position(-2*scale,0,0);
	position(2*scale,0,0);
	position(0,-2*scale,0);
	position(0,2*scale,0);
	position(0,0,-2*scale);
	position(0,0,2*scale);
	end();
	setCastShadows(false);

	myManualObjectNode->attachObject(this);
}
