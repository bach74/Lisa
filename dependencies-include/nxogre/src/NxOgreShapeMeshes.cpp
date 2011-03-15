/** \file    NxOgreShapeMeshes.cpp
 *  \see     NxOgreShapeMeshes.h
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
#include "NxOgreShapeMeshes.h"
#include "NxOgreActor.h"				// For:
#include "NxOgreHelpers.h"				// For:
#include "NxOgreResourceSystem.h"		// For:
#include "NxOgreMesh.h"					// For:
#include "NxOgreVoidPointer.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

Convex::Convex(Resources::Mesh* mesh, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mMesh = mesh;
}

/////////////////////////////////////////////////////////////

Convex::Convex(const Resources::ResourceIdentifier& identifier, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mResourceIdentifier = identifier;
	// meshname = ResourceSystem->removeResourcePrefix()
	// mResourceSystem->hasMesh(meshname) - Identifier will filter out xxx:// bits.
	//  -no
	//       -> resource = getResource(identifier)
	//       -> mesh = resource->getAsMesh()
	//  -yes
	//       -> mesh = ResourceSystem::getMesh()

}

/////////////////////////////////////////////////////////////

Convex::~Convex() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Convex::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	
	/// \todo See Cube::createShape

}

/////////////////////////////////////////////////////////////

void Convex::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene)  {
	
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mMesh == 0) {

		Resources::ResourceSystem* rs = Resources::ResourceSystem::getSingleton();
		NxString mesh_identifier = rs->removeResourcePrefix(mResourceIdentifier);
		mMesh = rs->getMesh(mesh_identifier);

		if (mMesh == 0) {
			mMesh = new Resources::Mesh(rs->get(mResourceIdentifier));
			rs->addMesh(mesh_identifier, mMesh);
		}

	}

	mShapeDescription.meshData = mMesh->mMesh.mConvexMesh;

	if (!isValid(mShapeDescription) || !isConvexShapeValid())
		return;

	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;

}

/////////////////////////////////////////////////////////////

void Convex::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

bool Convex::isConvexShapeValid() const {

	bool result = true;

	if (!mShapeDescription.meshData) {
#ifdef NX_DEBUG
		printf("ConvexShape::isValid (False) -> Mesh pointer is zero.");
#endif
		result = false;	
	}

	return result;
}

/////////////////////////////////////////////////////////////

TriangleMesh::TriangleMesh(Resources::Mesh* mesh, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mMesh = mesh;
}

/////////////////////////////////////////////////////////////

TriangleMesh::TriangleMesh(const Resources::ResourceIdentifier& identifier, const ShapeParams& params)
: Shape()
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);
	mResourceIdentifier = identifier;
}

/////////////////////////////////////////////////////////////

TriangleMesh::~TriangleMesh() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void TriangleMesh::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	/// \todo See Cube::createShape
}

/////////////////////////////////////////////////////////////

void TriangleMesh::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene)  {
	
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	std::cout << "TriangleMesh::createShape(" << mMesh << ")" << std::endl;

	if (mMesh == 0) {

		Resources::ResourceSystem* rs = Resources::ResourceSystem::getSingleton();
		std::cout << "rs => " << rs << std::endl;

		NxString mesh_identifier = rs->removeResourcePrefix(mResourceIdentifier);
		std::cout << "mesh identifier => " << mesh_identifier << std::endl;

		mMesh = rs->getMesh(mesh_identifier);
	
		std::cout << "mMesh => " << mMesh << std::endl;

		if (mMesh == 0) {
			mMesh = new Resources::Mesh(rs->get(mResourceIdentifier));

			std::cout << "mMesh => " << mMesh << std::endl;

			rs->addMesh(mesh_identifier, mMesh);
			std::cout << "Mesh!! ......." << std::endl;

		}

	}

	mShapeDescription.meshData = mMesh->mMesh.mTriangleMesh;

	if (!isValid(mShapeDescription) || !isTriangleMeshShapeValid()) {
		std::cout << "Not VALID!" << std::endl;	
		return;
	}

	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;

}

/////////////////////////////////////////////////////////////

void TriangleMesh::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

bool TriangleMesh::isTriangleMeshShapeValid() const {

	bool result = true;

	if (!mShapeDescription.meshData) {
#ifdef NX_DEBUG
		printf("ConvexShape::isValid (False) -> Mesh pointer is zero.");
#endif
		result = false;	
	}

	return result;
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.

