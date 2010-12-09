/** \file    NxOgrePhysXDriver.h
 *  \brief   Header for the PhysXDriver and PhysXParams classes.
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

#ifndef __NXOGRE_PHYSXDRIVER_H__
#define __NXOGRE_PHYSXDRIVER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"
#include "OgreFrameListener.h"

namespace NxOgre {

	/**
		\page physxparams PhysXParams

		String base params are case and space insensitive.

		Examples:
		<code>
			"floor: yes"
			"floor: yes, gravity: 0 -9 0"
			"floor: yes, gravity: 0 -9 0, material-restitution: 0.9"
		</code>

		Non-String based params can be used as well, and offer access to some variables of the params
		that cannot be converted into a string (pointers, etc.). 

		Due to efficency purposes and insane string conversion. With string parameters more than four, 
		you should work with the non-string based params system. 

		<code>
		   ActorParams params;
		   params.mFloor = true
		   params.mGravity = NxVec3(0, -9, 0);
		</code>

		Is exactly the same as:

		<code>
		   "floor: yes, gravity: 0 -9 0"
		</code>

		\subsection String names

		Class based params follow the rule when used as a string; The "m" prefix is removed, the name
		is lowercased and any camelCase is replaced as camel-case.

		<code>
		   mGravity      -> gravity
		   mMaxTimestep  -> max-timestep
		</code>

		\subsection Pointers

		Params that require pointers cannot be expressed as a string.
	*/
	
	/** \brief A collection of optional things that are passed around when PhysX is loaded, and
			   NxOgre sets up the World.
	    \example
		  <code>
		    "gravity: yes"
		  </code>
		\see \ref physxparams for the full string argument documentation.
	*/	
	class NxPublicClass PhysXParams : Params {

		public:


			/** \brief PhysXParams constructor for "class params".
			*/
			PhysXParams()  {
			                setToDefault();
			               }

			/** \brief PhysXParams constructor for "string params".
				\param _params Full string of params.
			*/
			PhysXParams(const char* _params)  {
			                                   setToDefault();
			                                   process(_params);
			                                  }

			/** \brief PhysXParams constructor for "string params" using an NxString.
				\param _params Full string of params.
			*/
			PhysXParams(const NxString& _params)  {
			                                       setToDefault();
			                                       process(_params);
			                                      }

			/** \brief Set's the member variables to the default values
			           according to the NxSceneDesc class and NxOgre's
			           definition of default.
			*/
			void setToDefault();

			void toNxPhysicsSDKDescription(NxPhysicsSDKDesc&);
			void fromNxPhysicsSDKDescription(NxPhysicsSDKDesc&);

		public:

			/** \brief Default Skin width.
			    \default 0.025
			    \example
			      C++     ->  mPhysXParams.mSkinWidth = 0.025;
			      String  ->  "skin-width: 0.3"
			*/
			NxReal mSkinWidth;


			/** \brief The default linear velocity, squared, below which objects start going to sleep.
			    \default (0.15*0.15)
			    \example
			      C++     ->  mPhysXParams.mSkinWidth = 0.0225;
			      String  ->  "sleep-linear-velocity-squared: 0.03"
			*/
			NxReal mSleepLinearVelocitySquared;


			/** \brief The default angular velocity, squared, below which objects start going to sleep.
			    \default (0.14*0.14)
			    \example
			      C++     ->  mPhysXParams.mSkinWidth = 0.0196;
			      String  ->  "sleep-angular-velocity-squared: 0.015"
			*/
			NxReal mSleepAngularVelocitySquared;


			/** \brief A contact with a relative velocity below this will not bounce.
			    \default -2
			    \example
			      C++     ->  mPhysXParams.mBounceThreshold = -2;
			      String  ->  "bounce-threshold: -2.1"
			*/
			NxReal mBounceThreshold;


			/** \brief This lets the user scale the magnitude of the dynamic friction applied to all objects.
			    \default 1
			    \example
			      C++     ->  mPhysXParams.mDynamicFrictionScale = 1;
			      String  ->  "dynamic-friction-scale: 4"
			*/
			NxReal mDynamicFrictionScale;


			/** \brief This lets the user scale the magnitude of the static friction applied to all objects.
			    \default 1
			    \example
			      C++     ->  mPhysXParams.mStaticFrictionScale = 1;
			      String  ->  "static-friction-scale: 4"
			*/
			NxReal mStaticFrictionScale;


			/** \brief See API Reference for NxBody::setMaxAngularVelocity() for details.
			    \default 7
			    \example
			      C++     ->  mPhysXParams.mMaxAngularVelocity = 7;
			      String  ->  "max-angular-velocity: 4"
			*/
			NxReal mMaxAngularVelocity;


			/** \brief Enable/disable continuous collision detection 
			    \default false
			    \example
			      C++     ->  mPhysXParams.mCCD = false;
			      String  ->  "ccd: yes"
			*/
			bool mCCD;


			/** \brief Size of Hardware mesh pages.
			    \default 65536
				\note    Currently the PhysX SDK will only use 65536. (273)
			    \example
			      C++     ->  mPhysXParams.mHardwarePageSize = 65536;
			      String  ->  "hardware-page-size: 65536"
			*/
			NxU32 mHardwarePageSize;


			/** \brief Maximum number of hardware pages supported concurrently on hardware.
			    \default 256
				\note    The value given must be a power of two.
			    \example
			      C++     ->  mPhysXParams.mHardwarePageMax = 256;
			      String  ->  "hardware-page-max: 256"
			*/
			NxU32 mHardwarePageMax;


			/** \brief Maximum number of convex meshes which will be resident on hardware.
			    \default 65536
				\note    The value given must be a power of two.
			    \example
			      C++     ->  mPhysXParams.mHardwarePageMax = 256;
			      String  ->  "hardware-page-max: 256"
			*/
			NxU32 mHardwareConvexMax;


			/** \brief Thread affinity mask for the background cooker thread.
			    \default 0 (SDK determines the affinity).
			    \example
			      C++     ->  mPhysXParams.mCookerThreadMask = 0;
			      String  ->  "cooker-thread-mask: 0"
			*/
			NxU32 mCookerThreadMask;


			struct NxPublicClass PhysXSDKFlags : Flags {

				void toDefault() {
				    mNoHardware              = false;
				}

				void  fromNxU32(NxU32);
				NxU32 toNxU32() const;
				void  parse(const NxString&);

				/** \brief Disallows the use of the hardware for the application.
				    \default false
				    \see NX_SDKF_NO_HARDWARE
				    \example
				      String variations => +no-hardware
				*/
				bool mNoHardware;

			};

			PhysXSDKFlags mFlags;

			/** \brief Used to enable adaptive forces to accelerate convergence of the solver.
			    \default 1.0
			    \example
			      C++     ->  mPhysXParams.mAdaptiveForce = 1;
			      String  ->  "adaptive-force: 1.5"
			*/
			NxReal mAdaptiveForce;


			/** \brief Controls default filtering for jointed bodies. (True = collision disabled)
			    \default true
			    \example
			      C++     ->  mPhysXParams.mCollisionVetoJointed = true;
			      String  ->  "collision-veto-jointed: no"
			*/
			bool mCollisionVetoJointed;



			/** \brief Controls whether two touching triggers generate a callback or not.
			    \default true
			    \example
			      C++     ->  mPhysXParams.mTriggerTriggerCallback = true;
			      String  ->  "trigger-trigger-callback: no"
			*/
			bool mTriggerTriggerCallback;


			/** \brief Distance epsilon for CCD algorithm.
			    \default 0.01
			    \example
			      C++     ->  mPhysXParams.mCCDEpsilon = 0.01;
			      String  ->  "ccd-epsilon: 0.05"
			*/
			NxReal mCCDEpsilon;


			/** \brief Used to accelerate the solver
			    \default 0
			    \example
			      C++     ->  mPhysXParams.mSolverConvergenceThreshold = 0;
			      String  ->  "solver-convergence-threshold: 1"
			*/
			NxReal mSolverConvergenceThreshold;


			/** \brief Used to accelerate HW Broad Phase.
			    \default 0.001
			    \example
			      C++     ->  mPhysXParams.mBBoxNoiseLevel = 0.001;
			      String  ->  "bbox-noise-level: 0.004"
			*/
			NxReal mBBoxNoiseLevel;


			/** \brief Used to set the sweep cache size.
			    \default 5.0
			    \example
			      C++     ->  mPhysXParams.mImplictSweepCacheSize = 5.0;
			      String  ->  "implicit-sweep-cache-size: 6.0"
			*/
			NxReal mImplictSweepCacheSize;


			/** \brief The default sleep energy threshold. Objects with an
			           energy below this threshold are allowed to go to sleep.
			    \note Only used when the NX_BF_ENERGY_SLEEP_TEST flag is set.
			    \default 0.005
			    \example
			      C++     ->  mPhysXParams.mDefaultSleepEnergy = 0.005;
			      String  ->  "default-sleep-energy: 6.0"
			*/
			NxReal mDefaultSleepEnergy;


			/** \brief On an instance of a Error, shutdown the application straight away.
				\param shutdown-on-errors (bool)
			    \default true
			*/
			bool mShutdownOnErrors;


			/** \brief Create and use the HTMLLog class with the Error system.
			    \default true
			*/
			bool mUseLog;


			enum TimeControllerType {
				TC_NONE = 0,
				TC_PTR = 1
#if (NX_USE_OGRE == 1)
				, TC_OGRE = 10
#endif
			};

			/** \brief Time controller to use.
			    \default TC_NONE
			*/
			NxU32 mTimeController;

			/** \brief Custom time controller (make sure TC_CUSTOM) mTimeController is set.
			    \default 0
			*/
			TimeController* mCustomTimeControllerPtr;


			struct DebugVisualisation {

				void setToDefault();
				void setToNormal();
				void applyToSDK(NxPhysicsSDK*);

				/** \brief This overall visualization scale gets multiplied with the individual scales. 
				    \default 0 (off)
				    \example
				      C++     ->  mPhysXParams.mScale = 0;
				*/
				NxReal mScale;


				/** \brief Visualize the world axes. 
				    \default true
				    \example
				      C++     ->  mPhysXParams.mWorldAxes = true;
				*/
				bool mWorldAxes;


				/** \brief Visualize a body's axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mBodyAxes = false;
				*/
				bool mBodyAxes;


				/** \brief Visualize a body's mass axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mBodyMassAxes = false;
				*/
				bool mBodyMassAxes;


				/** \brief Visualize the bodies' linear velocity.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mBodyLinearVelocity = false;
				*/
				bool mBodyLinearVelocity;


				/** \brief Visualize the bodies' angular velocity.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mBodyAngularVelocity = false;
				*/
				bool mBodyAngularVelocity;


				/** \brief Visualize the bodies' joint groups.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mBodyJointGroups = false;
				*/
				bool mBodyJointGroups;


				/** \brief Visualize local joint axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mJointLocalAxes = false;
				*/
				bool mJointLocalAxes;


				/** \brief Visualize joint world axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mJointWorldAxes = false;
				*/
				bool mJointWorldAxes;


				/** \brief Visualize joint limits.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mJointLimits = false;
				*/
				bool mJointLimits;


				/** \brief Visualize joint limits.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mContactPoint = false;
				*/
				bool mContactPoint;


				/** \brief Visualize contact normals.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mContactNormal = false;
				*/
				bool mContactNormal;


				/** \brief Visualize contact errors.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mContactError = false;
				*/
				bool mContactError;


				/** \brief Visualize actor axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mActorAxes = false;
				*/
				bool mActorAxes;


				/** \brief Visualize bounds (AABBs in world space).
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionAABBs = false;
				*/
				bool mCollisionAABBs;


				/** \brief Visualize collision shapes
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionShapes = false;
				*/
				bool mCollisionShapes;


				/** \brief Visualize shape axes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionAxes = false;
				*/
				bool mCollisionAxes;


				/** \brief Visualize compound (compound AABBs in world space). 
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionCompounds = false;
				*/
				bool mCollisionCompounds;


				/** \brief Visualize mesh and convex vertex normals.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionVertexNormals = false;
				*/
				bool mCollisionVertexNormals;


				/** \brief Visualize mesh and convex face normals.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionFaceNormals = false;
				*/
				bool mCollisionFaceNormals;


				/** \brief Visualize active edges for meshes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionEdges = false;
				*/
				bool mCollisionEdges;


				/** \brief Visualize bounding spheres.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionSpheres = false;
				*/
				bool mCollisionSpheres;


#if (NX_SDK_VERSION_NUMBER < 280)
				/** \brief Visualize SAP structures.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionSAP = false;
				*/
				bool mCollisionSAP;
#endif

				/** \brief Visualize static pruning structures.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionStatic = false;
				*/
				bool mCollisionStatic;


				/** \brief Visualize dynamic pruning structures.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionDynamic = false;
				*/
				bool mCollisionDynamic;


				/** \brief Visualize "free" pruning structures.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionFree = false;
				*/
				bool mCollisionFree;


				/** \brief Visualize CCD tests.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionCCD = false;
				*/
				bool mCollisionCCD;


				/** \brief Visualize CCD skeletons.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mCollisionSkeletons = false;
				*/
				bool mCollisionSkeletons;


				/** \brief Visualize emitter.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidEmitters = false;
				*/
				bool mFluidEmitters;


				/** \brief Visualize particle position.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidPosition = false;
				*/
				bool mFluidPosition;


				/** \brief Visualize particle velocity.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidVelocity = false;
				*/
				bool mFluidVelocity;


				/** \brief Visualize particle kernel radius.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidKernelRadius = false;
				*/
				bool mFluidKernelRadius;


				/** \brief Visualize fluid AABB.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidBounds = false;
				*/
				bool mFluidBounds;


				/** \brief Visualize fluid packets.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidPackets = false;
				*/
				bool mFluidPackets;


				/** \brief Visualize fluid motion limits.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidMotionLimit = false;
				*/
				bool mFluidMotionLimit;


				/** \brief Visualize fluid dynamic mesh collision.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidDynamicCollision = false;
				*/
				bool mFluidDynamicCollision;


				/** \brief Not implemented: Visualize fluid static collision.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidDynamicCollision = false;
				*/
				bool mFluidStaticCollision;


				/** \brief Visualize available fluid mesh packets.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidMeshPackets = false;
				*/
				bool mFluidMeshPackets;


				/** \brief Visualize fluid drain shapes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidDrains = false;
				*/
				bool mFluidDrains;


				/** \brief Visualize fluid data packets.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mFluidPacketData = false;
				*/
				bool mFluidPacketData;


				/** \brief Visualize cloth meshes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothMesh = false;
				*/
				bool mClothMesh;


				/** \brief Visualize cloth rigid body collision.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothCollisions = false;
				*/
				bool mClothCollisions;


				/** \brief Visualize cloth self collision.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothSelfCollisions = false;
				*/
				bool mClothSelfCollisions;


				/** \brief Visualize cloth clustering for the PPU.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothWorkPackets = false;
				*/
				bool mClothWorkPackets;


				/** \brief Visualize cloth sleeping.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothSleep = false;
				*/
				bool mClothSleep;


				/** \brief Visualize cloth sleeping with full per-vertex information.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothSleepVertex = false;
				*/
				bool mClothSleepVertex;


				/** \brief Visualize tearable cloth vertices.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothTearableVertices = false;
				*/
				bool mClothTearableVertices;


				/** \brief Visualize cloth tearing.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothTearing = false;
				*/
				bool mClothTearing;


				/** \brief Visualize cloth attachments.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothAttachment = false;
				*/
				bool mClothAttachment;


				/** \brief Visualize cloth valid bounds.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mClothValidBounds = false;
				*/
				bool mClothValidBounds;


				/** \brief Visualize soft body meshes.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyMesh = false;
				*/
				bool mSoftBodyMesh;


				/** \brief Visualize soft body collisions with rigid bodies.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyCollisions = false;
				*/
				bool mSoftBodyCollisions;


				/** \brief Visualize soft body clustering for simulation on the PPU.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyWorkPackets = false;
				*/
				bool mSoftBodyWorkPackets;


				/** \brief Visualize soft body sleeping.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodySleep = false;
				*/
				bool mSoftBodySleep;


				/** \brief Visualize soft body sleeping with full per-vertex information.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodySleepVertex = false;
				*/
				bool mSoftBodySleepVertex;


				/** \brief Visualize tearable soft body vertices.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyTearableVertices = false;
				*/
				bool mSoftBodyTearableVertices;


				/** \brief Visualize soft body tearing.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyTearing = false;
				*/
				bool mSoftBodyTearing;


				/** \brief Visualize soft body attachments.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyAttachment = false;
				*/
				bool mSoftBodyAttachment;


				/** \brief Visualize soft body valid bounds.
				    \default false
				    \example
				      C++     ->  mPhysXParams.mSoftBodyValidBounds = false;
				*/
				bool mSoftBodyValidBounds;

			};

			
			/** \brief Visualisation options for the DebugRenderer.
			    \default mDebugVisualisation.setToDefault()
			    \example
			      C++     ->  mPhysXParams.mDebugVisualisation.mBodyAxes = true;
			*/
			DebugVisualisation mDebugVisualisation;


		protected:

			void parse(Parameters);


	};

	/** \brief The PhysXDriver is the direct interface between
			   the NxPhysicsSDK and NxOgre.
	*/
	class NxPublicClass PhysXDriver {

		friend class World;

		protected:

			/** \internal
				\note This is automatically created when World is.
			*/
			PhysXDriver(World*, PhysXParams);

			/** \brief Totally shuts down PhysX and NxOgre.
			*/
			~PhysXDriver();

		public:

			/** \brief Get's a copy of the PhysicsSDK, the top-most PhysX class.
			*/
			NxPhysicsSDK*   getSDK();

			/** \brief Tells if the current hardware has a PhysX PPU or not.
			*/
			bool hasHardware();


			/** \brief Advances the simulation since time last passed. Does not 
			           visually update the Scene. Usually handled by the TimeController.
			    \param Time passed since last simulation.
			    \example <code>
			               mPhysXDriver->simulate(0.16667f);
			               mPhysXDriver->render(0.16667f);
			             </code>
			    \see TimeController
			*/
			void simulate(const float time);

			/** \brief Renders the changes of the simulation, using each SceneRenderer
			           for each Scene. Usually handled by the TimeController.
			    \param Time passed since last simulation.
			    \example <code>
			               mPhysXDriver->simulate(0.16667f);
			               mPhysXDriver->render(0.16667f);
			             </code>
			    \see TimeController
			*/
			void render(const float time);


			/** \brief Returns a copy of the World class
			    \return The World.
			*/
			World*	getWorld() {
			                    return mWorld;
			                   }

			/** \brief Returns a copy of the Error singleton class
			    \return the error class
			*/
			Error*  getError() {
			                    return mError;
			                   }

			/** \brief Returns the total time simulated.
			    \return time passed in seconds
			*/
			NxReal	getTime() const {
			                         return mTime;
			                        }

			/** \brief Retuns the total number of times simulated.
			*/
			unsigned int getNbSimulations() const {
			                                       return mNbSimulations;
			                                      }
#ifndef NX_SMALL
			/** \brief Creates the remote debugger connection class, and attempts to communicate
			    with the remote debugger based on the network address and port given.
				\param address The network address of the computer running the the debugger (default: localhost). 
				\param port The port the remote debugger is running at (default: 5245).
			*/
			void	createDebuggerConnection(const NxString& address = "localhost", unsigned int port = 5425);
#endif

#ifndef NX_SMALL
			/** \brief Removes the remote debugger connection class, and stops communicating
			           with the remote debugger.
			*/
			void	destroyDebuggerConnection();
#endif

			/** \brief Returns a copy of the RemoteDebuggerConnection class.
			*/
			RemoteDebuggerConnection* getRemoteDebuggerConnection() {
			                                                         return mDebugger;
			                                                        }

			/** \brief Default Skin width.
			    \default 0.025
			*/
			void setSkinWidth(NxReal val);


			/** \brief The default linear velocity, squared, below which objects start going to sleep.
			    \default (0.15*0.15)
			*/
			void setSleepLinearVelocitySquared(NxReal val);

			/** \brief The default angular velocity, squared, below which objects start going to sleep.
			    \default (0.14*0.14)
			*/
			void setSleepAngularVelocitySquared(NxReal val);


			/** \brief A contact with a relative velocity below this will not bounce.
			    \default -2
			*/
			void setBounceThreshold(NxReal val);

			/** \brief This lets the user scale the setagnitude of the dynamic friction applied to all objects.
			    \default 1
			*/
			void setDynamicFrictionScale(NxReal val);


			/** \brief This lets the user scale the setagnitude of the static friction applied to all objects.
			    \default 1
			*/
			void setStaticFrictionScale(NxReal val);


			/** \brief See API Reference for NxBody::setMaxAngularVelocity() for details.
			    \default 7
			*/
			void setMaxAngularVelocity(NxReal val);

			/** \brief Enable/disable continuous collision detection 
			    \default false
			*/
			void setCCD(bool val);

			/** \brief Used to enable adaptive forces to accelerate convergence of the solver.
			    \default 1.0
			*/
			void setAdaptiveForce(NxReal val);


			/** \brief Controls default filtering for jointed bodies. (True = collision disabled)
			    \default true
			*/
			void setCollisionVetoJointed(bool val);


			/** \brief Controls whether two touching triggers generate a callback or not.
			    \default true
			*/
			void setTriggerTriggerCallback(bool val);


			/** \brief Distance epsilon for CCD algorithm.
			    \default 0.01
			*/
			void setCCDEpsilon(NxReal val);


			/** \brief Used to accelerate the solver
			    \default 0
			*/
			void setSolverConvergenceThreshold(NxReal val);


			/** \brief Used to accelerate HW Broad Phase.
			    \default 0.001
			*/
			void setBBoxNoiseLevel(NxReal val);


			/** \brief Used to set the sweep cache size.
			    \default 5.0
			*/
			void setImplictSweepCacheSize(NxReal val);


			/** \brief The default sleep energy threshold. Objects with an
					   energy below this threshold are allowed to go to sleep.
				\note Only used when the NX_BF_ENERGY_SLEEP_TEST flag is set.
			    \default 0.005
			*/
			void setDefaultSleepEnergy(NxReal val);


			/** \brief Default Skin width.
			    \default 0.025
			*/
			NxReal getSkinWidth() const;


			/** \brief The default linear velocity, squared, below which objects start going to sleep.
			    \default (0.15*0.15)
			*/
			NxReal getSleepLinearVelocitySquared() const;

			/** \brief The default angular velocity, squared, below which objects start going to sleep.
			    \default (0.14*0.14)
			*/
			NxReal getSleepAngularVelocitySquared() const;


			/** \brief A contact with a relative velocity below this will not bounce.
			    \default -2
			*/
			NxReal getBounceThreshold() const;

			/** \brief This lets the user scale the getagnitude of the dynamic friction applied to all objects.
			    \default 1
			*/
			NxReal getDynamicFrictionScale() const;


			/** \brief This lets the user scale the getagnitude of the static friction applied to all objects.
			    \default 1
			*/
			NxReal getStaticFrictionScale() const;


			/** \brief See API Reference for NxBody::getMaxAngularVelocity() for details.
			    \default 7
			*/
			NxReal getMaxAngularVelocity() const;

			/** \brief Enable/disable continuous collision detection 
			    \default false
			*/
			bool getCCD() const;

			/** \brief Used to enable adaptive forces to accelerate convergence of the solver.
			    \default 1.0
			*/
			NxReal getAdaptiveForce() const;


			/** \brief Controls default filtering for jointed bodies. (True = collision disabled)
			    \default true
			*/
			bool getCollisionVetoJointed() const;


			/** \brief Controls whether two touching triggers generate a callback or not.
			    \default true
			*/
			bool getTriggerTriggerCallback() const;


			/** \brief Distance epsilon for CCD algorithm.
			    \default 0.01
			*/
			NxReal getCCDEpsilon() const;


			/** \brief Used to accelerate the solver
			    \default 0
			*/
			NxReal getSolverConvergenceThreshold() const;


			/** \brief Used to accelerate HW Broad Phase.
			    \default 0.001
			*/
			NxReal getBBoxNoiseLevel() const;


			/** \brief Used to get the sweep cache size.
			    \default 5.0
			*/
			NxReal getImplictSweepCacheSize() const;


			/** \brief The default sleep energy threshold. Objects with an
					   energy below this threshold are allowed to go to sleep.
				\note Only used when the NX_BF_ENERGY_SLEEP_TEST flag is get.
			    \default 0.005
			*/
			NxReal getDefaultSleepEnergy() const;


			/** \brief This overall visualization scale gets setVisualisationultiplied with the individual scales. 
			    \default 0 (off)
			*/
			void setVisualisationScale(NxReal scale);


			/** \brief Visualize the world axes. 
			    \default true
			*/
			void setVisualisationWorldAxesEnabled(bool val);


			/** \brief Visualize a body's axes.
			    \default false
			*/
			void setVisualisationBodyAxesEnabled(bool val);


			/** \brief Visualize a body's setVisualisationass axes.
			    \default false
			*/
			void setVisualisationBodyMassAxesEnabled(bool val);


			/** \brief Visualize the bodies' linear velocity.
			    \default false
			*/
			void setVisualisationBodyLinearVelocityEnabled(bool val);


			/** \brief Visualize the bodies' angular velocity.
			    \default false
			*/
			void setVisualisationBodyAngularVelocityEnabled(bool val);


			/** \brief Visualize the bodies' joint groups.
			    \default false
			    \example
			      C++     ->  setVisualisationPhysXParams.mBodyJointGroups = falseEnabled(bool val);
			*/
			void setVisualisationBodyJointGroupsEnabled(bool val);


			/** \brief Visualize local joint axes.
			    \default false
			    \example
			      C++     ->  setVisualisationPhysXParams.mJointLocalAxes = falseEnabled(bool val);
			*/
			void setVisualisationJointLocalAxesEnabled(bool val);


			/** \brief Visualize joint world axes.
			    \default false
			*/
			void setVisualisationJointWorldAxesEnabled(bool val);


			/** \brief Visualize joint limits.
			    \default false
			*/
			void setVisualisationJointLimitsEnabled(bool val);


			/** \brief Visualize joint limits.
			    \default false
			*/
			void setVisualisationContactPointEnabled(bool val);


			/** \brief Visualize contact normals.
			    \default false
			*/
			void setVisualisationContactNormalEnabled(bool val);


			/** \brief Visualize contact errors.
			    \default false
			*/
			void setVisualisationContactErrorEnabled(bool val);


			/** \brief Visualize actor axes.
			    \default false
			*/
			void setVisualisationActorAxesEnabled(bool val);


			/** \brief Visualize bounds (AABBs in world space).
			    \default false
			*/
			void setVisualisationCollisionAABBsEnabled(bool val);


			/** \brief Visualize collision shapes
			    \default false
			*/
			void setVisualisationCollisionShapesEnabled(bool val);


			/** \brief Visualize shape axes.
			    \default false
			*/
			void setVisualisationCollisionAxesEnabled(bool val);


			/** \brief Visualize compound (compound AABBs in world space). 
			    \default false
			*/
			void setVisualisationCollisionCompoundsEnabled(bool val);


			/** \brief Visualize setVisualisationesh and convex vertex normals.
			    \default false
			*/
			void setVisualisationCollisionVertexNormalsEnabled(bool val);


			/** \brief Visualize setVisualisationesh and convex face normals.
			    \default false
			*/
			void setVisualisationCollisionFaceNormalsEnabled(bool val);


			/** \brief Visualize active edges for setVisualisationeshes.
			    \default false
			*/
			void setVisualisationCollisionEdgesEnabled(bool val);


			/** \brief Visualize bounding spheres.
			    \default false
			*/
			void setVisualisationCollisionSpheresEnabled(bool val);

#if (NX_SDK_VERSION_NUMBER < 280)
			/** \brief Visualize SAP structures.
			    \default false
			*/
			void setVisualisationCollisionSAPEnabled(bool val);
#endif

			/** \brief Visualize static pruning structures.
			    \default false
			*/
			void setVisualisationCollisionStaticEnabled(bool val);


			/** \brief Visualize dynamic pruning structures.
			    \default false
			*/
			void setVisualisationCollisionDynamicEnabled(bool val);


			/** \brief Visualize "free" pruning structures.
			    \default false
			*/
			void setVisualisationCollisionFreeEnabled(bool val);


			/** \brief Visualize CCD tests.
			    \default false
			*/
			void setVisualisationCollisionCCDEnabled(bool val);


			/** \brief Visualize CCD skeletons.
			    \default false
			*/
			void setVisualisationCollisionSkeletonsEnabled(bool val);


			/** \brief Visualize emitter.
			    \default false
			*/
			void setVisualisationFluidEmittersEnabled(bool val);


			/** \brief Visualize particle position.
			    \default false
			*/
			void setVisualisationFluidPositionEnabled(bool val);


			/** \brief Visualize particle velocity.
			    \default false
			*/
			void setVisualisationFluidVelocityEnabled(bool val);


			/** \brief Visualize particle kernel radius.
			    \default false
			*/
			void setVisualisationFluidKernelRadiusEnabled(bool val);


			/** \brief Visualize fluid AABB.
			    \default false
			*/
			void setVisualisationFluidBoundsEnabled(bool val);


			/** \brief Visualize fluid packets.
			    \default false
			*/
			void setVisualisationFluidPacketsEnabled(bool val);


			/** \brief Visualize fluid setVisualisationotion limits.
			    \default false
			*/
			void setVisualisationFluidMotionLimitEnabled(bool val);


			/** \brief Visualize fluid dynamic setVisualisationesh collision.
			    \default false
			*/
			void setVisualisationFluidDynamicCollisionEnabled(bool val);


			/** \brief Not implemented: Visualize fluid static collision.
			    \default false
			*/
			void setVisualisationFluidStaticCollisionEnabled(bool val);


			/** \brief Visualize available fluid setVisualisationesh packets.
			    \default false
			*/
			void setVisualisationFluidMeshPacketsEnabled(bool val);


			/** \brief Visualize fluid drain shapes.
			    \default false
			*/
			void setVisualisationFluidDrainsEnabled(bool val);


			/** \brief Visualize fluid data packets.
			    \default false
			*/
			void setVisualisationFluidPacketDataEnabled(bool val);


			/** \brief Visualize cloth setVisualisationeshes.
			    \default false
			*/
			void setVisualisationClothMeshEnabled(bool val);


			/** \brief Visualize cloth rigid body collision.
			    \default false
			*/
			void setVisualisationClothCollisionsEnabled(bool val);


			/** \brief Visualize cloth self collision.
			    \default false
			*/
			void setVisualisationClothSelfCollisionsEnabled(bool val);


			/** \brief Visualize cloth clustering for the PPU.
			    \default false
			*/
			void setVisualisationClothWorkPacketsEnabled(bool val);


			/** \brief Visualize cloth sleeping.
			    \default false
			*/
			void setVisualisationClothSleepEnabled(bool val);


			/** \brief Visualize cloth sleeping with full per-vertex information.
			    \default false
			*/
			void setVisualisationClothSleepVertexEnabled(bool val);


			/** \brief Visualize tearable cloth vertices.
			    \default false
			*/
			void setVisualisationClothTearableVerticesEnabled(bool val);


			/** \brief Visualize cloth tearing.
			    \default false
			*/
			void setVisualisationClothTearingEnabled(bool val);


			/** \brief Visualize cloth attachments.
			    \default false
			*/
			void setVisualisationClothAttachmentEnabled(bool val);


			/** \brief Visualize cloth valid bounds.
			    \default false
			*/
			void setVisualisationClothValidBoundsEnabled(bool val);


			/** \brief Visualize soft body setVisualisationeshes.
			    \default false
			*/
			void setVisualisationSoftBodyMeshEnabled(bool val);


			/** \brief Visualize soft body collisions with rigid bodies.
			    \default false
			*/
			void setVisualisationSoftBodyCollisionsEnabled(bool val);


			/** \brief Visualize soft body clustering for simulation on the PPU.
			    \default false
			*/
			void setVisualisationSoftBodyWorkPacketsEnabled(bool val);


			/** \brief Visualize soft body sleeping.
			    \default false
			*/
			void setVisualisationSoftBodySleepEnabled(bool val);


			/** \brief Visualize soft body sleeping with full per-vertex information.
			    \default false
			*/
			void setVisualisationSoftBodySleepVertexEnabled(bool val);


			/** \brief Visualize tearable soft body vertices.
			    \default false
			*/
			void setVisualisationSoftBodyTearableVerticesEnabled(bool val);


			/** \brief Visualize soft body tearing.
			    \default false
			*/
			void setVisualisationSoftBodyTearingEnabled(bool val);


			/** \brief Visualize soft body attachments.
			    \default false
			*/
			void setVisualisationSoftBodyAttachmentEnabled(bool val);


			/** \brief Visualize soft body valid bounds.
			    \default false
			*/
			void setVisualisationSoftBodyValidBounds(bool val);


			/** \brief This overall visualization scale gets setVisualisationultiplied with the individual scales. 
			    \default 0 (off)
			*/
			NxReal getVisualisationScale() const;


			/** \brief Visualize the world axes. 
			    \default true
			*/
			bool getVisualisationWorldAxesEnabled() const;


			/** \brief Visualize a body's axes.
			    \default false
			*/
			bool getVisualisationBodyAxesEnabled() const;


			/** \brief Visualize a body's setVisualisationass axes.
			    \default false
			*/
			bool getVisualisationBodyMassAxesEnabled() const;


			/** \brief Visualize the bodies' linear velocity.
			    \default false
			*/
			bool getVisualisationBodyLinearVelocityEnabled() const;


			/** \brief Visualize the bodies' angular velocity.
			    \default false
			*/
			bool getVisualisationBodyAngularVelocityEnabled() const;


			/** \brief Visualize the bodies' joint groups.
			    \default false
			    \example
			      C++     ->  setVisualisationPhysXParams.mBodyJointGroups = falseEnabled() const;
			*/
			bool getVisualisationBodyJointGroupsEnabled() const;


			/** \brief Visualize local joint axes.
			    \default false
			    \example
			      C++     ->  setVisualisationPhysXParams.mJointLocalAxes = falseEnabled() const;
			*/
			bool getVisualisationJointLocalAxesEnabled() const;


			/** \brief Visualize joint world axes.
			    \default false
			*/
			bool getVisualisationJointWorldAxesEnabled() const;


			/** \brief Visualize joint limits.
			    \default false
			*/
			bool getVisualisationJointLimitsEnabled() const;


			/** \brief Visualize joint limits.
			    \default false
			*/
			bool getVisualisationContactPointEnabled() const;


			/** \brief Visualize contact normals.
			    \default false
			*/
			bool getVisualisationContactNormalEnabled() const;


			/** \brief Visualize contact errors.
			    \default false
			*/
			bool getVisualisationContactErrorEnabled() const;


			/** \brief Visualize actor axes.
			    \default false
			*/
			bool getVisualisationActorAxesEnabled() const;


			/** \brief Visualize bounds (AABBs in world space).
			    \default false
			*/
			bool getVisualisationCollisionAABBsEnabled() const;


			/** \brief Visualize collision shapes
			    \default false
			*/
			bool getVisualisationCollisionShapesEnabled() const;


			/** \brief Visualize shape axes.
			    \default false
			*/
			bool getVisualisationCollisionAxesEnabled() const;


			/** \brief Visualize compound (compound AABBs in world space). 
			    \default false
			*/
			bool getVisualisationCollisionCompoundsEnabled() const;


			/** \brief Visualize setVisualisationesh and convex vertex normals.
			    \default false
			*/
			bool getVisualisationCollisionVertexNormalsEnabled() const;


			/** \brief Visualize setVisualisationesh and convex face normals.
			    \default false
			*/
			bool getVisualisationCollisionFaceNormalsEnabled() const;


			/** \brief Visualize active edges for setVisualisationeshes.
			    \default false
			*/
			bool getVisualisationCollisionEdgesEnabled() const;


			/** \brief Visualize bounding spheres.
			    \default false
			*/
			bool getVisualisationCollisionSpheresEnabled() const;


#if (NX_SDK_VERSION_NUMBER < 280)
			/** \brief Visualize SAP structures.
			    \default false
			*/
			bool getVisualisationCollisionSAPEnabled() const;
#endif

			/** \brief Visualize static pruning structures.
			    \default false
			*/
			bool getVisualisationCollisionStaticEnabled() const;


			/** \brief Visualize dynamic pruning structures.
			    \default false
			*/
			bool getVisualisationCollisionDynamicEnabled() const;


			/** \brief Visualize "free" pruning structures.
			    \default false
			*/
			bool getVisualisationCollisionFreeEnabled() const;


			/** \brief Visualize CCD tests.
			    \default false
			*/
			bool getVisualisationCollisionCCDEnabled() const;


			/** \brief Visualize CCD skeletons.
			    \default false
			*/
			bool getVisualisationCollisionSkeletonsEnabled() const;


			/** \brief Visualize emitter.
			    \default false
			*/
			bool getVisualisationFluidEmittersEnabled() const;


			/** \brief Visualize particle position.
			    \default false
			*/
			bool getVisualisationFluidPositionEnabled() const;


			/** \brief Visualize particle velocity.
			    \default false
			*/
			bool getVisualisationFluidVelocityEnabled() const;


			/** \brief Visualize particle kernel radius.
			    \default false
			*/
			bool getVisualisationFluidKernelRadiusEnabled() const;


			/** \brief Visualize fluid AABB.
			    \default false
			*/
			bool getVisualisationFluidBoundsEnabled() const;


			/** \brief Visualize fluid packets.
			    \default false
			*/
			bool getVisualisationFluidPacketsEnabled() const;


			/** \brief Visualize fluid setVisualisationotion limits.
			    \default false
			*/
			bool getVisualisationFluidMotionLimitEnabled() const;


			/** \brief Visualize fluid dynamic setVisualisationesh collision.
			    \default false
			*/
			bool getVisualisationFluidDynamicCollisionEnabled() const;


			/** \brief Not implemented: Visualize fluid static collision.
			    \default false
			*/
			bool getVisualisationFluidStaticCollisionEnabled() const;


			/** \brief Visualize available fluid setVisualisationesh packets.
			    \default false
			*/
			bool getVisualisationFluidMeshPacketsEnabled() const;


			/** \brief Visualize fluid drain shapes.
			    \default false
			*/
			bool getVisualisationFluidDrainsEnabled() const;


			/** \brief Visualize fluid data packets.
			    \default false
			*/
			bool getVisualisationFluidPacketDataEnabled() const;


			/** \brief Visualize cloth setVisualisationeshes.
			    \default false
			*/
			bool getVisualisationClothMeshEnabled() const;


			/** \brief Visualize cloth rigid body collision.
			    \default false
			*/
			bool getVisualisationClothCollisionsEnabled() const;


			/** \brief Visualize cloth self collision.
			    \default false
			*/
			bool getVisualisationClothSelfCollisionsEnabled() const;


			/** \brief Visualize cloth clustering for the PPU.
			    \default false
			*/
			bool getVisualisationClothWorkPacketsEnabled() const;


			/** \brief Visualize cloth sleeping.
			    \default false
			*/
			bool getVisualisationClothSleepEnabled() const;


			/** \brief Visualize cloth sleeping with full per-vertex information.
			    \default false
			*/
			bool getVisualisationClothSleepVertexEnabled() const;


			/** \brief Visualize tearable cloth vertices.
			    \default false
			*/
			bool getVisualisationClothTearableVerticesEnabled() const;


			/** \brief Visualize cloth tearing.
			    \default false
			*/
			bool getVisualisationClothTearingEnabled() const;


			/** \brief Visualize cloth attachments.
			    \default false
			*/
			bool getVisualisationClothAttachmentEnabled() const;


			/** \brief Visualize cloth valid bounds.
			    \default false
			*/
			bool getVisualisationClothValidBoundsEnabled() const;


			/** \brief Visualize soft body setVisualisationeshes.
			    \default false
			*/
			bool getVisualisationSoftBodyMeshEnabled() const;


			/** \brief Visualize soft body collisions with rigid bodies.
			    \default false
			*/
			bool getVisualisationSoftBodyCollisionsEnabled() const;


			/** \brief Visualize soft body clustering for simulation on the PPU.
			    \default false
			*/
			bool getVisualisationSoftBodyWorkPacketsEnabled() const;


			/** \brief Visualize soft body sleeping.
			    \default false
			*/
			bool getVisualisationSoftBodySleepEnabled() const;


			/** \brief Visualize soft body sleeping with full per-vertex information.
			    \default false
			*/
			bool getVisualisationSoftBodySleepVertexEnabled() const;


			/** \brief Visualize tearable soft body vertices.
			    \default false
			*/
			bool getVisualisationSoftBodyTearableVerticesEnabled() const;


			/** \brief Visualize soft body tearing.
			    \default false
			*/
			bool getVisualisationSoftBodyTearingEnabled() const;


			/** \brief Visualize soft body attachments.
			    \default false
			*/
			bool getVisualisationSoftBodyAttachmentEnabled() const;


			/** \brief Visualize soft body valid bounds.
			    \default false
			*/
			bool getVisualisationSoftBodyValidBounds() const;

			/** \brief Return's a copy of the UserAllocator, used for cooking, and basic
				       memory work.
			*/
			UserAllocator* getUserAllocator();

		protected:

			/** \internal
			*/
			void  _createSDK(NxPhysicsSDKDesc&);

			/** \internal
			*/
			void  _createSDKfromID(NxString, NxString, NxString, NxString);

			/** \internal
			*/
			void  _destroySDK();

			/** \internal
			*/
			void  _dumpVersionsToConsole();

			Allocator*                   mAllocator;
			World*                       mWorld;
			NxPhysicsSDK*                mSDK;
			bool                         mFramelistener;
			UserAllocator*               mUserAllocator;
			Error*                       mError;
			Log*                         mLog;
			NxReal                       mTime,
			                             mTimeModifier;
			unsigned int                 mNbSimulations;
			RemoteDebuggerConnection*    mDebugger;
			TimeController*              mTimeController;
			Resources::ResourceSystem*   mResourceSystem;

		private:

	};

};

#endif
