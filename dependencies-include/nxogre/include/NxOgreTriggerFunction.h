/** \file    NxOgreTriggerFunction.h
 *  \brief   Header for the TriggerFunction and "Trigger Function" classes.
 *           classes.
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

#ifndef __NXOGRE_TRIGGERFUNCTION_H__
#define __NXOGRE_TRIGGERFUNCTION_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreSimpleActor.h"

namespace NxOgre {

	class NxPublicClass TriggerFunction : public TriggerContactCallback {
		
		public:
			virtual ~TriggerFunction() {}

			virtual void Enter(Trigger*, Actor*)                              {}
			virtual void Enter(Trigger*, CharacterSystem::Character*)         {}
			virtual void Enter(Shape*, Actor*)                                {}
			virtual void Enter(Shape*, CharacterSystem::Character*)           {}

			virtual void Stay(Trigger*, Actor*)                               {}
			virtual void Stay(Trigger*, CharacterSystem::Character*)          {}
			virtual void Stay(Shape*, Actor*)                                 {}
			virtual void Stay(Shape*, CharacterSystem::Character*)            {}

			virtual void Exit(Trigger*, Actor*)                               {}
			virtual void Exit(Trigger*, CharacterSystem::Character*)          {}
			virtual void Exit(Shape*, Actor*)                                 {}
			virtual void Exit(Shape*, CharacterSystem::Character*)            {}

			virtual bool isSharedWithTriggers() const {return true;}

			enum {
				TriggerFunctionHashIdentifier = 1000	// Temp.
			};
			virtual NxShortHashIdentifier getHashIdentifier() const { return TriggerFunctionHashIdentifier; }

	};

	namespace Functions {
		namespace Triggers {

			class NxPublicClass NoGravity : public TriggerFunction {

				public:
					void Enter(Trigger*, Actor*);
					void Exit(Trigger*, Actor*);
					void Enter(Shape*, Actor*);
					void Exit(Shape*, Actor*);

			};

			class NxPublicClass AddedGravity : public TriggerFunction {

				public:
					AddedGravity(float3 gravity);
					void Enter(Trigger*, Actor*);
					void Stay(Trigger*, Actor*);
					void Exit(Trigger*, Actor*);

					bool isSharedWithTriggers() const {return false;}

			};

			class NxPublicClass ReplacementGravity : public TriggerFunction {

				public:
					ReplacementGravity(float3 gravity);
					void Enter(Trigger*, Actor*);
					void Stay(Trigger*, Actor*);
					void Exit(Trigger*, Actor*);

					bool isSharedWithTriggers() const {return false;}

			};

			class NxPublicClass MoveToPosition : public TriggerFunction {

				public:
					MoveToPosition(float3 localPosition, NxReal force);
					void Stay(Trigger*, Actor*);

			};

		};
	};
	
}; // End of NxOgre namespace.

#endif
