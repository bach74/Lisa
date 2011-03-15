/** \file    NxOgreShapeWheel.cpp
 *  \see     NxOgreShapeWheel.h
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

#include "NxOgreStable.h"
#include "NxOgreShapeWheel.h"
#include "NxOgreShape.h"				// For: ShapeParams
#include "NxOgreRenderableSource.h"     // For: Wheel inherits RenderableSource.
#include "NxOgreNodeRenderable.h"       // For: Wheel uses NodeRenderable.
#include "NxOgreActor.h"
#include "NxOgreHelpers.h"
#include "NxOgreVoidPointer.h"
#include "NxOgreScene.h"                // For: Need Access to SceneRenderer
#include "NxOgreSceneRenderer.h"        // For: Creating a node Renderable

namespace NxOgre {


/////////////////////////////////////////////////////////////

void WheelParams::setToDefault() {

	ShapeParams::setToDefault();

	mSuspensionTravel = 1.0f;
	mInverseWheelMass = 1.0f;
	mFlags.toDefault();
	mMotorTorque = 0.0f;
	mBrakeTorque = 0.0f;
	mSteeringAngle = 0.0f;
	mSuspension.setToDefault();
	mLongitudalTireForceFunction.setToDefault();
	mLateralTireForceFunction.setToDefault();
	mWheelContactCallback = NULL;

}

/////////////////////////////////////////////////////////////

void WheelParams::parse(Parameters params) {

	setToDefault();

	ShapeParams::parse(params);

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {
		if (Set("suspension-travel", parameter, mSuspensionTravel)) continue;
		if (Set("inverse-wheel-mass", parameter, mInverseWheelMass)) continue;

		if (is("flags", parameter)) {
			mFlags.parse(parameter->j);
			continue;
		}

		if (Set("motor-torque", parameter, mMotorTorque)) continue;
		if (Set("brake-torque", parameter, mBrakeTorque)) continue;
		if (Set("steering-angle", parameter, mSteeringAngle)) continue;
		if (Set("suspension-damper", parameter, mSuspension.damper)) continue;
		if (Set("suspension-spring", parameter, mSuspension.spring)) continue;
		if (Set("suspension-target", parameter, mSuspension.targetValue)) continue;
		if (Set("suspension-target-value", parameter, mSuspension.targetValue)) continue;

	}

}

/////////////////////////////////////////////////////////////

void  WheelParams::WheelFlags::fromNxU32(NxU32) {
	/// \todo
}

/////////////////////////////////////////////////////////////

NxU32 WheelParams::WheelFlags::toNxU32() const {
	/// \todo
	return 0;
}

/////////////////////////////////////////////////////////////

void  WheelParams::WheelFlags::parse(const NxString&) {
	/// \todo
}

/////////////////////////////////////////////////////////////

Wheel::Wheel(NxReal radius, const WheelParams& params)
: Shape(), Machine(), mWheelParams(params), mWheel(0), mWheelRollAngle(0)
{
	// Can't use normal Shape constructor. It seems C++ can be very anal.
	Shape::paramsToDescription(&mShapeDescription, &mWheelParams);

	mHasRenderable = false;
	mShapeDescription.radius = radius;
	mShapeDescription.brakeTorque = params.mBrakeTorque;
	mShapeDescription.inverseWheelMass = params.mInverseWheelMass;
	mShapeDescription.lateralTireForceFunction = params.mLateralTireForceFunction;
	mShapeDescription.longitudalTireForceFunction = params.mLongitudalTireForceFunction;
	mShapeDescription.motorTorque = params.mMotorTorque;
	mShapeDescription.steerAngle = params.mSteeringAngle;
	mShapeDescription.suspension = params.mSuspension;
	mShapeDescription.suspensionTravel = params.mSuspensionTravel;
	mShapeDescription.wheelFlags = params.mFlags.toNxU32();

	mCallback = params.mWheelContactCallback;

}

/////////////////////////////////////////////////////////////

/** \brief Wheel constructor, WITH visualisation
*/
Wheel::Wheel(NxReal radius, const WheelParams& params, const NodeRenderableParams& nrp)
: Shape(), Machine(), mWheelParams(params), mWheel(0), mWheelRollAngle(0)
{

	// Can't use normal Shape constructor. It seems C++ can be very anal.
	Shape::paramsToDescription(&mShapeDescription, &mWheelParams);

	mShapeDescription.radius = radius;
	mShapeDescription.brakeTorque = params.mBrakeTorque;
	mShapeDescription.inverseWheelMass = params.mInverseWheelMass;
	mShapeDescription.lateralTireForceFunction = params.mLateralTireForceFunction;
	mShapeDescription.longitudalTireForceFunction = params.mLongitudalTireForceFunction;
	mShapeDescription.motorTorque = params.mMotorTorque;
	mShapeDescription.steerAngle = params.mSteeringAngle;
	mShapeDescription.suspension = params.mSuspension;
	mShapeDescription.suspensionTravel = params.mSuspensionTravel;
	mShapeDescription.wheelFlags = params.mFlags.toNxU32();

	mCallback = params.mWheelContactCallback;

	setRenderMode(RM_Interpolate);

	mHasRenderable = true;
	mRenderableParams = nrp;

}

/////////////////////////////////////////////////////////////

Wheel::~Wheel() {

	// Shape does not get released, as most of the time the destruction of
	// this shape, shortly results in the shape's actor.
	if (mHasRenderable) {
		VoidPointer* vp = static_cast<VoidPointer*>(mActor->userData);
		Actor* actor = vp->toActor();
		actor->getScene()->getSceneRenderer()->unregisterSource(this);
		delete mRenderable;
		mRenderable = 0;
	}

}

/////////////////////////////////////////////////////////////

void Wheel::createShape(NxActor* actor, NxShapeIndex index, Scene* scene)
{

	extendedParamsToDescription(scene, mWheelParams, &mShapeDescription);

	mShapeIndex = index;
	mActor = actor;
	
	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;
	NxShape* shape = actor->createShape(mShapeDescription);
	setNxShape(shape);


}

/////////////////////////////////////////////////////////////

void Wheel::createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex index, Scene* scene) {

	extendedParamsToDescription(scene, mWheelParams, &mShapeDescription);

	mVoidPointer = new VoidPointer(this, NxOgreClass_Shape);
	mShapeDescription.userData = mVoidPointer;

	shapes.push_back(&mShapeDescription);
	mShapeIndex = index;
/*
	if (mHasRenderable) {
		mRenderable = scene->getSceneRenderer()->createNodeRenderable(mRenderableParams);
		mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
		mVoidPointer->RenderPtr = this;
		scene->getSceneRenderer()->registerSource(this);
	}
*/

}

/////////////////////////////////////////////////////////////

void Wheel::releaseShape() {
	mActor->releaseShape(*mNxShape);
}

/////////////////////////////////////////////////////////////

void Wheel::setRadius(NxReal radius) {

	if (mWheel) {
		mWheel->setRadius(radius);
	}
	else {
		mShapeDescription.radius = radius;
	}

}

/////////////////////////////////////////////////////////////

NxReal Wheel::getRadius() const {

	if (mWheel) {
		return mWheel->getRadius();
	}
	else {
		return mShapeDescription.radius;
	}
}

/////////////////////////////////////////////////////////////

void Wheel::setNxShape(NxShape *shape) {

	if (shape == NULL) {
		NxThrow(NxString("NULL or invalid shape was attempted to be assigned to this shape '" + getShapeAsString() + "'.").c_str());
	}

	mNxShape = shape;
	mWheel = static_cast<NxWheelShape*>(shape);
	mActor = &shape->getActor();

	if (mHasRenderable) {
		VoidPointer* vp = static_cast<VoidPointer*>(mActor->userData);
		Actor* actor = vp->toActor();
		mRenderable = actor->getScene()->getSceneRenderer()->createNodeRenderable(mRenderableParams);
		mNodeRenderable = static_cast<NodeRenderable*>(mRenderable);
		mVoidPointer->RenderPtr = this;
		actor->getScene()->getSceneRenderer()->registerSource(this);
		registerMachine(actor->getScene());
	}

}

/////////////////////////////////////////////////////////////

void Wheel::simulate(const TimeStep& ts) {

	mWheelRollAngle += mWheel->getAxleSpeed() * ts.Delta;
	
	while (mWheelRollAngle > NxTwoPi)	//normally just 1x
		mWheelRollAngle -= NxTwoPi;
	while (mWheelRollAngle < -NxTwoPi)	//normally just 1x
		mWheelRollAngle += NxTwoPi;

	mWheelPose.m = mWheel->getGlobalPose();

#if (NX_SDK_VERSION_MAJOR >= 2) && (NX_SDK_VERSION_MINOR >= 7)

	NxWheelContactData wcd;
	wcd.contactPosition = 0;

	NxShape* s = mWheel->getContact(wcd);

	NxReal  stravel = mWheel->getSuspensionTravel(), radius = mWheel->getRadius();

	if(s) {
		mWheelPose.m.t += mWheel->getLocalOrientation() * mWheelPose.m.M * NxVec3( 0.0, radius - wcd.contactPosition, 0.0);
	} else {
		mWheelPose.m.t += mWheelPose.m.M * NxVec3( 0.0, -stravel , 0.0 );
	}

	NxMat33 Heading, Pitch;
	Heading.rotY( mWheel->getSteerAngle() );
	Pitch.rotX( mWheelRollAngle );

	mWheelPose.m.M = mWheelPose.m.M * Heading * Pitch; 	

#else
   
	NxWheelContactData wcd;
    NxShape* s = mWheel->getContact(wcd);	
	NxReal  stravel = mWheel->getSuspensionTravel(), radius = mWheel->getRadius();

    //have ground contact?
	if( s && wcd.contactPosition <=  (stravel + radius) ) {
		mWheelPose.m.t = NxVec3( mWheelPose.m.t.x, wcd.contactPoint.y + radius, mWheelPose.m.t.z );
    }
	else {
		mWheelPose.m.t = NxVec3( mWheelPose.m.t.x, mWheelPose.m.t.y - stravel, mWheelPose.m.t.z );
	}

    NxMat33 rot, axisRot, rollRot;
    rot.rotY( mWheel->getSteerAngle() );
    axisRot.rotY(0);
    rollRot.rotX(mWheelRollAngle);
    mWheelPose.m.M = rot * mWheelPose.m.M * axisRot * rollRot;

#endif

}

/////////////////////////////////////////////////////////////

Pose Wheel::getSourcePose(const TimeStep& ts) const {
	return mWheelPose;
}

/////////////////////////////////////////////////////////////

void Wheel::setMotorTorque(NxReal torque) {
	mWheel->setMotorTorque(torque);
}

/////////////////////////////////////////////////////////////

void Wheel::setBrakeTorque(NxReal torque) {
	mWheel->setBrakeTorque(torque);
}

/////////////////////////////////////////////////////////////

void Wheel::setSteerAngle(NxRadian steering) {
	mWheel->setSteerAngle(steering);
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.

