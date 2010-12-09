/** \file    NxOgreShape.h
 *  \brief   Header for the ShapeParams and Shape classes.
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

#ifndef __NXOGRE_SHAPE_H__
#define __NXOGRE_SHAPE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"
#include "NxOgreDualIdentifier.h"
#include "BetajaenCC.h"

namespace NxOgre {

	/** \page shapeparams ShapeParams
		
		String base params are case and space insensitive.

		Examples:
		
		<code>
			"offset: 1 0 1"

			"offset: 1 0 1, material: myMaterial"

			"offset: 1 0 1, material-index: 1, group: myGroup"
		</code>

		-	offset	(Vector3)
			- Description: Local offset of the shape compared to center of the Actor
			- Example:	"offset: 1 0 1"
			- See: ShapeParams::mLocalPose
		-	orientation (Quaternion)
			- Description: Local orientation of the shape.
			- Example:	"orientation: 1 0 0 1"
			- See: ShapeParams::mLocalPose
		-	generateCCD (bool)
			- Description: Generate a CCD skeleton for the shape.
			- Example:	"generateCCD: yes"
			- See: ShapeParams::mGenerateCCD
		-	generateCCDDelta (float)
			- Description: Delta value for the CCD skeleton generator
			- Example:	"generateCCDDelta: 0.8"
			- See: ShapeParams::mGenerateCCDDelta
		-	CCDDynamicFlag (bool)
			- Description: Enable Dynamic to Dynamic CCD.
			- Example:	"CCDDynamicFlag: true"
			- See: ShapeParams::mDynamicDynamicCCD
		-	material-index (unsigned int)
			- Description: NxMaterialIndex of the material to use. Use this or material, but not both.
			- Example:	"material-index: 1"
			- See: ShapeParams::mMaterialAsIndex
		-	material (string)
			- Description: Name of the material to use. Use this or material-index, but not both.
			- Example:	"material: myMaterial"
			- See: ShapeParams::mMaterialAsName
		-	group-index (unsigned int)
			- Description: NxCollisionGroup of the group to use. Use this or group, but not both.
			- Example:	"group-index: 1"
			- See: ShapeParams::mGroupAsIndex
		-	group (string)
			- Description: Name of the group to use. Use this or group-index, but not both.
			- Example:	"group: myCollisionGroup"
			- See: ShapeParams::mGroupAsName							
		-	skin-width (float)
			- Description: Skin Width of the shape
			- Example:	"skinwidth: -0.5"
			- See: ShapeParams::mSkinWidth		
		-	mesh-scale (Vector3)
			- Description: Scale any meshes (triangle, convex or heightmap) use with this shape.
			- Example:	"mesh-scale: 2 2 2"
			- See: ShapeParams::mMeshScale
		-	mass (float)
			- Description: Mass of this shape. Use this or density, do not use both. 
			- Example: "mass: 10"
			- See: ShapeParams::mMass and NxShape::mass for more information.
		-	density (float)
			- Description: Density of this shape. Use this or mass, do not use both.
			- Example: "Density: 1.5"
			- See: ShapeParams::mDensity and NxShape::density for more information.				
	*/

	/** \brief Params for all of the Shapes. Setting optional settings for the shape without
	           having a 50+ argument constructor.
	    \note  The Wheel shape uses it's own Params based upon the ShapeParams.
	    \See   \ref shapeparams for the full string argument documentation.
	*/
	class NxPublicClass ShapeParams : public Params {

		public:

			ShapeParams() {
			               setToDefault();
			              }

			ShapeParams(const char* p) {
			                            setToDefault();
			                            process(p);
			                           }

			ShapeParams(const NxString& p) {
			                                setToDefault();
			                                process(p);
			                                }

			/** \brief LocalPose of the shape from the Actors center.
				\note				
					For Quaternions use: m.M.fromQuat(NxQuat(w,x,y,z));
					For Vector3's use: m.t = NxVec3(x,y,z)
				\default mLocalPose.id()
			 */
			NxMat34 mLocalPose;

			/**  Automatically generate a CCD skeleton
				 \default	false
			 */
			bool mGenerateCCD;
			
			/**  Delta value for the CCD generator (How much the mesh will be scaled).
				 \default 0.8
			  */
			NxReal mGenerateCCDDelta;

			/** Allow Dynamic Dynamic CCD. (Sets NX_SF_DYNAMIC_DYNAMIC_CCD in mFlag to true).
				\default false
			 */
			bool mDynamicDynamicCCD;
			
			/**  Use a CCDSkeleton, but with this skeleton only.
			 	 \default NULL
			*/
			Skeleton* mCCDSkeleton;

			/** \brief Material to use. 
				\default 0, <blank string>
			*/
			MaterialIdentifier mMaterial;

			/** Use the ShapeGroup(NxCollisionGroup) from this name
			  	\default <blank string>
			 */
			NxString mGroupAsName;
			
			/** Use the ShapeGroup(NxCollisionGroup) from this index
				 \default 0
			 */
			NxCollisionGroup mGroupAsIndex;

			/**	GroupMask

			 */
			NxGroupsMask mGroupsMask;
			
			/** SkinWidth of the shape

			 */
			NxReal mSkinWidth;


			/** Mass of this individual shape when computing mass inertial properties for a rigidbody.
			    default (-1.0, calculate from density). Make sure density is 0.0 before changing.
			 */
			NxReal mMass;

			/** Density
				Density of this individual shape when computing mass inertial properties for a rigidbody.
				(Unless a valid mass >0.0 is provided). Make sure mass is -1.0 before changing.
				\default 1.0
			 */
			NxReal mDensity;
			
			/**  Specific ShapeFlags to be appended to the shape (NxBoxShape, NxConvexShape, etc.) flags.
				 \default NX_SF_VISUALISATION (Debug), 0 (Release)
			 */
			NxU32 mFlags;
			
			/** \brief Is the shape a trigger shape?
			*/
			bool  mTrigger;
			
			/** \brief The callback when the shape is a trigger
			*/
			TriggerContactCallback* mTriggerCallback;

			void setToDefault();
			void parse(Parameters);

			
	};// End of ShapeParams class

	////////////////////////////////////////////////////////////////////////////////////////////////

	/** \brief Shapes are wonderful things, they make matter spongy.
	*/
	class NxPublicClass Shape {

		public:


			/** \brief Shape Constructor.
				This is an empty class, create a shape using the constructor
				of the shape you wish to create; new CubeShape(), new SphereShape(), etc.
			*/
			Shape(NxShapeDesc* shape_description, const ShapeParams& = ShapeParams());

			/** \brief Alternate Shape constructor.
				This is an empty class, create a shape using the constructor
				of the shape you wish to create; new CubeShape(), new SphereShape(), etc.
				\note For usage when you don't want the params to be transfered to the NxShapeDesc
				      straight away.
			*/
			Shape();

			/** \brief Shape Destructor.
			*/
			virtual  ~Shape();


			/** \brief Copy this shape to another Actor
			*/
			virtual void  copyTo(Actor*, ShapeParams = ShapeParams()) = 0;


			/** \brief Move this shape to another Actor
			*/
			virtual void  moveTo(Actor*, ShapeParams = ShapeParams()) = 0;


			/** \brief Get the abstract NxShape.
			*/
			virtual NxShape*  getNxShape();


			/** \brief Get the CCD skeleton used with this shape
			*/
			virtual Skeleton*  getSkeleton();


			/** \brief Get the index assigned to this shape of an actor.
			*/
			NxShapeIndex  getIndex() const;


			/** \brief Set the index assigned to this shape of an actor.
			*/
			void  setIndex(NxShapeIndex index);


			/** \brief Get the String type of this shape
			*/
			virtual NxString  getShapeAsString()	const;

			/** \brief Get the Hash type of this shape.
			*/
			virtual NxShortHashIdentifier  getTypeHash() const;

			/** \brief Has the shape been attached to an actor yet?
			*/
			virtual bool  isAttached() const;


			/** \brief Get's a copy of the TriggerCallback, otherwise NULL if the
				       Shape does not have one.
			*/
			TriggerContactCallback*  getTriggerCallback();


			/** \brief Implement the shape based on description and parameters to an existing
			           actor.
			*/
			virtual void  createShape(NxActor* actor, NxShapeIndex, Scene* scene) = 0;


			/** \brief Implement the shape based on description and parameters to an actor
			           description.
			*/
			virtual void  createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene) = 0;


			/** \brief Recieve the copy of the NxShape, and it's index to the actor.
				\note  Used after creating the NxShape, the actor gives the shape the nxshape
					   and it's index.
			*/
			virtual void  setNxShape(NxShape*);


			/** \brief Release the shape based on description and parameters
			*/
			virtual void  releaseShape() = 0;

			
			/** \brief Shape params to description
			*/
			virtual void  paramsToDescription(NxShapeDesc*, ShapeParams*);


			/** \brief Extended Shape params to description
			*/
			void  extendedParamsToDescription(Scene*, const ShapeParams& params, NxShapeDesc*);

			/** \brief Is the shape description valid? In Debug mode details of why it's invalid
				is reported to the error.
			*/
			bool  isValid(NxShapeDesc&) const;

			NxShapeIndex                mShapeIndex;
			ShapeParams                 mParams;
			NxActor*                    mActor;
			NxShape*                    mNxShape;
			Skeleton*                   mSkeleton;
			VoidPointer*                mVoidPointer;
			TriggerContactCallback*     mTriggerCallback;

	};

	/////////////////////////////////////////////////////////

	
	/** \brief A Compound Shape, isn't really a shape. It just groups many shapes together that
	           can be used as one. Usually Compound shapes are used to make complicated actors
	           that can't be represented solely by one shape; Tables are a good example of this.
	    \note  After the CompoundShape has been passed to the Actor, the contents are taken out
	           and the CompoundShape pointer is deleted.
	*/
	class NxPublicClass CompoundShape : public Shape {

		friend class Actor;

		public:
			
			CompoundShape();
			~CompoundShape();

			void add(Shape*);

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

			NxShortHashIdentifier  getTypeHash() const;

		protected:

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

			unsigned int                 mNbShapes;
			Betajaen::SharedMap<unsigned int, Shape>  mShapes;

	};
};

#endif
