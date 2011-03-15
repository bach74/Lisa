/** \file    NxOgreIntersection.cpp
 *  \see     NxOgreIntersection.h
 *  \version 1.0-21
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
#include "NxOgreIntersection.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreContainer.h"
#include "NxOgreSimpleShape.h"
#include "NxOgreHelpers.h"
#include "NxOgreScene.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////////////////////////////////

Intersection::Intersection(Scene* scene, NxOgre::SimpleShape* shape, NxShapesType shapeFilter)
 : Actors(), mShape(shape), mShapeFilter(shapeFilter), mScene(scene)
{
	intersect();
}

/////////////////////////////////////////////////////////////////////////////////////////

Intersection::~Intersection() {

	if (mShape)
		delete mShape;
}

/////////////////////////////////////////////////////////////////////////////////////////

void Intersection::setShape(SimpleShape* shape) {

	if (mShape)
		delete mShape;
	mShape = shape;

}

/////////////////////////////////////////////////////////////////////////////////////////

void Intersection::intersect() {
	
	if (mShape == 0)
		return;

	empty();

	switch (mShape->getType()) {

		case SimpleShape::SST_Box:
			{
				SimpleBox* shape = static_cast<SimpleBox*>(mShape);
				NxBox box = NxBox(shape->getPoseAsNxMat34().t, shape->getDimensionsAsNxVec3(), shape->getPoseAsNxMat34().M);
				mScene->getNxScene()->overlapOBBShapes(box, mShapeFilter, 0, NULL, this);
			}
		break;

		case SimpleShape::SST_Sphere:
			{
				SimpleSphere* shape = static_cast<SimpleSphere*>(mShape);
				NxSphere sphere = NxSphere(shape->getPose().t, shape->getRadius());
				mScene->getNxScene()->overlapSphereShapes(sphere, mShapeFilter, 0, NULL, this);
			}
		break;

		case SimpleShape::SST_Capsule:
			{
				// SimpleCapsule* capsule = static_cast<SimpleCapsule*>(mShape);
				// NxCapsule capsule = NxCapsule(NxSegment(urgh, urgh2), capsule->getRadius());
				// mScene->getNxScene()->overlapCapsuleShapes(capsuleShape, mShapeFilter, 0, NULL, this);
			}
		break;

	}

}

/////////////////////////////////////////////////////////////////////////////////////////

bool Intersection::onEvent(NxU32 nbShapes, NxShape** shapes) {

	for (NxU32 i = 0; i < nbShapes; i++) {
		
		if (shapes[i]->getActor().userData == 0)
			continue;

		VoidPointer* aud = static_cast< VoidPointer* >(shapes[i]->getActor().userData);

		if (aud->getType() ==  NxOgreClass_Actor) {
			Actor* a = aud->toActor();
			insert(a->getName(), a);
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

CulledIntersection::CulledIntersection(Scene* scene, std::vector<SimplePlane*> planes, NxShapesType shapeFilter) : Actors(), mScene(scene), mShapeFilter(shapeFilter) {

	mNbPlanes = planes.size();
	mPlanes = new NxPlane[mNbPlanes];

	for (NxU32 i=0;i < planes.size();i++) {
		mPlanes[i] = NxPlane(planes[i]->getNormal(), planes[i]->getDistance());
		delete planes[i];
	}

	intersect();

}

/////////////////////////////////////////////////////////////////////////////////////////

CulledIntersection::~CulledIntersection() {

	delete [] mPlanes;

}

/////////////////////////////////////////////////////////////////////////////////////////

void CulledIntersection::intersect() {
	
	empty();
	mScene->getNxScene()->cullShapes(mNbPlanes, mPlanes, mShapeFilter, 0, NULL, this);

}

/////////////////////////////////////////////////////////////////////////////////////////

bool CulledIntersection::onEvent(NxU32 nbShapes, NxShape** shapes) {

	for (NxU32 i = 0; i < nbShapes; i++) {
		
		if (shapes[i]->getActor().userData == 0)
			continue;

		VoidPointer* aud = static_cast< VoidPointer* >(shapes[i]->getActor().userData);

		if (aud->getType() ==  NxOgreClass_Actor) {
			Actor* a = aud->toActor();
			insert(a->getName(), a);
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////

SimpleIntersection::SimpleIntersection(Scene* scene, NxOgre::SimpleShape* shape, NxShapesType shapeFilter)
 : mShape(shape), mShapeFilter(shapeFilter), mScene(scene)
{
	intersect();
}

/////////////////////////////////////////////////////////////////////////////////////////

SimpleIntersection::~SimpleIntersection() {

	if (mShape)
		delete mShape;
}

/////////////////////////////////////////////////////////////////////////////////////////

void SimpleIntersection::setShape(SimpleShape* shape) {

	if (mShape)
		delete mShape;
	mShape = shape;

}

/////////////////////////////////////////////////////////////////////////////////////////

bool SimpleIntersection::intersect() {
	
	if (mShape == 0)
		return false;

	mIntersectionValue = false;

	switch (mShape->getType()) {

		case SimpleShape::SST_Box:
			{
				SimpleBox* shape = static_cast<SimpleBox*>(mShape);
				NxBox box = NxBox(shape->getPoseAsNxMat34().t, shape->getDimensionsAsNxVec3(), shape->getPoseAsNxMat34().M);
				mIntersectionValue = mScene->getNxScene()->checkOverlapOBB(box, mShapeFilter);
			}
		break;

		case SimpleShape::SST_Sphere:
			{
				SimpleSphere* shape = static_cast<SimpleSphere*>(mShape);
				NxSphere sphere = NxSphere(shape->getPose().t, shape->getRadius());
				mIntersectionValue = mScene->getNxScene()->checkOverlapSphere(sphere, mShapeFilter);
			}
		break;

		case SimpleShape::SST_Capsule:
			{
				//  SimpleCapsule* shape = static_cast<SimpleCapsule*>(mShape);
				//	NxSphere sphere = NxCapsule(NxSegment(
				//	mScene->getNxScene()->overlapSphereShapes(sphere, mShapeFilter, 0, NULL, this);
			}
		break;

	}

	return mIntersectionValue;
}

/////////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
