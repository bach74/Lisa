/** \file    NxOgreMemoryResource.cpp
 *  \see     NxOgreMemoryResource.h
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
#include "NxOgreMemoryResource.h"

namespace NxOgre {
namespace Resources {
	
/////////////////////////////////////////////////////////////

MemoryResource::MemoryResource()
: mCurrentSize(0), mMaxSize(0), mBuffer(NULL), mReadBuffer(NULL)
{
}

/////////////////////////////////////////////////////////////

MemoryResource::~MemoryResource() {
	close();
}

/////////////////////////////////////////////////////////////

void MemoryResource::reuse(const ResourceIdentifier&, ResourceAccess) {
	close();
}

/////////////////////////////////////////////////////////////

void MemoryResource::close() {

	if(mBuffer) {
		delete [] mBuffer;
		mBuffer       = 0;
		mReadBuffer   = 0;
		mCurrentSize  = 0;
		mMaxSize      = 0;
	}

}

/////////////////////////////////////////////////////////////

size_t MemoryResource::tell() const {
	return 0;
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeUChar(unsigned char b) {
	storeBuffer(&b, sizeof(unsigned char));
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeUShort(unsigned short w) {
	storeBuffer(&w, sizeof(unsigned short));
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeUInt(unsigned int d) {
	storeBuffer(&d, sizeof(unsigned int));
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeFloat(float f) {
	storeBuffer(&f, sizeof(float));
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeDouble(double f) {
	storeBuffer(&f, sizeof(double));
}

/////////////////////////////////////////////////////////////

void MemoryResource::writeString(std::string) {
	NxThrow_AsWarning("Write std::string not supported in MemoryResource");
}

/////////////////////////////////////////////////////////////

void MemoryResource::write(const void* buffer, size_t size) {
	
	NxU32 expectedSize = mCurrentSize + size;

	if(expectedSize > mMaxSize) {
		
		mMaxSize = expectedSize + 4096;
		NxU8* newData = new NxU8[mMaxSize];

		if(mBuffer) {
			memcpy(newData, mBuffer, mCurrentSize);
			if(mBuffer) {
				delete [] mBuffer;
				mBuffer = NULL;
			}
		}
		mBuffer = newData;
		mReadBuffer = mBuffer;
	}

	memcpy(mBuffer+mCurrentSize, buffer, size);

	mCurrentSize += size;

}

/////////////////////////////////////////////////////////////

void MemoryResource::rewind() {
	mReadBuffer = static_cast<NxU8*>(mBuffer);
}
	
/////////////////////////////////////////////////////////////

unsigned char MemoryResource::getUChar() const {
	unsigned char b;
	memcpy(&b, mReadBuffer, sizeof(unsigned char));
	mReadBuffer += sizeof(unsigned char);
	return b;
}

/////////////////////////////////////////////////////////////

NxU16 MemoryResource::getShort() const {
	NxU16 w;
	memcpy(&w, mReadBuffer, sizeof(short));
	mReadBuffer += sizeof(short);
	return w;
}

/////////////////////////////////////////////////////////////

unsigned int MemoryResource::getUInt() const {
	unsigned int d;
	memcpy(&d, mReadBuffer, sizeof(unsigned int));
	mReadBuffer += sizeof(unsigned int);
	return d;
}

/////////////////////////////////////////////////////////////

float MemoryResource::getFloat() const {
	float f;
	memcpy(&f, mReadBuffer, sizeof(float));
	mReadBuffer += sizeof(float);
	return f;	
}

/////////////////////////////////////////////////////////////

double MemoryResource::getDouble() const {
	double f;
	memcpy(&f, mReadBuffer, sizeof(double));
	mReadBuffer += sizeof(double);
	return f;
}

/////////////////////////////////////////////////////////////

std::string	MemoryResource::getString()	const {
	NxThrow_AsWarning("Read std::string not supported in MemoryResource");
	return std::string();
}

/////////////////////////////////////////////////////////////

void MemoryResource::get(void* dest, size_t size) const {
	memcpy(dest, mReadBuffer, size);
	mReadBuffer += size;
}

/////////////////////////////////////////////////////////////

unsigned int MemoryResource::size() const {
	return mCurrentSize;
}

/////////////////////////////////////////////////////////////

void MemoryResource::seek(long s) {
	rewind();
	mReadBuffer += s;
}

/////////////////////////////////////////////////////////////

void MemoryResource::skip(long s) {
	mReadBuffer += s;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
