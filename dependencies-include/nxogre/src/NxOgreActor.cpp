/** \file    NxOgreActor.cpp
 *  \see     NxOgreActor.h
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
#include "NxOgreActor.h"

#include "NxOgreVoidPointer.h"          // For VoidPointer for NxActor
#include "NxOgrePose.h"                 // For conversions
#include "NxOgreHelpers.h"              // For conversions
#include "NxOgreScene.h"                // For Actor::mOwner
#include "NxOgreWorld.h"                // For mBirthFrame
#include "NxOgreShape.h"                // For Collision Model
#include "NxOgreDominanceGroup.h"       // For Dominance Groups
#include "NxOgreGroup.h"                // For ActorGroup and ShapeGroups
#include "NxOgreContainer.h"            // For Getting an ActorGroup

#if (NX_USE_OGRE == 1)
#  include "OgreStringConverter.h"
#  include "OgreRoot.h"
#  include "OgreSingleton.h"
#  include "OgreMatrix3.h"
#endif

namespace NxOgre
{

//////////////////////////////////////////////////////////

	void ActorParams::setToDefault()
	{


		mDensity                 = 0.0f;
		mActorFlags              = 0;
		mGroupAsIndex            = 0;
		mGroupAsName             = "";
#if NX_SDK_VERSION_NUMBER >= 272
		mDominanceGroupAsIndex   = 0;
		mDominanceGroupAsName    = "";
#endif
#if NX_SDK_VERSION_NUMBER >= 260
		mCompartment             = NULL;
#endif
		mMassLocalPose           . id();
		mMassSpaceInertia        . zero();
		mLinearVelocity          . zero();
		mAngularVelocity         . zero();
		mWakeUpCounter           = 20.0f * 0.02f;
		mMass                    = 10.0f;
		mLinearDamping           = 0.0f;
		mAngularDamping          = 0.05f;
		mMaxAngularVelocity      = -1.0f;
		mBodyFlags               = NX_BF_VISUALIZATION;
		mBodyFlags              |= NX_BF_ENERGY_SLEEP_TEST;
		mSleepLinearVelocity     = -1.0f;
		mSleepAngularVelocity    = -1.0f;
		mCCDMotionThreshold      = 0.0f;
		mSolverIterationCount    = 4;
		mSleepEnergyThreshold    = -1.0f;
		mSleepDamping            = 0.0f;

	}

//////////////////////////////////////////////////////////

	void ActorParams::parse(Parameters params)
	{

		setToDefault();

		for (Parameter* parameter = params.Begin(); parameter = params.Next();)
		{

			if (parameter->i == "static")
			{

				if (isYes(parameter->j))
				{
					mMass = 0;
					mDensity = 0;
					continue;
				}
				else
				{
					mMass = 10;
					mDensity = 0;
				}
			}

			if (parameter->i == "kinematic")
			{
				if (isYes(parameter->j))
				{
					mBodyFlags |= NX_BF_KINEMATIC;

					if (mMass == 0 || mDensity == 0)
					{
						mMass = 1;
						mDensity = 0;
					}
				}
			}

			if (Set("density", parameter, mDensity)) { continue; }

			if (Set("group", parameter, mGroupAsName)) { continue; }

			if (Set("group-index", parameter, mGroupAsIndex)) { continue; }

#if NX_SDK_VERSION_NUMBER >= 272

			if (Set("dominancegroup", parameter, mDominanceGroupAsName)) { continue; }

			if (Set("dominancegroup-index", parameter, mDominanceGroupAsIndex)) { continue; }

#endif

			if (Set("massspaceinertia", parameter, mMassSpaceInertia)) { continue; }

			if (Set("linearvelocity", parameter, mLinearVelocity)) { continue; }

			if (Set("angularvelocity", parameter, mAngularVelocity)) { continue; }

			if (Set("wakeupcounter", parameter, mWakeUpCounter)) { continue; }

			if (Set("mass", parameter, mMass)) { continue; }

			if (Set("lineardamping", parameter, mLinearDamping)) { continue; }

			if (Set("angulardamping", parameter, mAngularDamping)) { continue; }

			if (Set("maxangularvelocity", parameter, mMaxAngularVelocity)) { continue; }

			if (Set("sleepangularvelocity", parameter, mSleepAngularVelocity)) { continue; }

			if (Set("ccdmotionthreshold", parameter, mCCDMotionThreshold)) { continue; }

			if (Set("solveriterationcount", parameter, mSolverIterationCount)) { continue; }

			if (Set("sleepenergythreshold", parameter, mSleepEnergyThreshold)) { continue; }

			if (Set("sleepdamping", parameter, mSleepDamping)) { continue; }

		}

	}

//////////////////////////////////////////////////////////

	void ActorParams::fromNxActorDesc(NxActorDesc& desc)
	{

		mDensity                = desc.density;
		mActorFlags             = desc.flags;
		mGroupAsIndex           = desc.group;
#if NX_SDK_VERSION_NUMBER >= 272
		mDominanceGroupAsIndex  = desc.dominanceGroup;
#endif
#if NX_SDK_VERSION_NUMBER >= 260
		mCompartment            = desc.compartment;
#endif

	}

//////////////////////////////////////////////////////////

	void ActorParams::fromNxBodyDesc(NxBodyDesc& desc)
	{

		mMassLocalPose          = desc.massLocalPose;
		mMassSpaceInertia       = desc.massSpaceInertia;
		mLinearVelocity         = desc.linearVelocity;
		mAngularVelocity        = desc.angularVelocity;
		mWakeUpCounter          = desc.wakeUpCounter;
		mMass                   = desc.mass;
		mLinearDamping          = desc.linearDamping;
		mAngularDamping         = desc.angularDamping;
		mMaxAngularVelocity     = desc.maxAngularVelocity;
		mBodyFlags              = desc.flags;
		mSleepLinearVelocity    = desc.sleepLinearVelocity;
		mSleepAngularVelocity   = desc.sleepAngularVelocity;
		mCCDMotionThreshold     = desc.CCDMotionThreshold;
		mSolverIterationCount   = desc.solverIterationCount;
		mBodyFlags              = desc.flags;
		mSleepEnergyThreshold   = desc.sleepEnergyThreshold;
		mSleepDamping           = desc.sleepDamping;

	}

//////////////////////////////////////////////////////////

	Actor::Actor(const NxString& Identifier, Scene* scene, bool isActorBased) : mName(Identifier), mOwner(scene)
	{

		mActor = 0;

		if (isActorBased)
		{
			mOwner->_registerActor(mName, this);
		}

	}

//////////////////////////////////////////////////////////

	Actor::Actor(const NxString& name, Scene* scene, Shape* shape, const Pose& pose, const ActorParams& params)
		: mName(name), mOwner(scene)
	{

		if (name.length() == 0)
		{
			mName = NxCreateID(scene->getNbActors(), "Actor");
		}
		else
		{

			// Urgh.
			NxString identifier = name;

			if (identifier.substr(0, 1) == ">")
			{
				mName = identifier.substr(1, identifier.length() - 1);

				if (scene->getActors()->has(mName))
				{
					NxThrow(NxString("Duplicate Actor with identifier '" + mName + "' found!").c_str());
				}
			}
			else if (scene->getActors()->has(identifier))
			{
				// Generate a identifier based on the the suggested name.
				// i.e.
				//          myBody  -> myBody 1
				//          myBody10 -> myBody 11
				Actors actors;
				scene->getActors()->CopyTo(actors);

				NxU32 highest = 0;
				NxString workingName;

				for (Actor* a = actors.begin(); a = actors.next();)
				{
					if (Ogre::StringUtil::startsWith(a->getName(), identifier, false))
					{
						workingName = a->getName();
						workingName = workingName.substr(identifier.length(), workingName.length() - identifier.length());
						std::stringstream ss(workingName);
						NxU32 current = 0;
						ss >> current;

						if (current > highest)
						{
							highest = current;
						}
					}
				}

				highest++;
				mName = identifier;
				mName.append(Ogre::StringConverter::toString(highest));
			}
			else
			{
				mName = identifier;
			}
		}

		_createActor(shape, pose, params);
		mOwner->_registerActor(mName, this);
	}

//////////////////////////////////////////////////////////

	Actor::~Actor()
	{

		mOwner->_unregisterActor(mName);

		if (!isDead())
		{
			_destroyActor();
		}

	}

//////////////////////////////////////////////////////////

	void Actor::_createActor(Shape* shape, const Pose& pose, ActorParams params)
	{

		NxActorDesc ad;
		NxBodyDesc bd;
		ad.setToDefault();
		bd.setToDefault();

		mVoidPointer = new VoidPointer(this, NxOgreClass_Actor);
#if NX_SDK_VERSION_NUMBER >= 260
		ad.compartment = params.mCompartment;
#endif

		if (params.mMass == 0)
		{
			ad.density = params.mDensity;
		}

#if NX_SDK_VERSION_NUMBER >= 272

		if (params.mDominanceGroupAsIndex != 0)
		{
			ad.dominanceGroup = params.mDominanceGroupAsIndex;
		}
		else if (params.mDominanceGroupAsName.length() > 0)
		{
			ad.dominanceGroup = mOwner->getDominanceGroup(params.mDominanceGroupAsName)->getGroupID();
		}

#endif
		ad.flags = params.mActorFlags;

		ad.globalPose = pose;

		if (params.mGroupAsIndex != 0)
		{
			ad.group = params.mGroupAsIndex;
		}
		else if (params.mGroupAsName.length() > 0)
		{
			ad.group = mOwner->getActorGroup(params.mGroupAsName)->getGroupID();
		}

		ad.userData = mVoidPointer;

		if (params.mDensity == 0 && params.mMass == 0)
		{
			ad.body = NULL;
		}
		else
		{
			bd.angularDamping = params.mAngularDamping;
			bd.angularVelocity = params.mAngularVelocity;
			bd.CCDMotionThreshold = params.mCCDMotionThreshold;
			bd.flags = params.mBodyFlags;
			bd.linearDamping = params.mLinearDamping;
			bd.linearVelocity = params.mLinearVelocity;

			if (ad.density == 0)
			{
				bd.mass = params.mMass;
			}

			bd.massLocalPose = params.mMassLocalPose;
			bd.massSpaceInertia = params.mMassSpaceInertia;
			bd.maxAngularVelocity = params.mMaxAngularVelocity;
			bd.sleepAngularVelocity = params.mSleepAngularVelocity;
			bd.sleepDamping = params.mSleepDamping;
			bd.sleepEnergyThreshold = params.mSleepEnergyThreshold;
			bd.sleepLinearVelocity = params.mSleepLinearVelocity;
			bd.solverIterationCount = params.mSolverIterationCount;
			bd.wakeUpCounter = params.mWakeUpCounter;
			ad.body = &bd;
		}

		NxWatchDescribed(Shape, shape, mName.c_str());

		// first try finding this actor in the scene
		int count = this->mOwner->mScene->getNbActors();
		bool found = false;

		for (int i = 0; i < count; ++i)
		{
			if ((this->mOwner->mScene->getActors()[i]->getName()) && (strcmp(this->mOwner->mScene->getActors()[i]->getName(), mName.c_str()) == 0))
			{
				// use already created object
				NxActor* aa = this->mOwner->mScene->getActors()[i];
				mActor = aa;

				// set nxogre specific data to this actor
				aa->userData = ad.userData;
				found = true;
				break;
			}
		}

		//otherwise create
		if (!found)
		{
			shape->createShape(ad.shapes, 0, mOwner);

			if (shape->getTypeHash() == NxOgreClass_Shape)
			{
				mCollisionModel.Insert(shape);
			}

			ad.name = mName.c_str();
			mActor = mOwner->mScene->createActor(ad);
		}

		if (!mActor)
		{
			NxThrow(NxString("Creation of Actor with the identifier '" + mName + "' failed.").c_str());
			return;
		}

		if (shape->getTypeHash() == NxOgreClass_Shape)
		{
			NxU32 nbShapes = mActor->getNbShapes();
			NxShape* const* nx_shapes = mActor->getShapes();

			for (NxU32 i = 0; i < nbShapes; i++)
			{
				mCollisionModel[i]->setNxShape(nx_shapes[i]);
			}

		}
		else if (shape->getTypeHash() == NxOgreClass_CompoundShape)
		{

			NxU32 nbShapes = mActor->getNbShapes();
			NxShape* const* nx_shapes = mActor->getShapes();
			CompoundShape* compound_shape = static_cast<CompoundShape*>(shape);

			for (NxU32 i = 0; i < nbShapes; i++)
			{
				// added because when actor was previously created then mShapes[i]
				// was NULL
				if (compound_shape->mShapes[i] == NULL)
				{
					compound_shape->mShapes.Insert(i, new CompoundShape());
				}

				compound_shape->mShapes[i]->setNxShape(nx_shapes[i]);
				mCollisionModel.Insert(compound_shape->mShapes[i]);
			}

			delete shape;
			shape = 0;
			compound_shape = 0;
		}

		mBirthFrame = mOwner->getWorld()->getNbFrames();

	}

//////////////////////////////////////////////////////////

	void Actor::_destroyActor()
	{
//  mCollisionModel.destroyAllOwned();
		mCollisionModel.DestroyAll();
		delete mVoidPointer;
		mOwner->mScene->releaseActor(*mActor);
		mActor = 0;
	}

//////////////////////////////////////////////////////////

	void Actor::setName(NxString name)
	{
		mOwner->mActors.rename(mName, name);
		mName = name;
	}

//////////////////////////////////////////////////////////

	NxString Actor::getName() const
	{
		return mName;
	}

//////////////////////////////////////////////////////////

	NxScene* Actor::getNxScene()
	{
		return mOwner->getNxScene();
	}

//////////////////////////////////////////////////////////

	Actor*  Actor::duplicate(const NxString& name, const Pose& p)
	{
#if 0
		Blueprints::ActorBlueprint* ab = new Blueprints::ActorBlueprint();
		ab->serialise(this, mOwner);
		Actor* a = ab->unserialise(name, mOwner);
		a->setGlobalPose(p);
		delete ab;
		return a;
#endif

		return NULL;
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalPose(const Pose& pose)
	{
		mActor->setGlobalPose(pose);
	}

//////////////////////////////////////////////////////////

	Pose Actor::getGlobalPose() const
	{
		return Pose(mActor->getGlobalPose());
	}

//////////////////////////////////////////////////////////

#if (NX_USE_OGRE == 1)

	Ogre::Quaternion Actor::getGlobalOrientationAsOgreQuaternion() const
	{
		return Pose(mActor->getGlobalPose());
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalOrientation(const Ogre::Quaternion& quaternion)
	{
		NxQuat nx_quaternion; nx_quaternion.setWXYZ(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
		mActor->setGlobalOrientationQuat(nx_quaternion);
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getGlobalPositionAsOgreVector3() const
	{
		NxVec3 nx_vector = mActor->getGlobalPosition();
		return Ogre::Vector3(nx_vector.x, nx_vector.y, nx_vector.z);
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalPosition(const Ogre::Vector3& vector)
	{
		NxVec3 nx_vector(vector.x, vector.y, vector.z);
		mActor->setGlobalPosition(nx_vector);
	}

//////////////////////////////////////////////////////////

#endif


//////////////////////////////////////////////////////////

	NxMat33 Actor::getGlobalOrientation() const
	{
		return mActor->getGlobalOrientation();
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalOrientation(const NxMat33& matrix)
	{
		mActor->setGlobalOrientation(matrix);
	}

//////////////////////////////////////////////////////////

	float4 Actor::getGlobalOrientationAsFloat4() const
	{
		NxQuat nx_quaternion = mActor->getGlobalOrientationQuat();
		return float4(nx_quaternion.w, nx_quaternion.x, nx_quaternion.y, nx_quaternion.z);
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalOrientation(const float4& quaternion)
	{
		NxQuat nx_quaternion; nx_quaternion.setWXYZ(quaternion.i, quaternion.j, quaternion.k, quaternion.l);
		mActor->setGlobalOrientationQuat(nx_quaternion);
	}

//////////////////////////////////////////////////////////

	float3 Actor::getGlobalPositionAsFloat3() const
	{
		NxVec3 nx_vector = mActor->getGlobalPosition();
		return float3(nx_vector.x, nx_vector.y, nx_vector.z);
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalPosition(const float3& vector)
	{
		NxVec3 nx_vector(vector.i, vector.j, vector.k);
		mActor->setGlobalPosition(nx_vector);
	}

//////////////////////////////////////////////////////////

	NxQuat Actor::getGlobalOrientationAsNxQuat() const
	{
		return mActor->getGlobalOrientationQuat();
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalOrientation(const NxQuat& quaternion)
	{
		mActor->setGlobalOrientationQuat(quaternion);
	}

//////////////////////////////////////////////////////////

	NxVec3 Actor::getGlobalPositionAsNxVec3() const
	{
		return mActor->getGlobalPosition();
	}

//////////////////////////////////////////////////////////

	void Actor::setGlobalPosition(const NxVec3& vector)
	{
		mActor->setGlobalPosition(vector);
	}

//////////////////////////////////////////////////////////

	void Actor::moveGlobalPose(const Pose& pose)
	{
		mActor->moveGlobalPose(pose);
	}

//////////////////////////////////////////////////////////

	void Actor::moveGlobalPosition(const Ogre::Vector3& vec)
	{
		mActor->moveGlobalPosition(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::moveGlobalOrientation(const Ogre::Quaternion& quat)
	{
		mActor->moveGlobalOrientationQuat(NxConvert<NxQuat, Ogre::Quaternion>(quat));
	}

////////////////////////////////////////////////////////

	void Actor::moveTowards(const Pose& p, float force)
	{
		NxVec3 fc = p.m.t - mActor->getGlobalPosition();
		fc *= force;
		fc -= mActor->getPointVelocity(mActor->getGlobalPosition());
		mActor->addForceAtPos(fc, mActor->getGlobalPosition());
	}

//////////////////////////////////////////////////////////

	void Actor::setGroup(ActorGroup* ag)
	{
		mActor->setGroup(ag->getGroupID());
	}

//////////////////////////////////////////////////////////

	void Actor::setGroup(const NxString& GroupIdentifier)
	{
		mActor->setGroup(mOwner->getActorGroups()->get(GroupIdentifier)->getGroupID());
	}

//////////////////////////////////////////////////////////

	void Actor::setGroup(NxActorGroup agid)
	{
		mActor->setGroup(agid);
	}

//////////////////////////////////////////////////////////

	ActorGroup* Actor::getGroup() const
	{
		NxActorGroup agid = mActor->getGroup();
		return mOwner->getActorGroupsByIndex()->get(agid);
	}

//////////////////////////////////////////////////////////

	void Actor::raiseActorFlag(NxActorFlag f)
	{
		mActor->raiseActorFlag(f);
	}

//////////////////////////////////////////////////////////

	void Actor::clearActorFlag(NxActorFlag f)
	{
		mActor->clearActorFlag(f);
	}

//////////////////////////////////////////////////////////

	bool Actor::hasActorFlag(NxActorFlag f) const
	{
		return mActor->readActorFlag(f);
	}
//////////////////////////////////////////////////////////

	bool Actor::isDynamic() const
	{
		return mActor->isDynamic();
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetLocalPose(const Pose& pose)
	{
		mActor->setCMassOffsetLocalPose(pose);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetLocalPosition(const Ogre::Vector3& vec)
	{
		mActor->setCMassOffsetLocalPosition(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetLocalOrientation(const NxMat33& m)
	{
		mActor->setCMassOffsetLocalOrientation(m);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetLocalOrientation(const Ogre::Matrix3& vec)
	{
		NxUnderConstruction;
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetGlobalPose(const Pose& pose)
	{
		mActor->setCMassOffsetGlobalPose(pose);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetGlobalPosition(const Ogre::Vector3& vec)
	{
		mActor->setCMassOffsetGlobalPosition(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetGlobalOrientation(const NxMat33& m)
	{
		mActor->setCMassOffsetGlobalOrientation(m);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassOffsetGlobalOrientation(const Ogre::Matrix3& quat)
	{
		NxUnderConstruction;
		NxMat33 m;
		mActor->setCMassOffsetGlobalOrientation(m);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassGlobalPose(const Pose& pose)
	{
		mActor->setCMassGlobalPose(pose);
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassGlobalPosition(const Ogre::Vector3& vec)
	{
		mActor->setCMassGlobalPosition(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::setCMassGlobalOrientation(const Ogre::Quaternion& quat)
	{
		NxUnderConstruction;
		NxMat33 m;
		mActor->setCMassGlobalOrientation(m);
	}
//////////////////////////////////////////////////////////


	Pose Actor::getCMassLocalPose() const
	{
		Pose pose = mActor->getCMassLocalPose();
		return pose;
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getCMassLocalPosition()    const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getCMassLocalPosition());
	}

//////////////////////////////////////////////////////////

	Ogre::Quaternion Actor::getCMassLocalOrientation() const
	{
		return NxConvert<Ogre::Quaternion, NxQuat>(mActor->getCMassLocalOrientation());
	}

//////////////////////////////////////////////////////////

	Pose Actor::getCMassGlobalPose() const
	{
		Pose pose;
		pose = mActor->getCMassGlobalPose();
		return pose;
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getCMassGlobalPosition() const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getCMassGlobalPosition());
	}

//////////////////////////////////////////////////////////

	Ogre::Quaternion Actor::getCMassGlobalOrientation() const
	{
		NxQuat quat;
		mActor->getCMassGlobalOrientation().toQuat(quat);
		return NxConvert<Ogre::Quaternion, NxQuat>(quat);
	}

//////////////////////////////////////////////////////////


	void Actor::setMass(NxReal r)
	{
		mActor->setMass(r);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getMass() const
	{
		return mActor->getMass();
	}

//////////////////////////////////////////////////////////


	void Actor::setMassSpaceInertiaTensor(const Ogre::Vector3& vec)
	{
		mActor->setMassSpaceInertiaTensor(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getMassSpaceInertiaTensor()    const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getMassSpaceInertiaTensor());
	}

//////////////////////////////////////////////////////////

	Ogre::Matrix3 Actor::getGlobalInertiaTensor() const
	{
		NxUnderConstruction;
		Ogre::Matrix3 m;
		return m;
	}

//////////////////////////////////////////////////////////

	Ogre::Matrix3 Actor::getGlobalInertiaTensorInverse()    const
	{
		NxUnderConstruction;
		Ogre::Matrix3 m;
		return m;
	}

//////////////////////////////////////////////////////////


	void Actor::updateMassFromShapeFromDensity(NxReal r)
	{
		mActor->updateMassFromShapes(r, 0);
	}

//////////////////////////////////////////////////////////

	void Actor::updateMassFromShapeAsMass(NxReal r)
	{
		mActor->updateMassFromShapes(0, r);
	}

//////////////////////////////////////////////////////////

	void Actor::setLinearDamping(NxReal r)
	{
		mActor->setLinearDamping(r);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getLinearDamping() const
	{
		return mActor->getLinearDamping();
	}

//////////////////////////////////////////////////////////


	void Actor::setAngularDamping(NxReal r)
	{
		mActor->setAngularDamping(r);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getAngularDamping() const
	{
		return mActor->getAngularDamping();
	}

//////////////////////////////////////////////////////////

	void Actor::setLinearVelocity(const Ogre::Vector3& vec)
	{
		mActor->setLinearVelocity(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::setAngularVelocity(const Ogre::Vector3& vec)
	{
		mActor->setAngularVelocity(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////


	Ogre::Vector3 Actor::getLinearVelocity()    const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getLinearVelocity());
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getAngularVelocity() const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getAngularVelocity());
	}

//////////////////////////////////////////////////////////


	void Actor::setMaxAngularVelocity(NxReal r)
	{
		mActor->setMaxAngularVelocity(r);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getMaxAngularVelocity()   const
	{
		return mActor->getMaxAngularVelocity();
	}

//////////////////////////////////////////////////////////

	void Actor::setCCDMotionThreshold(NxReal r)
	{
		mActor->setCCDMotionThreshold(r);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getCCDMotionThreshold()   const
	{
		return mActor->getCCDMotionThreshold();
	}

//////////////////////////////////////////////////////////

	void Actor::setLinearMomentum(const Ogre::Vector3& vec)
	{
		mActor->setLinearMomentum(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	void Actor::setAngularMomentum(const Ogre::Vector3& vec)
	{
		mActor->setAngularMomentum(NxConvert<NxVec3, Ogre::Vector3>(vec));
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getLinearMomentum()        const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getLinearMomentum());
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getAngularMomentum()   const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getAngularMomentum());
	}

//////////////////////////////////////////////////////////

	void Actor::addForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		mActor->addForceAtPos(NxConvert<NxVec3, Ogre::Vector3>(force), NxConvert<NxVec3, Ogre::Vector3>(pos), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		mActor->addForceAtLocalPos(NxConvert<NxVec3, Ogre::Vector3>(force), NxConvert<NxVec3, Ogre::Vector3>(pos), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addLocalForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		mActor->addLocalForceAtPos(NxConvert<NxVec3, Ogre::Vector3>(force), NxConvert<NxVec3, Ogre::Vector3>(pos), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addLocalForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		mActor->addLocalForceAtLocalPos(NxConvert<NxVec3, Ogre::Vector3>(force), NxConvert<NxVec3, Ogre::Vector3>(pos), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addForce(const Ogre::Vector3& force, NxForceMode mode, bool wakeup)
	{
		mActor->addForce(NxConvert<NxVec3, Ogre::Vector3>(force), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addForce(const NxVec3& force, NxForceMode mode, bool wakeup)
	{
		mActor->addForce(force, mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addForce(NxReal x, NxReal y, NxReal z, NxForceMode mode, bool wakeup)
	{
		mActor->addForce(NxVec3(x, y, z), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addLocalForce(const Ogre::Vector3& force, NxForceMode mode, bool wakeup)
	{
		mActor->addLocalForce(NxConvert<NxVec3, Ogre::Vector3>(force), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addTorque(const NxVec3& torque, NxForceMode mode, bool wakeup)
	{
		mActor->addTorque(torque, mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addTorque(const Ogre::Vector3& torque, NxForceMode mode, bool wakeup)
	{
		mActor->addTorque(NxConvert<NxVec3, Ogre::Vector3>(torque), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	void Actor::addLocalTorque(const Ogre::Vector3& torque, NxForceMode mode, bool wakeup)
	{
		mActor->addLocalTorque(NxConvert<NxVec3, Ogre::Vector3>(torque), mode, wakeup);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::computeKineticEnergy() const
	{
		return mActor->computeKineticEnergy();
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getPointVelocity(const Ogre::Vector3& vec) const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getPointVelocity(NxConvert<NxVec3, Ogre::Vector3>(vec)));
	}

//////////////////////////////////////////////////////////

	Ogre::Vector3 Actor::getLocalPointVelocity(const Ogre::Vector3& vec) const
	{
		return NxConvert<Ogre::Vector3, NxVec3>(mActor->getLocalPointVelocity(NxConvert<NxVec3, Ogre::Vector3>(vec)));
	}

//////////////////////////////////////////////////////////

	bool Actor::isGroupSleeping() const
	{
		return mActor->isGroupSleeping();
	}

//////////////////////////////////////////////////////////

	bool Actor::isSleeping() const
	{
		return mActor->isSleeping();
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getSleepLinearVelocity() const
	{
		return mActor->getSleepLinearVelocity();
	}

//////////////////////////////////////////////////////////

	void Actor::setSleepLinearVelocity(NxReal threshold)
	{
		mActor->setSleepLinearVelocity(threshold);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getSleepAngularVelocity() const
	{
		return mActor->getSleepAngularVelocity();
	}

//////////////////////////////////////////////////////////

	void Actor::setSleepAngularVelocity(NxReal threshold)
	{
		mActor->setSleepAngularVelocity(threshold);
	}

//////////////////////////////////////////////////////////

	NxReal Actor::getSleepEnergyThreshold() const
	{
		return mActor->getSleepEnergyThreshold();
	}

//////////////////////////////////////////////////////////

	void Actor::setSleepEnergyThreshold(NxReal threshold)
	{
		mActor->setSleepEnergyThreshold(threshold);
	}

//////////////////////////////////////////////////////////

	void Actor::wakeUp(NxReal wakeCounterValue)
	{
		mActor->wakeUp(wakeCounterValue);
	}

//////////////////////////////////////////////////////////

	void Actor::putToSleep()
	{
		mActor->putToSleep();
	}

//////////////////////////////////////////////////////////

	void Actor::raiseBodyFlag(NxBodyFlag f)
	{
		mActor->raiseBodyFlag(f);
	}

//////////////////////////////////////////////////////////

	void Actor::clearBodyFlag(NxBodyFlag f)
	{
		mActor->clearBodyFlag(f);
	}

//////////////////////////////////////////////////////////

	bool Actor::hasBodyFlag(NxBodyFlag f) const
	{
		return mActor->readBodyFlag(f);
	}

//////////////////////////////////////////////////////////

	void Actor::setSolverIterationCount(NxU32 c)
	{
		mActor->setSolverIterationCount(c);
	}

//////////////////////////////////////////////////////////

	NxU32 Actor::getSolverIterationCount() const
	{
		return mActor->getSolverIterationCount();
	}

//////////////////////////////////////////////////////////

#if NX_SUPPORT_SWEEP_API

	NxU32 Actor::linearSweep(const Ogre::Vector3& motion, NxU32 flags, void* VoidPointer, NxU32 nbShapeDescriptions, NxSweepQueryHit* shapes, NxUserEntityReport<NxSweepQueryHit>* callback, const NxSweepCache* sweepCache)
	{
		return mActor->linearSweep(NxConvert<NxVec3, Ogre::Vector3>(motion), flags, VoidPointer, nbShapeDescriptions, shapes, callback, sweepCache);
	}

#endif

//////////////////////////////////////////////////////////

#if NX_SDK_VERSION_NUMBER >= 260

	Compartment* Actor::getCompartment() const
	{
		NxUnderConstruction;
		return NULL;
	}

#endif

//////////////////////////////////////////////////////////

	Shape* Actor::addShape(Shape* shape)
	{
		shape->createShape(mActor, mCollisionModel.Size() - 1, mOwner);
		mCollisionModel.Insert(shape);
		return shape;
	}

//////////////////////////////////////////////////////////

	bool Actor::removeShape(Shape* shape)
	{

		if (mCollisionModel.Size() == 1 || mActor->getNbShapes() == 1)
		{
			return false;
		}

		if (!mCollisionModel.Has(shape))
		{
			return false;
		}

		mActor->releaseShape(*shape->getNxShape());

		unsigned int position = mCollisionModel.WhereIs(shape);
		mCollisionModel.Destroy(position);

		return true;
	}

//////////////////////////////////////////////////////////

	bool Actor::removeShape(NxShapeIndex id)
	{

		if (mCollisionModel.Size() == 1 || mActor->getNbShapes() == 1 || id > mActor->getNbShapes())
		{
			return false;
		}

		Shape* shape = mCollisionModel[id];

		mActor->releaseShape(*shape->getNxShape());

		unsigned int position = mCollisionModel.WhereIs(shape);
		mCollisionModel.Destroy(position);

		return true;
	}

//////////////////////////////////////////////////////////

	NxU32 Actor::getNbShapes() const
	{
		return mCollisionModel.Size();
	}

//////////////////////////////////////////////////////////

	Actor::CollisionModel Actor::getCollisionModel()
	{
		return mCollisionModel;
	}

//////////////////////////////////////////////////////////

	void* Actor::getVoidPointer()
	{
		return mActor->userData;
	}

//////////////////////////////////////////////////////////

	VoidPointer* Actor::getUserData()
	{
		return mVoidPointer;
	}

//////////////////////////////////////////////////////////

	StringPairList Actor::saveCustom()
	{
		StringPairList l;
		l.insert("ActorType", "Actor");

		return l;
	}

//////////////////////////////////////////////////////////

	void Actor::disable()
	{

		mActor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
		mActor->raiseActorFlag(NX_AF_DISABLE_RESPONSE);
		mActor->raiseActorFlag(NX_AF_FLUID_DISABLE_COLLISION);
		mActor->raiseBodyFlag(NX_BF_FROZEN);
		mActor->raiseBodyFlag(NX_BF_FROZEN_ROT);
		mActor->setAngularVelocity(NxVec3(0, 0, 0));
		mActor->setAngularMomentum(NxVec3(0, 0, 0));
		mActor->setLinearMomentum(NxVec3(0, 0, 0));
		mActor->setLinearVelocity(NxVec3(0, 0, 0));

	}

//////////////////////////////////////////////////////////

	FixedJoint* Actor::joinWith(Actor* actorB, JointParams jp)
	{
		return mOwner->createFixedJoint(this, actorB, jp);
	}

//////////////////////////////////////////////////////////

}  //End of NxOgre namespace.
