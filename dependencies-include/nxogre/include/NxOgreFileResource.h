/** \file    NxOgreFileResource.h
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


#ifndef __NXOGRE_FILE_RESOURCE_H__
#define __NXOGRE_FILE_RESOURCE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreResource.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass FileResource : public Resource {

		friend class FileResourceManager;

		protected:

			FileResource(const ResourceIdentifier&, ResourceAccess);

		public:

			~FileResource();

			ResourceIdentifier  getResourceIdentifier() const;

			/** \brief Re-use the stream.
			*/
			void  reuse(const ResourceIdentifier&, ResourceAccess);

			/** \brief Close the stream.
			*/
			void  close();

			/** \brief The size of the stream.
			*/
			NxU32  size() const;

			/** \brief Set the read pointer to X bytes from the beginning of the stream.
			*/
			void  seek(long);

			/** \brief Skip forward so many bytes from the current position of the read pointer.
			*/
			void  skip(long);

			/** \brief How far is the read pointer from the beginning of the stream.
			*/
			size_t  tell() const;

			/** \brief Reset the readPointer to the beginning.
				\note <strong>Must</strong> be used with MemoryStreams after writing and reading is about to commence.
			*/
			void  rewind();

			/** \brief Write char to the stream.
			*/
			void  writeUChar(unsigned char);

			/** \brief Write short to the stream.
			*/
			void  writeUShort(unsigned short);

			/** \brief Write unsigned int to the stream.
			*/
			void  writeUInt(unsigned int);

			/** \brief Write float to the stream.
			*/
			void  writeFloat(float);

			/** \brief Write double to the stream.
			*/
			void  writeDouble(double);

			/** \brief Write a stl string to the stream.
			*/
			void  writeString(std::string);

			/** \brief Write any data to the stream.
			*/
			void  write(const void*, size_t length);

			/** \brief Get a char from the stream.
			*/
			unsigned char  getUChar() const;

			/** \brief Get a short from the stream.
			*/
			unsigned short  getShort() const;

			/** \brief Get a unsigned int from the stream.
			*/
			unsigned int  getUInt() const;

			/** \brief Get a float from the stream.
			*/
			float  getFloat() const;

			/** \brief Get a double from the stream.
			*/
			double  getDouble() const;

			/** \brief Get a stl string from the stream.
			*/
			std::string  getString() const;

			/** \brief Get any data from the stream.
			*/
			void  get(void* buffer, size_t length) const;

	protected:

			FILE*                mFile;
			NxU32                mSize;
			ResourceIdentifier   mResourceIdentifier;

	};

}; // End of Resources namespace.
}; // End of NxOgre namespace.

#endif
