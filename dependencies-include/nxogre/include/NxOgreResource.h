/** \file    NxOgreResource.h
 *  \brief   Header for the Resource class.
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


#ifndef __NXOGRE_RESOURCE_H__
#define __NXOGRE_RESOURCE_H__

#include "NxOgrePrerequisites.h"
#include "NxStream.h"						// For: Resource inherits NxStream (PhysX)

namespace NxOgre {
namespace Resources {

	class NxPublicClass Resource : public NxStream {

		friend class ResourceManager;

		public:

			virtual ~Resource() {}

		public:

			virtual   ResourceIdentifier  getResourceIdentifier() const = 0;

			/** \brief Re-use the stream.
			*/
			virtual   void  reuse(const ResourceIdentifier&, ResourceAccess) = 0;

			/** \brief Close the stream.
			*/
			virtual   void  close() = 0;

			/** \brief The size of the stream.
			*/
			virtual   NxU32  size() const = 0;

			/** \brief Set the read pointer to X bytes from the beginning of the stream.
			*/
			virtual   void  seek(long) = 0;

			/** \brief Skip forward so many bytes from the current position of the read pointer.
			*/
			virtual   void  skip(long) = 0;

			/** \brief How far is the read pointer from the beginning of the stream.
			*/
			virtual   size_t  tell() const = 0;

			/** \brief Reset the readPointer to the beginning.
				\note <strong>Must</strong> be used with MemoryStreams after writing and reading is about to commence.
			*/
			virtual   void  rewind() = 0;

			/** \brief Write char to the stream.
			*/
			virtual   void  writeUChar(unsigned char) = 0;

			/** \brief Write short to the stream.
			*/
			virtual   void  writeUShort(unsigned short) = 0;

			/** \brief Write unsigned int to the stream.
			*/
			virtual   void  writeUInt(unsigned int) = 0;

			/** \brief Write float to the stream.
			*/
			virtual   void  writeFloat(float) = 0;

			/** \brief Write double to the stream.
			*/
			virtual   void  writeDouble(double) = 0;

			/** \brief Write a stl string to the stream.
			*/
			virtual   void  writeString(std::string) = 0;

			/** \brief Write any data to the stream.
			*/
			virtual   void  write(const void*, size_t length) = 0;

			/** \brief Get a char from the stream.
			*/
			virtual   unsigned char  getUChar() const = 0;

			/** \brief Get a short from the stream.
			*/
			virtual   unsigned short  getShort() const = 0;

			/** \brief Get a unsigned int from the stream.
			*/
			virtual   unsigned int  getUInt() const = 0;

			/** \brief Get a float from the stream.
			*/
			virtual   float  getFloat() const = 0;

			/** \brief Get a double from the stream.
			*/
			virtual   double  getDouble() const = 0;

			/** \brief Get a stl string from the stream.
			*/
			virtual   std::string  getString() const = 0;

			/** \brief Get any data from the stream.
			*/
			virtual   void  get(void* buffer, size_t length) const = 0;

		protected:

			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxU8   readByte() const;

			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxU16   readWord() const;

			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxU32   readDword() const;

			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxReal   readFloat() const;

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			double   readDouble() const;
			
			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			void   readBuffer(void* buffer, NxU32 size) const;

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxStream&   storeByte(NxU8 b);

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::getUChar
				\internal
			*/
			NxStream&   storeWord(NxU16 w);

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::storeFloat
				\internal
			*/
			NxStream&   storeDword(NxU32 d);

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::storeFloat
				\internal
			*/
			NxStream&   storeFloat(NxReal f);

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::storeDouble
				\internal
			*/
			NxStream&   storeDouble(NxF64 f);

			
			/** \brief PhysX Interface. Do not override or use.
				\see ResourceStreamPtr::store
				\internal
			*/
			NxStream&   storeBuffer(const void* buffer, NxU32 size);

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif
