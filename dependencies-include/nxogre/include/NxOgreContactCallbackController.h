/** \file    NxOgreSleepCallback.h
 *  \brief   Header for the SleepCallback class.
 *  \version 1.0-20
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

#ifndef __NXOGRE_CONTACT_CALLBACK_CONTROLLER_H__
#define __NXOGRE_CONTACT_CALLBACK_CONTROLLER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContactCallback.h"

namespace NxOgre {

	class NxPublicClass ContactCallbackController : public NxUserContactReport {

		public:

			ContactCallbackController(Scene*);
			~ContactCallbackController();

			void onContactNotify(NxContactPair& pair, NxU32 events);
			void registerSimpleCallback(Actor*, Actor*);
			void registerGroupCallback(ActorGroup*, ActorGroup*);

		protected:
			
			Scene*       mScene;

			Betajaen::SharedMap<Actor*, ActorContactCallback>   mCallbacks;

	};

}; // End of NxOgre namespace.

#endif
