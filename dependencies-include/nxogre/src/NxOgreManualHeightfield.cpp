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

#include "NxOgreManualHeightfield.h"
#include "NxOgreHeightfield.h"
#include "NxOgreResourceSystem.h"
#include "NxOgrePhysXDriver.h"
#include "NxOgreResource.h"
#include "NxOgreMaterial.h"

#include "BetajaenCC.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

ManualHeightfield::ManualHeightfield()
: mNbColumns(0), mNbRows(0), mCurrentTesselation(false), mCurrentMaterial0(0),
mCurrentMaterial1(0), mSamples(0), mVerticalExtent(0), mThickness(0),
mConvexEdgeThreshold(0), mFlag_NX_HF_NO_BOUNDARY_EDGES(false)
{
}

/////////////////////////////////////////////////////////////

ManualHeightfield::~ManualHeightfield()
{
	clear();
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::clear() {

	if (mSamples)
		delete mSamples;

}

/////////////////////////////////////////////////////////////

void ManualHeightfield::begin(int nbColumns, int nbRows) {

	if (mSamples == 0)
		mSamples = new Betajaen::Flat<NxHeightFieldSample, Betajaen::SharedAllocator>(new Betajaen::SharedAllocator(), true);

	mSamples->_reserve(nbColumns * nbRows);
	
	mNbColumns = nbColumns;
	mNbRows = nbRows;

}

/////////////////////////////////////////////////////////////

Heightfield* ManualHeightfield::end(bool cleanup) {

	NxHeightField* nxhf = _createHeightFieldMesh();
	
	if (nxhf == 0)
		return 0;

	Heightfield* hf = NxNew(Heightfield)();
	hf->mHeightfield = nxhf;

	return hf;
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::endToHeightfield(Heightfield* hf) {
	NxHeightField* nxhf = _createHeightFieldMesh();
	hf->mHeightfield = nxhf;
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::setDefaultMaterial0(NxMaterialIndex i) {
	mCurrentMaterial0 = i;
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::setDefaultMaterial0(Material* material) {
	mCurrentMaterial0 = material->getMaterialIndex();
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::setDefaultMaterial1(Material* material) {
	mCurrentMaterial1 = material->getMaterialIndex();
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::setDefaultMaterial1(NxMaterialIndex i) {
	mCurrentMaterial1 = i;
}

/////////////////////////////////////////////////////////////

int2 ManualHeightfield::whereAmI() const {
	int2 coords(0,0);
	// probably mSamples->_size() % nbColumns, mSamples->_size() - mSamples->_size() & nbColumns
	return coords;
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::setTesselation(TesselationType i) {
	if (i == TT_TopRight_to_BottomLeft)
		mCurrentTesselation = false;
	else
		mCurrentTesselation = true;
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(short height) {
	NxHeightFieldSample hf_sample;
	hf_sample.height = height;
	hf_sample.materialIndex0 = mCurrentMaterial0;
	hf_sample.materialIndex1 = mCurrentMaterial1;
	hf_sample.tessFlag = mCurrentTesselation;
	sample(hf_sample);
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(short height, NxMaterialIndex mat0) {
	NxHeightFieldSample hf_sample;
	hf_sample.height = height;
	hf_sample.materialIndex0 = mat0;
	hf_sample.materialIndex1 = mCurrentMaterial1;
	hf_sample.tessFlag = mCurrentTesselation;
	sample(hf_sample);
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(short height, NxMaterialIndex mat0, NxMaterialIndex mat1) {
	NxHeightFieldSample hf_sample;
	hf_sample.height = height;
	hf_sample.materialIndex0 = mat0;
	hf_sample.materialIndex1 = mat1;
	hf_sample.tessFlag = mCurrentTesselation;
	sample(hf_sample);
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(short height, NxMaterialIndex mat0, NxMaterialIndex mat1, bool tess) {
	NxHeightFieldSample hf_sample;
	hf_sample.height = height;
	hf_sample.materialIndex0 = mat0;
	hf_sample.materialIndex1 = mat1;
	hf_sample.tessFlag = tess;

	sample(hf_sample);
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(short height, bool tess) {
	NxHeightFieldSample hf_sample;
	hf_sample.height = height;
	hf_sample.materialIndex0 = mCurrentMaterial0;
	hf_sample.materialIndex1 = mCurrentMaterial1;
	hf_sample.tessFlag = tess;
	sample(hf_sample);
}

/////////////////////////////////////////////////////////////

void ManualHeightfield::sample(NxHeightFieldSample hf_sample) {

	if (mSamples->End <= mSamples->Last)
		mSamples->_reserve( (1 + mSamples->_size()) * 2);

	*mSamples->Last = hf_sample;
	mSamples->Last++;

}

/////////////////////////////////////////////////////////////

NxHeightField* ManualHeightfield::_createHeightFieldMesh() {
	
	NxHeightField*     hf = 0;
	NxHeightFieldDesc  desc;
	
	desc.setToDefault();
	desc.nbRows = mNbRows;
	desc.nbColumns = mNbColumns;
	desc.samples = mSamples->First;
	desc.sampleStride = sizeof(NxU32); // sizeof(NxHeightFieldSample);
	desc.format = NX_HF_S16_TM;
	desc.thickness = mThickness;
	desc.verticalExtent = mVerticalExtent;
	desc.flags = 0;
	desc.convexEdgeThreshold = mConvexEdgeThreshold;
	
	if (mFlag_NX_HF_NO_BOUNDARY_EDGES)
		desc.flags |= NX_HF_NO_BOUNDARY_EDGES;

	hf = ResourceSystem::getSingleton()->getPhysXDriver()->getSDK()->createHeightField(desc);

	return hf;
}

/////////////////////////////////////////////////////////////

void   ManualHeightfield::setVerticalExtent(NxReal v) {
	mVerticalExtent = v;
}

/////////////////////////////////////////////////////////////

NxReal ManualHeightfield::getVerticalExtent() const {
	return mVerticalExtent;
}

/////////////////////////////////////////////////////////////

void   ManualHeightfield::setThickness(NxReal v) {
	mThickness = v;
}

/////////////////////////////////////////////////////////////

NxReal ManualHeightfield::getThickness() const {
	return mThickness;
}

/////////////////////////////////////////////////////////////

void   ManualHeightfield::setConvexEdgeThreshold(NxReal v) {
	mConvexEdgeThreshold = v;
}

/////////////////////////////////////////////////////////////

NxReal ManualHeightfield::getConvexEdgeThreshold() const {
	return mConvexEdgeThreshold;
}

/////////////////////////////////////////////////////////////

void   ManualHeightfield::setHasNoBoundaryEdges(bool v) {
	mFlag_NX_HF_NO_BOUNDARY_EDGES = v;
}

/////////////////////////////////////////////////////////////

bool   ManualHeightfield::getHasNoBoundaryEdges() const {
	return mFlag_NX_HF_NO_BOUNDARY_EDGES;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
