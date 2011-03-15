/** \file    NxOgreMesh.cpp
 *  \see     NxOgreMesh.h
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
#include "NxOgreMesh.h"
#include "NxOgreResource.h"
#include "NxOgreResourceSystem.h"
#include "NxOgrePhysXDriver.h"
#include "NxOgreResourceCallback.h"

#ifndef NX_SMALL
#   include "NxCooking.h"
#endif

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

Mesh::Mesh() {
	mMesh.zero();
}

/////////////////////////////////////////////////////////////

Mesh::Mesh(const ResourceIdentifier& ri) {
	load(ri);
}

/////////////////////////////////////////////////////////////

Mesh::Mesh(Resource* rs) {
	load(rs);
}

/////////////////////////////////////////////////////////////

Mesh::~Mesh() {
	// PhysX will destroy the Mesh for us.
	mMesh.zero();
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(MeshType type, void *data) {
	zero();
	mType = type;
	switch (mType) {
		default:
		case MT_Unknown:
		break;

		case MT_Triangle:
			{
				mTriangleMesh = static_cast<NxTriangleMesh*>(data);
				mNbReferences = mTriangleMesh->getReferenceCount();
			}
		break;

		case MT_Convex:
			{
				mConvexMesh   = static_cast<NxConvexMesh*>(data);
				mNbReferences = mConvexMesh->getReferenceCount();
			}
		break;

		case MT_Cloth:
			{
				mClothMesh    = static_cast<NxClothMesh*>(data);
				mNbReferences = mClothMesh->getReferenceCount();
			}
		break;

	}
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::zero() {
	mTriangleMesh      = 0;
	mConvexMesh        = 0;
	mSkeletonMesh      = 0;
	mClothMesh         = 0;
	mSoftBodyMesh      = 0;
	mType              = MT_Unknown;
	mNbReferences      = 0;
}

/////////////////////////////////////////////////////////////

MeshType Mesh::getMeshTypeFromResource(Resource* resource) {

	if (resource->size() < 8)
		return MT_Unknown;

	// Read the "NXS" Header.
	{
		char header[3] = {0, 0, 0};
		resource->get(&header, 3);
		if (!(header[0] == 'N' && header[1] == 'X' && header[2] == 'S'))
			return MT_Unknown;
	}

	// Skip forward a Byte (Usually x01)
	resource->skip(1);

	char mesh_header[4] = {0, 0, 0, 0};
	resource->get(&mesh_header, 4);

	resource->rewind();


	if (mesh_header[0] == 'M' &&
		mesh_header[1] == 'E' &&
		mesh_header[2] == 'S' &&
		mesh_header[3] == 'H')
	{
		return MT_Triangle;
	}
	else if (mesh_header[0] == 'C' &&
			 mesh_header[1] == 'V' &&
			 mesh_header[2] == 'X' &&
			 mesh_header[3] == 'M')
	{
		return MT_Convex;
	}
	/** More here */
	else
	{
		return MT_Unknown;
	}

}

/////////////////////////////////////////////////////////////

void Mesh::load(const ResourceIdentifier& ri) {
	Resource* resource = ResourceSystem::getSingleton()->get(ri, RA_Read);
	load(resource);
}

/////////////////////////////////////////////////////////////

void Mesh::load(Resource* resource) {

	ResourceSystem::getSingleton()->getCallback()->MeshLoading(this, resource);

	if (!mMesh.isZero()) {
		ResourceSystem::getSingleton()->getCallback()->MeshLoadingFailed(this, resource, R_HasMesh);
		return;
	}

	mMesh.zero();

	NxPhysicsSDK* sdk = ResourceSystem::getSingleton()->getPhysXDriver()->getSDK();

	MeshType mt = getMeshTypeFromResource(resource);

	switch (mt) {
		case MT_Triangle:
			{
				NxTriangleMesh* mesh = sdk->createTriangleMesh(*resource);
				ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);
				mMesh.set(mesh);
			}
		break;
		case MT_Convex:
			{
				NxConvexMesh* mesh = sdk->createConvexMesh(*resource);
				ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);
				mMesh.set(mesh);
			}
		break;
		case MT_Skeleton:
			{
				// NxCCDSkeleton* mesh = sdk->createCCDSkeleton(*resource);
				// mMesh.set(mesh);

				/// \todo apparently this can't be loaded like the NxStream, need a manual version of this.
			}
		break;
		case MT_Cloth:
			{
				NxClothMesh* mesh = sdk->createClothMesh(*resource);
				ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);
				mMesh.set(mesh);
			}
		break;
		case MT_SoftBody:
			{
				NxSoftBodyMesh* mesh = sdk->createSoftBodyMesh(*resource);
				ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);
				mMesh.set(mesh);
			}
		break;
	}
	
	ResourceSystem::getSingleton()->getCallback()->MeshLoaded(this);

}

/////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void Mesh::save(const ResourceIdentifier& ri) {
	Resource* resource = ResourceSystem::getSingleton()->get(ri, RA_Write);
	save(resource);
	NxDelete(resource);
}

#endif

/////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void Mesh::save(Resource* rs) {

	NxPhysicsSDK* sdk = ResourceSystem::getSingleton()->getPhysXDriver()->getSDK();

	switch (mMesh.mType) {
		case MT_Triangle:
			{
				NxTriangleMeshDesc desc;
				mMesh.mTriangleMesh->saveToDesc(desc);
				ResourceSystem::getSingleton()->getCookingInterface()->NxCookTriangleMesh(desc, *rs);
				/// \todo Write MaterialAlias to here.
			}
		break;
		case MT_Convex:
			{
				NxConvexMeshDesc desc;
				mMesh.mConvexMesh->saveToDesc(desc);
				ResourceSystem::getSingleton()->getCookingInterface()->NxCookConvexMesh(desc, *rs);
			}
		break;
		case MT_Skeleton:
			{
				// NxCCDSkeleton* mesh = sdk->createCCDSkeleton(*rs);
				// mMesh.set(mesh);

				/// \todo apparently this can't be loaded like the NxStream, need a manual version of this.
			}
		break;
		case MT_Cloth:
			{
				NxClothMesh* mesh = sdk->createClothMesh(*rs);
				mMesh.set(mesh);
			}
		break;
		case MT_SoftBody:
			{
				NxSoftBodyMesh* mesh = sdk->createSoftBodyMesh(*rs);
				mMesh.set(mesh);
			}
		break;
	}

}
#endif
/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(NxConvexMesh* m) {
	zero();
	mType = MT_Convex;
	mConvexMesh = m;
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(NxTriangleMesh* m) {
	zero();
	mType = MT_Triangle;
	mTriangleMesh = m;
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(NxCCDSkeleton* m) {
	zero();
	mType = MT_Skeleton;
	mSkeletonMesh = m;
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(NxClothMesh* m) {
	zero();
	mType = MT_Cloth;
	mClothMesh = m;
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::set(NxSoftBodyMesh* m) {
	zero();
	mType = MT_SoftBody;
	mSoftBodyMesh = m;
}

/////////////////////////////////////////////////////////////

bool Mesh::MeshData::isZero() const {
	return (mTriangleMesh == 0 && mConvexMesh == 0 && mSkeletonMesh == 0 && mClothMesh == 0 && mSoftBodyMesh == 0 && mMaterialAlias == 0);
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::increaseReference() {
	mNbReferences++;
}

/////////////////////////////////////////////////////////////

void Mesh::MeshData::decreaseReference() {
	if (mNbReferences != 0)
		mNbReferences--;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
