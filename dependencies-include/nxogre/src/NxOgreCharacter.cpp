/** \file    NxOgreCharacter.cpp
 *  \see     NxOgreCharacter.h
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

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreCharacter.h"
#include "NxOgreScene.h"
#include "NxOgreNxActorController.h"
#include "NxOgreKinematicCharacter.h"

#include "NxOgreCharacterModel.h"
#include "NxOgreCharacterMovementModel.h"

#include "NxOgreVoidPointer.h"
#include "NxOgreTimeStep.h"

namespace NxOgre {
namespace CharacterSystem {

/////////////////////////////////////////////////////////////

void CharacterParams::setToDefault() {

#if (NX_USE_CHARACTER_API == 1)
	mControllerType = CT_KINEMATIC;
#else
	mControllerType = CT_NXACTOR;
#endif

	mControllerPtr = 0;
	mStepOffset = 0.0f;
	mSlopeLimit = 0.0f;
	mUpDirection = NX_AXIS_PLUS_Y;
	//mGroupMask;
	mControllerCollisionShape = 0;

}

/////////////////////////////////////////////////////////////

Character::Character(const NxString& identifier, Pose pose, CharacterModel* model, CharacterParams params, Scene* scene)
: mName(identifier), mModel(model), mOwner(scene), mVoidPointer(0)
{

	if (model == 0) {
		NxThrow("Character Model pointer is null!");
		mDead = true;
		return;
	}

	if (params.mControllerType == params.CT_PTR && params.mControllerPtr == 0) {
		NxThrow("ControllerType is custom but given pointer is null!");
		mDead = true;
		return;
	}

	mVoidPointer = new VoidPointer(this, NxOgreClass_Character);

	// (TODO) Pass on voidpointer to controllers here.
	if (params.mControllerType == CharacterParams::CT_NXACTOR) {
		mController = NxNew(NxActorController)(pose, params.mControllerCollisionShape, scene, mVoidPointer);
	}
#if (NX_USE_CHARACTER_API == 1)
	else if (params.mControllerType == CharacterParams::CT_KINEMATIC) {
		mController = NxNew(KinematicCharacter)(pose, params.mControllerCollisionShape, scene, mVoidPointer);
	}
#endif
	else {
		mController = params.mControllerPtr;
		NxWatch(CharacterController, mController);
	}

	// Watch Model and set the garbage collection mode.
	NxWatch(CharacterModel, mModel);
	mModel->setGC();

	// Current movement model to default.
	mCurrentMovement = mModel->mDefaultMovementModel;

	// Reset all movemenet models to this.
	for (CharacterMovementModel* model = mModel->mMovementModels.begin(); model = mModel->mMovementModels.next();) {
		model->reset(this);
	}

	mCurrentMovement->enter(0, mController->getPose());

	mOwner->_registerCharacter(mName, this);
}

/////////////////////////////////////////////////////////////

Character::~Character() {

	mOwner->_unregisterCharacter(mName);

	mCurrentMovement->exit();

	// Delete bleh bleh here.
	if (mModel->mDeletionPolicy == GC_Delete)
		NxDelete(mModel);


	delete mController;
	delete mVoidPointer;

}

/////////////////////////////////////////////////////////////

void Character::simulate(const TimeStep& ts) {

	mCurrentMovement->simulate(ts.Delta);

	// get new movement vector
	const NxVec3 movementVector = mCurrentMovement->getGlobalMovementVector(ts.Delta);

	// get controller to move that vector.
	mController->move(movementVector);

	mCurrentMovement->setPose(mController->getPose());
	mCurrentMovement->simulateAfter(ts.Delta);

}

/////////////////////////////////////////////////////////////

void Character::forward() {
	mCurrentMovement->forward();
}

/////////////////////////////////////////////////////////////

void Character::backward() {
	mCurrentMovement->backward();
}

/////////////////////////////////////////////////////////////

void Character::left() {
	mCurrentMovement->left();
}

/////////////////////////////////////////////////////////////

void Character::right() {
	mCurrentMovement->right();
}

/////////////////////////////////////////////////////////////

void Character::up() {
	mCurrentMovement->up();
}

/////////////////////////////////////////////////////////////

void Character::down() {
	mCurrentMovement->down();
}

/////////////////////////////////////////////////////////////

}; // End of Character namespace.
}; // End of NxOgre namespace.

#endif
