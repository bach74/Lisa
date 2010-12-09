#include "stdafx.h"
#include "globals.h"
#include "exception.h"


/**-------------------------------------------------------------------------------
	getGravity
	
	@brief
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
Ogre::Vector3 Globals::getGravity()
{
	if (mScene) {
		NxVec3 gVec3;
		mScene->getNxScene()->getGravity(gVec3);
		return NxOgre::NxConvert<Ogre::Vector3, NxVec3>(gVec3);
	} else {
		throw Exception("Must initialize scene member first","Globals.cpp");
	}
}