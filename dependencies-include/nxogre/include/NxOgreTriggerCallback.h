/** \file    NxOgreTriggerCallback.h
 *  \brief   Header for the TriggerContactCallback and TriggerContactPtrCallback
 *           classes.
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

#ifndef __NXOGRE_TRIGGERCALLBACK_H__
#define __NXOGRE_TRIGGERCALLBACK_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreSimpleActor.h"

namespace NxOgre {

	class NxPublicClass TriggerContactCallback {
		
		friend class SceneTriggerController;
		friend class Trigger;

		protected:

				virtual ~TriggerContactCallback()                          {}

				virtual void Enter(Trigger*, Actor*)                       {}
				virtual void Enter(Trigger*, CharacterSystem::Character*)  {}
				virtual void Enter(Shape*, Actor*)                         {}
				virtual void Enter(Shape*, CharacterSystem::Character*)    {}

				virtual void Stay(Trigger*, Actor*)                        {}
				virtual void Stay(Trigger*, CharacterSystem::Character*)   {}
				virtual void Stay(Shape*, Actor*)                          {}
				virtual void Stay(Shape*, CharacterSystem::Character*)     {}

				virtual void Exit(Trigger*, Actor*)                        {}
				virtual void Exit(Trigger*, CharacterSystem::Character*)   {}
				virtual void Exit(Shape*, Actor*)                          {}
				virtual void Exit(Shape*, CharacterSystem::Character*)     {}

				/** \brief Should this Callback be deleted when the trigger using it is destroyed.
					\note As the a the TriggerContactCallback has no constructor the behaviour
					      of this is <em>random</em>. Make sure your your inherited TriggerContactCallback
						  class sets the value of this in it's own constructor.
				*/
				GarbageCollectionPolicy mDeletionPolicy;
	};

	/////////////////////////////////////////////////////////

	template <class TargetClass>
	class TriggerContactPtrCallback : public TriggerContactCallback {

		public:

			typedef void (TargetClass::*TriggerActorPtr)(Trigger*, Actor*);
			typedef void (TargetClass::*TriggerCharacterPtr)(Trigger*, CharacterSystem::Character*);
			typedef void (TargetClass::*ShapeActorPtr)(Shape*, Actor*);
			typedef void (TargetClass::*ShapeCharacterPtr)(Shape*, CharacterSystem::Character*);

			template <class TargetClass>
			explicit TriggerContactPtrCallback()
			{     empty();
			      mDeletionPolicy = GC_Delete;
			}

			template <class TargetClass>
			explicit TriggerContactPtrCallback(TargetClass* target_class)
			{     empty();
			      mDeletionPolicy = GC_Delete;
			      mClass = target_class;
			}


			template <class TargetClass>
			explicit TriggerContactPtrCallback(TargetClass* target_class, TriggerActorPtr stay)
			{     empty();
			      mDeletionPolicy = GC_Delete;
			      mClass = target_class;
			      Stay_TriggerActorPtr = stay;
			}

			template <class TargetClass>
			explicit TriggerContactPtrCallback(TargetClass* target_class, TriggerActorPtr enter, TriggerActorPtr exit)
			{     empty(); 
			      mDeletionPolicy = GC_Delete;
			      mClass = target_class;
			      Enter_TriggerActorPtr = enter;
			      ExiNxOgreClass_TriggerActorPtr = exit;
			}

			template <class TargetClass>
			explicit TriggerContactPtrCallback(TargetClass* target_class, TriggerActorPtr enter, TriggerActorPtr stay, TriggerActorPtr exit)
			{     empty(); 
			      mDeletionPolicy = GC_Delete;
			      mClass = target_class;
			      Enter_TriggerActorPtr = enter;
			      Stay_TriggerActorPtr = stay;
			      ExiNxOgreClass_TriggerActorPtr = exit;
			}


			void NxTemplateFunction empty() {
				mClass = 0;
				Enter_TriggerActorPtr = 0;
				Enter_TriggerCharacterPtr = 0;
				Enter_ShapeActorPtr = 0;
				Enter_ShapeCharacterPtr = 0;
				Stay_TriggerActorPtr = 0;
				Stay_TriggerCharacterPtr = 0;
				Stay_ShapeActorPtr = 0;
				Stay_ShapeCharacterPtr = 0;
				ExiNxOgreClass_TriggerActorPtr = 0;
				ExiNxOgreClass_TriggerCharacterPtr = 0;
				Exit_ShapeActorPtr = 0;
				Exit_ShapeCharacterPtr = 0;
			}

			void NxTemplateFunction Enter(Trigger* t, Actor* a) {
				if (Enter_TriggerActorPtr)
					(mClass->*Enter_TriggerActorPtr)(t, a);
			}

			void NxTemplateFunction Enter(Trigger* t, CharacterSystem::Character* c) {
				if (Enter_TriggerCharacterPtr)
					(mClass->*Enter_TriggerCharacterPtr)(t, c);
			}

			void NxTemplateFunction Enter(Shape* s, Actor* a) {
				if (Enter_ShapeActorPtr)
					(mClass->*Enter_ShapeActorPtr)(s, a);
			}
				
			void NxTemplateFunction Enter(Shape* s, CharacterSystem::Character* c) {
				if (Enter_ShapeCharacterPtr)
					(mClass->*Enter_ShapeCharacterPtr)(s, c);
			}

			void NxTemplateFunction Stay(Trigger* t, Actor* a) {
				if (Stay_TriggerActorPtr)
					(mClass->*Stay_TriggerActorPtr)(t, a);
			}

			void NxTemplateFunction Stay(Trigger* t, CharacterSystem::Character* c) {
				if (Stay_TriggerCharacterPtr)
					(mClass->*Stay_TriggerCharacterPtr)(t, c);
			}

			void NxTemplateFunction Stay(Shape* s, Actor* a) {
				if (Stay_ShapeActorPtr)
					(mClass->*Stay_ShapeActorPtr)(s, a);
			}

			void NxTemplateFunction Stay(Shape* s, CharacterSystem::Character* c) {
				if (Stay_ShapeCharacterPtr)
					(mClass->*Stay_ShapeCharacterPtr)(s, c);
			}

			void NxTemplateFunction Exit(Trigger* t, Actor* a) {
				if (ExiNxOgreClass_TriggerActorPtr)
					(mClass->*ExiNxOgreClass_TriggerActorPtr)(t, a);
			}

			void Exit(Trigger* t, CharacterSystem::Character* c) {
				if (ExiNxOgreClass_TriggerCharacterPtr)
					(mClass->*ExiNxOgreClass_TriggerCharacterPtr)(t, c);
			}

			void NxTemplateFunction Exit(Shape* s, Actor* a) {
				if (Exit_ShapeActorPtr)
					(mClass->*Exit_ShapeActorPtr)(s, a);
			}

			void Exit(Shape* s, CharacterSystem::Character* c) {
				if (Exit_ShapeCharacterPtr)
					(mClass->*Exit_ShapeCharacterPtr)(s, c);
			}

		protected:

			TargetClass* mClass;

			TriggerActorPtr            Enter_TriggerActorPtr;
			TriggerCharacterPtr        Enter_TriggerCharacterPtr;
			ShapeActorPtr              Enter_ShapeActorPtr;
			ShapeCharacterPtr          Enter_ShapeCharacterPtr;
			TriggerActorPtr            Stay_TriggerActorPtr;
			TriggerCharacterPtr        Stay_TriggerCharacterPtr;
			ShapeActorPtr              Stay_ShapeActorPtr;
			ShapeCharacterPtr          Stay_ShapeCharacterPtr;
			TriggerActorPtr            ExiNxOgreClass_TriggerActorPtr;
			TriggerCharacterPtr        ExiNxOgreClass_TriggerCharacterPtr;
			ShapeActorPtr              Exit_ShapeActorPtr;
			ShapeCharacterPtr          Exit_ShapeCharacterPtr;

	};
	
}; // End of NxOgre namespace.

#endif
