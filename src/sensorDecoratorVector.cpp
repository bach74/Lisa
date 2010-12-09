#include "stdafx.h"
#include "sensorDecoratorVector.h"
#include "exception.h"
#include "simulation.h"

#define ARROW_H 0.25


/**-------------------------------------------------------------------------------
    SensorDecoratorVector

    @brief
    @param color
    @return
---------------------------------------------------------------------------------*/
SensorDecoratorVector::SensorDecoratorVector(Sensor* sensor, const Ogre::ColourValue& color, bool persistent)
	: SensorDecorator(sensor), ManualObject(sensor->getSensorName())
{
	Ogre::SceneNode* myManualObjectNode = getSimulation()->getScene()->getSceneManager().getRootSceneNode()->createChildSceneNode(mName + "_node");

	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create(mName + "Material", OGRE_DEBUG_GROUP);
	myManualObjectMaterial->setReceiveShadows(false);
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(color);
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(color);

	myManualObjectNode->attachObject(this);

	mPersistent = persistent;
	mVisible = false;

	Ogre::Vector3 zero(0,0,0);
	begin(mName + "Material", Ogre::RenderOperation::OT_LINE_LIST);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	position(zero);
	end();
}

/**-------------------------------------------------------------------------------
	~SensorDecoratorVector
	
	@brief
	@return 
---------------------------------------------------------------------------------*/
SensorDecoratorVector::~SensorDecoratorVector()
{
	Ogre::MaterialManager::getSingleton().remove(mName + "Material");
	getSimulation()->getScene()->getSceneManager().getRootSceneNode()->removeAndDestroyChild(mName + "_node");
}

/**-------------------------------------------------------------------------------
    update

    @brief
    @return void
---------------------------------------------------------------------------------*/
void SensorDecoratorVector::update()
{
	mSensor->update();

	if (getDataValid())
	{
		std::vector<Ogre::Vector3> out;
		getValue(out);
		Ogre::Vector3 pos(out[0].x, out[0].y, out[0].z);
		Ogre::Vector3 force(out[1].x, out[1].y, out[1].z);

		getParentNode()->setPosition(pos);
		setVisible(true);

		Ogre::Vector3 posA(0, 0, 0);
		Ogre::Vector3 posB = force  / force.length() * 5;

		Ogre::Vector3 t0 = posB - posA;
		NxVec3 tan1, tan2;
		NxVec3 v3 = NxOgre::NxConvert<NxVec3, Ogre::Vector3>(t0);
		NxNormalToTangents(v3, tan1, tan2);

		t0.normalise();
		Ogre::Vector3 t1 = NxOgre::NxConvert<Ogre::Vector3, NxVec3>(tan1);
		Ogre::Vector3 t2 = NxOgre::NxConvert<Ogre::Vector3, NxVec3>(tan2);

		Ogre::Vector3 lobe1  = posB - t0 * ARROW_H + t1 * ARROW_H;
		Ogre::Vector3 lobe2  = posB - t0 * ARROW_H - t1 * ARROW_H;
		Ogre::Vector3 lobe3  = posB - t0 * ARROW_H + t2 * ARROW_H;
		Ogre::Vector3 lobe4  = posB - t0 * ARROW_H - t2 * ARROW_H;

		beginUpdate(0);
		position(posA);
		position(posB);
		position(posB);
		position(lobe1);
		position(posB);
		position(lobe2);
		position(posB);
		position(lobe3);
		position(posB);
		position(lobe4);
		end();
	}
	else
	{
		setVisible(false);
	}

	// if drawing is not persistent remove it after one draw
	if (getVisible() && !mPersistent && getDataValid())
	{
		setDataValid(false);
	}

}



