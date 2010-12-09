/** \file    NxOgreWheelSet.h
 *  \brief   Header for the WheelSet class.
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


#ifndef __NXOGRE_WHEELSET_H__
#define __NXOGRE_WHEELSET_H__

#include "NxOgrePrerequisites.h"
#include "BetajaenCC.h"                // For: WheelSet stores Wheel pointers in the WheelSet
#include "NxOgreShapeWheel.h"          // For: WheelSet use Betajaen::SharedMap, which requires Wheel
#include "NxOgreMachine.h"             // For: WheelSet inherits from Machine

namespace NxOgre {
	
	//////////////////////////////////////////////////////////////////////////////////////
	
	class NxPublicClass WheelSet : public Machine {

		public:

			class ExtendedWheel {

				public:

					ExtendedWheel();
					~ExtendedWheel();

					/** \brief Set's the Wheels motor torque regardless of Wheel function.
					*/
					void  setMotorTorque(NxReal torque);

					/** \brief Set's the Wheels braking torque regardless of Wheel function.
					*/
					void  setBrakingTorque(NxReal torque);

					/** \brief Engine function to ALL Driving Wheels
					*/
					void  drive(NxReal torque);
					
					/** \brief Transmission function to ALL Braking Wheels
					*/
					void  brake(NxReal torque);

					/** \brief Transmission function to ALL Steering wheels.
					*/
					void  steer(NxRadian angle);
					
					Wheel* mWheel;

					void  set(bool drive, bool steer, bool brake);

					bool  mIsDriving;
					bool  mIsSteering;
					bool  mIsBraking;

			};

			enum SimpleWheelIdentifier {
				FrontLeft = 0,
				FL = 0,
				FrontRight = 1,
				FR = 1,
				RearLeft = 2,
				RL = 2,
				RearRight = 3,
				RR = 3
			};

			enum TransmissionLayout {
				TL_Front,
				TL_Rear,
				TL_Four
			};

			void setAs(TransmissionLayout);

			static WheelSet*  createFourWheelSet(
					NxReal radius,
					float3 forward_left,
					float3 backward_right,
					Actor*, 
					WheelParams
				);

			static WheelSet*  createFourWheelSet(
					NxReal radius,
					float3 forward_left,
					float3 backward_right,
					Actor*, 
					WheelParams,
					NodeRenderableParams
			);

			static WheelSet*  createFourWheelSet(
					NxReal radius,
					float3 forward_left,
					float3 backward_right,
					Actor*,
					WheelParams,
					NodeRenderableParams left_wheels,
					NodeRenderableParams right_wheels
			);

			void  simulate(const TimeStep&);

			Wheel* get(SimpleWheelIdentifier);
			Wheel* get(unsigned int);

			/** \brief Set Motor Torque to ALL wheels.
			*/
			void  setMotorTorque(NxReal);

			/** \brief Set Braking Torque to ALL Wheels.
			*/
			void  setBrakingTorque(NxReal);


			/** \brief Engine function to ALL Driving Wheels
			*/
			void  drive(NxReal torque);
			
			/** \brief Transmission function to ALL Braking Wheels
			*/
			void  brake(NxReal torque);

			/** \brief Transmission function to ALL Steering wheels.
			*/
			void  steer(NxRadian angle);

			WheelSet::ExtendedWheel*  createWheel(unsigned int identifier, NxReal radius, float3 position, Actor*, WheelParams);
			WheelSet::ExtendedWheel*  createWheel(unsigned int identifier, NxReal radius, float3 position, Actor*, WheelParams, NodeRenderableParams);

		protected:

			WheelSet();
			~WheelSet();

			Betajaen::SharedMap<unsigned int, ExtendedWheel>  mWheels;

	}; // End of WheelSet class.
	
	
}; // End of NxOgre namespace.

#endif
