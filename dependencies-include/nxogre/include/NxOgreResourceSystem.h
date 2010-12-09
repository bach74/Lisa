/** \file    NxOgreResourceSystem.h
 *  \brief   Header for the ResourceSystem class.
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


#ifndef __NXOGRE_RESOURCE_SYSTEM_H__
#define __NXOGRE_RESOURCE_SYSTEM_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreMesh.h"                // For: BetajaenCC ResourceSystem::mMeshes.
#include "NxOgreHeightfield.h"          // For: BetajaenCC ResourceSystem::mHeightfields

namespace NxOgre {
namespace Resources {

	class NxPublicClass ResourceSystem {
		
		friend class PhysXDriver;

		protected:
			
			ResourceSystem(PhysXDriver*);
			~ResourceSystem();

		public:

			void                      addResourceManager(ResourceManager*);

			/** \brief Get's a Resource. Once the resource is loaded, it is parsed
			           and copied into the ResourceSystem. From that you can use
			           the getMesh, getTerrain, getMaterialAlias functions if you
			           wish to use the resource a second time.
			*/
			Resource*                 get(const ResourceIdentifier&, ResourceAccess = NxOgre::Resources::RA_Default);

			/** \brief Get's a MemoryResource for writing and reading to.
				\note  This is equivalent to ResourceSystem->get("m://", RA_Default);
				\param A brand new fresh Memory Resource to play with.
			*/
			Resource*                 getMemory();

			/** \brief Load and add a mesh into the PhysX SDK from a Resource Identifier (Common method)
				\note  Mesh name will be the ResourceIdentifier minus the prefix
						file://pyramid.nxs		-> pyramid.nxs
						file://media/cube.nxs	-> media/cube.nxs
			*/
			void                      addMesh(const ResourceIdentifier&);
			
			/** \brief Load an add a mesh into the PhysX SDK from a Resource Identifier and assign it a name (Common method).
			*/
			void                      addMeshAs(const ResourceIdentifier&, const NxString& MeshIdentifier);

			/** \brief Load and add a mesh into the PhysX SDK from a resource.
				\note  Mesh name will be the ResourceIdentifier minus the prefix
						file://pyramid.nxs		-> pyramid.nxs
						file://media/cube.nxs	-> media/cube.nxs
			*/
			void                      addMesh(Resource*);

			/** \brief Load and add a mesh into the PhysX SDK from a resource and assign it an name.
			*/
			void                      addMeshAs(Resource*, const NxString& MeshIdentifier);
			
			/** \brief Add a mesh to the Resource System from an existing Mesh
			*/
			void                      addMesh(const NxString& MeshIdentifier, Mesh*);
			
			/** \brief Get a mesh from Resource System using a Mesh identifier.
				\note  Remember to "return" a mesh after use, to decrease the reference count.
			*/
			Mesh*                     getMesh(const NxString& MeshIdentifier);
			
			/** \brief Return's a mesh from the Resource System. Allow meshes can be shared many many times, it
					   it required to know how many times it is used or in use, incase the Mesh has to be changed.
			*/
			void                      returnMesh(Mesh*);

			/** \brief Does a Mesh exist or not?
			*/
			bool                      hasMesh(const NxString& MeshIdentifier);
			
			/** \brief Clear the mesh from the Resource System (Does not remove the mesh from the PhysX SDK).
			*/
			void                      clearMesh(const NxString& MeshIdentifier);

			
			/** \brief Clear the mesh from the Resource System, and releases the mesh from the PhysX SDK.
			*/
			void                      destroyMesh(const NxString& MeshIdentifier);

			/** \brief Load and add a Heightfield into the PhysX SDK from a Resource Identifier (Common method)
				\note  Heightfield name will be the ResourceIdentifier minus the prefix
						file://pyramid.nxs		-> pyramid.nxs
						file://media/cube.nxs	-> media/cube.nxs
			*/
			void                      addHeightfield(const ResourceIdentifier&);
			
			/** \brief Load an add a Heightfield into the PhysX SDK from a Resource Identifier and assign it a name (Common method).
			*/
			void                      addHeightfieldAs(const ResourceIdentifier&, const NxString& HeightfieldIdentifier);

			/** \brief Load and add a Heightfield into the PhysX SDK from a resource.
				\note  Heightfield name will be the ResourceIdentifier minus the prefix
						file://pyramid.nxs		-> pyramid.nxs
						file://media/cube.nxs	-> media/cube.nxs
			*/
			void                      addHeightfield(Resource*);

			/** \brief Load and add a Heightfield into the PhysX SDK from a resource and assign it an name.
			*/
			void                      addHeightfieldAs(Resource*, const NxString& HeightfieldIdentifier);
			
			/** \brief Add a Heightfield to the Resource System from an existing Heightfield
			*/
			void                      addHeightfield(const NxString& HeightfieldIdentifier, Heightfield*);
			
			/** \brief Get a Heightfield from Resource System using a Heightfield identifier.
				\note  Remember to "return" a Heightfield after use, to decrease the reference count.
			*/
			Heightfield*              getHeightfield(const NxString& HeightfieldIdentifier);
			
			/** \brief Return's a Heightfield from the Resource System. Allow Heightfieldes can be shared many many times, it
					   it required to know how many times it is used or in use, incase the Heightfield has to be changed.
			*/
			void                      returnHeightfield(Heightfield*);

			/** \brief Does a Heightfield exist or not?
			*/
			bool                      hasHeightfield(const NxString& HeightfieldIdentifier);
			
			/** \brief Clear the Heightfield from the Resource System (Does not remove the Heightfield from the PhysX SDK).
			*/
			void                      clearHeightfield(const NxString& HeightfieldIdentifier);

			
			/** \brief Clear the Heightfield from the Resource System, and releases the Heightfield from the PhysX SDK.
			*/
			void                      destroyHeightfield(const NxString& HeightfieldIdentifier);


			void                      addMaterialAlias(Resource*);
			void                      addMaterialAlias(const ResourceIdentifier&);
			MaterialAlias*            getMaterialAlias(const NxString& identifier);
			void                      clearMaterialAlais(const NxString& identifier);

			// JSON (??)

			// Text (??)
#ifndef NX_DISABLE_COOKING
			NxCookingInterface*       getCookingInterface();
#endif
			NxString                  removeResourcePrefix(ResourceIdentifier&);
			NxString                  getResourcePrefix(ResourceIdentifier&);
			static ResourceSystem*    getSingleton();
			PhysXDriver*              getPhysXDriver();

			ResourceCallback*         getCallback();
			void                      setCallback(ResourceCallback*, GarbageCollectionPolicy = GC_Delete);

		protected:

			PhysXDriver*                                    mPhysXDriver;

#ifndef NX_DISABLE_COOKING
			NxCookingInterface*                             mCookingInterface;
#endif

			/// These could just be containers, then moved over to SharedMap's.
			Betajaen::SharedMap<NxString, Mesh>             mMeshes;
			Betajaen::SharedMap<NxString, Heightfield>      mHeightfields;
			Betajaen::SharedMap<NxString, ResourceManager>  mResourceManagers;
			static   ResourceSystem*                        mSingleton;

			ResourceCallback*                               mCallback;
			GarbageCollectionPolicy                         mCallbackDeletionPolicy;
	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif


#if 0

namespace NxOgre {
namespace Resources {

		typedef NxString ResourceIdentifier;

		enum ResourceType {
			RT_NXS_Mesh,
			RT_NXS_Convex,
			RT_NXS_SoftBody,
			RT_NXS_Cloth,
			RT_NXS_Terrain,
			RT_Terrain_Image,
			RT_Terrain_MaterialData,
			RT_Mesh_MaterialData,
			RT_JSON,
			RT_Unknown
		};

		enum MeshType {
			MT_Triangle = RT_NXS_Mesh,
			MT_Convex = RT_NXS_Convex,
			MT_SoftBody = RT_NXS_SoftBody,
			MT_Cloth = RT_NXS_Cloth
		};

		enum ResourceAccess {
			RA_Read,
			RA_Write,
			RA_ReadWrite
		};

		typedef Betajaen::SharedList<Resource> Resources;
		typedef Resources ResourceIterator;

		// A Resource, is a *non* loaded piece of data,
		// which is turned into a Mesh, Terrain, JSON, MaterialAlias. These are tracked by the ResourceSystem
		class Resource {

			protected:

				Resource(const NxString& _filtered_resource_identifier, ResourceAccess);
				virtual ~Resource();

			public:

		};

		class FileResource : Resource {

			protected:
				FileResource(const NxString& _filtered_resource_identifier, ResourceAccess);
				virtual ~FileResource();

			public:

		};

		class MemoryResource : Resource {

			protected:
				MemoryResource(const NxString& _filtered_resource_identifier, ResourceAccess);
				virtual ~MemoryResource();

			public:

		};

		class ResourceManager {

			public:

				virtual NxString getType() const {return "Base";}
				virtual Resource* operator()(const ResourceIdentifier&) {}
				
		};

		class FileResourceManager {
			public:
				NxString getType() const {return "File";}
				Resource* operator()(const ResourceIdentifier&) {}
		};

		class MemoryResourceManager {
			public:
				NxString getType() const {return "Memory";}
				Resource* operator()(const ResourceIdentifier&) {}
		};

		class ResourceSystem {

			public:
				Resource* get(ResourceIdentifier);
				void registerResourceManager(ResourceManager*);

			protected:
				Betajaen::SharedList<Mesh>     mMeshes;
				Betajaen::SharedList<Terrain>  mTerrain;

		};

		// Meshes
		//  - Cannot be edited
		//  - Can be read; usually for softbodies or cloth, 
		//    through a abstract MeshDataIterator (SoftBodyMeshDataIterator, ClothMeshDataIterator, etc.)
		//  - Holds the NxMesh pointer.
		//  - Keeps accounts of references to the Mesh.
		//  - Can be converted (saved) to a Resource
		//  - Can be converted (loaded) from a Resource
		//  - Mesh class represents triangle meshes, convex meshes, soft bodies, cloth, etc.
		class Mesh {

		};

		// Builds a mesh manually from code.
		//  - Can be used with utility functions to convert file formats (ogre->nxs)
		//  - 
		class ManualMesh {
		
			public:

			ManualMesh(MeshType);
			~ManualMesh();

			bool isValid const();
			bool hasValidVertices const();
			bool hasValidIndices const();
			bool hasValidNormals const();
			bool hasValidUV const();

			void begin(NxU32 initialVertices = 12, NxU32 initialIndexes = 12 * 3) {

			}

			void vertex(NxReal, NxReal, NxReal) {

			}

			void index(NxU32) {

			}

			void normal(NxReal, NxReal, NxReal) {

			}

			void uv(NxReal, NxReal) {

			}

			Mesh* end() {
				
			}

			protected:

				struct {
					MeshType type;
					Betajaen::Set<float3> vertices;
					Betajaen::Set<unsigned int> indexes;
				} mesh;

				bool __cookTriangle();
				bool __cookConvex();
				bool __cookSoftBody();
				bool __cookCloth();

		};

		class Terrain {

		};

		class SimpleTerrain : Terrain {

		};

	};


};
};

#endif