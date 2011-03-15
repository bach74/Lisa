/** \file    NxOgreClothRaycaster.cpp
 *  \see     NxOgreClothRaycaster.h
 *  \version 1.0-20
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *           version 2.1 of the License, or (at your option) any later version.
 *           
 *           This library is distributed in the hope that it will be useful,
 *           but WITHOUT ANY WARRANTY; without even the implied warranty of
 *           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received a copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NxOgreStable.h"
#include "NxOgreClothRaycaster.h"
#include "NxOgreHelpers.h"		// For conversions
#include "NxOgreScene.h"		// So I can raycast
#include "NxOgreContainer.h"	// For container access.
#include "NxOgreCloth.h"		// For getName()

namespace NxOgre {

#if (NX_USE_CLOTH_API == 1)

#if 0
////////////////////////////////////////////////////////////////////////////////

ClothRayCaster::ClothRayCaster(Scene* scene) : mScene(scene){

}

////////////////////////////////////////////////////////////////////////////////

ClothRayCaster::~ClothRayCaster() {

}

////////////////////////////////////////////////////////////////////////////////

bool ClothRayCaster::castCloth(Cloth* cloth, const Ogre::Vector3& worldPosition, const Ogre::Vector3& normal) {
	mCloth = cloth;
	NxRay ray(NxConvert<NxVec3, Ogre::Vector3>(worldPosition), NxConvert<NxVec3, Ogre::Vector3>(normal));
	mLastHitPosition.zero();
	mLastVertexId = 0;
	return cloth->raycast(ray, mLastHitPosition, mLastVertexId);
}

////////////////////////////////////////////////////////////////////////////////

bool ClothRayCaster::castAllCloths(const Ogre::Vector3& worldPosition, const Ogre::Vector3& normal) {
	if (!mScene)
		return false;

	Cloths* cloths = mScene->getCloths();
	mLastHitPosition.zero();
	mLastVertexId = 0;
	NxRay ray(NxConvert<NxVec3, Ogre::Vector3>(worldPosition), NxConvert<NxVec3, Ogre::Vector3>(normal));
	
	
	for(Cloth* cloth = cloths->begin();cloth = cloths->next();) {
		if (cloth->raycast(ray, mLastHitPosition, mLastVertexId)) {
			mCloth = cloth;
			return true;
		}
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////

Ogre::Vector3 ClothRayCaster::getHitPosition() {
	return NxConvert<Ogre::Vector3, NxVec3>(mLastHitPosition);
}

////////////////////////////////////////////////////////////////////////////////

NxU32 ClothRayCaster::getVertex() {
	return mLastVertexId;
}

////////////////////////////////////////////////////////////////////////////////

ClothVertex	ClothRayCaster::getClothVertex() {
	ClothVertex vertex;
	vertex.cloth = mCloth;
	vertex.vertex = mLastVertexId;
	return vertex;
}

////////////////////////////////////////////////////////////////////////////////
#endif

#endif

}; //End of NxOgre namespace.
