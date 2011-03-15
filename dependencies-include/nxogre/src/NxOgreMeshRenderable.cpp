/** \file    NxOgreMeshRenderable.cpp
 *  \see     NxOgreMeshRenderable.h
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
#include "NxOgreMeshRenderable.h"
#include "NxOgreScene.h"
#include "NxOgrePose.h"

namespace NxOgre {

//////////////////////////////////////////////////////////

void MeshRenderableParams::setToDefault() {

	ImplementationIdentifier       = NxString();
	ImplementationIdentifierType   = IT_CREATE;
	GraphicsModelIdentifier         = NxString();
	GraphicsModelPose              = Pose();
	GraphicsModelOffset            = Pose();
	GraphicsModelMaterial          = NxString();

}

//////////////////////////////////////////////////////////

void MeshRenderableParams::parse(Parameters params) {

	setToDefault();

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

		if (Set("implementation-identifier", parameter, ImplementationIdentifier)) continue;
		if (Set("i-identifier", parameter, ImplementationIdentifier)) continue;
	
		if (parameter->i == "identifier-usage" || parameter->i == "i-usage") {
			
			if (parameter->j.substr(0,1) == "c" || parameter->j.substr(0,1) == "C") {
				ImplementationIdentifierType = IT_CREATE;
			}
			else if (parameter->j.substr(0,1) == "u" || parameter->j.substr(0,1) == "U") {
				ImplementationIdentifierType = IT_USE;
			}
			else if (parameter->j.substr(0,1) == "n" || parameter->j.substr(0,1) == "N") {
				ImplementationIdentifierType = IT_NONE;
			}
			else {
				ImplementationIdentifierType = IT_CREATE;
			}

		}

		if (Set("model-identifier", parameter, GraphicsModelIdentifier)) continue;
		if (Set("m-identifier", parameter, GraphicsModelIdentifier)) continue;
		if (Set("position", parameter, GraphicsModelPose.m.t)) continue;
		if (Set("orientation", parameter, GraphicsModelPose.m.M)) continue;
		if (Set("offset-position", parameter, GraphicsModelOffset.m.t)) continue;
		if (Set("offset-orientation", parameter, GraphicsModelOffset.m.M)) continue;
		if (Set("material", parameter, GraphicsModelMaterial)) continue;

	}

}

//////////////////////////////////////////////////////////

MeshRenderable::MeshRenderable(MeshRenderableParams, Resources::Mesh* m, SceneRenderer* r)
	: Renderable(r), mMesh(m)
{}

//////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
