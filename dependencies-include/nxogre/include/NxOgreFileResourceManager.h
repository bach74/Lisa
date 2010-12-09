/** \file    NxOgreResourceManager.h
 *  \brief   Header for the ResourceManager class.
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


#ifndef __NXOGRE_FILE_RESOURCEMANAGER_H__
#define __NXOGRE_FILE_RESOURCEMANAGER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreResourceManager.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass FileResourceManager : public ResourceManager {
		
		friend class ResourceSystem;

		protected:

			FileResourceManager();
			NxString    getType() const {return "file";}
			Resource*   get(const ResourceIdentifier&, ResourceAccess);

	};

}; // End of Resources namespace.
}; // End of NxOgre namespace.

#endif
