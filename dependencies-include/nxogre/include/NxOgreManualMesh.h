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


#ifndef __NXOGRE_MANUAL_MESH_H__
#define __NXOGRE_MANUAL_MESH_H__

#include "NxOgrePrerequisites.h"

#ifndef NX_SMALL

#include "NxOgreMeshParams.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass ManualMesh {

		public:

			/** \brief A Mesh that can be built by hand
				\param MeshType       The type of mesh; Triangle, Convex, SoftBody, Cloth or CCDSkeleton.
				\param estimatedSize  estimatedSize of the Mesh (in vertices).
				\note  Using the estimatedSize the sizes of the parts of mesh are as following
				   - Vertices   = estimatedSize
				   - Indices    = estimatedSize * 3
				   - Normals    = estimatedSize * 3
				   - TexCoords  = estimatedSize * 3 * 2
				   - Tetrahedra = estimatedSize * 4
				These are of course depending on the type of mesh which may or may not use these.

				\note MeshTypes uses these
				    - Triangle  -> Vertices, Indices (optional, but recommended to include).
				    - Convex    -> Vertices. Indices (<=256) are optional.
				    - Cloth     -> Vertices, Indices, Normals, TexCoords.
				    - SoftBody  -> Vertices, Indices, Normals, TexCoords and Tetrahedra.
				    - Skeleton  -> Vertices (<= 64), Indices.

				\note If indices are not used in a Convex mesh, then it is known as a Convex point cloud
				      which PhysX will try and build a convex shape out of them, if you have specifics
				      use the Indices.
			*/
			ManualMesh(MeshType, NxU32 estimatedSize = 12, MeshParams = MeshParams());
			~ManualMesh();

			MeshType       getType() const;

			void begin();

			/** \brief Reserve vertices, normals and texture coordinates.
				\note  Normals and TextureCoordinates are obviously not reserved if the MeshType does
				       not use them.
			*/
			void estimateVertices(unsigned int size);

			/** \brief Reserve indices.
			*/
			void estimateIndices(unsigned int size);

			/** \brief Reserve tetrahedra.
			*/
			void estimateTetrahedra(unsigned int size);

			/** \brief Get number of vertices
			*/
			NxU32 getNbVertices() const;

			/** \brief Get number of indices
			*/
			NxU32 getNbIndices() const;

			/** \brief Get number of normals
			*/
			NxU32 getNbNormals() const;

			/** \brief Get number of texture coordinates
			*/
			NxU32 getNbTexCoords() const;

			/** \brief Get number of Tetrahedra
			*/
			NxU32 getNbTetrahedra() const;

			/** \brief  Add a vertex.
			    \return The vertex position, which can be used with index.
			*/
			NxU32 vertex(const NxVec3&);

			/** \brief  Add a vertex as a float3.
			    \return The vertex position, which can be used with index.
			*/
			NxU32 vertex(const float3&);

			/** \brief  Add a vertex as NxReals.
			    \return The vertex position, which can be used with index.
			*/
			NxU32 vertex(NxReal x, NxReal y, NxReal z);

			/** \brief Add an index.
			*/
			void index(NxU32);

			/** \brief Add three indexes (equilvent to calling index three times)
			*/
			void triangle(NxU32, NxU32, NxU32);

			/** \brief Normal as NxVec3.
			*/
			void normal(const NxVec3&);

			/** \brief Normal as float3.
			*/
			void normal(const float3&);

			/** \brief Normal as float3.
			*/
			void normal(NxReal x, NxReal y, NxReal z);

			/** \brief Coordinates using a UV mapping.
				\note  All following coordinates must be specified in this format.
			*/
			void coords(NxReal u, NxReal v);

			/** \brief Coordinates using a UVW mapping.
				\note  All following coordinates must be specified in this format.
			*/
			void coords(NxReal u, NxReal v, NxReal w);

			/** \brief Tetrahedra as a float4
			*/
			void tetrahedra(const float4&);

			/** \brief Tetrahedra as seperate NxReals
			*/
			void tetrahedra(NxReal w, NxReal x, NxReal y, NxReal z);

			/** \brief Finish generation, and cook to a mesh
			*/
			Mesh* end(bool cleanup = true);

			/** \brief Finish generation and cook to a specific resource stream.
			*/
			Mesh* end(Resource* cooking_stream, bool cleanup = true);

			/** \brief Set the params for the cooker
			*/
			void setMeshParams(MeshParams);

			/** \brief Get the MeshParams
			*/
			MeshParams& getMeshParams();

			/** \brief Is the mesh valid?
			*/
			bool isValid() const;

			/** \brief Why is the mesh not valid
			*/
			NxString isNotValidReasons() const;

			/** \brief Use an Material Alias
			*/
			void addMaterialAlias(MaterialAlias*);

			/** \brief Get an Material Alias
			*/
			MaterialAlias* getMaterialAlias();

			/** \brief <em>Fastest</em> way to add a material to the current index.
				\param The MaterialIdentifier in the Alias. <em>NOT</em> the NxMaterialIndex.
			*/
			void material(NxU32);

			/** \brief <em>Slow</em> way look up to add a material to the current index.
			*/
			void material(const NxString& material);

		protected:

			bool _usesVertices() const;
			bool _usesNormals() const;
			bool _usesTexCoords() const;
			bool _usesIndices() const;
			bool _usesTetrahedra() const;

			NxTriangleMesh* _cookAs_Triangle(Resource*);
			NxConvexMesh*   _cookAs_Convex(Resource*);

			void reserve(NxU32);

			Betajaen::Flat<float3>*  mVertices;
			Betajaen::Flat<float3>*  mNormals;
			Betajaen::Flat<float3>*  mTextureCoords;
			Betajaen::Flat<float4>*  mTetrahedra;
			Betajaen::Flat<NxU32>*   mIndices;
			Betajaen::Flat<NxU32>*   mMaterials;
			MeshType                 mType;
			bool                     mIsTextureCoordsUV;
			MeshParams               mCookingParams;

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.
#endif

#endif
