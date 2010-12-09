/** \file    NxOgreShapeWheel.h
 *  \brief   Header for the Wheel classes.
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

#ifndef __NXOGRE_WHEEL_PRIMITIVES_H__
#define __NXOGRE_WHEEL_PRIMITIVES_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreShape.h"                // For: Primitives inherits Shape
#include "NxOgreRenderableSource.h"     // For: Wheel inherits NodeRenderableSource
#include "NxOgreMachine.h"              // For: Wheel inherits Machine
#include "NxOgreNodeRenderable.h"       // For: Wheel is rendered using a NodeRenderable

namespace NxOgre {
	
	/** \brief Params for the Wheel, based upon the ShapeParams.
	*/
	class NxPublicClass WheelParams : public ShapeParams {

		public:
			WheelParams() {
			               ShapeParams::setToDefault();
			               setToDefault();
			              }

			WheelParams(const char* p) {
			                            setToDefault();
			                            process(p);
			                           }

			WheelParams(const NxString& p) {
			                                setToDefault();
			                                process(p);
			                               }

			void setToDefault();
			void parse(Parameters);

			/** \brief Default Skin width.
			    \default 0.025
			    \example
			      C++     ->  mPhysXParams.mSkinWidth = 0.025;
			      String  ->  "skin-width: 0.3"
			 */
			NxReal mSkinWidth;

			/** \brief Maximum extension distance of suspension along shape's -Y axis.
			    \default 1.0
			    \example
			      C++     ->  mPhysXParams.mSuspensionTravel = 1.1;
			      String  ->  "suspension-travel: 1.1"
			 */
			NxReal mSuspensionTravel;

			/** \brief Suspension intended for car wheel suspension effects.
			    \default Spring = 0, TargetValue = 0 and Damper = 0
			    \note    TargetValue is restricted to [0,1]
			    \example
			      C++     ->  mPhysXParams.mSuspension.damper = 1.1;
			      C++     ->  mPhysXParams.mSuspension.spring = 1.1;
			      C++     ->  mPhysXParams.mSuspension.targetValue = 1.1;
			      String  ->  "suspension-damper: 1.1"
			      String  ->  "suspension-spring: 1"
			      String  ->  "suspension-target: 1" (OR)
			      String  ->  "suspension-target-value: 1"
			 */
			NxSpringDesc  mSuspension;

			/** \brief Cubic hermite spline coefficients describing the longitudal tire force curve.
			    \default NxTireFunctionDesc::setToDefault()
			    \example
			      C++     ->  mLongitudalTireForceFunction.asymptoteSlip = 1.1;
			      C++     ->  mLongitudalTireForceFunction.asymptoteValue = 1.1;
			      C++     ->  mLongitudalTireForceFunction.extremumSlip = 1.1;
			      C++     ->  mLongitudalTireForceFunction.extremumValue = 1.1;
			      C++     ->  mLongitudalTireForceFunction.stiffnessFactor = 1.1;
			      String  ->  "long-asymptote-slip: 1.1"
			      String  ->  "long-asymptote-value: 1.1"
			      String  ->  "long-extremum-slip: 1.1"
			      String  ->  "long-extremum-value: 1.1"
			      String  ->  "long-stiffness: 1.1"
			*/
			NxTireFunctionDesc mLongitudalTireForceFunction;

			/** \brief Cubic hermite spline coefficients describing the lateral tire force curve.
			    \default NxTireFunctionDesc::setToDefault()
			    \example
			      C++     ->  mLateralTireForceFunction.asymptoteSlip = 1.1;
			      C++     ->  mLateralTireForceFunction.asymptoteValue = 1.1;
			      C++     ->  mLateralTireForceFunction.extremumSlip = 1.1;
			      C++     ->  mLateralTireForceFunction.extremumValue = 1.1;
			      C++     ->  mLateralTireForceFunction.stiffnessFactor = 1.1;
			      String  ->  "lat-asymptote-slip: 1.1"
			      String  ->  "lat-asymptote-value: 1.1"
			      String  ->  "lat-extremum-slip: 1.1"
			      String  ->  "lat-extremum-value: 1.1"
			      String  ->  "lat-stiffness: 1.1"
			*/
			NxTireFunctionDesc mLateralTireForceFunction;

			/** \brief Inverse mass of the wheel.
			    \default 1.0
			    \example
			      C++     ->  mInverseWheelMass = 0.5;
			      String  ->  "inverse-wheel-mass: 0.5"
			*/
			NxReal  mInverseWheelMass;

			struct NxPublicClass WheelFlags : Flags {

				void toDefault() {
					mAxisContactNormal = false;
					mLateralSlipVelocity = false;
					mLongitudinalSlipVelocity = false;
					mUnscaledSpringBehaviour = false;
					mAxleSpeedOverride = false;
					mEmulateLegacyWheel = false;
					mClampedFriction = false;
				}

				void  fromNxU32(NxU32);
				NxU32 toNxU32() const;
				void  parse(const NxString&);

				/** \brief Determines whether the suspension axis or the ground contact normal
				           is used for the suspension constraint.
				    \default false
				    \see NX_WF_WHEEL_AXIS_CONTACT_NORMAL
				    \example
				      String variations => +axis-contact-normal, +acn
				*/
				bool   mAxisContactNormal;

				/** \brief Is set the lateral slip velocity is used as the input to the tire function, rather than the slip angle.
				*/
				bool   mLateralSlipVelocity;
	
				/** \brief If set, the longutudal slip velocity is used as the input to the tire function, rather than the slip ratio.  
				*/
				bool   mLongitudinalSlipVelocity;

				/** \brief If set, does not factor out the suspension travel and wheel radius from the spring force computation.
						   This is the legacy behavior from the raycast capsule approach.
				*/
				bool   mUnscaledSpringBehaviour;

				/** \brief If set, the axle speed is not computed by the simulation but is rather expected to be 
					       provided by the user every simulation step via Wheel::setAxleSpeed().
				*/
				bool   mAxleSpeedOverride;

				/** \brief If set, the NxWheelShape will emulate the legacy raycast capsule based wheel.
				*/
				bool   mEmulateLegacyWheel;

				/** \brief If set, the NxWheelShape will clamp the force in the friction constraints.
				*/
				bool   mClampedFriction;

			};

			WheelFlags  mFlags;

			/** \brief Initial sum engine torque on the wheel axle.
			    \default 0
			    \example
			      C++     ->  mPhysXParams.mMotorTorque = 500;
			      String  ->  "motor-torque: 500"
			 */
			NxReal   mMotorTorque;

			/** \brief Initial amount of torque applied to braking
			    \default 0.0
			    \note Must be non-negative [0, inf)
			    \example
			      C++     ->  mPhysXParams.mBrakeTorque = 1.1;
			      String  ->  "brake-torque: 1.1"
			 */
			NxReal   mBrakeTorque;


			/** \brief Steering angle based on the Y axis.
			    \default 0
			    \note Must between as a Radian (-Pi, Pi)
			    \example
			      C++     ->  mPhysXParams.BrakeTorque = 1.1;
			      String  ->  "brake-torque: 1.1"
			 */
			NxRadian mSteeringAngle;

			/** \brief Callback used to modify the wheel contact point before the wheel constraints are created.
			    \default NULL
				\example
				   C++   ->  mWheelContactCallback = new MyWheelContactCallback();
			*/
			WheelContactCallback* mWheelContactCallback;

	};

	/** \brief Wheel (NxWheelShape) is probably the most common shape used in NxOgre,
			   in most cases nearly everything can be represented by a cube or cubes.
	*/
	class NxPublicClass Wheel : public Shape, public Machine, public RenderableSource {

		public:

			/** \brief Wheel constructor, WITHOUT visualisation.
			*/
			Wheel(NxReal radius, const WheelParams&);

			/** \brief Wheel constructor, WITH visualisation
			*/
			Wheel(NxReal radius, const WheelParams&, const NodeRenderableParams&);

			/** \brief Cube destructor
			*/
			~Wheel();

			/** \brief Set the radius of the wheel.
			*/
			void setRadius(NxReal size);

			/** \brief Get's the radius of the wheel.
			*/
			NxReal getRadius() const;

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

			void setMotorTorque(NxReal torque);
			void setBrakeTorque(NxReal torque);
			void setSteerAngle(NxRadian steering);

			// NxWheelShape::checkOverlapAABB
			// NxWheelShape::checkOverlapCapsule
			// NxWheelShape::checkOverlapOBB
			// NxWheelShape::checkOverlapSphere
			// *NxWheelShape::getAxleSpeed
			// *NxWheelShape::getBrakeTorque
			// NxWheelShape::getCCDSkeleton
			// *NxWheelShape::getContact
			// NxWheelShape::getFlag
			// NxWheelShape::getGlobalOrientation
			// NxWheelShape::getGlobalPose
			// NxWheelShape::getGlobalPosition
			// NxWheelShape::getGroup
			// NxWheelShape::getGroupsMask
			// *NxWheelShape::getInverseWheelMass
			// NxWheelShape::getLocalOrientation
			// NxWheelShape::getLocalPose
			// NxWheelShape::getLocalPosition
			// *NxWheelShape::getLongitudalTireForceFunction
			// NxWheelShape::getMaterial
			// *NxWheelShape::getMotorTorque


		protected:

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();
			virtual void setNxShape(NxShape *shape);

			void simulate(const TimeStep&);
			Pose  getSourcePose(const TimeStep&) const;

			NxShortHashIdentifier	getType() const {return NxOgreClass_Shape;}
			NxString				getStringType() const {return "NxOgre-Shape-Wheel";}

		protected:

			NxWheelShapeDesc      mShapeDescription;
			NxWheelShape*         mWheel;
			WheelParams           mWheelParams;
			bool                  mHasRenderable;
			NodeRenderableParams  mRenderableParams;
			NodeRenderable*       mNodeRenderable;
			WheelContactCallback* mCallback;
			NxReal                mWheelRollAngle;
			Pose                  mWheelPose;

	};

} // End of namespace

#endif