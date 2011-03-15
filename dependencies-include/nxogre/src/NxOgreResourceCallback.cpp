/** \file    NxOgreResourceCallback.cpp
 *  \see     NxOgreResourceCallback.h
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
#include "NxOgreResourceCallback.h"
#include "NxOgreResource.h"
#include "NxOgreHelpers.h"
#include "NxOgreManualMesh.h"
#include "NxOgreMesh.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

void DefaultResourceCallback::ResourceReadFailure(Resource* resource, unsigned int pos, const NxString& type) {
	NxString warning_text = "Could not read a '" + type + "'.";
	NxThrow_impl(warning_text.c_str(), 1, resource->getResourceIdentifier().c_str(), pos);
}

/////////////////////////////////////////////////////////////

void DefaultResourceCallback::ResourceWriteFailure(Resource* resource, unsigned int pos, const NxString& type) {
	NxString warning_text = "Could not write a '" + type + "'.";
	NxThrow_impl(warning_text.c_str(), 1, resource->getResourceIdentifier().c_str(), pos);
}

/////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void DefaultResourceCallback::ManualMeshCookFailure(ManualMesh* mmesh, Resource* resource) {
	NxString cooking_text;
	cooking_text.append("Manual mesh could not be cooked. Reasons are:");
	if (!mmesh->isValid())
		cooking_text.append("Manual mesh is in valid!");
	/// \todo Reasons here.
	NxThrow_impl(cooking_text.c_str(), 1, resource->getResourceIdentifier().c_str(), 0);
}

#endif

/////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void DefaultResourceCallback::ManualTerrainCookFailure(ManualHeightfield*, Resource*) {
	/// \todo
}

#endif

/////////////////////////////////////////////////////////////

void DefaultResourceCallback::MeshLoadingFailed(Mesh*, Resource* resource, Mesh::Reason reason) {
	NxString text("Mesh (" + resource->getResourceIdentifier() + ") could not be loaded!");
	if (reason == Mesh::R_HasMesh)
		text.append(" - Mesh is already loaded");
	NxThrow_impl(text.c_str(), 1, "Mesh::load", 0);
}

}; // End of Resources namespace.
}; // End of NxOgre namespace.
