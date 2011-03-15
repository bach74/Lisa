/** \file    NxOgreNodeRenderable.cpp
 *  \see     NxOgreNodeRenderable.h
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
#include "NxOgreNodeRenderable.h"
#include "NxOgreScene.h"
#include "NxOgrePose.h"
#include "NxOgreHelpers.h"
#include "NxOgreRenderableSource.h"

namespace NxOgre {

//////////////////////////////////////////////////////////

void NodeRenderableParams::setToDefault() {

	mMode                   = RenderableSource::RM_Absolute;
	mIdentifier             = NxString();
	mIdentifierUsage        = IU_Create;
	mGraphicsModel          = NxString();
	mGraphicsModelType      = GMU_Resource;
	mGraphicsModelScale     = NxVec3(1,1,1);
	mGraphicsModelPose      = Pose();
	mGraphicsModelOffset    = Pose();
	mGraphicsModelMaterial  = NxString();

}

//////////////////////////////////////////////////////////

void NodeRenderableParams::parse(Parameters params) {

	setToDefault();

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

		if (Set("identifier", parameter, mIdentifier)) continue;

		if (parameter->i == "identifier-type") {
			
			if (parameter->j.substr(0,1) == "c" || parameter->j.substr(0,1) == "C") {
				mIdentifierUsage = IU_Create;
			}
			else if (parameter->j.substr(0,1) == "r" || parameter->j.substr(0,1) == "R") {
				mIdentifierUsage = IU_Use;
			}
			else {
				mIdentifierUsage = IU_Create;
			}

		}

		if (Set("model", parameter, mGraphicsModel)) continue;

		if (parameter->i == "model-type") {
			
			NxString mt = parameter->j;
			NxStringToLower(mt);

			if (mt == "resource") {
				mGraphicsModelType = GMU_Resource;
			}
			else if (mt == "file") {
				mGraphicsModelType = GMU_File;
			}
			else if (mt == "reference"){
				mGraphicsModelType = GMU_Reference;
			}
			else {
				mGraphicsModelType = GMU_Resource;
			}

		}

		if (Set("scale", parameter, mGraphicsModelScale)) continue;
		if (Set("position", parameter, mGraphicsModelPose.m.t)) continue;
		if (Set("orientation", parameter, mGraphicsModelPose.m.M)) continue;
		if (Set("offset-position", parameter, mGraphicsModelOffset.m.t)) continue;
		if (Set("offset-orientation", parameter, mGraphicsModelOffset.m.M)) continue;
		if (Set("material", parameter, mGraphicsModelMaterial)) continue;

	}

}

//////////////////////////////////////////////////////////

NodeRenderable::NodeRenderable(const NodeRenderableParams&, SceneRenderer* r) : Renderable(r)
{}

//////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
