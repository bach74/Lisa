/** \file    NxOgreSleepCallback.h
 *  \brief   Header for the SleepCallback class.
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

#ifndef __NXOGRE_SLEEP_CALLBACK_H__
#define __NXOGRE_SLEEP_CALLBACK_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {


	/** \brief Class to alert you when an actor has fallen asleep or woken up.

		\example
			<code>

				class Sleepy : public SleepCallback {

				public:

						Sleepy() {
							i = 0;
						}

						ActorSleep(Actor*) {
							i++;
						}

						ActorWake(Actor*) {
							i--;
						}

						unsigned int getSleepingActors() const {
							return i;
						}
					
					protected:
						
						unsigned int i;
						
				};

				// ...

				mScene->setSleepCallback(new Sleepy(), GC_Delete);
			</code>
	*/
	class NxPublicClass SleepCallback {

		public:

			~SleepCallback() {}
			virtual void ActorWake(Actor*)  {}
			virtual void ActorSleep(Actor*) {}

	};

}; // End of NxOgre namespace.

#endif
