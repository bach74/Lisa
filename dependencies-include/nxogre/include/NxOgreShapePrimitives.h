/** \file    NxOgreShapePrimitives.h
 *  \brief   Header for the Ground, Cube, Sphere and Capsule classes.
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

#ifndef __NXOGRE_SHAPE_PRIMITIVES_H__
#define __NXOGRE_SHAPE_PRIMITIVES_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreShape.h"				// For: Primitives inherits Shape

namespace NxOgre {
	
	/////////////////////////////////////////////////////////

	/** \brief Ground (NxPlaneShape) is the most simplest shape in PhysX. It's designed
			   to provide a ground plane which is infinite in size.
	*/
	class NxPublicClass Ground : public Shape {

		public:
			
			/** \brief Ground Constructor (PhysX units) (Default Constructor)

				\param Distance		Distance from the center.
				\param Normal		Direction of the plane.
				\param ShapeParams	Params for this shape.
			*/
			Ground(NxReal distance = 0, NxVec3 normal = NxVec3(0, 1, 0), const ShapeParams& = ShapeParams());


			/** \brief Ground Constructor (Ogre units).

				\param Distance		Distance from the center.
				\param Normal		Direction of the plane.
				\param ShapeParams	Params for this shape.
			*/
			Ground(NxReal distance, Ogre::Vector3 normal, const ShapeParams& = ShapeParams());



			/** \brief Ground destructor.
			*/
			~Ground();


			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:	
			
			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();
		
		protected:

			NxPlaneShapeDesc mShapeDescription;

	};
	
	/////////////////////////////////////////////////////////

	/** \brief Cube (NxBoxShape) is probably the most common shape used in NxOgre,
			   in most cases nearly everything can be represented by a cube or cubes.
	*/
	class NxPublicClass Cube : public Shape {

		public:

			/** \brief Cube Constructor (Ogre units)
			*/
			Cube(Ogre::Vector3 size, const ShapeParams& = ShapeParams());

			/** \brief Cube Constructor (PhysX units)
			*/
			Cube(NxVec3 size, const ShapeParams& = ShapeParams());

			/** \brief Cube Constructor, where the length all sides of the cube is equal.
			*/
			Cube(NxReal sizeCubed, const ShapeParams& = ShapeParams());

			/** \brief Cube Constructor, Lazy version
			*/
			Cube(NxReal sizeX, NxReal sizeY, NxReal sizeZ, const ShapeParams& = ShapeParams());

			/** \brief Cube destructor
			*/
			~Cube();

			/** \brief Set the dimensions of the Cube.
				\note If you are setting the dimensions once the shape is created, the actor is not
					  woken to notice the changes.
			*/
			void setDimensions(const NxVec3& size);

			/** \brief Get's the dimensions of the Cube
			*/
			NxVec3 getDimensions() const;

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:	
			
			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();
		
		protected:

			NxBoxShapeDesc mShapeDescription;

	};

	/////////////////////////////////////////////////////////

	/** \brief Sphere (NxSphereShape) provides a perfect sphere.
	*/
	class NxPublicClass Sphere : public Shape {

		public:

			/** \brief Sphere constructor.
			*/
			Sphere(NxReal radius, const ShapeParams& = ShapeParams());

			/** \brief Sphere destructor.
			*/
			~Sphere();

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:	

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

		protected:

			NxSphereShapeDesc mShapeDescription;

	};

	/////////////////////////////////////////////////////////

	/** \brief Capsule (NxCapsuleShape) provides a capsule.
	*/
	class NxPublicClass Capsule : public Shape {

		public:

			/** \brief Capsule constructor.
			*/
			Capsule(NxReal radius, NxReal height, const ShapeParams& = ShapeParams());

			/** \brief Capsule destructor.
			*/
			~Capsule();

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:	

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

		protected:

			NxCapsuleShapeDesc mShapeDescription;

	};

	/////////////////////////////////////////////////////////

} // End of namespace

#endif
