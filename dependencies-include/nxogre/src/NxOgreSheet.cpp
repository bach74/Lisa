/** \file    NxOgreSheet.cpp
 *  \see     NxOgreSheet.h
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
#include "NxOgreSheet.h"

#if 0

#include "NxOgrePose.h"					// For conversions
#include "NxOgreHelpers.h"				// For conversions
#include "NxOgreScene.h"				// For Cloth::mOwner
#include "NxOgreResourceManager.h"		// For Dynamic Cloth fetching
/// #include "NxOgreDynamicMesh.h"
#include "NxOgreResourceMesh.h"
#include "NxOgreResourceStream.h"
#include "NxOgreResourceStreamPtr.h"
#include "NxOgreMeshRenderable.h"
#include "NxOgreSceneRenderer.h"

#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "OgreMovableObject.h"
#include "OgreRoot.h"
#include "OgreSingleton.h"
#include "OgreMeshManager.h"
#include "OgreStringConverter.h"

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////////////////

// Note for duplicate sheets using the same parameters for the cloth, the second duplicate sheet
// should use it's own name as a mesh with a prefix of cloth.

Sheet::Sheet(const NxString& identifier, Scene* scene, NxReal width, NxReal height, NxReal verticesPerRow, NxReal verticesPerColumn, Pose pose, ClothParams params, MeshRenderableParams visualParams)
: Cloth(identifier, scene) {
	
	NxString mesh_identifier;
	mesh_identifier.append("Cloth;");
	mesh_identifier.append(Ogre::StringConverter::toString(verticesPerRow));
	mesh_identifier.append(";");
	mesh_identifier.append(Ogre::StringConverter::toString(verticesPerColumn));
	mesh_identifier = ResourceManager::getSingleton()->getMeshIdentifier(mesh_identifier, NxVec3(width, 0, height));

	mDynamicMesh = ResourceManager::getSingleton()->getDynamicClothMesh(mesh_identifier);

	if (mDynamicMesh == 0) {
		mDynamicMesh = __createSheet(width, verticesPerRow, height, verticesPerColumn, mesh_identifier);
	}

	if (mDynamicMesh->mNbNormals == 0 && mDynamicMesh->mNbTextureCoordinates == 0) {
		__generateTextureCoordinatesAndNormals(width, verticesPerRow, height, verticesPerColumn);
	}

	createCloth(mDynamicMesh->getMeshPtr(), params, pose);

	mRenderable = mOwner->getSceneRenderer()->createMeshRenderable(visualParams, mDynamicMesh);
	mMeshRenderable = static_cast<MeshRenderable*>(mRenderable);

}

////////////////////////////////////////////////////////////////////////////////////////////////

Sheet::~Sheet() {

}

////////////////////////////////////////////////////////////////////////////////////////////////

DynamicClothMesh* Sheet::__createSheet(NxReal w, NxReal wD, NxReal h, NxReal hD, const NxString& meshIdentifier) {
	
	DynamicClothMesh* mesh = 0;
	ClothMeshIntermediary* cmi = 0;
	NxClothMesh* cloth_mesh = 0;
	ResourceManager* rm = ResourceManager::getSingleton();
	cmi = rm->generateClothMesh(w, h, wD, hD);
	//rm->cookClothMesh(cmi, aa);
		
	mesh = new DynamicClothMesh();
	mesh->fromClothMeshIntermediary(cmi);

#if (NX_USE_TEMPORARYCOOKING_TO_DISK == 1)

	if (ResourceManager::getSingleton()->cookClothMesh(cmi, ResourceStreamPtr(
			"file://"
			NX_USE_TEMPORARYCOOKING_TO_DISK_PATH
			" +write")))
	{
		ResourceManager::getSingleton()->loadClothMesh(meshIdentifier, ResourceStreamPtr(
			"file://"
			NX_USE_TEMPORARYCOOKING_TO_DISK_PATH
		));

		cloth_mesh = ResourceManager::getSingleton()->getClothMesh(meshIdentifier);
	}
	else {
		NxThrow_Warning("Convex mesh '" + meshname +  "' could not be used with ConvexShape. Cooking process failed.");
	}

#else

	ResourceStreamPtr memoryStream(NxMemoryStreamIdentifier);

	if (ResourceManager::getSingleton()->cookClothMesh(cmi, memoryStream)) {
		memoryStream->rewind();
		ResourceManager::getSingleton()->loadClothMesh(meshIdentifier, memoryStream);
		cloth_mesh = ResourceManager::getSingleton()->getClothMesh(meshIdentifier);
	}
	else {
		NxThrow_AsWarning(NxString("Cloth mesh '" + meshIdentifier +  "' could not be used with ConvexShape. Cooking process failed.").c_str());
	}

	memoryStream->close();

#endif

	delete cmi;
	mesh->mMeshPtr = cloth_mesh;

	rm->loadClothMesh(meshIdentifier, cloth_mesh);
	
	return mesh;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Sheet::__generateTextureCoordinatesAndNormals(NxReal w, NxReal wD, NxReal h, NxReal hD) {
	
	NxReal nbX = NxReal(w * wD) + 1;
	NxReal nbY = NxReal(h * hD) + 1;
	NxU32 totalX = (NxU32) nbX;
	NxU32 totalY = (NxU32) nbY;
	
	mDynamicMesh->mNbNormals = mDynamicMesh->mNbVertices;
	mDynamicMesh->mNormals = (NxVec3*) malloc(sizeof(NxVec3) * mDynamicMesh->mNbNormals);
	
	mDynamicMesh->mNbTextureCoordinates = mDynamicMesh->mNbVertices;
	mDynamicMesh->mTextureCoordinates = (float2*) malloc(sizeof(float2) * mDynamicMesh->mNbTextureCoordinates);



	NxVec3* n = mDynamicMesh->mNormals;
	NxVec3* v = mDynamicMesh->mVertices;
	float2* t = mDynamicMesh->mTextureCoordinates;

	NxVec3  vertex;
	for (NxU32 i = 0; i <= totalY; i++) {
		NxReal yCoord = NxReal(i) / nbY;
		for (NxU32 j = 0; j <= totalX; j++) {
			t->i = 1.0f - NxReal(j) / nbY;
			t->j = 1.0f - yCoord;
			vertex.set(v->x, v->y, v->z);
			vertex = vertex.cross(vertex);
			n->set(vertex);
			n->normalize();
			*n++;
			*v++;
			*t++;
		}
	}


}

////////////////////////////////////////////////////////////////////////////////////////////////

} //End of NxOgre namespace.

////#endif
#endif