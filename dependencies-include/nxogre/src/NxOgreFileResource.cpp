/** \file    NxOgreFileResource.cpp
 *  \see     NxOgreFileResource.h
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
#include "NxOgreFileResource.h"
#include "NxOgreResourceSystem.h"
#include "NxOgreResourceCallback.h"

namespace NxOgre {
namespace Resources {
	
//////////////////////////////////////////////////////////////////////

FileResource::FileResource(const ResourceIdentifier& _path, ResourceAccess _r_w_or_rw)
: mFile(0), mSize(0) {
	reuse(_path, _r_w_or_rw);
}

//////////////////////////////////////////////////////////////////////

FileResource::~FileResource() {
	close();
}

//////////////////////////////////////////////////////////////////////

ResourceIdentifier  FileResource::getResourceIdentifier() const {
	return mResourceIdentifier;
}

//////////////////////////////////////////////////////////////////////

void FileResource::close() {

	if(mFile)
		fclose(mFile);
	mFile = 0;

	ResourceSystem* rs = ResourceSystem::getSingleton();
	if (rs)
		rs->getCallback()->ResourceClosed(this);

}

//////////////////////////////////////////////////////////////////////

void FileResource::seek(long pos) {
	fseek(mFile, pos, SEEK_SET);
}

//////////////////////////////////////////////////////////////////////

void FileResource::skip(long pos) {
	fseek(mFile, pos, SEEK_CUR);
}

//////////////////////////////////////////////////////////////////////

size_t FileResource::tell() const {
	return ftell(mFile);
}

//////////////////////////////////////////////////////////////////////

void FileResource::reuse(const ResourceIdentifier& _path, ResourceAccess _r_w_or_rw) {
	
	if (mFile)
		close();

	bool reading = true;

	mResourceIdentifier = _path;

	NxString filename = _path;
	filename = ResourceSystem::getSingleton()->removeResourcePrefix(filename);


	if (_r_w_or_rw == RA_ReadWrite || _r_w_or_rw == RA_Write)
		reading = false;

	#ifdef NX_PLATFORM_WINDOWS
		fopen_s(&mFile,filename.c_str(), reading ? "rb" : "wb");
	#else
		mFile = fopen(filename.c_str(), reading ? "rb" : "wb");
	#endif

	if (mFile == 0) {
		NxThrow(NxString("File '" + filename + "' could not be opened for " + (reading ? "Reading" : "Writing")).c_str());
	}
	Resources::ResourceSystem::getSingleton()->getCallback()->ResourceOpened(this);

	if (reading) {
		fseek(mFile, 0, SEEK_END);
		mSize = ftell(mFile);
		fseek(mFile, 0, SEEK_SET);
	}

}

//////////////////////////////////////////////////////////////////////

NxU32 FileResource::size() const {
	return mSize;
}

//////////////////////////////////////////////////////////////////////

void FileResource::rewind() {
	fseek(mFile, 0, SEEK_SET);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeUChar(unsigned char data) {
	size_t w = fwrite(&data, sizeof(unsigned char), 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeUShort(NxU16 data) {
	size_t w = fwrite(&data, sizeof(NxU16), 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeUInt(unsigned int data) {
	size_t w = fwrite(&data, sizeof(unsigned int), 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeFloat(float data) {
	size_t w = fwrite(&data, sizeof(float), 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeDouble(double data) {
	size_t w = fwrite(&data, sizeof(double), 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

void FileResource::writeString(std::string s) {
	for (NxU32 i=0;i < s.length();i++) {
		writeUChar(s[i]);
	}
	writeUChar(0);
}

//////////////////////////////////////////////////////////////////////

void FileResource::write(const void* data, size_t l) {
	size_t w = fwrite(data, l, 1, mFile);
	// NX_ASSERT(w);
}

//////////////////////////////////////////////////////////////////////

unsigned char FileResource::getUChar() const {
	unsigned char d=0;fread(&d, sizeof(unsigned char), 1, mFile);
	return d;
}

//////////////////////////////////////////////////////////////////////

NxU16 FileResource::getShort() const {
	NxU16 d=0;fread(&d, sizeof(NxU16), 1, mFile);
	return d;
}

//////////////////////////////////////////////////////////////////////

unsigned int FileResource::getUInt() const{
	unsigned int d=0;fread(&d, sizeof(unsigned int), 1, mFile);
	return d;
}

//////////////////////////////////////////////////////////////////////

float FileResource::getFloat() const{
	float d=0;fread(&d, sizeof(float), 1, mFile);
	return d;
}

//////////////////////////////////////////////////////////////////////

double FileResource::getDouble() const{
	double d=0;fread(&d, sizeof(double), 1, mFile);
	return d;
}

//////////////////////////////////////////////////////////////////////

std::string FileResource::getString()	const {

	std::stringstream ss;
	char c;

	while (!feof(mFile)) {
		fread(&c, sizeof(NxU8), 1, mFile);
		if (c == 0) break;
		ss << c;
	}

	return ss.str();
}

//////////////////////////////////////////////////////////////////////

void FileResource::get(void* buffer, size_t size) const {
	fread(buffer, size, 1, mFile);
}

//////////////////////////////////////////////////////////////////////



}; // End of Resources namespace.
}; // End of NxOgre namespace.
