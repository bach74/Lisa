/** \file    NxOgreDeletionCallback.h
 *  \brief   Header for the DeletionCallback class and DelayedActor struct.
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

#ifndef __NXOGRE_DELETION_CALLBACK_H__
#define __NXOGRE_DELETION_CALLBACK_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContactCallback.h"

namespace NxOgre {

	/////////////////////////////////////////////////////////

	struct NxPublicClass DelayedActor {
	
		/** \brief Actor to be destroyed
		*/
		Actor*         actor;

		/** \brief Void pointer of the actor, which if the actor is rendered, renderptr is usable.
		*/
		VoidPointer*   voidPtr;

		/** \brief Custom data for you to use whilst the actor is being "delayed" deleted.
		*/
		void*          custom;

		/** \brief Custom integer for you to use whilst the actor is being "delayed" deleted.
		*/
		int            customInt;

		/** \brief Number of frames deleted.
		*/
		unsigned int   nbFramesDelayed;

	};

	/////////////////////////////////////////////////////////

	class NxPublicClass DeletionCallback {

		public:

			virtual ~DeletionCallback() {}

			/** \brief This actor has been requested to be delay deleted, depending
					    on the delete, the actor may be "dead" or still physically active.
				\note  Any special effects should start here.
			*/
			virtual void onActorDelayDeleteBegin(DelayedActor*) = 0;

			/** \brief Should this Actor be deleted? or be delayed for another frame.
				\note  Called each simulation until Actor deleted, any special effects
				       should be continued here.
				\return True if the Actor should be deleted now.
			*/
			virtual bool onActorDelayDelete(DelayedActor*, NxReal dT) = 0;

			/** \brief This actor is now going to be deleted.
				\note Called when result of ActorDelayed true. Any special effects should
					  be immediately destroyed and cleaned up.
			*/
			virtual void onActorDelayDeleteEnd(DelayedActor*) = 0;

	};

	/////////////////////////////////////////////////////////

}; // End of NxOgre namespace.

#endif
