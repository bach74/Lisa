/** \file    NxOgreTrigger.cpp
 *  \see     NxOgreTrigger.h
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
#include "NxOgreTrigger.h"
#include "NxOgreTriggerCallback.h"
#include "NxOgreSimpleActor.h"
#include "NxOgreScene.h"
#include "NxOgreSimpleShape.h"
#include "NxOgreVoidPointer.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////////////

Trigger::Trigger(SimpleShape* shape, TriggerContactCallback* callback, Scene* scene)
: SimpleActor(scene), mCallback(callback)
{

	NxActorDesc  actor_description;
	actor_description.setToDefault();

	switch(shape->getType()) {

		case SimpleShape::SST_Box: {

			SimpleBox* sb = shape->getAsBox();
			NxBoxShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.dimensions  = sb->getDimensionsAsNxVec3();
			shape_description.shapeFlags |= NX_TRIGGER_ENABLE;

			actor_description.globalPose = sb->getPose();
			actor_description.shapes.push_back(&shape_description);

		} break;

		case SimpleShape::SST_Sphere: {

			SimpleSphere* ss = shape->getAsSphere();
			NxSphereShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.radius = ss->getRadius();
			shape_description.shapeFlags |= NX_TRIGGER_ENABLE;

			actor_description.globalPose = ss->getPose();
			actor_description.shapes.push_back(&shape_description);

		} break;

		case SimpleShape::SST_Capsule: {

			SimpleCapsule* sc = shape->getAsCapsule();
			NxCapsuleShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.radius = sc->getRadius();
			shape_description.height = sc->getHeight();
			shape_description.shapeFlags |= NX_TRIGGER_ENABLE;

			actor_description.globalPose = sc->getPose();
			actor_description.shapes.push_back(&shape_description);

		} break;

	}

	delete shape;

	mUserData = new VoidPointer(this, NxOgreClass_Trigger);
	actor_description.userData = mUserData;

	mActor = scene->getNxScene()->createActor(actor_description);

}

/////////////////////////////////////////////////////////////////////

Trigger::~Trigger() {
	
	if (mCallback)
		if (mCallback->mDeletionPolicy == GC_Delete)
			delete mCallback;

	delete mUserData;

	mScene->getNxScene()->releaseActor(*mActor);
	
}

/////////////////////////////////////////////////////////////////////

void Trigger::addSimpleShape(SimpleShape*) {

}

/////////////////////////////////////////////////////////////////////

Actors Trigger::getActors() {
	NxUnderConstruction;
	Actors actors;
	// ... Lots of code goes here.
	return actors;
}

/////////////////////////////////////////////////////////////////////

}; // End of NxOgre namespace.

