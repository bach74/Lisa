/** \file    NxOgreManualMesh.h
 *  \brief   Header for the ManualMesh class.
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


#ifndef __NXOGRE_MANUAL_MESH_UTIL_H__
#define __NXOGRE_MANUAL_MESH_UTIL_H__

#include "NxOgrePrerequisites.h"

#ifndef NX_SMALL

#include "NxOgreMeshParams.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass ManualMeshUtil {

		public:

			static ManualMesh*  createSheet(MeshType, float2 size, float2 division, MeshParams = MeshParams(), bool doubleSized = false);
			static Mesh*        cookSheet(MeshType, float2 size, float2 division, MeshParams = MeshParams(), bool doubleSized = false);

			static ManualMesh*  createBox(MeshType, NxVec3 size, MeshParams = MeshParams(), NxU32 subdivision_level = 1);
			static Mesh*        cookBox(MeshType, NxVec3 size, MeshParams = MeshParams(), NxU32 subdivision_level = 1);
			
			static ManualMesh*  createSphere(MeshType, NxReal radius, MeshParams = MeshParams(), NxU32 subdivision_level = 4);
			static Mesh*        cookSphere(MeshType, NxReal radius, MeshParams = MeshParams(), NxU32 subdivision_level = 4);
			
			static ManualMesh*  createTetrahedron(MeshType, NxVec3 size, MeshParams = MeshParams());
			static Mesh*        cookTetrahedron(MeshType, NxVec3 size, MeshParams = MeshParams());

		private:

			static ManualMesh*  __createSheet_as_Triangle(float2 size, float2 division, bool ds, MeshParams);
			static ManualMesh*  __createSheet_as_Convex(float2 size, float2 division, bool ds, MeshParams);
			static ManualMesh*  __createSheet_as_Cloth(float2 size, float2 division, bool ds, MeshParams);
			static ManualMesh*  __createSheet_as_Softbody(float2 size, float2 division, bool ds, MeshParams);
			static ManualMesh*  __createSheet_as_Skeleton(float2 size, float2 division, bool ds, MeshParams);

			static ManualMesh*  __createBox_as_Triangle(NxVec3 size, NxReal sl, MeshParams);
			static ManualMesh*  __createBox_as_Convex(NxVec3 size, NxReal sl, MeshParams);
			static ManualMesh*  __createBox_as_Cloth(NxVec3 size, NxReal sl, MeshParams);
			static ManualMesh*  __createBox_as_Softbody(NxVec3 size, NxReal sl, MeshParams);
			static ManualMesh*  __createBox_as_Skeleton(NxVec3 size, NxReal sl, MeshParams);

			static ManualMesh*  __createSphere_as_Triangle(NxReal r, MeshParams);
			static ManualMesh*  __createSphere_as_Convex(NxReal r, MeshParams);
			static ManualMesh*  __createSphere_as_Cloth(NxReal r, MeshParams);
			static ManualMesh*  __createSphere_as_Softbody(NxReal r, MeshParams);
			static ManualMesh*  __createSphere_as_Skeleton(NxReal r, MeshParams);

			static ManualMesh*  __createTetrahedron_as_Triangle(NxVec3 size, MeshParams);
			static ManualMesh*  __createTetrahedron_as_Convex(NxVec3 size, MeshParams);
			static ManualMesh*  __createTetrahedron_as_Cloth(NxVec3 size, MeshParams);
			static ManualMesh*  __createTetrahedron_as_Softbody(NxVec3 size, MeshParams);
			static ManualMesh*  __createTetrahedron_as_Skeleton(NxVec3 size, MeshParams);

			ManualMeshUtil() {}
			~ManualMeshUtil() {}

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.
#endif

#endif
