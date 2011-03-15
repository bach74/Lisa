/** \file    NxOgreResource.cpp
 *  \see     NxOgreResource.h
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
#include "NxOgreResource.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

NxU8   Resource::readByte() const {
	return getUChar();
}

/////////////////////////////////////////////////////////////

NxU16   Resource::readWord() const {
	return getShort();
}

/////////////////////////////////////////////////////////////

NxU32   Resource::readDword() const {
	return getUInt();
}

/////////////////////////////////////////////////////////////

NxReal   Resource::readFloat() const {
	return getFloat();
}

/////////////////////////////////////////////////////////////

double   Resource::readDouble() const {
	return getDouble();
}

/////////////////////////////////////////////////////////////

void   Resource::readBuffer(void* buffer, NxU32 size) const {
	return get(buffer, size);
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeByte(NxU8 b) {
	writeUChar(b);
	return *this;
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeWord(NxU16 w) {
	writeUShort(w);
	return *this;
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeDword(NxU32 d) {
	writeUInt(d);
	return *this;
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeFloat(NxReal f) {
	writeFloat(f);
	return *this;
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeDouble(NxF64 f) {
	writeDouble(f);
	return *this;
}

/////////////////////////////////////////////////////////////

NxStream&   Resource::storeBuffer(const void* buffer, NxU32 size) {
	write(buffer, size);
	return *this;
}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
