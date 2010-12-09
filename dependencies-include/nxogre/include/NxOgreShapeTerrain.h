/** \file    NxOgreShapeTerrain.h
 *  \brief   Header for the Terrain class.
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

#ifndef __NXOGRE_SHAPE_TERRAIN_H__
#define __NXOGRE_SHAPE_TERRAIN_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"
#include "NxOgreShape.h"				// For: Terrain inherits Shape

namespace NxOgre {

	
	class NxPublicClass TerrainParams : Params {

		public:


			/** \brief MeshParams constructor for "class params".
			*/
			TerrainParams()  {
			               setToDefault();
			              }

			/** \brief MeshParams constructor for "string params".
				\param _params Full string of params.
			*/
			TerrainParams(const char* _params)  {
			                                  setToDefault();
			                                  process(_params);
			                                 }

			/** \brief MeshParams constructor for "string params" using an NxString.
				\param _params Full string of params.
			*/
			TerrainParams(const NxString& _params)  {
			                                      setToDefault();
			                                      process(_params);
			                                     }

			/** \brief Set's the member variables to the default values
			           according to PhysX's cooking utility and NxOgre's
			           definition of default.
			*/
			void setToDefault();

		public:
			
			enum TerrainCentering {
				/** \brief Don't center, don't do anything with the Local Pose of the shape.*/
				TC_None        = 0,
				/** \brief Center the XZ of the mesh to 0,?,0 */
				TC_CenterXZ    = 1,
				/** \brief Center XZ, and put the lowest point of the mesh (-32768 at 0), so the entire mesh is above 0 */
				TC_CenterAbove = 2 
			};


			/** \brief Center the terrain to the actor.
			    \note  This override's mShapeParams.mLocalPose
			    \default TC_None (from TerrainCentering enum)
			    \example
			      C++     ->  mTerrainParams.mCenter = TC_CenterXZ;
			      String  ->  "center: xz"
						{ none, xz, xz-above}
			 */
			NxU32							mCentering;


			/** \brief The high 9 bits of this number are used to complete the material indices in the samples. 
			    \default 0
			    \example
			      C++     ->  mTerrainParams.mMaterialIndexHighBits = 0;
			      String  ->  "material-index-high-bits: 0"
			 */
			NxMaterialIndex					mMaterialIndexHighBits;


			/** \brief The the material index that designates holes in the height field.
			    \default 0 (No hole)
			    \example
			      C++     ->  mTerrainParams.mHoleMaterial = 0;
			      String  ->  "hole-material: 0"
			 */
			NxMaterialIndex                  mHoleMaterial;


			struct NxPublicClass TerrainFlags : Flags {

				void toDefault() {
				   mSmoothSphereCollisions              = false;
				   mVisualiseTerrain                    = false;
				}

				void  fromNxU32(NxU32);
				NxU32 toNxU32() const;
				void  parse(const NxString&);

				/** \brief Smooth sphere collisions.
				    \default false
				    \see NX_MESH_SMOOTH_SPHERE_COLLISIONS
				    \example
				      String variations => +smooth-sphere-collisions, +ssc
				*/
				bool mSmoothSphereCollisions;

				/** \brief Visualise Terrain in Debug renderer.
				    \default false
				    \see NX_SF_VISUALIZE
				    \note This will cause a massive drop in FPS in application.
				    \example
				      String variations => +visualise-terrain, +vt
				*/
				bool mVisualiseTerrain;

			};

			/** \brief Initial flags of the scene
			    \default (nothing)
			    \examples
			      C++     ->  mTerrainParams.mFlags.mSmoothSphereCollisions = true;
			      String  ->  "terrain-flags: +ssc"
			 */
			TerrainFlags       mFlags;

		protected:

			void parse(Parameters);
	};

	/** \brief Terrain (NxTerrainShape) provides a terrain from a heightfield.
	*/
	class NxPublicClass Terrain : public Shape {

		public:

			/** \brief Terrain Constructor; loading a resource to use as a terrain.
			*/
			Terrain(const Resources::ResourceIdentifier&, float3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());

			/** \brief Terrain Constructor; loading a resource to use as a terrain.
			*/
			Terrain(const Resources::ResourceIdentifier&, NxVec3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());

#if (NX_USE_OGRE == 1)
			/** \brief Terrain Constructor; loading a resource to use as a terrain.
			*/
			Terrain(const Resources::ResourceIdentifier&, Ogre::Vector3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());
#endif

			/** \brief Terrain Constructor; using a direct terrain
			*/
			Terrain(Resources::Heightfield*, float3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());

			/** \brief Terrain Constructor; using a direct terrain
			*/
			Terrain(Resources::Heightfield*, NxVec3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());

#if (NX_USE_OGRE == 1)
			/** \brief Terrain Constructor; using a direct terrain
			*/
			Terrain(Resources::Heightfield*, Ogre::Vector3 size, const ShapeParams& = ShapeParams(), const TerrainParams& = TerrainParams());
#endif

			/** \brief Terrain destructor
			*/
			~Terrain();

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:

			bool isTerrainShapeValid() const;

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

		protected:


			NxHeightFieldShapeDesc           mShapeDescription;
			Resources::ResourceIdentifier    mResourceIdentifier;
			Resources::Heightfield*          mHeightfield;
			TerrainParams                    mTerrainParams;

	};


} // End of namespace

#endif
 