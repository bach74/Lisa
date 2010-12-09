/** \file    NxOgreWheelContactCallback.h
 *  \brief   Header for the WheelContactCallback classes.
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

#ifndef __NXOGRE_WHEELCONTACT_CALLBACK_H__
#define __NXOGRE_WHEELCONTACT_CALLBACK_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	/** \brief This callback is called once for each wheel and sub step before the wheel constraints are setup
			and fed to the SDK. The values passed in the parameters can be adjusted to affect the vehicle simulation.
			The most interesting values are contactPosition, contactPoint, and contactNormal. The contactPosition value
			specifies how far on the travel distance the contactPoint was found. If you want to simulate a bumpy road,
			then this is the main parameter to change. It is also good to adjust the contactPoint variable, so that the
			wheel forces are applied in the correct position. 
	*/
	class NxPublicClass WheelContactCallback : public NxUserWheelContactModify {
		
		public:
			
			/** \brief Wheel has contact with a shape.
			*/
			virtual bool WheelContact(Wheel*, NxVec3& point, NxVec3& normal, NxReal& position, NxReal& force, Shape* other, NxMaterialIndex& otherShapeMaterialIndex, NxU32 otherShapeFeatureIndex) {}

		protected:

			
			/**
			\param wheelShape The WheelShape that is being processed.
			\param contactPoint The contact point (in world coordinates) that is being used for the wheel.
			\param contactNormal The normal of the geometry at the contact point.
			\param contactPosition The distance on the spring travel distance where the wheel would end up if it was resting on the contact point.
			\param normalForce The normal force on the wheel from the last simulation step.
			\param otherShape The shape with which the wheel is in contact.
			\param otherShapeMaterialIndex The material on the other shape in the position where the wheel is in contact. Currently has no effect on the simulation.
			\param otherShapeFeatureIndex The feature on the other shape in the position where the wheel is in contact.

			return Return true to keep the contact (with the possibly edited values) or false to drop the contact.
			*/
			bool onWheelContact(NxWheelShape* wheelShape, NxVec3& contactPoint, NxVec3& contactNormal, NxReal& contactPosition, NxReal& normalForce, NxShape* otherShape, NxMaterialIndex& otherShapeMaterialIndex, NxU32 otherShapeFeatureIndex);

			virtual ~ContactCallback() {}
			GarbageCollectionPolicy* mDeletionPolicy;


	};

	template <class TargetClass>
	class WheelContactPtrCallback : public WheelContactCallback {

		protected:

			typedef void (TargetClass::*ContactFunctionPtr)(Wheel*, NxVec3& point, NxVec3& normal, NxReal& position, NxReal& force, Shape* other);

			template <class TargetClass>
			explicit WheelContactPtrCallback(TargetClass* _instance, ContactFunctionPtr _function_ptr) {
				mDeletionPolicy = GC_Delete;
				mClass = _instance;
				mFunction = _function_ptr;
			}

			~WheelContactPtrCallback() {}

			bool WheelContact(Wheel*, NxVec3& point, NxVec3& normal, NxReal& position, NxReal& force, Shape* other);

			TargetClass* mClass;
			ContactFunctionPtr mFunction;

	};


}; // End of NxOgre namespace.

#endif
