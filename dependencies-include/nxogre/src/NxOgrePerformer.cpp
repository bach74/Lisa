/** \file    NxOgrePerformer.cpp
 *  \see     NxOgrePerformer.h
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

#include "NxOgrePerformer.h"
#include "NxOgreCharacter.h"
#include "NxOgreDualIdentifier.h"
#include "NxOgreOgreNodeRenderable.h"
#include "NxOgreRenderable.h"
#include "NxOgreRenderableSource.h"
#include "NxOgreNodeRenderable.h"
#include "NxOgreSceneRenderer.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreScene.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreHelpers.h"
#include "NxOgreCharacterController.h"

namespace NxOgre {
namespace CharacterSystem {

/////////////////////////////////////////////////////////////////////

Performer::Performer(const VisualIdentifier& identifier, const Pose& pose, CharacterModel* model, const CharacterParams& params, Scene* scene)
: Character(identifier.getIdentifier(), pose, model, params, scene)
{

	NodeRenderableParams visualParams;
	visualParams.setToDefault();
	visualParams.mIdentifier = mName;
	visualParams.mIdentifierUsage = NodeRenderableParams::IU_Create;
	visualParams.mIntent = getStringType();

	NxString visualIdentifier = identifier.getVisualIdentifier();

	if (NxStringStartsWith(visualIdentifier, "(reference)")) {
		NxString graphicsModel = NxStringSubstr(visualIdentifier, 11);
		NxStringTrim(graphicsModel);
		visualParams.mGraphicsModel = graphicsModel;
		visualParams.mGraphicsModelType = NodeRenderableParams::GMU_Reference;
	}
	else {
		visualParams.mGraphicsModel = visualIdentifier;
		visualParams.mGraphicsModelType = NodeRenderableParams::GMU_Resource;
	}

	setRenderMode(RM_Absolute);
	mRenderable = mOwner->getSceneRenderer()->createNodeRenderable(visualParams);
	mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
	mVoidPointer->RenderPtr = this;

	mOwner->getSceneRenderer()->registerSource(this);

}

/////////////////////////////////////////////////////////////////////

Performer::Performer(const NxString& identifier, const Pose& pose, CharacterModel* model, const CharacterParams& params, const NodeRenderableParams& visualParams, Scene* scene)
: Character(identifier, pose, model, params, scene)
{
	
	setRenderMode(RM_Absolute);

	mRenderable = mOwner->getSceneRenderer()->createNodeRenderable(visualParams);
	mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
	mVoidPointer->RenderPtr = this;

	mOwner->getSceneRenderer()->registerSource(this);
}

/////////////////////////////////////////////////////////////////////

Performer::~Performer() {

	mOwner->getSceneRenderer()->unregisterSource(this);

	if (mRenderable) {
		delete mRenderable;
		mRenderable = 0;
	}

}

/////////////////////////////////////////////////////////////////////

Pose Performer::getSourcePose(const TimeStep&) const {
	return Pose(mController->getPose());
}

/////////////////////////////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
