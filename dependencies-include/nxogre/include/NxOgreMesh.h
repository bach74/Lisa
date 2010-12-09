/** \file    NxOgreMesh.h
 *  \brief   Header for the Mesh class.
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


#ifndef __NXOGRE_MESH_H__
#define __NXOGRE_MESH_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass Mesh {

		friend class ResourceSystem;
		friend class ManualMesh;
		friend class ManualMeshUtil;
		friend class Convex;
		friend class TriangleMesh;

		public:

			Mesh();
			Mesh(const ResourceIdentifier&);
			Mesh(Resource*);
			~Mesh();

			void load(Resource*);
			void load(const ResourceIdentifier&);
#ifndef NX_SMALL
			void save(Resource*);
#endif

#ifndef NX_SMALL
			void save(const ResourceIdentifier&);
#endif
			MeshType  getType() const;
			NxU32     getReferenceCount() const;
			MeshType  getMeshTypeFromResource(Resource*);

			enum Reason {
				R_HasMesh         = 0,
				R_InvalidResource = 1,
			};

		protected:

			struct MeshData {

				void set(MeshType, void* data);
				void set(NxConvexMesh*);
				void set(NxTriangleMesh*);
				void set(NxCCDSkeleton*);
				void set(NxClothMesh*);
				void set(NxSoftBodyMesh*);
				void increaseReference();
				void decreaseReference();
				void zero();
				bool isZero() const;
				void destroy();

				NxTriangleMesh*                mTriangleMesh;
				NxConvexMesh*                  mConvexMesh;
				NxCCDSkeleton*                 mSkeletonMesh;
				NxClothMesh*                   mClothMesh;
				NxSoftBodyMesh*                mSoftBodyMesh;
				MeshType                       mType;
				NxU32                          mNbReferences;
				Betajaen::SharedList<float3>*  mTextureCoordinates;
				MaterialAlias*                 mMaterialAlias;
			};

			MeshData       mMesh;

			/// \internal BJN<42><RESOURCE:HEADER><RESOURCE:LENGTH_INCLUDING_HEADER><DATA>
			ResourceType   getNextResourceTypeFromResource(Resource*);
			
			/// \internal BJN<42>TXCO
			void _load_TextureCoords();

			/// \internal BJN<42>TXCO
			void _write_TextureCoords(bool uv_or_uvw, Betajaen::Flat<float3>*);

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif
