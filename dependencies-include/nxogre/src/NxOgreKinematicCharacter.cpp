/** \file    NxOgreKinematicCharacter.cpp
 *  \see     NxOgreKinematicCharacter.h
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

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreKinematicCharacter.h"
#include "NxOgreSimpleShape.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreScene.h"

// BoxController.cpp, 42
#define NX_KINEMATIC_CHARACTER_SHAPE_DELTA 0.8

namespace NxOgre {
namespace CharacterSystem {

////////////////////////////////////////////////////

KinematicCharacter::KinematicCharacter(NxMat34 pose, SimpleShape* shape, Scene* scene, VoidPointer* vptr)
: CharacterController(scene, vptr), mActor(0), mUserData(0), mShapeUserData(0)
{
	NxActorDesc a_desc;
	NxBodyDesc b_desc;
	a_desc.body = &b_desc;

	if (shape->getType() == SimpleShape::SST_Box) {

		SimpleBox* box = shape->getAsBox();
		NxBoxShapeDesc shape_desc;
		shape_desc.dimensions = (box->getDimensionsAsNxVec3() * 0.5f) * NX_KINEMATIC_CHARACTER_SHAPE_DELTA;
		mShapeUserData = NxNew(VoidPointer)(vptr->Ptr, NxOgreClass_CharacterShape, vptr->RenderPtr);
		shape_desc.userData = mShapeUserData;
		a_desc.shapes.pushBack(&shape_desc);

	}
	else if (shape->getType() == SimpleShape::SST_Capsule) {

		SimpleCapsule* capsule = shape->getAsCapsule();
		NxCapsuleShapeDesc shape_desc;
		shape_desc.radius = capsule->getRadius() * NX_KINEMATIC_CHARACTER_SHAPE_DELTA;
		shape_desc.height = capsule->getHeight() * NX_KINEMATIC_CHARACTER_SHAPE_DELTA;
		mShapeUserData = NxNew(VoidPointer)(vptr->Ptr, NxOgreClass_CharacterShape, vptr->RenderPtr);
		shape_desc.userData = mShapeUserData;
		a_desc.shapes.pushBack(&shape_desc);

	}
	else {
		NxThrow("Invalid shape passed to KinematicCharacter must be capsule or box");
		return;
	}

	a_desc.density = 10.0f;
	a_desc.globalPose = pose;
	b_desc.flags |= NX_BF_KINEMATIC;
	a_desc.userData = (void*) vptr;

	NxDelete(shape);

	mActor = mScene->getNxScene()->createActor(a_desc);

}

////////////////////////////////////////////////////

KinematicCharacter::~KinematicCharacter() {
	NxDelete(mShapeUserData);
	if (mActor)
		mScene->getNxScene()->releaseActor(*mActor);
}

////////////////////////////////////////////////////

void KinematicCharacter::init(NxMat34 pose) {
	// move mActor to pose.
}

////////////////////////////////////////////////////

void KinematicCharacter::move(const NxVec3& direction) {
	// Ahhh. So temp, so very temp.
	mActor->moveGlobalPosition(getPosition() + direction);
}

////////////////////////////////////////////////////

void KinematicCharacter::setPosition(const NxVec3& position) {

}

////////////////////////////////////////////////////

NxVec3 KinematicCharacter::getPosition() const {
	// Temp.
	return mActor->getGlobalPosition();
}

////////////////////////////////////////////////////

void KinematicCharacter::setOrientation(const NxQuat& orientation) {

}

////////////////////////////////////////////////////

NxQuat KinematicCharacter::getOrientation() const {
	NxQuat q;q.id();
	return q;
}

////////////////////////////////////////////////////

NxMat34 KinematicCharacter::getPose() const {
	// Temp.
	return mActor->getGlobalPose();
}

////////////////////////////////////////////////////

void KinematicCharacter::setSize(const NxVec3& size) {

}

////////////////////////////////////////////////////

NxVec3 KinematicCharacter::getSize() const {
	return NxVec3(0,0,0);
}

////////////////////////////////////////////////////

void KinematicCharacter::setStepSize(NxReal stepSize) {

}

////////////////////////////////////////////////////

NxReal KinematicCharacter::getStepSize() const {
	return 0;
}

////////////////////////////////////////////////////

void KinematicCharacter::setSlopeLimit(NxRadian slopeLimit) {

}

////////////////////////////////////////////////////

NxRadian KinematicCharacter::getSlopeLimit() const {
	return 0;
}

////////////////////////////////////////////////////

void KinematicCharacter::setGravityEnabled(bool gravity) {

}

////////////////////////////////////////////////////

bool KinematicCharacter::getGravityEnabled() const {
	return false;
}

////////////////////////////////////////////////////

void KinematicCharacter::setUpDirection(NxVec3 upDirection) {

}

////////////////////////////////////////////////////

NxVec3 KinematicCharacter::getUpDirection() const {
	return NxVec3(0,0,0);
}

////////////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#undef NX_KINEMATIC_CHARACTER_SHAPE_DELTA

#endif
