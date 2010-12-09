/** \file    NxOgreMesh.h
 *  \brief   Header for the Mesh class.
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


#ifndef __NXOGRE_HEIGHTFIELD_H__
#define __NXOGRE_HEIGHTFIELD_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass Heightfield {

		friend class ResourceSystem;
		friend class ManualHeightfield;
		friend class Terrain;

		public:

			Heightfield();
			Heightfield(const ResourceIdentifier&);
			Heightfield(Resource*);
			~Heightfield();

			void load(Resource*);
			void load(const ResourceIdentifier&);
			void save(Resource*);
			void save(const ResourceIdentifier&);

			NxU32     getReferenceCount() const;
			
			enum Reason {
				R_HasHeightfield    = 0,
				R_InvalidResource   = 1,
			};

			NxU32  getNbRows() const;
			NxU32  getNbColumns() const;

		protected:

			void  increaseReference();
			void  decreaseReference();

			/// \internal BJN<42>HTFD
			bool _save(Resource*);
	
			/// \internal BJN<42>HTFD
			bool _load(Resource*);

			NxHeightField* mHeightfield;
			NxU32          mNbReferences;

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif
