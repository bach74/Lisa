/** \file    NxOgreSimpleActor.cpp
 *  \see     NxOgreSimpleActor.h
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
#include "NxOgreSimpleActor.h"
#include "NxOgreSimpleShape.h"
#include "NxOgrePose.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

SimpleActor::SimpleActor(Scene* scene) 
: mScene(scene), mActor(0) {}

/////////////////////////////////////////////////////////////

SimpleActor::~SimpleActor() {

}

/////////////////////////////////////////////////////////////

void SimpleActor::_addShapeToDescription(SimpleShape* shape, NxActorDesc* actor_description, bool gp) {

	switch(shape->getType()) {

		case SimpleShape::SST_Box: {


			SimpleBox* sb = shape->getAsBox();
			NxBoxShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.dimensions  = sb->getDimensionsAsNxVec3();

			if (gp)
				actor_description->globalPose = sb->getPose();
			else
				shape_description.localPose = sb->getPose();

			actor_description->shapes.push_back(&shape_description);

		} break;

		case SimpleShape::SST_Sphere: {

			SimpleSphere* ss = shape->getAsSphere();
			NxSphereShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.radius = ss->getRadius();

			if (gp)
				actor_description->globalPose = ss->getPose();
			else
				shape_description.localPose = ss->getPose();

			actor_description->shapes.push_back(&shape_description);

		} break;

		case SimpleShape::SST_Capsule: {

			SimpleCapsule* sc = shape->getAsCapsule();
			NxCapsuleShapeDesc shape_description;
			shape_description.setToDefault();
			shape_description.radius = sc->getRadius();
			shape_description.height = sc->getHeight();
			actor_description->shapes.push_back(&shape_description);

			if (gp)
				actor_description->globalPose = sc->getPose();
			else
				shape_description.localPose = sc->getPose();

			actor_description->shapes.push_back(&shape_description);

		} break;

	}

	delete shape;

}

/////////////////////////////////////////////////////////////

void SimpleActor::setGlobalPose(const Pose&) {

}

/////////////////////////////////////////////////////////////

Pose SimpleActor::getGlobalPose() const {
	Pose pose;
	return pose;
}

/////////////////////////////////////////////////////////////

NxActor* SimpleActor::getNxActor() {
	return mActor;
}

/////////////////////////////////////////////////////////////

Scene* SimpleActor::getScene() {
	return mScene;
}

/////////////////////////////////////////////////////////////

} // End of NxOgre namespace.
