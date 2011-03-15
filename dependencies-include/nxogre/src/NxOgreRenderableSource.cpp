/** \file    NxOgreRenderableSource.cpp
 *  \see     NxOgreRenderableSource.h
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
#include "NxOgreRenderableSource.h"
#include "NxOgreRenderable.h"
#include "NxOgreHelpers.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

void RenderableSource::setRenderMode(RenderMode rm) {
	
	reset();

	mRenderMode = rm;

	switch (rm) {

		default:
		case RM_Absolute:
			{
				mRenderFunction = &RenderableSource::render_Absolute;
			}
		break;
		
		case RM_Interpolate:
			{
				mRenderFunction = &RenderableSource::render_Interpolate;
			}
		break;

	};

}

/////////////////////////////////////////////////////////////

void RenderableSource::setCustomRenderMode(RenderFunctionPtr func) {
	mRenderMode = RM_Custom;
	mRenderFunction = func;
}

/////////////////////////////////////////////////////////////

void RenderableSource::setRenderable(Renderable* renderable) {
	mRenderable = renderable;
}

/////////////////////////////////////////////////////////////

Renderable* RenderableSource::getRenderable() {
	return mRenderable;
}

/////////////////////////////////////////////////////////////

NxString RenderableSource::getRenderableType() const {
	if (mRenderable == 0)
		return "Unknown";
	return mRenderable->getType();
}

/////////////////////////////////////////////////////////////

NxShortHashIdentifier RenderableSource::getRenderableTypeHash() {
	if (mRenderable == 0)
		return 0;
	return mRenderable->getHashType();
}

/////////////////////////////////////////////////////////////

void RenderableSource::render(const TimeStep& ts) {
	(this->*mRenderFunction)(ts);
}

/////////////////////////////////////////////////////////////

void RenderableSource::render_Absolute(const TimeStep& ts) {
	mRenderPose = getSourcePose(ts);
	mRenderable->setPose(mRenderPose);
}

/////////////////////////////////////////////////////////////

void RenderableSource::render_Interpolate(const TimeStep& ts) {
	Pose sourcePose = getSourcePose(ts);
	mRenderPose = NxInterpolate(mAlphaPose, sourcePose, ts.Alpha);
	mRenderable->setPose(mRenderPose);
	mAlphaPose = sourcePose; /// \note May be mRenderPose, need to check with Luis.

}

/////////////////////////////////////////////////////////////

void RenderableSource::reset() {
	mRenderPose.id();
	mAlphaPose.id();
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
