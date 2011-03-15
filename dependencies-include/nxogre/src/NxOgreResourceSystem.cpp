/** \file    NxOgreResourceSystem.cpp
 *  \see     NxOgreResourceSystem.h
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
#include "NxOgreResourceSystem.h"
#ifndef NX_DISABLE_COOKING
#include "NxCooking.h"						// For: NxCookingInterface
#endif
#include "NxOgrePhysXDriver.h"				// For: PhysXDriver is required for access to Allocator and Error.
#include "NxOgreUserAllocator.h"			// For: NxInitCooking in NxCookingInterface requires a cast.
#include "NxOgreError.h"					// For: NxInitCooking in NxCookingInterface requires a cast.
#include "NxOgreResourceManager.h"			// For: Resource fetching from ResourceManagers.
#include "NxOgreMemoryResourceManager.h"
#include "NxOgreFileResourceManager.h"
#include "NxOgreHelpers.h"
#include "NxOgreMesh.h"
#include "NxOgreResourceCallback.h"
#include "BetajaenCC.h"

namespace NxOgre {
namespace Resources {

ResourceSystem* ResourceSystem::mSingleton = 0;

/////////////////////////////////////////////////////////////

ResourceSystem::ResourceSystem(PhysXDriver* driver) 
: mPhysXDriver(driver)
#ifndef NX_DISABLE_COOKING
, mCookingInterface(0)
#endif
{
	mSingleton = this;
	setCallback(new DefaultResourceCallback(), GC_Delete);

	addResourceManager(new MemoryResourceManager());
	addResourceManager(new FileResourceManager());

}

/////////////////////////////////////////////////////////////

ResourceSystem::~ResourceSystem() {
#ifndef NX_DISABLE_COOKING
	if (mCookingInterface) {
		mCookingInterface->NxCloseCooking();
		// Cooking lib should be destroyed by PhysX.
		mCookingInterface = 0;
	}
#endif
	mSingleton = 0;
}

/////////////////////////////////////////////////////////////

ResourceSystem* ResourceSystem::getSingleton() {
	return mSingleton;
}

/////////////////////////////////////////////////////////////

#ifndef NX_DISABLE_COOKING

NxCookingInterface* ResourceSystem::getCookingInterface() {

	if (mCookingInterface == 0) {
	
		mCookingInterface = NxGetCookingLib(NX_PHYSICS_SDK_VERSION);
		/// mUserAllocator will be eventually replaced with the Allocator class.
		mCookingInterface->NxInitCooking(mPhysXDriver->getUserAllocator(), mPhysXDriver->getError());
	}

	return mCookingInterface;
}

#endif

/////////////////////////////////////////////////////////////

Resource* ResourceSystem::get(const ResourceIdentifier& ri, ResourceAccess ra) {
	
	NxString prefix = ri;
	prefix = NxStringSubstrLeft(prefix, NxStringWhereIs(prefix, "://"));
	if (mResourceManagers.Get(prefix) == 0)
		return 0;

	return mResourceManagers[prefix]->get(ri, ra);
}

/////////////////////////////////////////////////////////////

Resource* ResourceSystem::getMemory() {
	return mResourceManagers["m"]->get(NxString(), RA_Default);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addResourceManager(ResourceManager* rm) {
	mResourceManagers.Insert(rm->getType(), rm);
	mCallback->ResourceManagerAdded(rm);
}

/////////////////////////////////////////////////////////////

NxString ResourceSystem::removeResourcePrefix(ResourceIdentifier& ri) {
	NxU32 p = NxStringWhereIs(ri, "://");

	if (p == std::string::npos) // Temp.
		return ri;

	return NxStringSubstr(ri, p + 3);
}

/////////////////////////////////////////////////////////////

NxString ResourceSystem::getResourcePrefix(ResourceIdentifier& ri) {
	return NxStringSubstrLeft(ri, NxStringWhereIs(ri, "://"));
}

/////////////////////////////////////////////////////////////

PhysXDriver* ResourceSystem::getPhysXDriver() {
	return mPhysXDriver;
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addMesh(Resource* resource) {
	Mesh* mesh = NxNew(Mesh)(resource);
	NxString mesh_identifier = removeResourcePrefix(resource->getResourceIdentifier());
	mMeshes.Insert(mesh_identifier, mesh);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addMesh(const NxString& mesh_identifier, Mesh* mesh) {
	mMeshes.Insert(mesh_identifier, mesh);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addMesh(const ResourceIdentifier& ri) {
	Resource* r = get(ri, RA_Read);
	Mesh* mesh = NxNew(Mesh)(r);
	NxString mesh_identifier = removeResourcePrefix(r->getResourceIdentifier());
	mMeshes.Insert(mesh_identifier, mesh);
	NxDelete(r);
}

/////////////////////////////////////////////////////////////

Mesh* ResourceSystem::getMesh(const NxString& mesh_identifier) {
	Mesh* mesh = mMeshes.Get(mesh_identifier);
	if (mesh != 0)
		mesh->mMesh.increaseReference();
	return mesh;
}

/////////////////////////////////////////////////////////////

bool ResourceSystem::hasMesh(const NxString& mesh_identifier) {
	return (mMeshes.Get(mesh_identifier) != 0);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::returnMesh(NxOgre::Resources::Mesh* mesh) {
	mesh->mMesh.decreaseReference();
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addMeshAs(const ResourceIdentifier& ri, const NxString& MeshIdentifier) {
	Resource* r = get(ri, RA_Read);
	Mesh* mesh = NxNew(Mesh)(r);
	mMeshes.Insert(MeshIdentifier, mesh);
	delete r;
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addMeshAs(Resource* resource, const NxString& MeshIdentifier) {
	Mesh* mesh = NxNew(Mesh)(resource);
	mMeshes.Insert(MeshIdentifier, mesh);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addHeightfield(const ResourceIdentifier& ri) {
	Resource* r = get(ri, RA_Read);
	Heightfield* hf = NxNew(Heightfield)(r);
	NxString hf_identifier = removeResourcePrefix(r->getResourceIdentifier());
	mHeightfields.Insert(hf_identifier, hf);
	NxDelete(r);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addHeightfieldAs(const ResourceIdentifier& ri, const NxString& heightfield_identifier) {
	Resource* r = get(ri, RA_Read);
	Heightfield* hf = NxNew(Heightfield)(r);
	mHeightfields.Insert(heightfield_identifier, hf);
	delete r;
}

/////////////////////////////////////////////////////////////

void ResourceSystem:: addHeightfield(Resource* resource) {
	Heightfield* hf = NxNew(Heightfield)(resource);
	NxString hf_identifier = removeResourcePrefix(resource->getResourceIdentifier());
	mHeightfields.Insert(hf_identifier, hf);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addHeightfieldAs(Resource* resource, const NxString& heightfield_identifier) {
	Heightfield* hf = NxNew(Heightfield)(resource);
	mHeightfields.Insert(heightfield_identifier, hf);
}

/////////////////////////////////////////////////////////////

void ResourceSystem::addHeightfield(const NxString& heightfield_identifier, Heightfield* hf) {
	mHeightfields.Insert(heightfield_identifier, hf);
}

/////////////////////////////////////////////////////////////

Heightfield* ResourceSystem::getHeightfield(const NxString& heightfield_identifier) {
	Heightfield* hf = mHeightfields.Get(heightfield_identifier);
	hf->increaseReference();
	return hf;
}

/////////////////////////////////////////////////////////////

void  ResourceSystem::returnHeightfield(Heightfield* hf) {
	hf->decreaseReference();
}

/////////////////////////////////////////////////////////////

bool  ResourceSystem::hasHeightfield(const NxString& heightfield_identifier) {
	return (mHeightfields.Get(heightfield_identifier) != 0);
}

/////////////////////////////////////////////////////////////

void  ResourceSystem::clearHeightfield(const NxString& heightfield_identifier) {

}

/////////////////////////////////////////////////////////////

void  ResourceSystem::destroyHeightfield(const NxString& heightfield_identifier) {

}

/////////////////////////////////////////////////////////////

ResourceCallback* ResourceSystem::getCallback() {
	return mCallback;
}

/////////////////////////////////////////////////////////////

void ResourceSystem::setCallback(ResourceCallback* callback, GarbageCollectionPolicy gcp) {
	if (mCallback && mCallbackDeletionPolicy == GC_Delete)
		delete mCallback;
	mCallback = callback;
	mCallbackDeletionPolicy = gcp;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
