/** \file    NxOgreContactCallback.h
 *  \brief   Header for the ContactCallback classes.
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

#ifndef __NXOGRE_CONTACT_CALLBACK_H__
#define __NXOGRE_CONTACT_CALLBACK_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	/** \brief ContactCallback where a class inherits this class, which is then called.
		\note  Your class needs to specify a deletion policy (ContactCallback::mDeletionPolicy)
		       otherwise on the removal of the contact from the actor, the destruction of this
		       class is <em>random</em>.
		\example
			<code>
				class myClass : public ContactCallback {

					myClass() {
						mDeletionPolicy = GC_Never_Delete;
					}

					void Contact(Actor*, Actor*, NxContactPair&, NxU32 ContactFlags) {
						
					}
				};

				mMyClass = new myClass();

				ContactCallbackController* controller = mScene->getContactCallbackController();
				controller->addCallback(myActor, myActor2, mMyClass);
			</code>

	*/
	class NxPublicClass ContactCallback {
		public:
			virtual void Contact(Actor*, Actor*, NxContactPair&, NxU32 ContactFlags) {}
			virtual ~ContactCallback() {}
			GarbageCollectionPolicy* mDeletionPolicy;
	};

	/** \brief ContactPtrCallback which calls a function in any class. Use ContactCallbackController
			   for the creation and destruction of this class.
		\example
			<code>
				class myClass {
					void hit(Actor*, Actor*, NxContactPair&, NxU32 ContactFlags);
				};

				mMyClass = new myClass();

				ContactCallbackController* controller = mScene->getContactCallbackController();
				controller->addCallback<myClass>(myActor, myActor2, mMyClass, &myClass::hit); 
			</code>
	*/
	template <class TargetClass>
	class ContactPtrCallback : public ContactCallback {
		
		friend class ActorContactCallback;
		friend class ContactCallbackController;

		protected:
			typedef void (TargetClass::*ContactFunctionPtr)(Actor*, Actor*, NxContactPair, NxU32 ContactFlags);
			
			template <class TargetClass>
			explicit ContactPtrCallback(TargetClass* _instance, ContactFunctionPtr _function_ptr) {
				mDeletionPolicy = GC_Delete;
				mClass = _instance;
				mFunction = _function_ptr;
			}

			virtual void Contact(Actor*, Actor*, NxContactPair&, NxU32 ContactFlags) {}
			virtual ~ContactPtrCallback() {}
			
			
			TargetClass* mClass;
			ContactFunctionPtr mFunction;
	};

	/** \brief A list of contact callbacks for a specific Actor.
	*/
	class ActorContactCallback {
		public:
			void Contact(Actor*, Actor*, NxContactPair&, NxU32 ContactFlags);
			Betajaen::SharedList<ContactCallback> mContacts;
	};


}; // End of NxOgre namespace.

#endif
