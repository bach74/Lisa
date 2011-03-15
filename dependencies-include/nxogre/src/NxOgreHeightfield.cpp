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
#include "NxOgreHeightfield.h"
#include "NxOgreResource.h"
#include "NxOgreResourceSystem.h"
#include "NxOgrePhysXDriver.h"
#include "NxOgreResourceCallback.h"
#include "NxOgreManualHeightfield.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

Heightfield::Heightfield() : mNbReferences(0) {
	mHeightfield = 0;
}

/////////////////////////////////////////////////////////////

Heightfield::Heightfield(const ResourceIdentifier& ri) : mNbReferences(0) {
	mHeightfield = 0;
	load(ri);
}

/////////////////////////////////////////////////////////////

Heightfield::Heightfield(Resource* rs) : mNbReferences(0) {
	mHeightfield = 0;
	load(rs);
}

/////////////////////////////////////////////////////////////

Heightfield::~Heightfield() {
	mHeightfield = 0;
}

/////////////////////////////////////////////////////////////

void Heightfield::load(const ResourceIdentifier& ri) {
	Resource* resource = ResourceSystem::getSingleton()->get(ri, RA_Read);
	load(resource);
	NxDelete(resource);
}

/////////////////////////////////////////////////////////////

void Heightfield::load(Resource* resource) {

	ResourceSystem::getSingleton()->getCallback()->HeightfieldLoading(this, resource);

	if (!mHeightfield == 0) {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldLoadingFailed(this, resource, R_HasHeightfield);
		return;
	}

	if(_load(resource)) {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldLoaded(this);
	}
	else {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldLoadingFailed(this, resource, R_InvalidResource);
	}

}

/////////////////////////////////////////////////////////////

void Heightfield::save(const ResourceIdentifier& ri) {
	
	Resource* rs = ResourceSystem::getSingleton()->get(ri, RA_Write);

	ResourceSystem::getSingleton()->getCallback()->HeightfieldSaving(this, rs);

	if (_save(rs)) {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldSaved(this, rs);
	}
	else {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldSavingFailed(this, rs, R_InvalidResource);
	}

	NxDelete(rs);
}

/////////////////////////////////////////////////////////////

void Heightfield::save(Resource* rs) {

	ResourceSystem::getSingleton()->getCallback()->HeightfieldSaving(this, rs);

	if (_save(rs)) {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldSaved(this, rs);
	}
	else {
		ResourceSystem::getSingleton()->getCallback()->HeightfieldSavingFailed(this, rs, R_InvalidResource);
	}

}

/////////////////////////////////////////////////////////////

bool Heightfield::_save(NxOgre::Resources::Resource *rs) {

	// Write header BJN<42>
	rs->writeUChar('N');
	rs->writeUChar('x');
	rs->writeUChar('O');
	rs->writeUChar(42);

	// Write heightfield header
	rs->writeUChar('H');
	rs->writeUChar('T');
	rs->writeUChar('F');
	rs->writeUChar('D');

	/// \todo MaterialAlias
	/// Write "0" to say it doesn't have a material alias attached.
	rs->writeUChar(0);

	// Write width (as two bytes - short)
	rs->writeUShort((unsigned short)mHeightfield->getNbRows());
	
	// Write height (as two bytes - short)
	rs->writeUShort((unsigned short)mHeightfield->getNbColumns());

	unsigned int wh = mHeightfield->getNbRows() * mHeightfield->getNbColumns();
	const char* currentByte = (char*) mHeightfield->getCells();
	for (unsigned int i=0;i < wh;i++) {
		NxHeightFieldSample* currentSample = (NxHeightFieldSample*)currentByte;
		rs->write(currentSample, sizeof(NxHeightFieldSample));
		currentByte += sizeof(NxHeightFieldSample);
	}

	//	for as width * height
	//		write:-
	//			height - 16 bits, a signed 16 bit integer which specifies the elevation at the sample
	//			materialIndex0 - 7 bits, material index
	//			tessFlag - 1 bit, tessellation flag
	//			materialIndex1 - 7 bits, material index
	//			unused/reserved - 1 bit 
	//	endfor
	//	if (material alais)
	//		- read material alias (using material alias class)
	//  close resource
	//	ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);


	// Loop through the material indices again, and change them according to the alias.

	return true;
}

/////////////////////////////////////////////////////////////

bool Heightfield::_load(NxOgre::Resources::Resource *rs) {

	// Write header NxO<42>
	if (rs->size() < 8)
		return false;

	// Read the "NxO" Header.
	{
		char header[3] = {0, 0, 0};
		rs->get(&header, 3);
		if (!(header[0] == 'N' && header[1] == 'x' && header[2] == 'O'))
			return false;
	}

	// Skip forward a Byte (Usually x42)
	rs->skip(1);

	char mesh_header[4] = {0, 0, 0, 0};
	rs->get(&mesh_header, 4);

	if (!(mesh_header[0] == 'H' && mesh_header[1] == 'T' && mesh_header[2] == 'F' && mesh_header[3] == 'D'))
		return false;

	/// \todo MaterialAlias
	/// Write "0" to say it doesn't have a material alias attached.
	rs->getUChar();//	rs->writeUChar(0);

	// Write width (as two bytes - short)
	unsigned short nbRows = rs->getShort(); //rs->writeUShort((unsigned short)mHeightfield->getNbRows());
	
	// Write height (as two bytes - short)
	unsigned short nbColumns = rs->getShort(); //rs->writeUShort((unsigned short)mHeightfield->getNbColumns());

	unsigned int wh = nbRows * nbColumns;

	ManualHeightfield* man_heightfield = new ManualHeightfield();
	man_heightfield->begin(nbColumns, nbRows);

	for (unsigned int i=0;i < wh;i++) {
		NxHeightFieldSample sample;
		rs->get(&sample, sizeof(NxHeightFieldSample));
		man_heightfield->sample(sample);
	}

	man_heightfield->endToHeightfield(this);
	delete man_heightfield;

	// Read Header
	// Does it Start with a BJN<42>
	//	-> No?
	//		return false
	// Read 4 bytes
	//	Does it equal HTFD?
	//	-> No?
	//		return false
	//	Read 1 byte
	//		is it true?
	//			- has material alias
	//		is it false?
	//			- doesn't have material alias
	//	Read 2 bytes as width
	//	Read 2 bytes as height
	//	for as width * height
	//		write:-
	//			height - 16 bits, a signed 16 bit integer which specifies the elevation at the sample
	//			materialIndex0 - 7 bits, material index
	//			tessFlag - 1 bit, tessellation flag
	//			materialIndex1 - 7 bits, material index
	//			unused/reserved - 1 bit 
	//	endfor
	//	if (material alais)
	//		- read material alias (using material alias class)
	//  close resource
	//	ResourceSystem::getSingleton()->getCallback()->ResourceFullyRead(resource);


	// Loop through the material indices again, and change them according to the alias.

	return true;
}

/////////////////////////////////////////////////////////////

NxU32  Heightfield::getNbRows() const {
	if (mHeightfield)
		return mHeightfield->getNbRows();
	return 0;
}

/////////////////////////////////////////////////////////////

NxU32  Heightfield::getNbColumns() const {
	if (mHeightfield)
		return mHeightfield->getNbColumns();
	return 0;
}

/////////////////////////////////////////////////////////////

void  Heightfield::increaseReference() {
	mNbReferences++;
}

/////////////////////////////////////////////////////////////

void  Heightfield::decreaseReference() {
	if (mNbReferences != 0)
		mNbReferences--;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
