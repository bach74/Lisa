/** \file    NxOgreTrigger.h
 *  \brief   Header for the Trigger and TriggerCallback classes.
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

#ifndef __NXOGRE_TRIGGER_H__
#define __NXOGRE_TRIGGER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreSimpleActor.h"

namespace NxOgre {

	/** \brief
	*/
	class NxPublicClass Trigger : public SimpleActor {

		friend class SceneTriggerController;
		friend class VoidPointer;

		public:

			Trigger(SimpleShape*, TriggerContactCallback*, Scene*);
			~Trigger();

			/** \brief Get the callback associated with this trigger
			*/
			TriggerContactCallback* getCallback()  {
			                                        return mCallback;
			                                       }

			void addSimpleShape(SimpleShape*);


			Actors getActors();

		protected:
			TriggerContactCallback*  mCallback;
			VoidPointer*             mUserData;
	};

#if 0
	/** \brief
	*/
	class NxPublicClass SimpleTrigger : public Trigger {

		SimpleTrigger(SimpleShape*, TriggerContactCallback*, Scene*);
		~SimpleTrigger();

	protected:

		void __no_gravity_e_ta(Trigger*, Actor*);
		void __no_gravity_e_ta(Trigger*, CharacterSystem::Character*);
		void __no_gravity_e_sa(Shape*, Actor*);
		void __no_gravity_e_sc(Shape*, Character*);
		void __no_gravity_x_ta(Trigger*, Actor*);
		void __no_gravity_x_ta(Trigger*, CharacterSystem::Character*);
		void __no_gravity_x_sa(Shape*, Actor*);
		void __no_gravity_x_sc(Shape*, Character*);
		void __no_gravity_i_ta(Trigger*, Actor*);
		void __no_gravity_i_ta(Trigger*, CharacterSystem::Character*);
		void __no_gravity_i_sa(Shape*, Actor*);
		void __no_gravity_i_sc(Shape*, Character*);

		void __add_gravity_e_ta(Trigger*, Actor*);
		void __add_gravity_e_ta(Trigger*, CharacterSystem::Character*);
		void __add_gravity_e_sa(Shape*, Actor*);
		void __add_gravity_e_sc(Shape*, Character*);
		void __add_gravity_x_ta(Trigger*, Actor*);
		void __add_gravity_x_ta(Trigger*, CharacterSystem::Character*);
		void __add_gravity_x_sa(Shape*, Actor*);
		void __add_gravity_x_sc(Shape*, Character*);
		void __add_gravity_i_ta(Trigger*, Actor*);
		void __add_gravity_i_ta(Trigger*, CharacterSystem::Character*);
		void __add_gravity_i_sa(Shape*, Actor*);
		void __add_gravity_i_sc(Shape*, Character*);

		void __replace_gravity_e_ta(Trigger*, Actor*);
		void __replace_gravity_e_ta(Trigger*, CharacterSystem::Character*);
		void __replace_gravity_e_sa(Shape*, Actor*);
		void __replace_gravity_e_sc(Shape*, Character*);
		void __replace_gravity_x_ta(Trigger*, Actor*);
		void __replace_gravity_x_ta(Trigger*, CharacterSystem::Character*);
		void __replace_gravity_x_sa(Shape*, Actor*);
		void __replace_gravity_x_sc(Shape*, Character*);
		void __replace_gravity_i_ta(Trigger*, Actor*);
		void __replace_gravity_i_ta(Trigger*, CharacterSystem::Character*);
		void __replace_gravity_i_sa(Shape*, Actor*);
		void __replace_gravity_i_sc(Shape*, Character*);

	};
#endif

}; // End of NxOgre namespace.

#endif
