/** \file    NxOgreSimpleShape.h
 *  \brief   Header for the SimpleShape, SimpleBoxShape, SimpleSphereShape,
 *           SimpleCapsuleShape and SimpleConvexShape classes.
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

#ifndef __NXOGRE_SIMPLE_SHAPE_H__
#define __NXOGRE_SIMPLE_SHAPE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"
#include "NxOgrePose.h"

#include "OgrePlane.h"				// For Ogre Plane
#include "OgreVector3.h"			// For Various
#include "OgreQuaternion.h"			// For Various

namespace NxOgre {

	////////////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass SimpleShape {

		public:

			/** \brief Creates a Simple Shape from a basic string.

				\example
					<code>
						"cube: 1 1 1"
						"box: 1 1 1"
						"capsule: 1 1"
						"sphere: 1"
						"plane: 1 1 1 1.0"
						"convex: convexName"
						"trianglemesh: triangleName"
					</code>
			*/
			static SimpleShape*	createFromString(const NxString&);

			enum SimpleShapeType{
				SST_Plane,
				SST_Box,
				SST_Sphere,
				SST_Capsule,
				SST_Convex
			};

			SimpleShapeType getType()						{return mType;}
			void setInverse(bool i)							{mInverse = i;}
			bool getInverse()								{return mInverse;}


			SimplePlane*	getAsPlane();
			SimpleBox*		getAsBox();
			SimpleSphere*	getAsSphere();
			SimpleCapsule*	getAsCapsule();
			SimpleConvex*	getAsConvex();

			virtual ~SimpleShape() {}

		protected:

			SimpleShape(SimpleShapeType type) : mType(type) {} 
			SimpleShapeType						mType;

			/** "Inverse Shape"
				If the Shape is inside out or not.
				 With ForceFields then the shape is an exclusion with false, and inclusion to true;
				 With OverlapTest then this is ???.
			*/
			bool								mInverse;

	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass SimplePlane : public SimpleShape {
	
		friend class SimpleShape;

		public:

			SimplePlane(NxReal x, NxReal y, NxReal z, NxReal d) : SimpleShape(SimpleShape::SST_Plane), 
				mNormal(x,y,z), mDistance(d) {}

			SimplePlane(NxVec3 normal, NxReal distance) : SimpleShape(SimpleShape::SST_Plane),
				mNormal(normal), mDistance(distance) {}

			SimplePlane(NxPlane plane) : SimpleShape(SimpleShape::SST_Plane) {
				mNormal = plane.normal;
				mDistance = plane.d;
			}

			SimplePlane(Ogre::Plane plane) : SimpleShape(SimpleShape::SST_Plane) {
				mNormal.set(plane.normal.x, plane.normal.y, plane.normal.z);
				mDistance = plane.d;
			}

			~SimplePlane() {}

			NxVec3		getNormal() {return mNormal;}
			NxF32		getDistance() {return mDistance;}
		protected:

			NxVec3		mNormal;
			NxF32		mDistance;

	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass SimpleBox : public SimpleShape {
		
		friend class SimpleShape;

		public:

			SimpleBox(NxReal s) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(s,s,s);
				mPose.id();
			}
			
			SimpleBox(NxReal w, NxReal h, NxReal d) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(w, h, d);
				mPose.id();
			}

#if NX_USE_OGRE == 1
			SimpleBox(const Ogre::Vector3& d) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(d);
				mPose.id();
			}
#endif

#if NX_USE_OGRE == 1
			SimpleBox(const Ogre::Vector3& d, const NxOgre::Pose& p) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(d);
				setPose(p);
			}

#endif
			SimpleBox(const NxVec3& d) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(d);
				mPose.id();
			}

			SimpleBox(const NxVec3& d, const NxMat34& p) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(d);
				setPose(p);
			}
			
			SimpleBox(const float3& d) : SimpleShape(SimpleShape::SST_Box) {
				setDimensions(d);
				mPose.id();
			}

			SimpleBox(const float3& d, const NxOgre::Pose& p) : SimpleShape(SimpleShape::SST_Box)  {
				setDimensions(d);
				setPose(p);
			}

			~SimpleBox() {}

			void setDimensions(NxReal x, NxReal y, NxReal z)  {mDimensions.set(x, y, z);}
			void setDimensions(const NxVec3& d)         {mDimensions = d;}
			void setDimensions(const float3& d)         {mDimensions.set(d.i, d.j, d.k);}
#if NX_USE_OGRE == 1
			void setDimensions(const Ogre::Vector3& d)  {mDimensions.set(d.x, d.y, d.z);}
#endif

			void setPose(const NxMat34& p)              {mPose = p;}
			void setPose(const NxOgre::Pose& p)         {mPose = p;}

			NxVec3 getDimensionsAsNxVec3()              {return mDimensions;}
			float3 getDimensions()                      {return float3(mDimensions.x, mDimensions.y, mDimensions.z);}
#if NX_USE_OGRE == 1
			Ogre::Vector3 getDimensionsAsOgreVector3()  {return Ogre::Vector3(mDimensions.x, mDimensions.y, mDimensions.z);}
#endif

			NxMat34 getPoseAsNxMat34()                  {return mPose;}
			Pose    getPose()                           {return NxOgre::Pose(mPose);}
		protected:
			
			NxVec3		mDimensions;
			NxMat34		mPose;

	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass SimpleSphere : public SimpleShape {
		
		friend class SimpleShape;

		public:

			SimpleSphere(NxReal radius) : SimpleShape(SimpleShape::SST_Sphere), mRadius(radius) {}
			SimpleSphere(NxReal radius, NxOgre::Pose p) : SimpleShape(SimpleShape::SST_Sphere), mRadius(radius) {mPose = p;}
			SimpleSphere(NxReal radius, NxMat34 pose) : SimpleShape(SimpleShape::SST_Sphere), mRadius(radius), mPose(pose) {}
			~SimpleSphere()			{}

			NxReal getRadius()			{return mRadius;}
			NxMat34 getPose()			{return mPose;}

	protected:
			
			NxReal		mRadius;
			NxMat34		mPose;
	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass SimpleCapsule : public SimpleShape {
		
		friend class SimpleShape;

		public:

			SimpleCapsule(NxReal r, NxReal h) : SimpleShape(SimpleShape::SST_Sphere), mRadius(r), mHeight(h) {}
			SimpleCapsule(NxReal r, NxReal h, NxOgre::Pose p) : SimpleShape(SimpleShape::SST_Sphere), mRadius(r), mHeight(h) {mPose = p;}
			SimpleCapsule(NxReal r, NxReal h, NxMat34 pose) : SimpleShape(SimpleShape::SST_Sphere), mRadius(r), mHeight(h) {}
			~SimpleCapsule() {}

			NxReal getRadius()		{return mRadius;}
			NxReal getHeight()		{return mHeight;}
			NxMat34 getPose()		{return mPose;}

		protected:
			
			NxReal		mRadius;
			NxReal		mHeight;
			NxMat34		mPose;
	};

	///////////////////////////////////////////////////////////////////////

	/** SimpleConvex
		@todo
	 */
	class NxPublicClass SimpleConvex : public SimpleShape {

		friend class SimpleShape;

		public:

			SimpleConvex() : SimpleShape(SimpleShape::SST_Convex) {}
			~SimpleConvex() {}

		protected:

	};

	///////////////////////////////////////////////////////////////////////

};

#endif
