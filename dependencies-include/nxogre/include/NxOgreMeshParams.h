/** \file    NxOgreMeshParams.h
 *  \brief   Header for the MeshParams class.
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


#ifndef __NXOGRE_MESHPARAMS_H__
#define __NXOGRE_MESHPARAMS_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

namespace NxOgre {
namespace Resources {
		class NxPublicClass MeshParams : Params {

		public:


			/** \brief MeshParams constructor for "class params".
			*/
			MeshParams()  {
			               setToDefault();
			              }

			/** \brief MeshParams constructor for "string params".
				\param _params Full string of params.
			*/
			MeshParams(const char* _params)  {
			                                  setToDefault();
			                                  process(_params);
			                                 }

			/** \brief MeshParams constructor for "string params" using an NxString.
				\param _params Full string of params.
			*/
			MeshParams(const NxString& _params)  {
			                                      setToDefault();
			                                      process(_params);
			                                     }

			/** \brief Set's the member variables to the default values
			           according to PhysX's cooking utility and NxOgre's
			           definition of default.
			*/
			void setToDefault();

		public:

			/** \brief Local pose of the mesh
			    \default id()
			    \note Applys to these types of meshes only: Triangle, Convex, Cloth, SoftBody and Skeleton. 
			    \example
			      C++     ->  mMeshParams.mLocalPose.t = NxVec3(1,2,3);
			 */
			NxMat34 mLocalPose;


			/** \brief Scale of the texture coordinates per face
			    \default 1 1
			    \note Applys to these types of meshes only: Cloth and SoftBody.
			    \example
			      C++     ->  mMeshParams.mTextureCoordinateScale = float2(2,2);
			      String  ->  "texture-coordinate-scale: 2 2"
			 */
			float2 mTextureCoordinateScale;

			struct MeshFlags : Flags {

				void toDefault() {
				    mFlipNormals              = false;

				}

				void  fromNxU32(NxU32);
				NxU32 toNxU32() const;
				void  parse(const NxString&);

				/** \brief Flip normals
				    \default false
				    \see NX_MF_FLIP_NORMALS
				    \note Applys to these types of meshes only: Triangle 
				    \example
				      String variations => +flip-normals, +fp
				*/
				bool mFlipNormals;

			};

			/** \brief Initial flags of the scene
			    \default +fp +disable-scene-mutex
			    \examples
			      C++     ->  mMeshParams.mFlags.mFlipNormals = true;
			      String  ->  "scene-flags: +disable-sse +disable-scene-mutex"
			 */
			MeshFlags       mFlags;


		protected:

			void parse(Parameters);


	};


}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif
