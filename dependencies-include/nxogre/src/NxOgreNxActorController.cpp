/** \file    NxOgreNxActorController.cpp
 *  \see     NxOgreNxActorController.h
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

#include "NxOgreNxActorController.h"

namespace NxOgre {
namespace CharacterSystem {

////////////////////////////////////////////////////

NxActorController::NxActorController(NxMat34 pose, SimpleShape* shape, Scene* scene, VoidPointer* ptr)
 : CharacterController(scene, ptr) {

}

////////////////////////////////////////////////////

NxActorController::~NxActorController() {

}

////////////////////////////////////////////////////

NxActorGroup NxActorController::getActorGroup() {
	return mActor->getGroup();
}

////////////////////////////////////////////////////

NxCollisionGroup NxActorController::getCollisionGroup() {
	return mShape->getGroup();
}

////////////////////////////////////////////////////

void NxActorController::setActorGroup(NxActorGroup) {

}

////////////////////////////////////////////////////

void NxActorController::setCollisionGroup(NxCollisionGroup) {

}

////////////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
