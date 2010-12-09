/** \file    NxOgreShapeMeshes.h
 *  \brief   Header for the Convex, Prism and TriangleMesh classes.
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

#ifndef __NXOGRE_SHAPE_MESHES_H__
#define __NXOGRE_SHAPE_MESHES_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreShape.h"				// For: Primitives inherits Shape

namespace NxOgre {

	/////////////////////////////////////////////////////////

	/** \brief Convex (NxConvexShape) provide a convex shape.
		\note For Concave shapes; a collection of Convex shapes is used to make up the various
		parts of that shape or if it's easier use a TriangleMesh.
	*/
	class NxPublicClass Convex : public Shape {

		public:

			/** \brief Convex Constructor; using a direct mesh
			*/
			Convex(Resources::Mesh*, const ShapeParams& = ShapeParams());

			/** \brief Convex Constructor; loading a resource to use as a mesh.
			*/
			Convex(const Resources::ResourceIdentifier&, const ShapeParams& = ShapeParams());

			/** \brief Convex destructor
			*/
			~Convex();

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:

			bool isConvexShapeValid() const;

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

		protected:

			NxConvexShapeDesc                mShapeDescription;
			Resources::ResourceIdentifier    mResourceIdentifier;
			Resources::Mesh*                 mMesh;

	};


	////////////////////////////////////////////////////////////////////

	/** \brief TriangleMesh (NxConvexShape) provide a TriangleMesh shape.
	*/
	class NxPublicClass TriangleMesh : public Shape {

		public:

			/** \brief TriangleMesh Constructor; using a direct mesh
			*/
			TriangleMesh(Resources::Mesh*, const ShapeParams& = ShapeParams());

			/** \brief TriangleMesh Constructor; loading a resource to use as a mesh.
			*/
			TriangleMesh(const Resources::ResourceIdentifier&, const ShapeParams& = ShapeParams());

			/** \brief TriangleMesh destructor
			*/
			~TriangleMesh();

			virtual void copyTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}
			virtual void moveTo(Actor*, ShapeParams = ShapeParams()) {NxUnderConstruction;}

		protected:

			bool isTriangleMeshShapeValid() const;

			virtual void createShape(NxActor* actor, NxShapeIndex, Scene* scene);
			virtual void createShape(NxArray<NxShapeDesc*>& shapes, NxShapeIndex, Scene* scene);
			virtual void releaseShape();

		protected:

			NxTriangleMeshShapeDesc          mShapeDescription;
			Resources::ResourceIdentifier    mResourceIdentifier;
			Resources::Mesh*                 mMesh;

	};



} // End of namespace

#endif
 