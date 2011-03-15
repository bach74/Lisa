/** \file    NxOgreWheelSet.cpp
 *  \see     NxOgreWheelSet.h
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
#include "NxOgreWheelSet.h"
#include "NxOgreShapeWheel.h"
#include "NxOgreScene.h"
#include "BetajaenCC.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

WheelSet* WheelSet::createFourWheelSet(
	NxReal radius,
	float3 forward_left, 
	float3 backward_right,
	NxOgre::Actor* actor,
	WheelParams wp
) {

	WheelSet* set = NxNew(WheelSet)();

	ExtendedWheel* w0 = set->createWheel(FrontLeft, radius, forward_left, actor, wp);
	forward_left.i    = backward_right.i;
	ExtendedWheel* w1 = set->createWheel(FrontRight, radius, forward_left, actor, wp);

	ExtendedWheel* w3 = set->createWheel(RearRight, radius, backward_right, actor, wp);
	backward_right.i  = forward_left.i;
	ExtendedWheel* w2 = set->createWheel(RearLeft, radius, backward_right, actor, wp);

	set->registerMachine(actor->getScene());

	return set;

}

/////////////////////////////////////////////////////////////

WheelSet* WheelSet::createFourWheelSet(
		NxReal radius,
		float3 forward_left,
		float3 backward_right,
		Actor* actor, 
		WheelParams wp,
		NodeRenderableParams nrp
) {

	WheelSet* set = NxNew(WheelSet)();

	ExtendedWheel* w0 = set->createWheel(FrontLeft, radius, forward_left, actor, wp, nrp);
	forward_left.i    = backward_right.i;
	ExtendedWheel* w1 = set->createWheel(FrontRight, radius, forward_left, actor, wp, nrp);
	ExtendedWheel* w3 = set->createWheel(RearRight, radius, backward_right, actor, wp, nrp);
	backward_right.i  = -backward_right.i;
	ExtendedWheel* w2 = set->createWheel(RearLeft, radius, backward_right, actor, wp, nrp);

	set->registerMachine(actor->getScene());

	return set;

}

WheelSet* WheelSet::createFourWheelSet(
	NxReal radius,
	float3 forward_left,
	float3 backward_right,
	Actor* actor,
	WheelParams wp,
	NodeRenderableParams lnrp,
	NodeRenderableParams rnrp
) {

	WheelSet* set = NxNew(WheelSet)();

	ExtendedWheel* w0 = set->createWheel(FrontLeft, radius, forward_left, actor, wp, lnrp);
	forward_left.i    = backward_right.i;
	ExtendedWheel* w1 = set->createWheel(FrontRight, radius, forward_left, actor, wp, rnrp);

	ExtendedWheel* w3 = set->createWheel(RearRight, radius, backward_right, actor, wp, rnrp);
	backward_right.i  = forward_left.i;
	ExtendedWheel* w2 = set->createWheel(RearLeft, radius, backward_right, actor, wp, lnrp);

	set->registerMachine(actor->getScene());

	return set;
}

/////////////////////////////////////////////////////////

WheelSet::WheelSet() {
}

/////////////////////////////////////////////////////////

WheelSet::~WheelSet() {
	// Remove the Wheels from the WheelSet, Actor "owns" the classes and should destroy them.
	mWheels.RemoveAll();
}

/////////////////////////////////////////////////////////

void WheelSet::simulate(const TimeStep&) {

}

/////////////////////////////////////////////////////////

Wheel* WheelSet::get(SimpleWheelIdentifier identifier) {
	return mWheels.Get(identifier)->mWheel;
}

/////////////////////////////////////////////////////////////

Wheel* WheelSet::get(unsigned int identifier) {
	return mWheels.Get(identifier)->mWheel;
}

/////////////////////////////////////////////////////////////

void WheelSet::setMotorTorque(NxReal torque) {
	mWheels.Each<NxReal>(&WheelSet::ExtendedWheel::setMotorTorque, torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::drive(NxReal torque) {
	mWheels.Each<NxReal>(&WheelSet::ExtendedWheel::drive, torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::brake(NxReal torque) {
	mWheels.Each<NxReal>(&WheelSet::ExtendedWheel::brake, torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::steer(NxRadian angle) {
	mWheels.Each<NxReal>(&WheelSet::ExtendedWheel::steer, angle);
}

/////////////////////////////////////////////////////////////

WheelSet::ExtendedWheel*  WheelSet::createWheel(unsigned int identifier, NxReal radius, float3 position, Actor* actor, WheelParams wp) {
	ExtendedWheel* exWheel = NxNew(ExtendedWheel)();
	wp.mLocalPose.t.set(position.i, position.j, position.k);
	exWheel->mWheel = NxNew(Wheel)(radius, wp);
	mWheels.Insert(identifier, exWheel);
	actor->addShape(exWheel->mWheel);
	return exWheel;
}

/////////////////////////////////////////////////////////////

WheelSet::ExtendedWheel*  WheelSet::createWheel(unsigned int identifier, NxReal radius, float3 position, Actor* actor, WheelParams wp, NodeRenderableParams nrp) {
	ExtendedWheel* exWheel = NxNew(ExtendedWheel)();
	wp.mLocalPose.t.set(position.i, position.j, position.k);
	exWheel->mWheel = NxNew(Wheel)(radius, wp, nrp);
	mWheels.Insert(identifier, exWheel);
	actor->addShape(exWheel->mWheel);
	return exWheel;
}

/////////////////////////////////////////////////////////////

WheelSet::ExtendedWheel::ExtendedWheel() 
: mWheel(0), mIsDriving(false), mIsBraking(false), mIsSteering(false)
{
}

/////////////////////////////////////////////////////////////

WheelSet::ExtendedWheel::~ExtendedWheel()
{
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::setMotorTorque(NxReal torque) {
	mWheel->setMotorTorque(torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::setBrakingTorque(NxReal torque) {
	mWheel->setBrakeTorque(torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::drive(NxReal torque) {
	if (mIsDriving)
		mWheel->setMotorTorque(torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::brake(NxReal torque) {
	if (mIsBraking)
		mWheel->setBrakeTorque(torque);
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::steer(NxRadian angle) {
	if (mIsSteering)
		mWheel->setSteerAngle(angle);
}

/////////////////////////////////////////////////////////////

void WheelSet::ExtendedWheel::set(bool drive, bool steer, bool brake) {
	mIsDriving = drive;
	mIsSteering = steer;
	mIsBraking = brake;
}

/////////////////////////////////////////////////////////////

void WheelSet::setAs(TransmissionLayout tl) {
	switch(tl) {
		case TL_Front:
			mWheels.Get(FL)->set(true, true, true);
			mWheels.Get(FR)->set(true, true, true);
			mWheels.Get(RL)->set(false, false, true);
			mWheels.Get(RR)->set(false, false, true);
		break;
		case TL_Rear:
			mWheels.Get(FL)->set(false, true, true);
			mWheels.Get(FR)->set(false, true, true);
			mWheels.Get(RL)->set(true, false, true);
			mWheels.Get(RR)->set(true, false, true);
		break;
		case TL_Four:
			mWheels.Get(FL)->set(true, true, true);
			mWheels.Get(FR)->set(true, true, true);
			mWheels.Get(RL)->set(true, false, true);
			mWheels.Get(RR)->set(true, false, true);
		break;
	}
}

/////////////////////////////////////////////////////////////

}; // End of NxOgre namespace.
