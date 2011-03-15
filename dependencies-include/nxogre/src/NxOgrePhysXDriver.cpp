/** \file    NxOgrePhysXDriver.cpp
 *  \see     NxOgrePhysXDriver.h
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
#include "NxOgrePhysXDriver.h"
#include "NxOgreWorld.h"			// For: World & PhysXDriver work together.
#include "NxOgreError.h"			// For: Starting up Error.
#include "NxOgreLog.h"				// For: Setting up Log, and passing on to Error.
#include "NxOgreHelpers.h"			// For: String manipulation in PhysXParams.
#include "NxOgreUserAllocator.h"
#include "NxOgreRemoteDebuggerConnection.h"
#include "NxOgreResourceSystem.h"
#include "NxOgreTimer.h"

#if defined NX_PLATFORM_WINDOWS && (NX_DEBUG == 1)
#  include "windows.h"
#endif

#if (NX_USE_OGRE == 1)
#  include "NxOgreOgreTimeController.h"
#endif

namespace NxOgre {

///////////////////////////////////////////////////////////////////////

void PhysXParams::setToDefault() {

	mSkinWidth = 0.025f;
	mSleepLinearVelocitySquared = (0.15 * 0.15);
	mSleepAngularVelocitySquared = (0.14 * 0.14);
	mBounceThreshold = -2;
	mDynamicFrictionScale = 1;
	mStaticFrictionScale = 1;
	mMaxAngularVelocity = 7;
	mCCD = false;
	mAdaptiveForce = 1.0f;
	mCollisionVetoJointed = true;
	mTriggerTriggerCallback = true;
	mCCDEpsilon = 0.01f;
	mSolverConvergenceThreshold = 0;
	mBBoxNoiseLevel = 0.001;
	mImplictSweepCacheSize = 5.0;
	mDefaultSleepEnergy = 0.05;
	mShutdownOnErrors = false;
	mTimeController = TC_NONE;
	mCustomTimeControllerPtr = 0;
	mUseLog = true;
	mDebugVisualisation.setToDefault();
	mHardwarePageSize = 65536;
	mHardwarePageMax = 256;
	mHardwareConvexMax = 65536;
	mCookerThreadMask = 0;
	mFlags.toDefault();

}

///////////////////////////////////////////////////////////////////////

void PhysXParams::parse(Parameters params) {

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

		if (Set("skin-width", parameter, mSkinWidth)) continue;
		if (Set("sleep-linear-velocity-squared", parameter, mSleepLinearVelocitySquared)) continue;
		if (Set("sleep-angular-velocity-squared", parameter, mSleepAngularVelocitySquared)) continue;
		if (Set("bounce-threshold", parameter, mBounceThreshold)) continue;
		if (Set("dynamic-friction-scale", parameter, mDynamicFrictionScale)) continue;
		if (Set("static-friction-scale", parameter, mStaticFrictionScale)) continue;
		if (Set("max-angular-velocity", parameter, mMaxAngularVelocity)) continue;
		if (Set("ccd", parameter, mCCD)) continue;
		if (Set("adaptive-force", parameter, mAdaptiveForce)) continue;
		if (Set("collision-veto-joint", parameter, mCollisionVetoJointed)) continue;
		if (Set("trigger-trigger-callback", parameter, mTriggerTriggerCallback)) continue;
		if (Set("ccd-epsilon", parameter, mCCDEpsilon)) continue;
		if (Set("solver-convergence-threshold", parameter, mSolverConvergenceThreshold)) continue;
		if (Set("bbox-noise-level", parameter, mBBoxNoiseLevel)) continue;
		if (Set("implict-sweeep-cache-size", parameter, mImplictSweepCacheSize)) continue;
		if (Set("default-sleep-energy", parameter, mDefaultSleepEnergy)) continue;
		if (Set("shutdown-on-errors", parameter, mShutdownOnErrors)) continue;
#if (NX_USE_OGRE == 1)
		if (Set("time-controller", parameter, mTimeController, TC_NONE, "none", TC_PTR, "pointer", TC_OGRE, "ogre")) continue;
#else
		if (Set("time-controller", parameter, mTimeController, TC_NONE, "none", TC_PTR, "pointer")) continue;
#endif
		if (Set("use-log", parameter, mUseLog)) continue;

	}

}

///////////////////////////////////////////////////////////////////////

void PhysXParams::DebugVisualisation::setToDefault() {

	mScale  = 0;
	mWorldAxes  = false;
	mBodyAxes  = false;
	mBodyMassAxes  = false;
	mBodyLinearVelocity = false;
	mBodyAngularVelocity = false;
	mBodyJointGroups = false;
	mJointLocalAxes = false;
	mJointWorldAxes = false;
	mJointLimits = false;
	mContactPoint = false;
	mContactNormal = false;
	mContactError = false;
	mActorAxes = false;
	mCollisionAABBs = false;
	mCollisionShapes = false;
	mCollisionAxes = false;
	mCollisionCompounds = false;
	mCollisionVertexNormals = false;
	mCollisionFaceNormals = false;
	mCollisionEdges = false;
	mCollisionSpheres = false;
#if (NX_SDK_VERSION_NUMBER < 280)
	mCollisionSAP = false;
#endif
	mCollisionStatic = false;
	mCollisionDynamic = false;
	mCollisionFree = false;
	mCollisionCCD = false;
	mCollisionSkeletons = false;
	mFluidEmitters = false;
	mFluidPosition = false;
	mFluidVelocity = false;
	mFluidKernelRadius = false;
	mFluidBounds = false;
	mFluidPackets = false;
	mFluidMotionLimit = false;
	mFluidDynamicCollision = false;
	mFluidStaticCollision = false;
	mFluidMeshPackets = false;
	mFluidDrains = false;
	mFluidPacketData = false;
	mClothMesh = false;
	mClothCollisions = false;
	mClothSelfCollisions = false;
	mClothWorkPackets = false;
	mClothSleep = false;
	mClothSleepVertex = false;
	mClothTearableVertices = false;
	mClothTearing = false;
	mClothAttachment = false;
	mClothValidBounds = false;
	mSoftBodyMesh = false;
	mSoftBodyCollisions = false;
	mSoftBodyWorkPackets = false;
	mSoftBodySleep = false;
	mSoftBodySleepVertex = false;
	mSoftBodyTearableVertices = false;
	mSoftBodyTearing = false;
	mSoftBodyAttachment = false;
	mSoftBodyValidBounds = false;

}

///////////////////////////////////////////////////////////////////////

void PhysXParams::DebugVisualisation::setToNormal() {
	mScale  = 0;
	mWorldAxes  = true;
	mBodyAxes  = true;
	mBodyMassAxes  = false;
	mBodyLinearVelocity = true;
	mBodyAngularVelocity = true;
	mBodyJointGroups = true;
	mJointLocalAxes = true;
	mJointWorldAxes = true;
	mJointLimits = true;
	mContactPoint = true;
	mContactNormal = true;
	mContactError = true;
	mActorAxes = false;
	mCollisionAABBs = false;
	mCollisionShapes = true;
	mCollisionAxes = false;
	mCollisionCompounds = false;
	mCollisionVertexNormals = true;
	mCollisionFaceNormals = true;
	mCollisionEdges = true;
	mCollisionSpheres = true;
#if (NX_SDK_VERSION_NUMBER < 280)
	mCollisionSAP = false;
#endif
	mCollisionStatic = true;
	mCollisionDynamic = true;
	mCollisionFree = true;
	mCollisionCCD = true;
	mCollisionSkeletons = true;
	mFluidEmitters = true;
	mFluidPosition = true;
	mFluidVelocity = false;
	mFluidKernelRadius = false;
	mFluidBounds = false;
	mFluidPackets = false;
	mFluidMotionLimit = false;
	mFluidDynamicCollision = false;
	mFluidStaticCollision = false;
	mFluidMeshPackets = false;
	mFluidDrains = true;
	mFluidPacketData = false;
	mClothMesh = false;
	mClothCollisions = false;
	mClothSelfCollisions = false;
	mClothWorkPackets = false;
	mClothSleep = false;
	mClothSleepVertex = false;
	mClothTearableVertices = false;
	mClothTearing = false;
	mClothAttachment = false;
	mClothValidBounds = false;
	mSoftBodyMesh = true;
	mSoftBodyCollisions = false;
	mSoftBodyWorkPackets = false;
	mSoftBodySleep = false;
	mSoftBodySleepVertex = false;
	mSoftBodyTearableVertices = false;
	mSoftBodyTearing = false;
	mSoftBodyAttachment = false;
	mSoftBodyValidBounds = false;
}

///////////////////////////////////////////////////////////////////////

void PhysXParams::DebugVisualisation::applyToSDK(NxPhysicsSDK*) {

	// Oh.

}

///////////////////////////////////////////////////////////////////////

void PhysXParams::PhysXSDKFlags::fromNxU32(NxU32 flag) {

	if (flag & NX_SDKF_NO_HARDWARE)
		mNoHardware = true;

}

///////////////////////////////////////////////////////////////////////

NxU32 PhysXParams::PhysXSDKFlags::toNxU32() const {
	
	NxU32 flag = 0;

	if (mNoHardware)
		flag |= NX_SDKF_NO_HARDWARE;

	return flag;
}

///////////////////////////////////////////////////////////////////////

void  PhysXParams::PhysXSDKFlags::parse(const NxString& flag_str) {

	Container<unsigned int, NxString> str_flags;
	str_flags = NxStringTokenize(flag_str, "+", true);

	if (str_flags.count() == 0)
		return;

	for (NxU32 i=0;i < str_flags.count();i++) {

		NxString flag_str = str_flags[i];

		NxStringTrim(flag_str);
		NxStringToLower(flag_str);

		if (set("no-hardware", flag_str, mNoHardware)) continue;

		// ...

	}

}

///////////////////////////////////////////////////////////////////////

void PhysXParams::toNxPhysicsSDKDescription(NxPhysicsSDKDesc& description) {
	description.cookerThreadMask = mCookerThreadMask;
	description.hwConvexMax = mHardwareConvexMax;
	description.hwPageMax = mHardwarePageMax;
	description.hwPageSize = mHardwarePageSize;
	description.flags = mFlags.toNxU32();
}

///////////////////////////////////////////////////////////////////////

void PhysXParams::fromNxPhysicsSDKDescription(NxPhysicsSDKDesc& description) {
	mCookerThreadMask = description.cookerThreadMask;
	mHardwareConvexMax = description.hwConvexMax;
	mHardwarePageMax = description.hwPageMax;
	mHardwarePageSize = description.hwPageSize;
	mFlags.fromNxU32(description.flags);
}

///////////////////////////////////////////////////////////////////////


PhysXDriver::PhysXDriver(World* w, PhysXParams params)
: mFramelistener(false),
  mWorld(w),
  mSDK(0),
  mTime(0),
  mTimeModifier(1),
  mNbSimulations(0),
  mLog(0),
  mDebugger(0),
  mTimeController(0)
{

	mAllocator = new Allocator();
	mError = new Error(this, params.mShutdownOnErrors);
	mUserAllocator = NxCreateAllocator("Global");

	mResourceSystem = new Resources::ResourceSystem(this);
	mAllocator->createLeakFile();

	switch(params.mTimeController) {
		case PhysXParams::TC_PTR:
			mTimeController = params.mCustomTimeControllerPtr;
		break;

#if (NX_USE_OGRE == 1)
		case PhysXParams::TC_OGRE:
			mTimeController = new OgreTimeController(this);
		break;
#endif

	};

	if (params.mUseLog) {
		mLog = NxNew(HTMLLog)();
		mError->addReporter(mLog, true);
	}

	NxPhysicsSDKDesc description;
	description.setToDefault();
	params.toNxPhysicsSDKDescription(description);

	_createSDK(description);

	if (mSDK == 0)
		return;

	_dumpVersionsToConsole();

	setSkinWidth(params.mSkinWidth);
	setSleepLinearVelocitySquared(params.mSleepLinearVelocitySquared);
	setSleepAngularVelocitySquared(params.mSleepAngularVelocitySquared);
	setBounceThreshold(params.mBounceThreshold);
	setDynamicFrictionScale(params.mDynamicFrictionScale);
	setStaticFrictionScale(params.mStaticFrictionScale);
	setMaxAngularVelocity(params.mMaxAngularVelocity);
	setCCD(params.mCCD);
	setAdaptiveForce(params.mAdaptiveForce);
	setCollisionVetoJointed(params.mCollisionVetoJointed);
	setTriggerTriggerCallback(params.mTriggerTriggerCallback);
	setCCDEpsilon(params.mCCDEpsilon);
	setSolverConvergenceThreshold(params.mSolverConvergenceThreshold);
	setBBoxNoiseLevel(params.mBBoxNoiseLevel);
	setImplictSweepCacheSize(params.mImplictSweepCacheSize);
	setDefaultSleepEnergy(params.mDefaultSleepEnergy);
	params.mDebugVisualisation.applyToSDK(mSDK);

}

///////////////////////////////////////////////////////////////////////

PhysXDriver::~PhysXDriver() {

#ifndef NX_SMALL
	if (mDebugger)
		destroyDebuggerConnection();
#endif

	if (mTimeController)
		delete mTimeController;

	delete mResourceSystem;

	_destroySDK();

	NxDebug("PhysX SDK has stopped.");

	delete mUserAllocator;
	delete mError;
	delete mAllocator;
}

///////////////////////////////////////////////////////////////////////

NxPhysicsSDK* PhysXDriver::getSDK() {
	return mSDK;
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::_createSDK(NxPhysicsSDKDesc& desc) {

	NxSDKCreateError errorCode = NXCE_NO_ERROR;


	mSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, mUserAllocator, mError, NxPhysicsSDKDesc(), &errorCode);
	// mSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, mError, desc, &errorCode);
	
	if(!mSDK && errorCode != 0) {
		std::stringstream s;

#if (NX_DEBUG == 1)
		s   << "Unable to start the PhysX SDK!" << std::endl << std::endl;
		
		switch (errorCode) {

			default: 
				s << "Unknown Error." 
				  << "Please report to the NxOgre team. " << std::endl;
			break;
						
			case NXCE_PHYSX_NOT_FOUND:
				s << "Unable to find the PhysX libraries. The PhysX drivers are not installed correctly." << std::endl;
				s << "- You can download the PhysX Drivers (also known as SystemSoftware) from http://www.ageia.com/drivers/" << std::endl;
				s << "- Install/Reinstall the drivers. Make sure the version of the SystemSoftware is compatible with the SDK." << std::endl;
				s << "- Look at the SDK release notes for further information, or visit http://devsupport.ageia.com" << std::endl;
			break;

			case NXCE_WRONG_VERSION:
				s << "The application supplied a version number that does not match with the libraries." << std::endl;
				s << "- Make sure that the NxCreatePhysicsSDK function passes on NX_PHYSICS_SDK_VERSION." << std::endl;
			break;

			case NXCE_DESCRIPTOR_INVALID:
				s << "The supplied SDK descriptor is invalid." << std::endl;
				s << " - Look at NxPhysicsSDKDesc in nxphysicssdk.h for more information." << std::endl;
			break;
			
			case NXCE_CONNECTION_ERROR:
				s << "A PhysX card was found, but there are problems when communicating with the card." << std::endl;
				s << " - Please visit http://support.ageia.com and/or your PhysX card manufacture." << std::endl; 
			break;
			
			case NXCE_RESET_ERROR: 
				s << "A PhysX card was found, but it did not reset (or initialize) properly." << std::endl;
				s << " - Please visit http://support.ageia.com and/or your PhysX card manufacturer." << std::endl; 
			break;

			case NXCE_IN_USE_ERROR:
				s << "A PhysX card was found, but it is already in use by another application." << std::endl;
				s << " - Close down all programs using the PhysX hardware before using this application." << std::endl; 
			break;

			case NXCE_BUNDLE_ERROR:
				s << "A PhysX card was found, but there are issues with loading the firmware." << std::endl;
				s << " - Please visit http://support.ageia.com and/or your PhysX card manufacturer." << std::endl;
			break;

		}
#else
		s << "Unable to start the PhysX SDK!" << std::endl << std::endl << "Please refer to the developer or publisher's website or support line for information relating to the errors detailed."
		  << std::endl << std::endl << "	-> Error Code: ";

		switch (errorCode) {
			case NXCE_NO_ERROR:				s << "NXCE_NO_ERROR" << std::endl; break;
			case NXCE_PHYSX_NOT_FOUND:		s << "NXCE_PHYSX_NOT_FOUND" << std::endl; break;
			case NXCE_WRONG_VERSION:		s << "NXCE_WRONG_VERSION" << std::endl; break;
			case NXCE_DESCRIPTOR_INVALID:	s << "NXCE_DESCRIPTOR_INVALID" << std::endl; break;
			case NXCE_CONNECTION_ERROR:		s << "NXCE_CONNECTION_ERROR" << std::endl; break;
			case NXCE_RESET_ERROR:			s << "NXCE_RESET_ERROR" << std::endl; break;
			case NXCE_IN_USE_ERROR:			s << "NXCE_IN_USE_ERROR" << std::endl; break;
			case NXCE_BUNDLE_ERROR:			s << "NXCE_BUNDLE_ERROR" << std::endl; break;
		}

		s   << " - Reason: ";
		
		switch (errorCode) {
			default: s << "Unknown Error" << std::endl; break;
			case NXCE_NO_ERROR: s << "No Error(!!?)" << std::endl; break;
			case NXCE_PHYSX_NOT_FOUND: s << "Unable to find the PhysX libraries. The PhysX drivers are not installed correctly." << std::endl; break;
			case NXCE_WRONG_VERSION: s << "The application supplied a version number that does not match with the libraries." << std::endl; break;
			case NXCE_DESCRIPTOR_INVALID: s << "The supplied SDK descriptor is invalid." << std::endl; break;
			case NXCE_CONNECTION_ERROR: s << "A PhysX card was found, but there are problems when communicating with the card." << std::endl; break;
			case NXCE_RESET_ERROR: s << "A PhysX card was found, but it did not reset (or initialize) properly." << std::endl; break;
			case NXCE_IN_USE_ERROR: s << "A PhysX card was found, but it is already in use by another application." << std::endl; break;
			case NXCE_BUNDLE_ERROR: s << "A PhysX card was found, but there are issues with loading the firmware." << std::endl; break;
		}

		s << std::endl;
#endif

		s <<  std::endl << std::endl << std::endl <<  "Application information:" << std::endl
		<< "- PhysX    => " << NX_SDK_VERSION_MAJOR << "." << NX_SDK_VERSION_MINOR << "." << NX_SDK_VERSION_BUGFIX << std::endl
		<< "- NxOgre   => " << Nx_Version_Full << std::endl
		<< "- Ogre     => " << OGRE_VERSION_MAJOR << "." << OGRE_VERSION_MINOR << "." << OGRE_VERSION_PATCH << " '" << OGRE_VERSION_NAME << "'." << std::endl;
	

		#ifdef NX_PLATFORM_WINDOWS
		s	<< "- Platform => Windows";
		#endif


		#ifdef NX_PLATFORM_LINUX
				s	<< "- Platform => Linux";
		#endif

		#if (NX_DEBUG == 1)
				s	<< " Debug";
		#endif

		s << std::endl;

		s << "- Error  => ";
		
		switch (errorCode) {
			case NXCE_NO_ERROR:				s << "NXCE_NO_ERROR" << std::endl; break;
			case NXCE_PHYSX_NOT_FOUND:		s << "NXCE_PHYSX_NOT_FOUND" << std::endl; break;
			case NXCE_WRONG_VERSION:		s << "NXCE_WRONG_VERSION" << std::endl; break;
			case NXCE_DESCRIPTOR_INVALID:	s << "NXCE_DESCRIPTOR_INVALID" << std::endl; break;
			case NXCE_CONNECTION_ERROR:		s << "NXCE_CONNECTION_ERROR" << std::endl; break;
			case NXCE_RESET_ERROR:			s << "NXCE_RESET_ERROR" << std::endl; break;
			case NXCE_IN_USE_ERROR:			s << "NXCE_IN_USE_ERROR" << std::endl; break;
			case NXCE_BUNDLE_ERROR:			s << "NXCE_BUNDLE_ERROR" << std::endl; break;
		}

		NxThrow(s.str().c_str());

#if defined NX_PLATFORM_WINDOWS && (NX_DEBUG == 1)
		s << std::endl << "On clicking of OK this Application will quit. See log or console window for a copy of this message and further information.";
 		MessageBox( NULL, s.str().c_str(), "Unable to start the PhysX SDK!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#endif


		mWorld->shutdown();
	}

}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::_createSDKfromID(NxString a,NxString b,NxString c,NxString d) {
	NxUnderConstruction;
//	mSDK = NxCreatePhysicsSDKWithID(NX_PHYSICS_SDK_VERSION,a.c_str(),b.c_str(),c.c_str(),d.c_str()/* To-Implement:, mAllocator, mError */);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::_destroySDK() {
	mSDK->release();
	mSDK = 0;
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::simulate(float time) {
	
	if (mTimeModifier) {
		mTime += time * mTimeModifier;
		mWorld->simulate(time * mTimeModifier);
#ifndef NX_SMALL
		if (mDebugger)
			mDebugger->simulate(time);
#endif
		mNbSimulations++;
	}

	
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::render(float time) {

	if (mTimeModifier) {
		mWorld->render(time * mTimeModifier);
	}
}

///////////////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void PhysXDriver::createDebuggerConnection(const NxString& address, unsigned int port) {
	if (mDebugger)
		return;
	mDebugger = new RemoteDebuggerConnection(address, port, this);
}

#endif

///////////////////////////////////////////////////////////////////////

#ifndef NX_SMALL

void PhysXDriver::destroyDebuggerConnection() {
	if (mDebugger) {
		delete mDebugger;
		mDebugger = 0;
	}
}

#endif 

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::hasHardware() {
	return (mSDK->getHWVersion() != NX_HW_VERSION_NONE);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setSkinWidth(NxReal val) {
	mSDK->setParameter(NX_SKIN_WIDTH, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setSleepLinearVelocitySquared(NxReal val) {
	mSDK->setParameter(NX_DEFAULT_SLEEP_LIN_VEL_SQUARED, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setSleepAngularVelocitySquared(NxReal val) {
	mSDK->setParameter(NX_DEFAULT_SLEEP_ANG_VEL_SQUARED, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setBounceThreshold(NxReal val) {
	mSDK->setParameter(NX_BOUNCE_THRESHOLD, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setDynamicFrictionScale(NxReal val) {
	mSDK->setParameter(NX_DYN_FRICT_SCALING, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setStaticFrictionScale(NxReal val) {
	mSDK->setParameter(NX_STA_FRICT_SCALING, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setMaxAngularVelocity(NxReal val) {
	mSDK->setParameter(NX_MAX_ANGULAR_VELOCITY, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setCCD(bool val) {
	mSDK->setParameter(NX_CONTINUOUS_CD, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setAdaptiveForce(NxReal val) {
	mSDK->setParameter(NX_ADAPTIVE_FORCE, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setCollisionVetoJointed(bool val) {
	mSDK->setParameter(NX_COLL_VETO_JOINTED, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setTriggerTriggerCallback(bool val) {
	mSDK->setParameter(NX_TRIGGER_TRIGGER_CALLBACK, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setCCDEpsilon(NxReal val) {
	mSDK->setParameter(NX_CCD_EPSILON, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setSolverConvergenceThreshold(NxReal val) {
	mSDK->setParameter(NX_SOLVER_CONVERGENCE_THRESHOLD, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setBBoxNoiseLevel(NxReal val) {
	mSDK->setParameter(NX_BBOX_NOISE_LEVEL, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setImplictSweepCacheSize(NxReal val) {
	mSDK->setParameter(NX_IMPLICIT_SWEEP_CACHE_SIZE, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setDefaultSleepEnergy(NxReal val) {
	mSDK->setParameter(NX_DEFAULT_SLEEP_ENERGY, val);
}


///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getSkinWidth() const {
	return mSDK->getParameter(NX_SKIN_WIDTH);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getSleepLinearVelocitySquared() const {
	return mSDK->getParameter(NX_DEFAULT_SLEEP_LIN_VEL_SQUARED);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getSleepAngularVelocitySquared() const {
	return mSDK->getParameter(NX_DEFAULT_SLEEP_ANG_VEL_SQUARED);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getBounceThreshold() const {
	return mSDK->getParameter(NX_BOUNCE_THRESHOLD);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getDynamicFrictionScale() const {
	return mSDK->getParameter(NX_DYN_FRICT_SCALING);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getStaticFrictionScale() const {
	return mSDK->getParameter(NX_STA_FRICT_SCALING);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getMaxAngularVelocity() const {
	return mSDK->getParameter(NX_MAX_ANGULAR_VELOCITY);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getCCD() const {
	return !!mSDK->getParameter(NX_CONTINUOUS_CD);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getAdaptiveForce() const {
	return mSDK->getParameter(NX_ADAPTIVE_FORCE);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getCollisionVetoJointed() const {
	return !!mSDK->getParameter(NX_COLL_VETO_JOINTED);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getTriggerTriggerCallback() const {
	return !!mSDK->getParameter(NX_TRIGGER_TRIGGER_CALLBACK);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getCCDEpsilon() const {
	return mSDK->getParameter(NX_CCD_EPSILON);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getSolverConvergenceThreshold() const {
	return mSDK->getParameter(NX_SOLVER_CONVERGENCE_THRESHOLD);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getBBoxNoiseLevel() const {
	return mSDK->getParameter(NX_BBOX_NOISE_LEVEL);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getImplictSweepCacheSize() const {
	return mSDK->getParameter(NX_IMPLICIT_SWEEP_CACHE_SIZE);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getDefaultSleepEnergy() const {
	return mSDK->getParameter(NX_DEFAULT_SLEEP_ENERGY);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationScale(NxReal val) {
	mSDK->setParameter(NX_VISUALIZATION_SCALE, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationWorldAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_WORLD_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationBodyAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_BODY_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationBodyMassAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_BODY_MASS_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationBodyLinearVelocityEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationBodyAngularVelocityEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_BODY_ANG_VELOCITY, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationBodyJointGroupsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_BODY_JOINT_GROUPS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationJointLocalAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_JOINT_LOCAL_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationJointWorldAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_JOINT_WORLD_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationJointLimitsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_JOINT_LIMITS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationContactPointEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationContactNormalEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationContactErrorEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CONTACT_ERROR, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationActorAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionAABBsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_AABBS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionShapesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionAxesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_AXES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionCompoundsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_COMPOUNDS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionVertexNormalsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_VNORMALS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionFaceNormalsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_FNORMALS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionEdgesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_EDGES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionSpheresEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_SPHERES, val);
}

///////////////////////////////////////////////////////////////////////

#if (NX_SDK_VERSION_NUMBER < 280)
void PhysXDriver::setVisualisationCollisionSAPEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_SAP, val);
}
#endif
///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionStaticEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_STATIC, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionDynamicEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_DYNAMIC, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionFreeEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_FREE, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionCCDEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_CCD, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationCollisionSkeletonsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_COLLISION_SKELETONS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidEmittersEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_EMITTERS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidPositionEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_POSITION, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidVelocityEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_VELOCITY, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidKernelRadiusEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_KERNEL_RADIUS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidBoundsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_BOUNDS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidPacketsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_PACKETS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidMotionLimitEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_MOTION_LIMIT, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidDynamicCollisionEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_DYN_COLLISION, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidStaticCollisionEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_STC_COLLISION, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidMeshPacketsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_MESH_PACKETS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidDrainsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_DRAINS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationFluidPacketDataEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_FLUID_PACKET_DATA, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothMeshEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_MESH, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothCollisionsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_COLLISIONS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothSelfCollisionsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_SELFCOLLISIONS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothWorkPacketsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_WORKPACKETS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothSleepEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_SLEEP, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothSleepVertexEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_SLEEP_VERTEX, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothTearableVerticesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_TEARABLE_VERTICES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothTearingEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_TEARING, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothAttachmentEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_ATTACHMENT, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationClothValidBoundsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_CLOTH_VALIDBOUNDS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyMeshEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_MESH, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyCollisionsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_COLLISIONS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyWorkPacketsEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_WORKPACKETS, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodySleepEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_SLEEP, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodySleepVertexEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_SLEEP_VERTEX, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyTearableVerticesEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_TEARABLE_VERTICES, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyTearingEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_TEARING, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyAttachmentEnabled(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_ATTACHMENT, val);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::setVisualisationSoftBodyValidBounds(bool val) {
	mSDK->setParameter(NX_VISUALIZE_SOFTBODY_VALIDBOUNDS, val);
}

///////////////////////////////////////////////////////////////////////

NxReal PhysXDriver::getVisualisationScale() const {
	return mSDK->getParameter(NX_VISUALIZATION_SCALE);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationWorldAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_WORLD_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationBodyAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_BODY_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationBodyMassAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_BODY_MASS_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationBodyLinearVelocityEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_BODY_LIN_VELOCITY);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationBodyAngularVelocityEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_BODY_ANG_VELOCITY);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationBodyJointGroupsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_BODY_JOINT_GROUPS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationJointLocalAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_JOINT_LOCAL_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationJointWorldAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_JOINT_WORLD_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationJointLimitsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_JOINT_LIMITS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationContactPointEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CONTACT_POINT);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationContactNormalEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CONTACT_NORMAL);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationContactErrorEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CONTACT_ERROR);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationActorAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_ACTOR_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionAABBsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_AABBS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionShapesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_SHAPES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionAxesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_AXES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionCompoundsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_COMPOUNDS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionVertexNormalsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_VNORMALS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionFaceNormalsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_FNORMALS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionEdgesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_EDGES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionSpheresEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_SPHERES);
}

///////////////////////////////////////////////////////////////////////

#if (NX_SDK_VERSION_NUMBER < 280)
bool PhysXDriver::getVisualisationCollisionSAPEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_SAP);
}
#endif
///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionStaticEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_STATIC);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionDynamicEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_DYNAMIC);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionFreeEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_FREE);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionCCDEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_CCD);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationCollisionSkeletonsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_COLLISION_SKELETONS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidEmittersEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_EMITTERS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidPositionEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_POSITION);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidVelocityEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_VELOCITY);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidKernelRadiusEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_KERNEL_RADIUS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidBoundsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_BOUNDS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidPacketsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_PACKETS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidMotionLimitEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_MOTION_LIMIT);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidDynamicCollisionEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_DYN_COLLISION);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidStaticCollisionEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_STC_COLLISION);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidMeshPacketsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_MESH_PACKETS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidDrainsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_DRAINS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationFluidPacketDataEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_FLUID_PACKET_DATA);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothMeshEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_MESH);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothCollisionsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_COLLISIONS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothSelfCollisionsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_SELFCOLLISIONS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothWorkPacketsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_WORKPACKETS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothSleepEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_SLEEP);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothSleepVertexEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_SLEEP_VERTEX);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothTearableVerticesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_TEARABLE_VERTICES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothTearingEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_TEARING);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothAttachmentEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_ATTACHMENT);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationClothValidBoundsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_CLOTH_VALIDBOUNDS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyMeshEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_MESH);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyCollisionsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_COLLISIONS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyWorkPacketsEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_WORKPACKETS);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodySleepEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_SLEEP);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodySleepVertexEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_SLEEP_VERTEX);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyTearableVerticesEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_TEARABLE_VERTICES);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyTearingEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_TEARING);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyAttachmentEnabled() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_ATTACHMENT);
}

///////////////////////////////////////////////////////////////////////

bool PhysXDriver::getVisualisationSoftBodyValidBounds() const {
	return !!mSDK->getParameter(NX_VISUALIZE_SOFTBODY_VALIDBOUNDS);
}

///////////////////////////////////////////////////////////////////////

void PhysXDriver::_dumpVersionsToConsole() {

	char* version_string = (char*) malloc(sizeof(char) * 1024);
	unsigned int compiled_string_length = 0;

	compiled_string_length = 
		sprintf(version_string,
			"%s started. Working with \n"
			"  - PhysX    => %i.%i.%i (%i)\n"
#if (NX_USE_OGRE == 1)
			"  - Ogre     => %i.%i.%i (%s)\n"
#endif
			"  - Hardware => Probably\n"
			"  - Platform => "
#ifdef NX_PLATFORM_WINDOWS
"Windows"
#else
#ifdef NX_PLATFORM_LINUX
	"Linux"
#else
	"Unknown"
#endif
#endif

#ifdef NX_DEBUG
" (Debug)"
#else
" (Release)"
#endif
			"\n"
			, Nx_Version_Full,
			NX_SDK_VERSION_MAJOR, NX_SDK_VERSION_MINOR, NX_SDK_VERSION_BUGFIX, NX_SDK_VERSION_NUMBER,
#if (NX_USE_OGRE == 1)
			OGRE_VERSION_MAJOR, OGRE_VERSION_MINOR, OGRE_VERSION_PATCH, OGRE_VERSION_NAME
#endif
			
			);

	char* compiled_string = (char*) malloc(sizeof(char) * compiled_string_length + 1);
	memcpy(compiled_string, version_string, sizeof(char) * compiled_string_length);
	compiled_string[compiled_string_length] = 0;

	NxDebug(compiled_string);

	free(compiled_string);
	free(version_string);
}

/////////////////////////////////////////////////////////////

UserAllocator* PhysXDriver::getUserAllocator() {
	return mUserAllocator;
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
