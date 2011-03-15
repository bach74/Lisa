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
#include "NxOgreShapeTerrain.h"
#include "NxOgreActor.h"				// For:
#include "NxOgreHelpers.h"				// For:
#include "NxOgreResourceSystem.h"		// For:
#include "NxOgreHeightfield.h"			// For:
#include "NxOgreVoidPointer.h"
#include "BetajaenCC.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

void TerrainParams::setToDefault() {

	mCentering = TC_None;
	mMaterialIndexHighBits = 0;
	mHoleMaterial = 0;
	mFlags.toDefault();
}

/////////////////////////////////////////////////////////////

void TerrainParams::parse(Parameters params) {

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {
		
		if (Set("centering", parameter, mCentering, TC_CenterAbove, "xz-above", TC_CenterXZ, "xz")) continue;
		if (Set("hole-material", parameter, mHoleMaterial)) continue;
		if (Set("material-index-high-bits", parameter, mMaterialIndexHighBits)) continue;
		if (is("flags", parameter)) {
			mFlags.parse(parameter->j);
			continue;
		}
	}

}

/////////////////////////////////////////////////////////////

void  TerrainParams::TerrainFlags::fromNxU32(NxU32 flag) {

	if (flag & NX_MESH_SMOOTH_SPHERE_COLLISIONS)
		mSmoothSphereCollisions = true;

}

/////////////////////////////////////////////////////////////

NxU32  TerrainParams::TerrainFlags::toNxU32() const {
	
	NxU32 flag = 0;

	if (mSmoothSphereCollisions)
		flag |= NX_MESH_SMOOTH_SPHERE_COLLISIONS;

	return flag;
}

/////////////////////////////////////////////////////////////

void  TerrainParams::TerrainFlags::parse(const NxString& flag_str) {

	Container<unsigned int, NxString> str_flags;
	str_flags = NxStringTokenize(flag_str, "+", true);

	if (str_flags.count() == 0)
		return;

	for (NxU32 i=0;i < str_flags.count();i++) {

		NxString flag_str = str_flags[i];

		NxStringTrim(flag_str);
		NxStringToLower(flag_str);
	
		if (set("smooth-sphere-collisions", flag_str, mSmoothSphereCollisions)) continue;
		if (set("ssc", flag_str, mSmoothSphereCollisions)) continue;
		if (set("visualise-terrain", flag_str, mVisualiseTerrain)) continue;
		if (set("vt", flag_str, mVisualiseTerrain)) continue;

	}

}

/////////////////////////////////////////////////////////////

Terrain::Terrain(Resources::Heightfield* hf, float3 size, const ShapeParams& params, const TerrainParams& t_params)
: Shape(), mHeightfield(0), mTerrainParams(t_params)
{
	mParams = params;
	paramsToDescription(&mShapeDescription, &mParams);

	mHeightfield = hf;

	mShapeDescription.setToDefault();

	mShapeDescription.rowScale = size.i / NxReal(hf->getNbRows());
	mShapeDescription.columnScale = size.k / NxReal(hf->getNbColumns());
	mShapeDescription.heightScale = size.j / 32768.0f ; // (size.j * 0.5f) / 32768.0f; // 0.5 should be for 16-bit, if weird then remove.
	
}

/////////////////////////////////////////////////////////////

Terrain::~Terrain() {
	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
}

/////////////////////////////////////////////////////////////

void Terrain::createShape(NxActor* actor, NxShapeIndex index, Scene* scene) {
	
	/// \todo See Cube::createShape

}

/////////////////////////////////////////////////////////////

void Terrain::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene)  {
	
	extendedParamsToDescription(scene, mParams, &mShapeDescription);
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	if (mHeightfield == 0) {

		Resources::ResourceSystem* rs = Resources::ResourceSystem::getSingleton();
		NxString heightfield_identifier = rs->removeResourcePrefix(mResourceIdentifier);
		mHeightfield = rs->getHeightfield(heightfield_identifier);

		if (mHeightfield == 0) {
			mHeightfield = new Resources::Heightfield(rs->get(mResourceIdentifier));
			rs->addHeightfield(heightfield_identifier, mHeightfield);
		}

	}


	mShapeDescription.heightField = mHeightfield->mHeightfield;

	if (mTerrainParams.mCentering == TerrainParams::TC_CenterXZ) {
		mShapeDescription.localPose.t.x = -((mShapeDescription.rowScale * mShapeDescription.heightField->getNbRows()) * 0.5f);
		mShapeDescription.localPose.t.z = -((mShapeDescription.rowScale * mShapeDescription.heightField->getNbColumns()) * 0.5f);
	}
	else if (mTerrainParams.mCentering == TerrainParams::TC_CenterAbove) {
		mShapeDescription.localPose.t.x = -((mShapeDescription.rowScale * mShapeDescription.heightField->getNbRows()) * 0.5f);
		mShapeDescription.localPose.t.y =   (mShapeDescription.heightScale * 32768.0f);
		mShapeDescription.localPose.t.z = -((mShapeDescription.rowScale * mShapeDescription.heightField->getNbColumns()) * 0.5f);
	}

	mShapeDescription.shapeFlags ^= NX_SF_VISUALIZATION;      // Terrain visualation results in the application
	                                                          // in a near catatonic state when enabled.

	mShapeDescription.holeMaterial = mTerrainParams.mHoleMaterial;
	mShapeDescription.materialIndexHighBits = mTerrainParams.mMaterialIndexHighBits;
	mShapeDescription.meshFlags = mTerrainParams.mFlags.toNxU32();
	

	if (!isValid(mShapeDescription) || !isTerrainShapeValid())
		return;

	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;

}

/////////////////////////////////////////////////////////////

void Terrain::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

bool Terrain::isTerrainShapeValid() const {

	bool result = true;

	/// \todo

	return result;
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
