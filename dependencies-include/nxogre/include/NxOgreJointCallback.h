/** \file    NxOgreJointCallback.h
 *  \brief   Header for the JointCallback class.
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

#ifndef __NXOGRE_JOINT_CALLBACK_H__
#define __NXOGRE_JOINT_CALLBACK_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

namespace NxOgre {

	class NxPublicClass JointCallback {
		
		public:

			//////////////////////////////////////////////////////////////

			class JointBreakCallback {

				public:

					virtual void onBreak(Joint*, NxReal, Actor*, Actor*) {}

			};

			//////////////////////////////////////////////////////////////

			template <typename T>
			class JointBreakMethodCallback : public JointBreakCallback {
			
				public:

					JointBreakMethodCallback(
					T* v,
					void (T::*BreakCallback)(Joint*, NxReal, Actor*, Actor*))
					: mInstance(v), mMethod(BreakCallback)
					{}

					/////////////////////////////////////////////////////

					void onBreak(Joint* j, NxReal i, Actor* a, Actor* b) {
						(mInstance->*mMethod)(j,i,a,b);
					}

					/////////////////////////////////////////////////////

					T* mInstance;
					void (T::*mMethod)(Joint, NxReal, Actor*, Actor*);
			
			};

			//////////////////////////////////////////////////////////

			template <typename T> explicit
			JointCallback(T* v,
			void (T::*JointBreakMethod)(Joint*, NxReal, Actor*, Actor*))
			: mCallback(new JointBreakMethodCallback<T>(v, JointBreakMethod)) {}

			void onBreak(Joint* j, NxReal impulse, Actor* a, Actor* b) {
				mCallback->onBreak(j,impulse, a,b);
			}

			//////////////////////////////////////////////////////////

			JointBreakCallback*	mCallback;

	};


};

#endif
