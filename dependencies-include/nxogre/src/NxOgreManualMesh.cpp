/** \file    NxOgreManualMesh.cpp
 *  \see     NxOgreManualMesh.h
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

#ifndef NX_SMALL

#include "NxOgreManualMesh.h"
#include "NxOgreMeshParams.h"
#include "NxOgreMesh.h"
#include "NxOgreResourceSystem.h"
#include "NxOgrePhysXDriver.h"
#include "NxOgreResource.h"

#include "NxCooking.h"

#include "BetajaenCC.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

ManualMesh::ManualMesh(MeshType type, NxU32 estimatedSize, MeshParams mp)
: mType(type), mVertices(0), mNormals(0), mIndices(0), mTextureCoords(0), mTetrahedra(0)
{

	estimateVertices(estimatedSize);

	if (_usesIndices())
		estimateIndices(estimatedSize);

	if (_usesTetrahedra())
		estimateTetrahedra(estimatedSize);
}

/////////////////////////////////////////////////////////////

ManualMesh::~ManualMesh() {

}

/////////////////////////////////////////////////////////////

void ManualMesh::reserve(NxU32 e) {
	
}

/////////////////////////////////////////////////////////////

MeshType ManualMesh::getType() const {
	return mType;
}

/////////////////////////////////////////////////////////////

void ManualMesh::begin() {

}

/////////////////////////////////////////////////////////////

void ManualMesh::estimateVertices(unsigned int size) {
	
	if (mVertices == 0)
		mVertices = new Betajaen::Flat<float3, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true);
	mVertices->_reserve(size);

	// Reserve normals
	if (_usesNormals()) {
		if (mNormals == 0)
			mNormals = new Betajaen::Flat<float3, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true);
		mNormals->_reserve(size);
	}

	// Reserve texture coords
	if (_usesTexCoords()) {
		if (mTextureCoords == 0)
			mTextureCoords = new Betajaen::Flat<float3, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true); 
		mTextureCoords->_reserve(size);
	}

}

/////////////////////////////////////////////////////////////

void ManualMesh::estimateIndices(unsigned int size) {

	if (_usesIndices()) {
		if (mIndices == 0)
			mIndices = new Betajaen::Flat<NxU32, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true);
		mIndices->_reserve(size);
	}

}

/////////////////////////////////////////////////////////////

void ManualMesh::estimateTetrahedra(unsigned int size) {

	if (_usesTetrahedra()) {
		if (mTetrahedra == 0)
			mTetrahedra = new Betajaen::Flat<float4, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true);
		mTetrahedra->_reserve(size); 
	}

}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::getNbVertices() const {
	return mVertices->_size();
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::getNbIndices() const {
	return mVertices->_size();
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::getNbNormals() const {
	return mNormals->_size();
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::getNbTexCoords() const {
	return mTextureCoords->_size();
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::getNbTetrahedra() const {
	return mTetrahedra->_size();
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::vertex(const NxVec3& v) {
	return vertex(v.x, v.y, v.z);
}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::vertex(const float3& v) {

	if (mVertices->End <= mVertices->Last)
		mVertices->_reserve( (1 + mVertices->_size()) * 2);

	*mVertices->Last = v;
	mVertices->Last++;

	return mVertices->_size() - 1;

}

/////////////////////////////////////////////////////////////

NxU32 ManualMesh::vertex(NxReal x, NxReal y, NxReal z) {
	return vertex(float3(x, y, z));
}

/////////////////////////////////////////////////////////////

void ManualMesh::index(NxU32 v) {

	if (mIndices->End <= mIndices->Last)
		mIndices->_reserve( (1 + mIndices->_size()) * 2);

	*mIndices->Last = v;
	mIndices->Last++;

}

/////////////////////////////////////////////////////////////

void ManualMesh::triangle(NxU32 a, NxU32 b, NxU32 c) {
	index(a);
	index(b);
	index(c);
}

/////////////////////////////////////////////////////////////

void ManualMesh::normal(const NxVec3& v) {
	normal(float3(v.x, v.y, v.z));
}

/////////////////////////////////////////////////////////////

void ManualMesh::normal(const float3& v) {

	if (mNormals->End<= mNormals->Last)
		mNormals->_reserve( (1 + mNormals->_size()) * 2);

	*mNormals->Last = v;
	mNormals->Last++;

}

/////////////////////////////////////////////////////////////

void ManualMesh::normal(NxReal x, NxReal y, NxReal z) {
	normal(float3(x, y, z));
}

/////////////////////////////////////////////////////////////

void ManualMesh::coords(NxReal u, NxReal v) {

	if (mTextureCoords->End<= mTextureCoords->Last)
		mTextureCoords->_reserve( (1 + mTextureCoords->_size()) * 2);

	*mTextureCoords->Last = float3(u, v, 0);
	mTextureCoords->Last++;

	mIsTextureCoordsUV = true;
}

/////////////////////////////////////////////////////////////

void ManualMesh::coords(NxReal u, NxReal v, NxReal w) {

	if (mTextureCoords->End<= mTextureCoords->Last)
		mTextureCoords->_reserve( (1 + mTextureCoords->_size()) * 2);

	*mTextureCoords->Last = float3(u, v, w);
	mTextureCoords->Last++;

	mIsTextureCoordsUV = false;

}

/////////////////////////////////////////////////////////////

void ManualMesh::tetrahedra(const float4& v) {

	if (mTetrahedra->End<= mTetrahedra->Last)
		mTetrahedra->_reserve( (1 + mTetrahedra->_size()) * 2);

	*mTetrahedra->Last = v;
	mTetrahedra->Last++;

}

/////////////////////////////////////////////////////////////

void ManualMesh::tetrahedra(NxReal w, NxReal x, NxReal y, NxReal z) {
	tetrahedra(float4(w, x, y, z));
}

/////////////////////////////////////////////////////////////

Mesh* ManualMesh::end(bool cleanup) {
	Resource* mem = ResourceSystem::getSingleton()->getMemory();
	Mesh* mesh = end(mem, cleanup);
	delete mem;
	return mesh;
}

/////////////////////////////////////////////////////////////

Mesh* ManualMesh::end(Resource* r, bool cleanup) {
	Mesh* mesh = 0;

	switch(mType) {

		case MT_Triangle:
			{
				NxTriangleMesh* cooked_mesh = _cookAs_Triangle(r);
				mesh = new Mesh();
				mesh->mMesh.set(mType, cooked_mesh);
			}
		break;

		case MT_Convex:
			{
				NxConvexMesh* cooked_mesh = _cookAs_Convex(r);
				mesh = new Mesh();
				mesh->mMesh.set(mType, cooked_mesh);
			}
		break;

		case MT_Skeleton:

		break;

		case MT_Cloth:

		break;

		case MT_SoftBody:

		break;

	};

	return mesh;
}

/////////////////////////////////////////////////////////////

void ManualMesh::setMeshParams(MeshParams mp) {
	mCookingParams = mp;
}

/////////////////////////////////////////////////////////////

MeshParams& ManualMesh::getMeshParams() {
	return mCookingParams;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::_usesVertices() const {
	return true;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::_usesNormals() const {
	if (mType == MT_Convex || mType == MT_Skeleton)
		return false;
	return true;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::_usesTexCoords() const {
	if (mType == MT_Triangle || mType == MT_Convex || mType == MT_Skeleton)
		return false;
	return true;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::_usesIndices() const {
	if (mType == MT_Convex)
		return false;
	return true;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::_usesTetrahedra() const {
	if (mType == MT_SoftBody)
		return true;
	return false;
}

/////////////////////////////////////////////////////////////

bool ManualMesh::isValid() const {

	switch(mType) {
		case MT_Triangle:
			{
				if(mVertices->_size() < 3) 	//at least 1 trig's worth of points
					return false;
				if (mIndices->_size() == 0 && (mVertices->_size() % 3))		// Non-indexed mesh => we must ensure the geometry defines an implicit number of triangles // i.e. numVertices can't be divided by 3
					return false;
			}
		break;
		case MT_Skeleton: if (mVertices->_size() > 64) return false; break;
	}

	return true;
}

/////////////////////////////////////////////////////////////

NxTriangleMesh* ManualMesh::_cookAs_Triangle(Resource* cooking_stream) {

	if (!isValid()) {
		NxThrow_AsWarning("Triangle Mesh is invalid!");
		return 0;
	}

	NxTriangleMeshDesc   description;
	NxTriangleMesh*      mesh;
	NxCookingInterface*  cooker = ResourceSystem::getSingleton()->getCookingInterface();

	description.setToDefault();
	description.numVertices = mVertices->_size();
	description.pointStrideBytes = sizeof(float3);
	description.points = mVertices->First;

	if (mIndices->_size()) {
		description.numTriangles = mIndices->_size() / 3;
		description.triangleStrideBytes = sizeof(NxU32) * 3;
		description.triangles = mIndices->First;
	}

	bool result = false;
	result = cooker->NxCookTriangleMesh(description, *cooking_stream);

	if (!result) {
		NxThrow("Cooking of TriangleMesh failed!");
		return 0;
	}

	cooking_stream->rewind();

	mesh = ResourceSystem::getSingleton()->getPhysXDriver()->getSDK()->createTriangleMesh(*cooking_stream);

	return mesh;
}

/////////////////////////////////////////////////////////////

NxConvexMesh* ManualMesh::_cookAs_Convex(Resource* cooking_stream) {

	if (!isValid()) {
		NxThrow_AsWarning("Convex Mesh is invalid!");
		return 0;
	}

	NxConvexMeshDesc     description;
	NxConvexMesh*        mesh;
	NxCookingInterface*  cooker = ResourceSystem::getSingleton()->getCookingInterface();

	description.setToDefault();
	description.numVertices       = mVertices->_size();
	description.pointStrideBytes  = sizeof(float3);
	description.points            = mVertices->First;
	description.flags            |= NX_CF_COMPUTE_CONVEX;

	if (mIndices) {
		if (mIndices->_size()) {
			description.numTriangles         = mIndices->_size() * 3;
			description.triangleStrideBytes  = sizeof(NxU32) * 3;
			description.triangles            = mIndices->First;
		}
	}

	// Check geometry
	if(description.numVertices < 3 ||	//at least 1 trig's worth of points
		(description.numVertices > 0xffff && description.flags & NX_CF_16_BIT_INDICES))
		printf("+ verts\n");
	if(!description.points)
		printf("+ points\n");
	if(description.pointStrideBytes < sizeof(NxPoint))	//should be at least one point's worth of data
		printf("+ point size\n");

	// Check topology
	// The triangles pointer is not mandatory: the vertex cloud is enough to define the convex hull.
	if(description.triangles)
	{
	// Indexed mesh
	if(description.numTriangles < 2)	//some algos require at least 2 trigs
		printf("+ num triangles < 2\n");
	if(description.flags & NX_CF_16_BIT_INDICES)
		{
		if((description.triangleStrideBytes < sizeof(NxU16)*3))
			printf("+ tri stride\n");
		}
	else
		{
		if((description.triangleStrideBytes < sizeof(NxU32)*3))
			printf("+ tri stride2\n");
		}
	}
	else
	{
	// We can compute the hull from the vertices
	if(!(description.flags & NX_CF_COMPUTE_CONVEX))
		printf("+ compute convex\n");
	}


	bool result = false;
	result = cooker->NxCookConvexMesh(description, *cooking_stream);

	if (result == false) {
		NxThrow("Cooking of Convex mesh failed!");
		return 0;
	}

	cooking_stream->rewind();

	mesh = ResourceSystem::getSingleton()->getPhysXDriver()->getSDK()->createConvexMesh(*cooking_stream);

	return mesh; 

}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.

#endif
