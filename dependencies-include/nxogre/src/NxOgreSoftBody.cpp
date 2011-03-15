/** \file    NxOgreSoftBody.cpp
 *  \see     NxOgreSoftBody.h
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

#include "NxOgreStable.h"
#include "NxOgreSoftBody.h"

#if (NX_USE_SOFTBODY_API == 0)
#include "NxOgrePose.h"					// For conversions
#include "NxOgreHelpers.h"				// For conversions
#include "NxOgreScene.h"				// For Cloth::mOwner
#include "NxOgreCooking.h"				// For Cooking NxClothMesh and Ogre::Mesh
#include "NxOgreMemoryStream.h"
#include "NxCooking.h"

#include "OgreStringConverter.h"

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////////////////


void SoftBodyParams::setToDefault() {
	


}

////////////////////////////////////////////////////////////////////////////////////////////////

void SoftBodyParams::parse(Parameters params) {

	setToDefault();

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

	}
}

//////////////////////////////////////////////////////////

void SoftBody::__ParamsToDescription(SoftBodyParams params, const Pose &pose) {
	mSoftBodyDescription.setToDefault();
}

//////////////////////////////////////////////////////////

SoftBody::SoftBody(const NxString& TetAndMeshFilePrefix, Scene* scene, const Pose& pose, SoftBodyParams sbp) : mOwner(scene), mUpdateBB(true) {
	mName = NxCreateID(mOwner->getNbSoftBodies(), TetAndMeshFilePrefix);
	__ParamsToDescription(sbp, pose);
	mSoftBodyDescription.softBodyMesh = __createSoftBodyMesh(TetAndMeshFilePrefix, mName);
	__createMesh(mName, sbp);
	/*__ParamsToDescription(params, pose);
	mClothDescription.clothMesh = __createClothMesh(params.width,params.height,params.vertexDistance);
	__createCloth(params);
	mOwner->_registerCloth(mName, this);*/
}


//////////////////////////////////////////////////////////

SoftBody::SoftBody(NxReal width, NxReal height, NxReal depth, Scene* scene, const Pose& pose, SoftBodyParams sbp) : mOwner(scene), mUpdateBB(true) {
	mName = NxCreateID(mOwner->getNbSoftBodies(), Ogre::StringConverter::toString(width + height + depth));
	__ParamsToDescription(sbp, pose);
	mSoftBodyDescription.softBodyMesh = __createCubeSoftBodyMesh(width, height, depth, sbp);
	__createMesh(mName, sbp);
}

//////////////////////////////////////////////////////////

SoftBody::~SoftBody() {
	//mOwner->_unregisterCloth(mName);
	//__destroyCloth();
}

//////////////////////////////////////////////////////////

NxScene* SoftBody::getNxScene() {
	return mOwner->getNxScene();
}

//////////////////////////////////////////////////////////

NxSoftBodyMesh*	SoftBody::__createCubeSoftBodyMesh(NxReal wx, NxReal wy, NxReal wz, SoftBodyParams sbp) {
	
	
	NxReal h = 1.0f;
	int numX = (int)(wx / h) + 1;
	int numY = (int)(wy / h) + 1;
	int numZ = (int)(wz / h) + 1;
	

	mSoftBodyMeshDescription.setToDefault();
	mSoftBodyMeshDescription.numVertices				= (numX+1) * (numY+1) * (numZ+1);
	mSoftBodyMeshDescription.numTetrahedra				= numX*numY*numZ*5;

	mVertices = new NxVec3[mSoftBodyMeshDescription.numVertices];
	mTetrahedra = new NxU32[mSoftBodyMeshDescription.numTetrahedra * 4];


	mSoftBodyMeshDescription.vertexStrideBytes			= sizeof(NxVec3);
	mSoftBodyMeshDescription.tetrahedronStrideBytes		= 4 * sizeof(NxU32);
	mSoftBodyMeshDescription.vertexMassStrideBytes		= sizeof(NxReal);
	mSoftBodyMeshDescription.vertexFlagStrideBytes		= sizeof(NxU32);
	mSoftBodyMeshDescription.vertices					= mVertices;
	mSoftBodyMeshDescription.tetrahedra					= mTetrahedra;
	mSoftBodyMeshDescription.vertexMasses				= 0;
	mSoftBodyMeshDescription.vertexFlags				= 0;
	mSoftBodyMeshDescription.flags						= 0;

	NxI32 i, j, k;
	NxVec3 offset(h * numX * 0.5f, h * numY * 0.5f, h * numZ * 0.5f);
	NxVec3 *p = mVertices;
	for (i = 0; i <= numX; i++) {
		for (j = 0; j <= numY; j++) {
			for (k = 0; k <= numZ; k++) {
				p->set(h*i, h*j, h*k); 
				*p -=offset;
				p++;
			}
		}
	}

	NxI32 i1,i2,i3,i4,i5,i6,i7,i8;

	NxU32 *id = mTetrahedra;
	for (i = 0; i < numX; i++) {
		for (j = 0; j < numY; j++) {
			for (k = 0; k < numZ; k++) {
		        i5 = (i*(numY+1) + j)*(numZ+1) + k; i1 = i5+1;
		        i6 = ((i+1)*(numY+1) + j)*(numZ+1) + k; i2 = i6+1;
		        i7 = ((i+1)*(numY+1) + (j+1))*(numZ+1) + k; i3 = i7+1;
		        i8 = (i*(numY+1) + (j+1))*(numZ+1) + k; i4 = i8+1;

				if ((i + j + k) % 2 == 1) {
					*id++ = i1; *id++ = i2; *id++ = i6; *id++ = i3;
					*id++ = i6; *id++ = i3; *id++ = i7; *id++ = i8;
					*id++ = i1; *id++ = i8; *id++ = i4; *id++ = i3;
					*id++ = i1; *id++ = i6; *id++ = i5; *id++ = i8;
					*id++ = i1; *id++ = i3; *id++ = i6; *id++ = i8;
				}
				else {
					*id++ = i2; *id++ = i5; *id++ = i1; *id++ = i4;
					*id++ = i2; *id++ = i7; *id++ = i6; *id++ = i5;
					*id++ = i2; *id++ = i4; *id++ = i3; *id++ = i7;
					*id++ = i5; *id++ = i7; *id++ = i8; *id++ = i4;
					*id++ = i2; *id++ = i5; *id++ = i4; *id++ = i7;
				}
			}
		}
	}

#if 0
						#if (NX_DEBUG == 0)

							MemoryWriteBuffer buf;
							if (!NxCookSoftBodyMesh(mSoftBodyMeshDescription, buf)) {
								std::stringstream s;
								s << "Cloth Mesh failed to cook";

								NxThrow(s.str());
							}
							
						  mSoftBodyMesh = mOwner->getNxScene()->getPhysicsSDK().createSoftBodyMesh(MemoryReadBuffer(buf.data));

						#else

							NxString filename = mName + ".SoftBody.nxs";
							
							UserStream buf(filename.c_str(),false);

							if (!NxCookSoftBodyMesh(mSoftBodyMeshDescription, buf)) {
								std::stringstream s;
								s << "SoftBody Mesh failed to cook";
								NxThrow(s.str());
							}
							fclose(buf.fp);

							UserStream rbuf(filename.c_str(), true);

							mSoftBodyMesh = mOwner->getNxScene()->getPhysicsSDK().createSoftBodyMesh(rbuf);
							fclose(rbuf.fp);

						#endif
#endif

  return mSoftBodyMesh;

}

//////////////////////////////////////////////////////////

void SoftBody::__allocateReceiveBuffers(NxU32 numVertices, NxU32 numTetrahedra) {

	NxU32 maxVertices = numVertices;
	mReceiveBuffers.verticesPosBegin = (NxVec3*)malloc(sizeof(NxVec3)*maxVertices);		
	mReceiveBuffers.verticesPosByteStride = sizeof(NxVec3);
	mReceiveBuffers.maxVertices = maxVertices;
	mReceiveBuffers.numVerticesPtr = (NxU32*)malloc(sizeof(NxU32));

	// the number of tetrahedra is constant, even if the softbody is torn
	NxU32 maxIndices = 4 * numTetrahedra;
	mReceiveBuffers.indicesBegin = (NxU32*)malloc(sizeof(NxU32)*maxIndices);
	mReceiveBuffers.indicesByteStride = sizeof(NxU32);
	mReceiveBuffers.maxIndices = maxIndices;
	mReceiveBuffers.numIndicesPtr = (NxU32*)malloc(sizeof(NxU32));

	// init the buffers in case we want to draw the mesh 
	// before the SDK as filled in the correct values
	*mReceiveBuffers.numVerticesPtr = 0;
	*mReceiveBuffers.numIndicesPtr = 0;

}

//////////////////////////////////////////////////////////

void SoftBody::__releaseReceiveBuffers() {
	NxVec3* vp;
	NxU32* up; 
	vp = (NxVec3*)mReceiveBuffers.verticesPosBegin; free(vp);
	up = (NxU32*)mReceiveBuffers.numVerticesPtr; free(up);

	up = (NxU32*)mReceiveBuffers.indicesBegin; free(up);
	up = (NxU32*)mReceiveBuffers.numIndicesPtr; free(up);
}

//////////////////////////////////////////////////////////

void SoftBody::__createMesh(const NxString& name, SoftBodyParams sbp) {
	


	NxVec3* p = (NxVec3*)mSoftBodyMeshDescription.vertices;
	NxU32* t = (NxU32*)mSoftBodyMeshDescription.tetrahedra;
	NxReal* m = (NxReal*)mSoftBodyMeshDescription.vertexMasses;
	NxU32* f = (NxU32*)mSoftBodyMeshDescription.vertexFlags;
	free(p); free(t);
	free(m); free(f);

	__allocateReceiveBuffers(mSoftBodyMeshDescription.numVertices, mSoftBodyMeshDescription.numTetrahedra);
	mSoftBodyDescription.meshData = mReceiveBuffers;

	mSoftBody = mOwner->getNxScene()->createSoftBody(mSoftBodyDescription);
}

//////////////////////////////////////////////////////////

NxSoftBodyMesh* SoftBody::__createSoftBodyMesh(const NxString& name, const NxString& mesh) {
	static const NxU16 MESH_STRING_LEN = 256;
	char s[MESH_STRING_LEN];
	int i0,i1,i2,i3;
	NxVec3 v;

	FILE *f = fopen(name.c_str(), "r");
	if (!f) return false;

	NxArray<NxVec3> tempVertices;
	NxArray<NxU32> tempIndices;
	NxBounds3 bounds;
	bounds.setEmpty();
	
	while (!feof(f)) {
		if (fgets(s, MESH_STRING_LEN, f) == NULL) break;

		if (strncmp(s, "v ", 2) == 0) {	// vertex
			sscanf(s, "v %f %f %f", &v.x, &v.y, &v.z);
			tempVertices.push_back(v);
			bounds.include(v);
		}
		else if (strncmp(s, "t ", 2) == 0) {	// tetra
			sscanf(s, "t %i %i %i %i", &i0,&i1,&i2,&i3);
			tempIndices.push_back(i0);
			tempIndices.push_back(i1);
			tempIndices.push_back(i2);
			tempIndices.push_back(i3);
		}
	}

	if(tempVertices.size() == 0) return false;

	mSoftBodyMeshDescription.numVertices				= tempVertices.size();
	mSoftBodyMeshDescription.numTetrahedra				= tempIndices.size() / 4;
	mSoftBodyMeshDescription.vertexStrideBytes			= sizeof(NxVec3);
	mSoftBodyMeshDescription.tetrahedronStrideBytes		= 4*sizeof(NxU32);
	mSoftBodyMeshDescription.vertexMassStrideBytes		= sizeof(NxReal);
	mSoftBodyMeshDescription.vertexFlagStrideBytes		= sizeof(NxU32);
	mSoftBodyMeshDescription.vertices					= (NxVec3*)malloc(sizeof(NxVec3)*mSoftBodyMeshDescription.numVertices);
	mSoftBodyMeshDescription.tetrahedra					= (NxU32*)malloc(sizeof(NxU32)*mSoftBodyMeshDescription.numTetrahedra*4);
	mSoftBodyMeshDescription.vertexMasses				= 0;
	mSoftBodyMeshDescription.vertexFlags				= 0;
	mSoftBodyMeshDescription.flags						= 0;

	// copy points and indices
	NxReal diag = bounds.min.distance(bounds.max);
	NxVec3 mOffset = (bounds.min + bounds.max) * 0.5f;
	
	NxVec3 *vSrc = (NxVec3*)tempVertices.begin();
	NxVec3 *vDest = (NxVec3*)mSoftBodyMeshDescription.vertices;
	for (NxU32 i = 0; i < mSoftBodyMeshDescription.numVertices; i++, vDest++, vSrc++) 
		*vDest = (*vSrc) - mOffset;
	memcpy((NxU32*)mSoftBodyMeshDescription.tetrahedra, tempIndices.begin(), sizeof(NxU32)*mSoftBodyMeshDescription.numTetrahedra*4);

#if 0
				#if (NX_DEBUG == 0)

					MemoryWriteBuffer buf;
					if (!NxCookSoftBodyMesh(mSoftBodyMeshDescription, buf)) {
						std::stringstream s;
						s << "SoftBody Mesh failed to cook";

						NxThrow(s.str());
					}
					
				  mSoftBodyMesh = mOwner->getNxScene()->getPhysicsSDK().createSoftBodyMesh(MemoryReadBuffer(buf.data));

				#else

					NxString filename = mName + ".SoftBody.nxs";
					
					UserStream buf(filename.c_str(),false);

					if (!NxCookSoftBodyMesh(mSoftBodyMeshDescription, buf)) {
						std::stringstream s;
						s << "SoftBody Mesh failed to cook";
						NxThrow(s.str());
					}
					fclose(buf.fp);

					UserStream rbuf(filename.c_str(), true);

					mSoftBodyMesh = mOwner->getNxScene()->getPhysicsSDK().createSoftBodyMesh(rbuf);
					fclose(rbuf.fp);

				#endif
#endif
  return mSoftBodyMesh;

}

//////////////////////////////////////////////////////////

void SoftBody::__loadObj(const NxString& name) {

}

//////////////////////////////////////////////////////////

}  //End of NxOgre namespace.
#endif
