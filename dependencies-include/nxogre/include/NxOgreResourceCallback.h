/** \file    NxOgreResourceCallback.h
 *  \brief   Header for the ResourceCallback class.
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

#ifndef __NXOGRE_RESOURCE_CALLBACK_H__
#define __NXOGRE_RESOURCE_CALLBACK_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreMesh.h"
#include "NxOgreHeightfield.h"

namespace NxOgre {
namespace Resources {

	/** \brief Class to tell you when an event in the Resource system is happening. 
	*/
	class NxPublicClass ResourceCallback {

		public:

			~ResourceCallback() {}

			virtual void ResourceManagerAdded(ResourceManager*)                                  {}
			virtual void ResourceManagerDestroyed(ResourceManager*)                              {}

			virtual void ResourceOpened(Resource*)                                               {}
			virtual void ResourceReadFailure(Resource*, unsigned int pos, const NxString& type)  {}
			virtual void ResourceWriteFailure(Resource*, unsigned int pos, const NxString& type) {}
			virtual void ResourceFullyRead(Resource*)                                            {}
			virtual void ResourceFullyWrote(Resource*)                                           {}
			virtual void ResourceClosed(Resource*)                                               {}

			virtual void MeshLoading(Mesh*, Resource*)                                           {}
			virtual void MeshLoaded(Mesh*)                                                       {}
			virtual void MeshLoadingFailed(Mesh*, Resource*, Mesh::Reason)                       {}
			virtual void MeshSaving(Mesh*, Resource*)                                            {}
			virtual void MeshSavingFailed(Mesh*, Resource*, Mesh::Reason)                        {}
			virtual void MeshSaved(Mesh*)                                                        {}

			virtual void MeshDestroyed(Mesh*)                                                    {}
			virtual void MeshReferenced(Mesh*, unsigned int nbReferences)                        {}
			virtual void MeshReturned(Mesh*)                                                     {}
#ifndef NX_SMALL
			virtual void ManualMeshCooking(ManualMesh*)                                          {}
			virtual void ManualMeshCooked(ManualMesh*)                                           {}
			virtual void ManualMeshCookFailure(ManualMesh*, Resource*)                           {}
#endif
			virtual void HeightfieldLoading(Heightfield*, Resource*)                             {}
			virtual void HeightfieldLoaded(Heightfield*)                                         {}
			virtual void HeightfieldLoadingFailed(Heightfield*, Resource*, Heightfield::Reason)  {}
			virtual void HeightfieldSaving(Heightfield*, Resource*)                              {}
			virtual void HeightfieldSavingFailed(Heightfield*, Resource*, Heightfield::Reason)   {}
			virtual void HeightfieldSaved(Heightfield*, Resource*)                               {}

			virtual void HeightfieldDestroyed(Heightfield*)                                      {}
			virtual void HeightfieldReferenced(Heightfield*, unsigned int nbReferences)          {}
			virtual void HeightfieldReturned(Heightfield*)                                       {}

#ifndef NX_SMALL
			virtual void ManualHeightfieldCooking(ManualHeightfield*)                            {}
			virtual void ManualHeightfieldCooked(ManualHeightfield*)                             {}
			virtual void ManualHeightfieldCookFailure(ManualHeightfield*, Resource*)             {}
#endif
	};

	/** \brief This is the default Resource callback used by the Resource System when no resource callback is
		       used by the user. Warnings and Fatal events are reported to the ErrorReporter.
	*/
	class NxPublicClass DefaultResourceCallback : public ResourceCallback {
		public:
			~DefaultResourceCallback() {}

			void ResourceReadFailure(Resource*, unsigned int pos, const NxString& type);
			void ResourceWriteFailure(Resource*, unsigned int pos, const NxString& type);
#ifndef NX_SMALL
			void ManualMeshCookFailure(ManualMesh*, Resource*);
			void ManualTerrainCookFailure(ManualHeightfield*, Resource*);
#endif
			void MeshLoadingFailed(Mesh*, Resource*, Mesh::Reason);

	};
}; // End of Resource namespace.
}; // End of NxOgre namespace.

#endif
