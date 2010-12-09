/** \file    NxOgreSoftBody.h
 *  \brief   Header for the SoftBodyParams and SoftBody classes.
 *  \version 1.0-20
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


#ifndef __NXOGRE_SOFT_BODY_H__
#define __NXOGRE_SOFT_BODY_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

#if (NX_USE_SOFTBODY_API == 0)

#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreAxisAlignedBox.h"

namespace NxOgre {


	class NxPublicClass SoftBodyParams : public Params {

		public:


			SoftBodyParams() {}
			SoftBodyParams(const char* p) {setToDefault();process(p);}
			SoftBodyParams(NxString p) {setToDefault();process(p);}

			void			setToDefault();
			void			parse(Parameters);			

			NxString		mesh_material;

	}; // End of ClothParams class

	class NxPublicClass SoftBody {

		public:

			// fileNames must go:
			//		myFile.mesh->
			//			myFile.mesh			(mesh file)
			//			myFile.mesh.tet		(tethedral file)
			SoftBody(const NxString& TetAndMeshFilePrefix, Scene*, const Pose&, SoftBodyParams = "");
			SoftBody(NxReal width, NxReal height, NxReal depth, Scene*, const Pose&, SoftBodyParams = "");
			~SoftBody();

			//////////////////////////////////////////////////////////

			NxString	getName() const{return mName;}
			Scene*		getScene() {return mOwner;}
			NxScene*	getNxScene();

			void			simulate(NxReal);
			void			render(NxReal);
			
			enum HardwareBinding {
				HWB_VERTEX = 0,
				HWB_NORMAL = 1,
				HWB_TEXTURE = 2
			};

		protected:

			void						__createSoftBody(SoftBodyParams);
			void						__ParamsToDescription(SoftBodyParams params, const Pose& pose);
			void						__destroySoftBody();
			NxSoftBodyMesh*				__createSoftBodyMesh(const NxString& name, const NxString& mesh);
			NxSoftBodyMesh*				__createCubeSoftBodyMesh(NxReal, NxReal, NxReal, SoftBodyParams sbp);
			void						__createMesh(const NxString& name, SoftBodyParams sbp);
			void						__allocateReceiveBuffers(NxU32 numVertices, NxU32 numTetrahedra);
			void						__releaseReceiveBuffers();
			void						__loadObj(const NxString& name);

			Scene					   *mOwner;
			NxActor*					mActor;
			NxString					mName;
			
			NxSoftBody*					mSoftBody;
			NxSoftBodyDesc				mSoftBodyDescription;
			NxSoftBodyMeshDesc			mSoftBodyMeshDescription;
			NxSoftBodyMesh*				mSoftBodyMesh;
			Ogre::MeshPtr				mMesh;
			Ogre::SubMesh*				mSubMesh;
			NxMeshData					mReceiveBuffers;
			NxBounds3					mNxBounds;
			Ogre::AxisAlignedBox		mAABox;
			bool						mUpdateBB;
			bool						mIsTearable;

			NxU32*						mTriangles;
			NxVec3*						mVertices;
			Ogre::Vector3*				mNormals;
			Ogre::Vector2*				mTextCoords;
			NxU32*						mTetrahedra;

			NxU32						mVertexCount;
			NxU32						mTriangleCount;
			NxU32						mTextCoordCount;
			NxU32						mTetrahedraCount;
			Ogre::IndexData*			mIndexData;
			Ogre::VertexData*			mVertexData;
			Ogre::SceneNode*			mNode;
			Ogre::Entity*				mEntity;

		private:


	};// End of SoftBody Class

};// End of namespace
#endif
#endif
