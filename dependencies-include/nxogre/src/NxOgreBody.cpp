/** \file    NxOgreBody.cpp
 *  \see     NxOgreBody.h
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
#include "NxOgreBody.h"
#include "NxOgreActor.h"		// For: Body inherits Actor
#include "NxOgrePose.h"			// For: conversions
#include "NxOgreHelpers.h"		// For: conversions
#include "NxOgreScene.h"		// For: Actor::mOwner
#include "NxOgreContainer.h"
#include "NxOgreOgreNodeRenderable.h"
#include "NxOgreRenderable.h"
#include "NxOgreRenderableSource.h"
#include "NxOgreNodeRenderable.h"
#include "NxOgreSceneRenderer.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreHelpers.h"

namespace NxOgre {

//////////////////////////////////////////////////////////

Body::Body(const VisualIdentifier& identifier, Scene* scene, Shape *firstShapeDescription,
		   const Pose& pose, const ActorParams& params)
:	Actor(identifier.getIdentifier(), scene, firstShapeDescription, pose, params)
	
{

	NodeRenderableParams visualParams;
	visualParams.setToDefault();
	visualParams.mIdentifier = mName;
	visualParams.mIdentifierUsage = NodeRenderableParams::IU_Create;
	visualParams.mIntent = getStringType();

	NxString visualIdentifier = identifier.getVisualIdentifier();

	
	if (NxStringStartsWith(visualIdentifier, "(reference)")) {
		// (TODO) (Less STL references) Make a function for.
		NxString entityName = visualIdentifier.substr(11, entityName.length() - 11);
		NxStringTrim(entityName);
		visualParams.mGraphicsModel = entityName;
		visualParams.mGraphicsModelType = NodeRenderableParams::GMU_Reference;
	}
	else {
		visualParams.mGraphicsModel = visualIdentifier;
		visualParams.mGraphicsModelType = NodeRenderableParams::GMU_Resource;
	}


	setRenderMode(visualParams.mMode);

	mRenderable = mOwner->getSceneRenderer()->createNodeRenderable(visualParams);
	mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
	mVoidPointer->RenderPtr = this;

	mOwner->getSceneRenderer()->registerSource(this);

}

//////////////////////////////////////////////////////////

Body::Body(const NxString& identifier, Scene* scene, Shape *firstShapeDescription,
		   const Pose& pose, const NodeRenderableParams& visualParams, const ActorParams& params)
: Actor(identifier, scene, firstShapeDescription, pose, params)
{

	setRenderMode(visualParams.mMode);

	mRenderable = mOwner->getSceneRenderer()->createNodeRenderable(visualParams);
	mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
	mVoidPointer->RenderPtr = this;
	

	mOwner->getSceneRenderer()->registerSource(this);
}

//////////////////////////////////////////////////////////

Body::~Body() {

	mOwner->getSceneRenderer()->unregisterSource(this);

	if (mRenderable) {
		delete mRenderable;
		mRenderable = 0;
	}


}

//////////////////////////////////////////////////////////

Pose Body::getSourcePose(const TimeStep&) const {
	return getGlobalPose();
}

//////////////////////////////////////////////////////////

}  //End of NxOgre namespace.
