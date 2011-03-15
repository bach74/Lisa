/** \file    NxOgreSceneTriggerController.cpp
 *  \see     NxOgreSceneTriggerController.h
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
#include "NxOgreSceneTriggerController.h"
#include "NxOgreScene.h"
#include "NxOgreTrigger.h"
#include "NXOgreTriggerCallback.h"
#include "NxOgreVoidPointer.h"

namespace NxOgre {

//////////////////////////////////////////////////////////////////////////////

SceneTriggerController::SceneTriggerController(Scene* scene) : mScene(scene) {
	mNxScene = mScene->getNxScene();
}

//////////////////////////////////////////////////////////////////////////////

SceneTriggerController::~SceneTriggerController() {

}

//////////////////////////////////////////////////////////////////////////////

void SceneTriggerController::onTrigger(NxShape& trigger_shape, NxShape& collision_shape, NxTriggerFlag flags) {

	// Check to see if both Trigger and Actor are NxOgre created. This won't work will
	// all cases, there is bound to be one developer who thinks VoidPointer is their own
	// personal playground. But the next piece of code will crash for them, and they'll
	// see this message if they bother to debug it. Well done you.

	if (!trigger_shape.getActor().userData && !collision_shape.getActor().userData)
		return;

	VoidPointer* trigger_ud = static_cast<VoidPointer*>(trigger_shape.getActor().userData);
	TriggerContactCallback* callback = 0;
	VoidPointer* collision_shape_actor_ud = static_cast<VoidPointer*>(collision_shape.getActor().userData);

	if (trigger_ud->getType() == NxOgreClass_Trigger) {

		callback = trigger_ud->toTrigger()->getCallback();
		Trigger* trigger = trigger_ud->toTrigger();

		if (collision_shape_actor_ud->getType() == NxOgreClass_Actor) {

			Actor* actor = collision_shape_actor_ud->toActor();

			switch (flags) {
				case NX_TRIGGER_ON_ENTER:
					callback->Enter(trigger, actor);
				break;

				case NX_TRIGGER_ON_LEAVE:
					callback->Exit(trigger, actor);
				break;

				case NX_TRIGGER_ON_STAY:
					callback->Stay(trigger, actor);
				break;

			}

		}
		else if (collision_shape_actor_ud->getType() == NxOgreClass_Character) {

			CharacterSystem::Character* character = collision_shape_actor_ud->toCharacter();

			switch (flags) {
				case NX_TRIGGER_ON_ENTER:
					callback->Enter(trigger, character);
				break;

				case NX_TRIGGER_ON_LEAVE:
					callback->Exit(trigger, character);
				break;

				case NX_TRIGGER_ON_STAY:
					callback->Stay(trigger, character);
				break;

			}

		}

	}
	else if (trigger_ud->getType() == NxOgreClass_Actor) {

		VoidPointer* trigger_shape_ud = static_cast<VoidPointer*>(trigger_shape.userData);
		Shape* shape = trigger_shape_ud->toShape();
		callback = shape->getTriggerCallback();

		if (collision_shape_actor_ud->getType() == NxOgreClass_Actor) {

			Actor* actor = collision_shape_actor_ud->toActor();

			switch (flags) {
				case NX_TRIGGER_ON_ENTER:
					callback->Enter(shape, actor);
				break;

				case NX_TRIGGER_ON_LEAVE:
					callback->Exit(shape, actor);
				break;

				case NX_TRIGGER_ON_STAY:
					callback->Stay(shape, actor);
				break;

			}

		}
		else if (collision_shape_actor_ud->getType() == NxOgreClass_Character) {

			CharacterSystem::Character* character = collision_shape_actor_ud->toCharacter();

			switch (flags) {
				case NX_TRIGGER_ON_ENTER:
					callback->Enter(shape, character);
				break;

				case NX_TRIGGER_ON_LEAVE:
					callback->Exit(shape, character);
				break;

				case NX_TRIGGER_ON_STAY:
					callback->Stay(shape, character);
				break;

			}

		}
	
	}


}

//////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
