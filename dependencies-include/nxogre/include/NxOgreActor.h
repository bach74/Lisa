/** \file    NxOgreActor.h
 *  \brief   Header for the ActorParams and Actor classes.
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

#ifndef __NXOGRE_ACTOR_H__
#define __NXOGRE_ACTOR_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"		// For: mCollisionList
#include "NxOgreParams.h"
#include "NxOgrePose.h"
#include "BetajaenCC.h"
#include "NxOgreShape.h"			// For: SharedList<Shape>

namespace NxOgre {

	/**	\page actorparams ActorParams
		
		String base params are case and space insensitive.

		Examples:
		
		<code>
			"mass: 1"
			"mass: 1, group: myActors"
			"mass: 1, group: myActors, lineardamping: 3"
		</code>

		Non-String based params can be used as well, and offer access to some variables of the params
		that cannot be converted into a string (pointers, etc.). 

		Due to efficency purposes and insane string conversion. With string parameters more than four, 
		you should work with the non-string based params system. 

		<code>
			ActorParams params;
			params.setToDefault();
			params.mMass = 10;
			params.mGroupAsIndex = 1;
		</code>

		Is exactly the same as:

		<code>
			"mass: 10, group-index: 1"
		</code>
		
		Current Supported String Params
		-----------------------------
		

		-	group	(string)
			- Description: Actor Group name of this actor. Use this or group-index, but not both.
			- Example: "group: myGroup"
	 		- See: ActorParams::mGroupAsName
	 	
	 	-	group-index	(unsigned int)
	 		- Description: Actor Group ID of this actor. Use this or group, but not both.
	 		- Example: "group-index: 0"
	 		- See: ActorParams::mGroupAsIndex
	 	
	 	-	dominancegroup (unsigned int)
	 		- Description: Dominance Group ID of this actor.
	 		- Example:	"dominancegroup: 0"
	 		- See:	ActorParams::mDominanceGroup
	 	
	 	-	massspaceinertia (Vector3)
	 	 	- Description: Mass Space Inertia of this Actor
	 	 	- Example: "massspaceinertia: 1 0 1"
	 	 	- See:	ActorParams::mMassSpaceInertia
	 	 
	 	-	linearvelocity (Vector3)
	 	 	- Description: Linear Velocity of this Actor
	 	 	- Example: "linearvelocity: 1 0 1"
	 	 	- See:	ActorParams::mLinearVelocity
	 	 	
	 	-	angularvelocity (Vector3)
	 	 	- Description: Angular Velocity of this Actor
	 	 	- Example: "angularvelocity: 1 0 1"
	 	 	- See:	ActorParams::mAngularVelocity
	 	 	
	 	-	wakeupcounter (float)
	 	 	- Description: Wake up time counter
	 	 	- Example: "wakeupcounter: 1000.0"
	 	 	- See:	ActorParams::mWakeupCounter
	 	 		
		-	mass (float)
			- Description: Mass of this Actor. Use this or density, do not use both. 
			- Example: "mass: 10"	
			- See: ActorParams::mMass and NxBodyDesc::mass for more information.
			
		-	lineardamping (float)
			- Description: Linear Damping of the Actor
			- Example: "lineardamping: 0.1"
			- See:	ActorParams::mLinearDamping
		
		-	angulardamping (float)
			- Description: Angular Damping of the Actor
			- Example: "angulardamping: 0.1"
			- See:	ActorParams::mAngularDamping
				
		-	maxangularvelocity (float)
			- Description: Maximum allowed angular velocity
			- Example: "maxangularvelocity: 10"
			- See:	ActorParams::mMaxAngularVelocity
				
		-	sleepangularvelocity (float)
			- Description: Maximum angular velocity at which the Actor can go to sleep. 
			- Example: "sleepangularvelocity: 20"
			- See:	ActorParams:mSleepAngularVelocity
				
		-	ccdmotionthreshold (float)
			- Description: When CCD is globally enabled, it is still not performed if the 
						   motion distance of all points on the Actor is below this threshold. 
			- Example: "ccdmotionthreshold: 5"
			- See:	ActorParams::mCCDMotionThreshold
				
		-	solveriterationcount (unsigned int)
			- Description:   Number of solver iterations performed when processing joint/contacts
							 connected to this Actor.
			- Example: "solveriterationcount: 5"
			- Range: 1 to 255
			- See: ActorParams::mSolverIterationCount
		
		-	sleepenergytheshold (float) 
			- Description:	Threshold for the energy-based sleeping algorithm. Only used when
							the NX_BF_ENERGY_SLEEP_TEST flag is set
 			- Example: "sleepenergythreshold: 0.006"
 			- See: ActorParams::mSleepEnergyThreshold
 		
 		-	sleepdamping (float)
			- Description:	Damping factor for bodies that are about to sleep. 
			- Example: "sleepdamping: 0.5"
			- See: ActorParams::mSleepDamping
		
		-	node-scale (Vector3)
			- Applicable to Body and Actors that use a visual representation of the NxActor.
			- Description: Scale factor of the SceneNode
			- Example: "node-slace: 2 2 2"
			- See: ActorParams::mNodeScale
		
		-	node-shadows (bool)
			- Applicable to Body and Actors that use a visual representation of the NxActor.
			- Description: Apply shadows to the first entity (Body class). See other custom Actors
						   to see how shadows apply to it.
			- Example: "node-shadows: yes"
			- See: ActorParams::mNodeShaodws
				
		-	node (string)
			- Applicable to Body and Actors that use a visual representation of the NxActor.
			- Description: Name of the SceneNode, or name of an existing SceneNode to use (Body only).
			- Example: "node: myNodeName"			
			- See: ActorParams::mNodeName
						
	*/
	

	/** ActorParams

		\see \ref actorparams for the full string argument documentation.
	*/		
	class NxPublicClass ActorParams : public Params {

		public:

			/** \brief Class based params.
				\note Faster, less readable and reusable.
				\see \ref actorparams
				\example
				<code>
					ActorParams ap;
					ap.mMass = 10;
					ap.mGroup = "myGroup";
					..., ap, ...
				</code>

			*/
			ActorParams()  {
			                setToDefault();
			               }

			/** \brief String based params. "mass: 10, group: myGroup"
				\note Slower but readable.
				\params String of params.
				\see \ref actorparams
				\example
				<code>
					..., "mass: 10, group: myGroup", ...
				</code>
			*/
			ActorParams(const char* p)  {
			                             process(p);
			                            }

			/** \brief String based params. "mass: 10, group: myGroup"
				\note Slower but readable.
				\params 
				\see \ref actorparams
				\example
				<code>
					..., "mass: 10, group: myGroup", ...
				</code>
			*/
			ActorParams(NxString p)  {
			                          process(p);
			                         }

			/** \brief Set's the Params to default based on NxActorDesc and NxBodyDesc defaults.
			*/
			void  setToDefault();

			/** \brief Set's the Params based from an NxActorDesc
			*/
			void  fromNxActorDesc(NxActorDesc&);

			/** \brief Set's the Params based from a NxBodyDesc
			*/
			void  fromNxBodyDesc(NxBodyDesc&);

			////////////////////////////////////////////////////////////////

#if NX_SDK_VERSION_NUMBER >= 260
			
			/** \brief Compartment.
				\default NULL
				\example
					C++     ->  mActorParams.mCompartment = CompartmentPtr;
					String  ->  N/A
				\see NxActorDesc::compartment for more information.
			*/
			NxCompartment*  mCompartment;

#endif

			/** \brief Density (mass calculated by volume).
				\default 0
				\example
					C++     ->  mActorParams.density = 10.0f;
					String  ->  "density: 10"
				\note
					Due how PhysX works then the mass of the Actor must be zero, else
					it uses Mass instead. If you wish to make the Actor static then both
					the density and the mass of the actor must be zero, or if you use
					string params then "static: yes" is equilvent to "mass: 0, density: 0".
				\see NxActorDesc::density for more information.
				\see ActorParams::mMass
			*/
			NxReal  mDensity;
			
#if NX_SDK_VERSION_NUMBER >= 272 

			/** \brief DominanceGroup (as Name).
			    \default "" (Resorts to dominance group with identifier "Default")
			*/
			NxString  mDominanceGroupAsName;

			/** \brief DominanceGroup (as Index)
				\default 0
			*/
			NxDominanceGroup  mDominanceGroupAsIndex;

#endif

			/** \brief Flags of the Actor.
				\default 0
				\example
					C++     ->  mActorParams.mActorFlags = NX_AF_DISABLE_COLLISION | NX_AF_DISABLE_RESPONSE;
					String  ->  N/A
				\see NxActorDesc::flags for more information.
				\see NxActorFlag enum.
			*/
			NxU32  mActorFlags;


			// TODO: Turn these to DualIdentifier
			NxActorGroup  mGroupAsIndex;
			NxString  mGroupAsName;


			/** \brief Angular Damping.
				\default 0.05f;
				\example
					C++     ->  mActorParams.mAngularDamping = 1.0f;
					String  ->  "angulardamping: 1"
				\see NxActorDesc::angular for more information.
			*/
			NxReal  mAngularDamping;


			/** \brief Angular Damping.
				\default 0
				\example
					C++     ->  mActorParams.mAngularDamping = 1.0f;
					String  ->  "angulardamping: 1 1 1"
				\see NxActorDesc::density for more information.
				\see ActorParams::mMass
			*/
			NxVec3  mAngularVelocity;


			/** \brief CCD Motion Threshold
			*/
			NxReal  mCCDMotionThreshold;


			/** \brief Flags for the Body portion of an Actor, assuming it is dynamic.
				\see NxBodyDesc
			*/
			NxU32  mBodyFlags;


			/** \brief Linear Damping of the Actor
			*/
			NxReal  mLinearDamping;


			/** \brief Initial linear velocity of the actor
			*/
			NxVec3  mLinearVelocity;


			/** \brief Mass of the Actor.
				\note When used, make sure density is zero.
				\default 10
			*/
			NxReal  mMass;


			/** \brief Mass Local Pose of the body portion of the Actor
				\default NxMatrix34.id()
			*/
			NxMat34  mMassLocalPose;


			/** \brief Mass Space Inertia of the body portion of the Actor
			*/
			NxVec3  mMassSpaceInertia;


			/** \brief Maximum angular velocity of the Actor
			*/
			NxReal  mMaxAngularVelocity;
			
			/** \brief I forget.
			*/
			NxReal  mSleepAngularVelocity;


			/** \brief
			*/
			NxReal  mSleepDamping;


			/** \brief
			*/
			NxReal				mSleepEnergyThreshold;


			/** \brief
			*/
			NxReal				mSleepLinearVelocity;


			/** \brief
			*/
			NxU32				mSolverIterationCount;


			/** \brief
			*/
			NxReal				mWakeUpCounter;


			private:


			/** \internal
			*/
			void  parse(Parameters);

	}; // End of ActorParams class

	/** \brief An Actor is a single unit of matter in the Scene.
		  It is physically represented by a "Collision Model" or a shape. If the actor
		  has some mass then it is known as a Dynamic Actor, capable of scurrying around
		  in the Scene. If the Actor has no mass then it is a static actor which never
		  ever moves.

		 \note
		  By default the Actor class has no form of visualisation it is completely
		  invisible. If your looking for a Actor class that does require visualisation
		  then you can use the Body class, or your own.

	*/
	class NxPublicClass Actor {

		public:

			/** \brief Main actor constructor. 
				\note  For many purposes, Actors must be created through its parent's
				       createActor function.
				\param Identifier     Unique identifier of the Actor.
				\param Scene          Parent scene to use.
				\param Shape          Shape/Collision Model of the actor
				\param Pose           First pose of the Actor
				\param ActorParams    Additional creation information wrapped in a ActorParams class.
			*/
			Actor(const NxString& Identifier, Scene*, Shape*, const Pose&, const ActorParams& = ActorParams());

			/** \brief Pretty much obvious Actor destructor
			*/
			virtual ~Actor();

		protected:

			/** \brief Constructor that must be used for inherited actors only.
			*/
			Actor(const NxString& Identifier, Scene*, bool isActorBased = true);

		public:

			/** \brief A list of Shapes used in an Actor
			*/
			typedef Betajaen::SharedList<Shape>		CollisionModel;

		public:

			Scene* getScene()  {
			                     return mOwner;
			                    }

			/** \brief Get's a copy of the NxScene pointer that Scene represents.
			*/
			NxScene* getNxScene();

			/** \brief Unique Hash of this class as a string (using getStringType)
			*/
			virtual NxShortHashIdentifier getType() const {
			  return NxOgreClass_Actor; /* "NxOgre-Actor" */
			}

			/** \brief Unique class identifier.
			*/
			virtual NxString getStringType() const {
			  return "NxOgre-Actor";
			}

			/** \brief Is the actor dead, usually if the NxActor is missing or null. But this 
					   "deadness" is can be specified by the inherited actor.
			*/
			virtual bool isDead() const {
			  return (mActor == NULL);
			}

			/** \brief Duplicate this actor
				\param	name	Name of the new Actor
				\param	pose	Position/Orientation of the new actor.
				\note
				  This function is rather slow and inefficent when used repeatedly. Use a
				  ActorBlueprint instead to keep a single blueprint of the actor and create
				  as many as you want from that.
			 */
			Actor* duplicate(const NxString& name, const Pose& p);


			/** \internal
				\brief Creates the NxActor. Must be used by inherited actors in their constructor
				       or create method.
			*/
			void _createActor(Shape*, const Pose&,ActorParams params);
			
			/** \internal
				\brief Destroys the NxActor. Must be used by interited actors in their destructor
				       or destroy method.
			*/
			void _destroyActor();

			/** \brief Get's a copy of the NxActor which this Actor is representing.
			*/
			NxActor* getNxActor() {
			                        return mActor;
			                       }

			/** \brief Renames this Actor to something else, it also updates the container
			           in Scene parent mScene container.
			*/
			void setName(NxString);

			/** \brief Get's the name of this Actor
			*/
			NxString getName() const;

			/** \brief Set's the pose of the actor in the global frame.
			*/
			void setGlobalPose(const Pose&);
			
			/** \brief Get's the pose fo the actor from the global frame.
			*/
			Pose getGlobalPose() const;

#if (NX_USE_OGRE == 1)
			/** \brief Get's the orientiation only of this actor as a Ogre quaternion.
				\note Ogre::Quaternion's w, x, y, z represent w, x, y, z in order given.
			*/
			Ogre::Quaternion  getGlobalOrientationAsOgreQuaternion() const;

			/** \brief Set's the orientation of this actor from a Ogre quaternion.
			*/
			void setGlobalOrientation(const Ogre::Quaternion&);

			/** \brief Get's the global position only of this actor as a Ogre Vector3
			*/
			Ogre::Vector3  getGlobalPositionAsOgreVector3() const;

			/** \brief Set's the global position only of this actor from a Ogre Vector3
			*/
			void setGlobalPosition(const Ogre::Vector3&);
#endif

			/** \brief Get's the orientation only of this actor as a 3x3 matrix placed
				into a NxMat33 class.
			*/
			NxMat33 getGlobalOrientation() const;

			/** \brief Set's the orientation only of this actor as a 3x3 matrix placed
				into a NxMat33 class.
			*/
			void setGlobalOrientation(const NxMat33& matrix);

			/** \brief Get's the orientation only of this actor as a quaternion placed
				inside a float4 vector.

				\note float4's i, j, k, l represent w, x, y, z in order given.
			*/
			float4 getGlobalOrientationAsFloat4() const;

			/** \brief Set's the orientation only of this actor as a quaternion placed
				inside a float4 vector.

				\note float4's i, j, k, l represent w, x, y, z in order given.
			*/
			void setGlobalOrientation(const float4& quaternion);

			/** \brief Get's the global position only of this Actor as a float3
				\note  float3's i, j, k represent x, y, z in order given.
			*/
			float3 getGlobalPositionAsFloat3() const;

			/** \brief Set's the global position only of this Actor as a float3
				\note  float3's i, j, k represent x, y, z in order given.
			*/
			void setGlobalPosition(const float3& vector);


			/** \brief Get's the orientation only of this actor as a quaternion placed
				inside a NxQuat.
				\note NxQuat's w, x, y, z represent w, x, y, z in order given.
			*/
			NxQuat getGlobalOrientationAsNxQuat() const;


			/** \brief Set's the orientation only of this actor as a quaternion placed
				inside a NxQuat.
				\note NxQuat's w, x, y, z represent w, x, y, z in order given.
			*/
			void setGlobalOrientation(const NxQuat& quaternion);

			/** \brief Get's the global position only of this Actor as a NxVec3
			*/
			NxVec3 getGlobalPositionAsNxVec3() const;

			/** \brief Set's the global position only of this Actor as a float3
			*/
			void setGlobalPosition(const NxVec3& vector);

			/** \brief 
			*/
			void moveGlobalPose(const Pose&);
			
			/** \brief
			*/
			void moveGlobalPosition(const Ogre::Vector3&);
			
			/** \brief
			*/
			void moveGlobalOrientation(const Ogre::Quaternion&);

			/** \brief Calculates a rough force and applies it to this actor towards a 
			           specific point in global space.
			    \param Pose  The point in space to move towards too.
			    \param Force The "oomph" to move it.
			*/
			void moveTowards(const Pose&, float force = 10.0f);


			/** \brief Add a shape to this Actor.
			*/
			Shape* addShape(Shape*);

			/** \brief Remove a shape from this Actor.
				\note Removing the last shape from this actor will cause PhysX to go boom.
			*/
			bool removeShape(Shape*);
			
			/** \brief Remove a shape from this Actor.
				\note Removing the last shape from this actor will cause PhysX to go boom.
			*/
			bool removeShape(NxShapeIndex);
			
			/** \brief Returns the number of shapes used with this Actor
			*/
			NxU32 getNbShapes() const;

			/** \brief Get's a copy of the container of the pointer of Shapes that are
			           used with this Actor
			*/
			CollisionModel getCollisionModel();

			/** \brief Set's this Actor to another ActorGroup.
			*/
			void setGroup(ActorGroup*);

			/** \brief Set's this Actor to another ActorGroup.
			*/
			void setGroup(const NxString& GroupIdentifier);
			
			
			/** \brief Set's this Actor to another ActorGroup.
			*/
			void setGroup(NxActorGroup);
			
			/** \brief Get's a copy of the ActorGroup that this Actor is under.
			*/
			ActorGroup* getGroup() const;

			/** \brief
			*/
			void raiseActorFlag(NxActorFlag);
			
			/** \brief
			*/
			void clearActorFlag(NxActorFlag);
			
			/** \brief
			*/
			bool hasActorFlag(NxActorFlag) const;
			
			/** \brief Does the Actor have any mass, hence movable and reacts to forces.
			*/
			bool isDynamic() const;

			void setCMassOffsetLocalPose(const Pose&);
			void setCMassOffsetLocalPosition(const Ogre::Vector3&);
			void setCMassOffsetLocalOrientation(const NxMat33&);
			void setCMassOffsetLocalOrientation(const Ogre::Matrix3&);
			void setCMassOffsetGlobalPose(const Pose&);
			void setCMassOffsetGlobalPosition(const Ogre::Vector3&);
			void setCMassOffsetGlobalOrientation(const NxMat33&);
			void setCMassOffsetGlobalOrientation(const Ogre::Matrix3&);
			void setCMassGlobalPose(const Pose&);
			void setCMassGlobalPosition(const Ogre::Vector3&);
			void setCMassGlobalOrientation(const Ogre::Quaternion&);

			Pose							getCMassLocalPose()	const;
			Ogre::Vector3 					getCMassLocalPosition()	const;
			Ogre::Quaternion 				getCMassLocalOrientation() const;
			Pose							getCMassGlobalPose() const;
			Ogre::Vector3 					getCMassGlobalPosition() const;
			Ogre::Quaternion				getCMassGlobalOrientation()	const;

			//////////////////////////////////////////////////////////

			void							setMass(NxReal);
			NxReal							getMass() const;

			void							setMassSpaceInertiaTensor(const Ogre::Vector3&);
			Ogre::Vector3					getMassSpaceInertiaTensor()	const;
			Ogre::Matrix3					getGlobalInertiaTensor() const;
			Ogre::Matrix3					getGlobalInertiaTensorInverse()	const;

			void							updateMassFromShapeFromDensity(NxReal);
			void							updateMassFromShapeAsMass(NxReal);

			//////////////////////////////////////////////////////////

			void							setLinearDamping(NxReal);
			NxReal							getLinearDamping() const;

			void							setAngularDamping(NxReal);
			NxReal							getAngularDamping() const;

			//////////////////////////////////////////////////////////

			void							setLinearVelocity(const Ogre::Vector3&);
			void							setAngularVelocity(const Ogre::Vector3&);

			Ogre::Vector3					getLinearVelocity()	const;
			Ogre::Vector3					getAngularVelocity() const;

			void							setMaxAngularVelocity(NxReal);
			NxReal							getMaxAngularVelocity()	const;


			//////////////////////////////////////////////////////////

			void							setCCDMotionThreshold(NxReal);
			NxReal							getCCDMotionThreshold()	const;

			//////////////////////////////////////////////////////////

			void							setLinearMomentum(const Ogre::Vector3&);
			void							setAngularMomentum(const Ogre::Vector3&);
			Ogre::Vector3					getLinearMomentum() const;
			Ogre::Vector3					getAngularMomentum() const;

			//////////////////////////////////////////////////////////

			void							addForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			

			void							addForce(const Ogre::Vector3& force, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addForce(const NxVec3& force, NxForceMode = NX_FORCE, bool wakeup = true);
			void							addForce(NxReal x, NxReal y, NxReal z, NxForceMode = NX_FORCE, bool wakeup = true);
			void							addLocalForce(const Ogre::Vector3& force, NxForceMode mode = NX_FORCE, bool wakeup = true);
			
			void							addTorque(NxReal x, NxReal y, NxReal z, NxForceMode mode = NX_FORCE, bool wakeup = true) {
				addTorque(NxVec3(x,y,z), mode, wakeup);
			}
			void							addTorque(const NxVec3& torque, NxForceMode mode = NX_FORCE, bool wakeup = true); 
			void							addTorque(const Ogre::Vector3& torque, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalTorque(const Ogre::Vector3& torque, NxForceMode mode = NX_FORCE, bool wakeup = true);
			NxReal							computeKineticEnergy() const;

			//////////////////////////////////////////////////////////

			Ogre::Vector3					getPointVelocity(const Ogre::Vector3& point) const;
			Ogre::Vector3					getLocalPointVelocity(const Ogre::Vector3& point) const;

			//////////////////////////////////////////////////////////

			bool							isGroupSleeping() const;
			bool							isSleeping() const;
    		NxReal							getSleepLinearVelocity() const;
    		void							setSleepLinearVelocity(NxReal threshold);
    		NxReal							getSleepAngularVelocity() const;
    		void							setSleepAngularVelocity(NxReal threshold);
			NxReal							getSleepEnergyThreshold() const;
			void							setSleepEnergyThreshold(NxReal threshold);
			void							wakeUp(NxReal wakeCounterValue=NX_SLEEP_INTERVAL);
			void							putToSleep();

			//////////////////////////////////////////////////////////

			void							raiseBodyFlag(NxBodyFlag);
			void							clearBodyFlag(NxBodyFlag);
			bool							hasBodyFlag(NxBodyFlag) const;
			void							setSolverIterationCount(NxU32);
			NxU32							getSolverIterationCount() const;

			//////////////////////////////////////////////////////////

#if NX_SUPPORT_SWEEP_API
			NxU32							linearSweep(const Ogre::Vector3& motion, NxU32 flags, void* VoidPointer, NxU32 nbShapeDescriptions, NxSweepQueryHit* ShapeDescriptions, NxUserEntityReport<NxSweepQueryHit>* callback, const NxSweepCache* sweepCache=NULL);
#endif

			//////////////////////////////////////////////////////////
#if NX_SDK_VERSION_NUMBER >= 260
			Compartment*					getCompartment() const;
#endif
			//////////////////////////////////////////////////////////

			CollisionModel					mCollisionModel;

			void*							getVoidPointer();
			VoidPointer*						getUserData();

			/** joinWith

				Creates a fixedJoint with this actor and the referenced actor.

			*/
			FixedJoint*						joinWith(Actor*, JointParams);

			/** Disable

				Nearly kills the actor in the Scene. Disables collision, movement,
				rotation, reporting. If the Actor is subclassed the visualisation
				will be removed (or hidden). This is best used with a batch
				delete of Actors (just before a batch deletion is done) to hide
				the Actor from the screen, and just before it is deleted.

				If you want to undisable this actor, you will need to loose the 
				NX_AF_DISABLE_COLLISION, NX_AF_COLLISION_RESPONSE, NX_BF_FROZEN,
				flags. See the code in disable for more details.

			*/
			void							disable();
			NxU32							getBirthFrame() {return mBirthFrame;}

			//////////////////////////////////////////////////////////

			virtual StringPairList			saveCustom();
			virtual void					restoreCustom(StringPairList)	{}

		protected:

			Scene						   *mOwner;
			NxActor*						mActor;
			NxString						mName;
			VoidPointer*					mVoidPointer;
			NxU32							mBirthFrame;
			
		private:


	};// End of Actor Class


	/**
		
		\page customactors Custom Actors

	Using your own Actor class with NxOgre:

	The Header of "IActor", the inherited Actor.

	<code>
	class NxPublicClass IActor : public Actor {

		public:

			// Constructors similar to. Used for creating a NxActor by hand through a blueprint,
			// or the NxuStream tool
			IActor(const NxString& name, Scene*);

			// Constructors similar to. Normal Everyday Constructor.
			// Name, Scene, ShapeBlueprint, Pose, ActorParams are required by Actor, so they
			// must be part of your constructor.
			IActor(const NxString& name, Scene*, ShapeBlueprint*, const Pose&, ActorParams = "");
			
			// Destructor.
			virtual ~IActor();

			// Your IActor may have some visualisation.
			virtual bool			hasVisualisation() const	{return true;}
	
			// to call ShapeSimulate
			void					simulate(float);

			// to call ShapeRender, and to render your visualisation.
			void					render(float);

			// Save any custom data related to your Inherited Actor to a StringPairList
			StringPairList			saveCustom();

			// Restore any custom data to your Inherited Actor.
			void					restoreCustom(StringPairList);

			// Disable Visualisation, for when it is "disabled". This hides things, it does not delete things.
			void					disableVisualisation();

	};
	</code>


	The code side of the IActor:

	<code>
	IActor::IActor(const NxString& name, Scene* scene) : Actor(name, scene) {
		// Do nothing. Not even your own visualisation. RestoreCustom will kick in soon to handle that.
	}

	IActor::IActor(const NxString& identifier, Scene* scene, ShapeBlueprint *firstShapeDescription, const Pose& pose, ActorParams params)
	: Actor(identifier, scene, firstShapeDescription, pose, params) {
		// Identifier, Scene, firstShapeDescription,  pose, params are all required by Actor. 
		// So they should be part of your constructor.

		// Setup visualisation stuff here.
		//  You can access the SceneManager from mOwner->getSceneMgr()
	}

	IActor::~IActor {
		// Clean up your visualisation here. The destructor in Actor will clean up the NxActor stuff.
	}


	void IActor::simulate(float dT) {
		// Required...
		if (mActor) {
			shapeSimulate(dT);
		}
	}

	void IActor::render(float dT) {
		// You can get the Position and Orientation of the NxActor using:
		//	getGlobalPosition();
		//  getGlobalOrientation();
		//
		// If you have NX_UNSTABLE_USE_SCENE_ACTIVE_TRANSFORM on, render will only be called
		// if the NxActor has moved.
	}


	StringPairList IActor::saveCustom() {

		// Required...
		StringPairList l;
		l.insert("ActorType", "IActor"); // IActor or the name of your class; *Not* Actor or Body.
		l.insert("Key", "Value");
		// You can have multiple keys with the same name.
	}

	void IActor::restoreCustom(StringPairList spl) {
		
		for (StringPairList::StringPair sp = spl.begin();spl.hasNext();) {
			sp = spl.next();

			NxString key = sp.first;
			NxString value = sp.second;
			Ogre::StringUtil::toLowerCase(key);

			if (key == "x") {
				mY = value;
			}
	}

	void IActor::disableVisualisation() {
		if (mNode->getParent() != NULL) {
			mNode->getParent()->removeChild(mNode);
		}
	}

	</code>

	/////////////////////////////////////////////////////////////////

	Using a NxOgre Container to store your IActor.

	<code>
	class SomeGameManagerClass {
		
		typedef NxOgre::Container<NxString, IActor*> IActors;

		IActors mActors;

	};
	</code>

	/////////////////////////////////////////////////////////////////

	Creating an IActor and storing the pointer.
	
	<code>
	IActor* iactor = new IActor("name", mScene, new CubeShape(1), Vector3::ZERO, "mass: 10");
	mIActors.insert(iactor->getName(), iactor);
	// A copy of the IActor has been placed in mScene::mActors. NxOgre does not "own" the class
	// we do. So we are responsible for deleting it.
	
	// To own the IActor, we must "lock" it.
	IActors.lock(iactor->getName(), true);
	</code>

	//////////////////////////////////////////////////////////////////

	When the time is right, we must delete the IActor before the destruction of the Scene.

	Either:
	<code>
			mIActors.destroyAllOwned();
			mWorld->destroyScene(mScene->getName());
	</code>		
		or:
	<code>
			mIActors.destroyAllOwned();
			delete mWorld;
	</code>
	//////////////////////////////////////////////////////////////////

	*/

};// End of namespace

#endif
