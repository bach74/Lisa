/** \file    NxOgreShapePrimitives.cpp
 *  \see     NxOgreShapePrimitives.h
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
#include "NxOgreShapePrimitives.h"
#include "NxOgreActor.h"
#include "NxOgreHelpers.h"
#include "NxOgreVoidPointer.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

Ground::Ground(NxReal d, Ogre::Vector3 n, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.d = d;
	mShapeDescription.normal = NxConvert<NxVec3, Ogre::Vector3>(n);
}

/////////////////////////////////////////////////////////////

Ground::Ground(NxReal d, NxVec3 n, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.d = d;
	mShapeDescription.normal = n;
}

/////////////////////////////////////////////////////////////

Ground::~Ground() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Ground::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mShapeIndex = index;
	mActor = actor;
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;
	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	NxShape* shape = actor->createShape(mShapeDescription);
	setNxShape(shape);
}

/////////////////////////////////////////////////////////////

void Ground::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;
}

/////////////////////////////////////////////////////////////

void Ground::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

Cube::Cube(Ogre::Vector3 size, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.dimensions.set(NxConvert<NxVec3, Ogre::Vector3>(0.5f * size));
}

/////////////////////////////////////////////////////////////

Cube::Cube(NxVec3 size, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.dimensions.set(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);
}

/////////////////////////////////////////////////////////////

Cube::Cube(NxReal size, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.dimensions.set(size * 0.5f, size * 0.5f, size * 0.5f);
}

/////////////////////////////////////////////////////////////

Cube::Cube(NxReal sizeX, NxReal sizeY, NxReal sizeZ, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.dimensions.set(sizeX * 0.5f, sizeY * 0.5f, sizeZ * 0.5f);
}

/////////////////////////////////////////////////////////////

Cube::~Cube() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Cube::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mShapeIndex = index;
	mActor = actor;
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	NxShape* shape = actor->createShape(mShapeDescription);
	setNxShape(shape);
}

/////////////////////////////////////////////////////////////

void Cube::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;
}

/////////////////////////////////////////////////////////////

void Cube::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

void Cube::setDimensions(const NxVec3& size) {
	if (mNxShape) {
		NxBoxShape* sh = static_cast<NxBoxShape*>(mNxShape);
		sh->setDimensions(size * 2);
	}
	else {
		mShapeDescription.dimensions = size;
	}
}

/////////////////////////////////////////////////////////////

NxVec3 Cube::getDimensions() const {

	if (mNxShape) {
		NxBoxShape* sh = static_cast<NxBoxShape*>(mNxShape);
		return sh->getDimensions() * 2;
	}

	return mShapeDescription.dimensions;
	
}

/////////////////////////////////////////////////////////////

Sphere::Sphere(NxReal radius, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.radius = radius;
}

/////////////////////////////////////////////////////////////

Sphere::~Sphere() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Sphere::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mShapeIndex = index;
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	NxShape* shape = actor->createShape(mShapeDescription);
	setNxShape(shape);
}

/////////////////////////////////////////////////////////////

void Sphere::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene) {

	extendedParamsToDescription(scene, mParams, &mShapeDescription);

	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;
}

/////////////////////////////////////////////////////////////

void Sphere::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

Capsule::Capsule(NxReal radius, NxReal height, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mShapeDescription.radius = radius;
	mShapeDescription.height = height;
}

/////////////////////////////////////////////////////////////

Capsule::~Capsule() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Capsule::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mShapeIndex = index;
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;
	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	NxShape* shape = actor->createShape(mShapeDescription);
	setNxShape(shape);
}

/////////////////////////////////////////////////////////////

void Capsule::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene) {
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;
	if (mParams.mTrigger) {
		mTriggerCallback = mParams.mTriggerCallback;
		mShapeDescription.shapeFlags |= NX_TRIGGER_ENABLE;
	}
	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;
}

/////////////////////////////////////////////////////////////

void Capsule::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.

