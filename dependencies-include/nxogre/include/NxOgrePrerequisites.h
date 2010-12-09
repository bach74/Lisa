/** \file    NxOgrePrerequisites.h
 *  \brief   Second most common header used by NxOgre classes. It's use is to
 *           prototyping all of the classes and global functions, and to centeralise
 *           typedef's and enums.
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

#ifndef __NXOGRE_PREREQUISITES_H__
#define __NXOGRE_PREREQUISITES_H__

#include "NxOgreStable.h"
#include "BetajaenCC.h"
#include "NxOgreExtendedTypes.h"
#include "NxOgrePrerequisitesOgre.h"

// Namespace "NxOgre" classes
// ----------------------------------------------------------
namespace NxOgre {
   class  Actor;                            //  In files; 
   class  ActorGroup;                       //  In files; 
   class  ActorParams;                      //  In files; 
   class  AccumulatorSceneController;       //  In files; 
   class  AccumulatorSceneRenderer;         //  In files; 
   class  BaseCharacterHitReport;           //  In files; 
   class  Body;                             //  In files; 
   class  Compartment;                      //  In files; 
   class  Capsule;                          //  In files; 
   class  CharacterHitReport;               /// \deprecated
   class  CombustionEngine;                 //  In files; 
   class  CompoundShape;                    //  In files; 
   class  ContactStream;                    //  In files; 
   class  Convex;                           //  In files; 
   class  Cube;                             //  In files; 
   class  CulledIntersection;               //  In files; 
   class  CylindricalJoint;                 //  In files; 
   class  DeletionCallback;                 //  In files; 
   class  Engine;                           //  In files; 
   class  Error;                            //  In files; 
   class  ErrorReport;                      //  In files; 
   class  ErrorReporter;                    //  In files; 
   class  FixedSceneController;             //  In files; 
   class  FixedJoint;                       //  In files; 
   class  Ground;                           //  In files; 
   class  GroupCallback;                    //  In files; 
   class  InternalCombustionEngine;         //  In files; 
   class  Intersection;                     //  In files; 
   class  Joint;                            //  In files; 
   class  JointCallback;                    //  In files; 
   class  JointParams;                      //  In files; 
   class  Log;                              //  In files; 
   class  Machine;                          //  In files; 
   class  Material;                         //  In files; 
   class  MeshRenderable;                   //  In files; 
   class  Motor;                            //  In files; 
   class  NodeRenderable;                   //  In files; 
   class  NullSceneController;              //  In files; 
   class  NullSceneRenderer;                //  In files; 
   class  OgreResourceSystem;               //  In files; 
   class  PrismaticJoint;                   //  In files; 
   class  Params;                           //  In files; 
   class  PhysXDriver;                      //  In files; 
   class  PhysXParams;                      //  In files; 
   class  Pose;                             //  In files; 
   class  RayCaster;                        //  In files; 
   class  Renderable;                       //  In files; 
   class  Renderables;                      //  In files; 
   class  RenderableSource;                 //  In files; 
   class  RemoteDebuggerConnection;         //  In files; 
   class  RevoluteJoint;                    //  In files; 
   class  Scene;                            //  In files; NxOgreScene.h, NxOgreScene.cpp
   class  SceneParams;                      //  In files; NxOgreScene.h, NxOgreScene.cpp
   class  SceneContactController;           //  In files; 
   class  SceneController;                  //  In files; 
   class  SceneRenderer;                    //  In files; 
   class  SceneTriggerController;           //  In files; 
   class  Skeleton;                         //  In files; 
   class  Shape;                            //  In files; 
   class  ShapeGroup;                       //  In files; 
   class  ShapeParams;                      //  In files; 
   class  SleepCallback;                    //  In files; 
   class  SimpleActor;                      //  In files; 
   class  SimpleBox;                        //  In files; 
   class  SimpleCapsule;                    //  In files; 
   class  SimpleConvex;                     //  In files; 
   class  SimpleIntersection;               //  In files; 
   class  SimplePlane;                      //  In files; 
   class  SimpleShape;                      //  In files; 
   class  SimpleSphere;                     //  In files; 
   class  Sphere;                           //  In files; 
   class  SphericalJoint;                   //  In files; 
   class  StringPairList;                   //  In files; 
   class  Terrain;                          //  In files;  NxOgreShapeTerrain.h, NxOgreShapeTerrain.cpp
   class  TimeController;                   //  In files;  NxOgreTimeController.h, NxOgreTimeController.cpp
   class  Timer;                            //  In files;  NxOgreTimer.h, NxOgreTimer.cpp
   class  TimeStep;                         //  In files;  NxOgreTimeStep.h
   class  TriangleMesh;                     //  In files; 
   class  Trigger;                          //  In files; 
   class  TriggerContactCallback;           //  In files; 
   class  UserAllocator;                    //  In files; 
   class  VariableSceneController;          //  In files; 
   class  VisualIdentifier;                 //  In files; 
   class  Wheel;                            //  In files; 
   class  WheelContactCallback;             //  In files;
   class  WheelParams;                      //  In files; 
   class  World;                            //  In files; 
   class  VoidPointer;                      //  In files;  NxOgreVoidPointer.h
};


// Namespace "NxOgre" structs
// ----------------------------------------------------------
namespace NxOgre {
   struct  DelayedActor;                    //  In files; 
   struct  RayCastHit;                      //  In files; 
};


// Namespace "NxOgre" templates
// ----------------------------------------------------------
namespace NxOgre {

   template <typename _class>               //  In files; 
      class ActorGroupMethodPointer;        //            

   template <typename _identifier_type,     //  In files; 
             typename _type>                //            
      class Container;                      //            

   template <typename _first,               //  In files; 
             typename _second>              //            
      class DualIdentifier;                 //            

   template<typename _type>                 //  In files; 
      class List;                           //            

   template <class TargetClass>             //  In files; 
      class TriggerContactPtrCallback;      //            
};


// Namespace "NxOgre::Resource" classes
// ----------------------------------------------------------
namespace NxOgre {
namespace Resources {

   class Heightfield;
   class Mesh;
   class ManualMesh;
   class ManualHeightfield;
   class MaterialAlias;
   class Resource;
   class ResourceCallback;
   class ResourceManager;
   class ResourceSystem;

};
};


// Namespace "NxOgre::Resources" typedefss and enums.
// ----------------------------------------------------------
namespace NxOgre {
namespace Resources {

	typedef std::string                           ResourceIdentifier;
	typedef Betajaen::SharedList<Resource>        ResourceList;
	typedef ResourceList                          ResourceListIterator;

	enum ResourceType {
		RT_PhysX_Mesh,
		RT_PhysX_Convex,
		RT_PhysX_SoftBody,
		RT_PhysX_Cloth,
		RT_PhysX_Heightfield,
		RT_PhysX_Skeleton,
		RT_MaterialAlias,
		RT_JSON,
		RT_Unknown
	};

	enum MeshType {
		MT_Triangle = RT_PhysX_Mesh,
		MT_Convex   = RT_PhysX_Convex,
		MT_SoftBody = RT_PhysX_SoftBody,
		MT_Cloth    = RT_PhysX_Cloth,
		MT_Skeleton = RT_PhysX_Skeleton,
		MT_Unknown
	};

	enum ResourceAccess {
		RA_Read,
		RA_Write,
		RA_ReadWrite,
		RA_Default
	};

};
};


// Cloth API classes and typedef.
// ----------------------------------------------------------
#if (NX_USE_CLOTH_API == 1)
namespace NxOgre {
   class  Cloth;                            //  In files; 
   class  ClothMeshIntermediary;            //  In files; 
   class  ClothParams;                      //  In files; 
   class  ClothRayCaster;                   //  In files; 
   typedef Container<std::string, Cloth*> Cloths;
};
#endif 


// Fluid API classes
// ----------------------------------------------------------
#if (NX_USE_FLUID_API == 1)
namespace NxOgre {
   class  Fluid;                            //  In files; 
   class  FluidDrain;                       //  In files; 
   class  FluidEmitter;                     //  In files; 
   class  FluidParams;                      //  In files;
   class  FluidMesh;                        //  In files; 
   typedef Container<std::string, Fluid*>         Fluids;
   typedef Container<std::string, FluidDrain*>    FluidDrains;
   typedef Container<std::string, FluidEmitter*>  FluidEmitters;
};
#endif


// Forcefield API classes
// ----------------------------------------------------------
#if (NX_USE_FORCEFIELD_API == 1)
namespace NxOgre {
   class  ForceField;                       //  In files; 
   class  ForceFieldFunction;               //  In files; 
   class  ForceFieldParams;                 //  In files;
   typedef Container<std::string, ForceField*> ForceFields;
};
#endif


// Debug Renderer API classes
// ----------------------------------------------------------
#if (NX_USE_DEBUG_RENDERER_API == 1)
namespace NxOgre {
   class  DebugRenderer;                    //  In files; 
};
#endif


// Softbody API classes
// ----------------------------------------------------------
#if (NX_USE_SOFTBODY_API == 1)
namespace NxOgre {
   class  SoftBody;                         //  In files; 
   class  SoftBodyParams;                   //  In files;
   typedef Container<std::string, SoftBody*> SoftBodies;
};
#endif


// PhysX 2.7.2+ classes
// ----------------------------------------------------------
#if (NX_SDK_VERSION_NUMBER >= 272) 
namespace NxOgre {
   class  DominanceGroup;                   //  In files; 
   typedef Container<std::string, DominanceGroup*> DominanceGroups;
   typedef Container<NxDominanceGroup, DominanceGroup*> DominanceGroupsByIndex;
};
#endif


// Namespace "NxOgre::CharacterSystem" classes
// ----------------------------------------------------------
namespace NxOgre {
namespace CharacterSystem {
   class  Character;                        //  In files; 
   class  CharacterParams;                  //  In files; 
   class  CharacterHitReport;               //  In files; 
   class  CharacterController;              //  In files; 
   class  CharacterModel;                   //  In files; 
   class  CharacterMovementModel;           //  In files; 
   class  Performer;                        //  In files; 
   class  NxActorController;                //  In files; 
   class  KinematicCharacter;               //  In files; 
   typedef Container<std::string, CharacterSystem::CharacterMovementModel*>  CharacterMovementModels;
};
};


// Namespace "NxOgre" typedef
// ----------------------------------------------------------
namespace NxOgre {
   typedef Ogre::String   NxString;
   typedef NxU32          NxShapeIndex;
   typedef NxU32          NxErrorIndex;
   typedef NxU32          NxMeshID;
   typedef NxU32          NxSkeletonID;
   typedef NxU32          NxJointID;
   typedef NxReal         NxRadian;
   typedef unsigned long  NxHashIdentifier;
   typedef NxU16          NxShortHashIdentifier;
   typedef NxU32          NxRenderableSourceID;
   typedef NxU32          NxMachineID;
};


// Namespace "NxOgre" typedef's
// ----------------------------------------------------------
namespace NxOgre {

   /** \brief Simple identifier to identify a resource, and a resource type.
       \example
         "file://myMesh.mesh"
             Use the FileResourceSystem to read myMesh.mesh
         "file://media/resources/myMesh.mesh +write"
             Use the FileResourceSystem to write to myMesh.mesh"
         "ogre://myMesh.mesh"
             Use the OgreResourceSystem to load myMesh.mesh
         "myMesh.mesh"
             Use the FileResourceSystem to load myMesh.mesh, without a 
             resourcetype header; file is assumed.
   */
   typedef NxString ResourceIdentifier;
   
   
   /** \brief A list of resources, with an attached ResourceIdentifier
       \note std::map; First = Name of the resource (without extension) and second = Full ResourceIdentifier.
   */
   typedef std::map<NxString, NxString>  ResourceAccessList;
   
   
   /** \brief A list of actors, organised by name.
   */
   typedef Container<NxString, Actor*>  Actors;
   
   
   /** \brief A list of actor groups, organised by name.
   */
   typedef Container<NxString, ActorGroup*>  ActorGroups;
   
   
   /** \brief A list of actor groups, organised by NxActorGroup (unsigned short).
   */
   typedef Container<NxActorGroup, ActorGroup*>  ActorGroupsByIndex;
   
   
   /** \brief A list of string based properties identified by key and value.
   */
   typedef Container<NxString, NxString>  BlueprintUserData;
   
   
   /** \brief A list of Characters, identified by a NxString.
   */
   typedef Container<NxString, CharacterSystem::Character*>  Characters;
   
   
   /** \brief A list of error reporters, organised by NxErrorIndex (unsigned int).
   */
   typedef Container<NxErrorIndex, ErrorReporter*>  ErrorReporterList;
   
   /** \brief A list of joints.
   */
   typedef Container<NxJointID, Joint*>  Joints;
   
   
   /** \brief A list of machines.
   */
   typedef Container<NxMachineID, Machine*>  Machines;
   
   
   /** \brief A list of materials.
   */
   typedef Container<NxString, Material*>  MaterialList;
   
   
   /** \brief A list of materials organised by an NxMaterialIndex.
   */
   typedef Container<NxMaterialIndex, Material*>  MaterialListByIndex;
   
   
   /** \brief A list of materialpairs
   */
   typedef Container<NxString, NxMaterialIndex>  MaterialPair;
   
   
   /** \brief A list of Raycasts Hits
   */
   typedef Container<NxString, RayCastHit>  RayCastReport;
   
   /** \brief A list of Scenes organised by NxString.
   */
   typedef Container<NxString, Scene*>  Scenes;
   
   
   /** \brief A list of ShapeGroups organised by a NxString.
   */
   typedef Container<NxString, ShapeGroup*>  ShapeGroups;
   
   
   /** \brief A list of ShapeGroups organised by a NxCollisionGroup.
   */
   typedef Container<NxCollisionGroup, ShapeGroup*>  ShapeGroupsByIndex;
   
   
   /** \brief A simple list of NxString organised by an unsigned int.
   */
   typedef Container<NxU32, NxString>  StringList;
   
   
   /** \brief A simple list of triggers organised by a NxString
   */
   typedef Container<NxString, Trigger*>  Triggers;
   
   
   /** \brief A list of Wheels organised by an unsignd int.
   */
   typedef Container<NxU32, Wheel*>  Wheels;
   
   
   /// \deprecated
   typedef List<CharacterHitReport*>  CharacterHitReports;
   
   
   /** \brief Used to convert the material id's in a mesh to our own, aided with a MaterialAlias.
       \note  First is meshes material ID, second is the MaterialList's
   */
   typedef std::map<NxMaterialIndex, NxMaterialIndex> MaterialConversionList;
   
   
   /** \brief An identifier for actor/shape groups which has two forms of identification; unsigned
              int or a NxString.
   */
   typedef DualIdentifier<NxU32, NxString>  GroupIdentifier;
   
   
   /** \brief An identifier for materials which has two forms of identification; unsigned int
              or NxString.
   */
   typedef DualIdentifier<NxMaterialIndex, NxString>  MaterialIdentifier;
   
   
   /** \brief Throw error, error reporting function.
       \note  Use NxThrow, NxThrow_AsWarning macros instead of this function.
       \param message  Message to print
       \param type     Error type (0 = Debug, 1 = Warning, 2 = Fatal)
       \param source   Filename of the error
       \param line     Line of the error.
   */
   void NxPublicFunction NxThrow_impl(const char* message, unsigned int type, const char* source, unsigned int line);
   
   
   /** \brief prints a NxString to the operating system console window.
       \deprecated
   */
   void NxPublicFunction NxToConsole(const NxString&);
   
   /** \brief prints a NxString to the operating system console window with a [NxOgre] prefix.
   */
   void NxPublicFunction NxPrint(const char* message, const char* header = "NxOgre");
   
   /** \brief NxOgre Debug message macro.
    \param A Message to print
    \example
        NxDebug("I am right here.");
   */
   #define NxDebug(a)                NxThrow_impl(a, 0, __FUNCTION__, __LINE__);
   
   
   /** \brief NxOgre Throw a warning macro.
    \param A Message to print
    \example
        NxThrow_AsWarning("I am right here.");
   */
   #define NxThrow_AsWarning(a)      NxThrow_impl(a, 1, __FUNCTION__, __LINE__);
   
   
   /** \brief NxOgre Throw a error macro.
    \param A Message to print
    \example
        NxThrow("I am right here.");
   */
   #define NxThrow(a)                NxThrow_impl(a, 2, __FUNCTION__, __LINE__);
   
   
   /** \brief NxOgre construction placeholder. Used in functions that have incomplete or no
              code but must be implemented.
   */
   #define NxUnderConstruction       NxDebug("This function called contains no or little code.");
   
   
   /** \brief Resource identifier for when cooking or reading from to memory.
   */
   #define NxMemoryStreamIdentifier  "memory://"
   
   
   /** \brief Axis enum.
   */
   enum NxAxis {
     NxAxis_X           = 0,
     NxAxis_Y           = 1,
     NxAxis_Z           = 2,
     NxAxis_Negative_X  = 3,
     NxAxis_Negative_Y  = 4,
     NxAxis_Negative_Z  = 5,
     NxAxis_Up          = 1,
     NxAxis_Down        = 4
   };
   
   
   /** \brief Directional array as NxVec3 using NxAxis enum.
   */
   static const NxVec3 NxDirection[6] ={
     NxVec3( 1, 0, 0), // NxAxis_X
     NxVec3( 0, 1, 0), // NxAxis_Y, NxAxis_Up
     NxVec3( 0, 0, 1), // NxAxis_Z
     NxVec3(-1, 0, 0), // NxAxis_Negative_X
     NxVec3( 0,-1, 0), // NxAxis_Negative_Y, NxAxis_Down
     NxVec3( 0, 0,-1)  // NxAxis_Negative_Z
   };
   
   
   /** \brief String operator used with searching of identifiers.
   */
   enum NxStringOperator {
     SO_STARTS_WITH,
     SO_ENDS_WITH
   };
   
   
   /** \brief Comparison operator.
   */
   enum NxComparisonOperator {
     CO_MORE_THAN  = 0,
     CO_LESS_THAN  = 1,
     CO_EXACTLY    = 2,
     CO_NOT        = 3
   };
   
   
   /** \brief When a class' parent class is destroyed should it destroy this pointer along
              with it. GC_Never_Delete is handy when you are using your own classes with
              NxOgre and have your own system of handling pointers.
   */
   enum GarbageCollectionPolicy {
     /** \brief Never delete class (Class is privately owned by application).
     */
     GC_Never_Delete = 0,
     /** \brief Delete class (Usually when holder class is destroyed).
     */
     GC_Delete       = 1
   };
   
   
   /** \brief NxOgre classes (as an enum) that can be used with a VoidPointer.
   */
   enum NxOgreClassType {
   
    /** \brief Basic types. Used for any type of casting, including derivatives.
        \note Must be used in VoidPointers.
    */
    NxOgreClass_Unknown            = 0,
    NxOgreClass_World              = 1,
    NxOgreClass_PhysXDriver        = 2,
    NxOgreClass_Scene              = 3,
   
    NxOgreClass_Actor              = 10,
    NxOgreClass_SimpleActor        = 11,
    NxOgreClass_Character          = 12,
   
    NxOgreClass_Trigger            = 20,
    NxOgreClass_ForceField         = 21,
   
    NxOgreClass_Shape              = 30,
    NxOgreClass_CompoundShape      = 31,
    NxOgreClass_CharacterShape     = 32,
   
    /** \brief Derivatives; used for "light" casting.
        \note <em>Cannot</em> be used in VoidPointer.
    */
    NxOgreClass_Body               = 1000,
    NxOgreClass_Performer          = 1001
   };
   
};


#endif
