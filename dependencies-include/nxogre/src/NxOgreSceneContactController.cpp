/** \file    NxOgreSceneContactController.cpp
 *  \see     NxOgreSceneContactController.h
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
#include "NxOgreSceneContactController.h"
#include "NxOgreScene.h"
#include "NxOgreGroup.h"
#include "NxOgreContactStream.h"
#include "NxOgreVoidPointer.h"

namespace NxOgre {

//////////////////////////////////////////////////////////////////////////////

SceneContactController::SceneContactController(Scene* scene) : mScene(scene) {
	mNxScene = mScene->getNxScene();
	mActors = mScene->getActors();
	mActorGroups = mScene->getActorGroups();
	mActorGroupsIndexed = mScene->getActorGroupsByIndex();
}

//////////////////////////////////////////////////////////////////////////////

SceneContactController::~SceneContactController() {

}

//////////////////////////////////////////////////////////////////////////////

void SceneContactController::onContactNotify(NxContactPair &pair, NxU32 events) {

	Actor *a, *b;
	
	if (pair.actors[0]->userData && pair.actors[1]->userData) {
		a = (static_cast<VoidPointer*>(pair.actors[0]->userData))->toActor();
		b = (static_cast<VoidPointer*>(pair.actors[1]->userData))->toActor();
	}
	else {
		return;
	}

	
	NxActorGroup agid = pair.actors[0]->getGroup();
	NxActorGroup bgid = pair.actors[1]->getGroup();
	
	ActorGroup *ag, *bg;

	ContactStream* stream = new ContactStream(pair.stream);

	switch(events) {

		case NX_NOTIFY_ON_TOUCH:
			
			ag = mActorGroupsIndexed->get(agid);
			bg = mActorGroupsIndexed->get(bgid);
			
			if (ag)
				ag->onTouch(a, b, stream);

			if (bg)
				bg->onTouch(b, a, stream);

		break;

		case NX_NOTIFY_ON_START_TOUCH:
			
			ag = mActorGroupsIndexed->get(agid);
			bg = mActorGroupsIndexed->get(bgid);
			
			if (ag)
				ag->onStartTouch(a, b, stream);

			if (bg)
				bg->onStartTouch(b, a, stream);

		break;

		case NX_NOTIFY_ON_END_TOUCH:

			ag = mActorGroupsIndexed->get(agid);
			bg = mActorGroupsIndexed->get(bgid);
			
			if (ag)
				ag->onEndTouch(a, b, stream);

			if (bg)
				bg->onEndTouch(b, a, stream);

		break;
	}

	delete stream;

}

//////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
