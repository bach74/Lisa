/** \file    NxOgreIntersection.h
 *  \brief   Header for the Intersection, SimpleIntersection and Culled-
 *           Intersection classes.
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

#ifndef __NXOGRE_INTERSECTION_H__
#define __NXOGRE_INTERSECTION_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreActor.h"			// Used for Actors inheritance
#include "NxOgreContainer.h"		// An intersection is a container of actors.

namespace NxOgre {

	/////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass Intersection : public Actors, public NxUserEntityReport<NxShape*> {
		
		public:

			Intersection(Scene*, SimpleShape*, NxShapesType shapeFilter = NX_ALL_SHAPES);
			~Intersection();

			void				setShape(SimpleShape*);
			void				intersect();
			bool				onEvent(NxU32, NxShape**);

		protected:

			Scene*				mScene;
			NxShapesType		mShapeFilter;

		private:
			
			SimpleShape*		mShape;
	};

	/////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass SimpleIntersection {

		public:

			SimpleIntersection(Scene*, SimpleShape*, NxShapesType shapeFilter = NX_ALL_SHAPES);
			~SimpleIntersection();

			void		setShape(SimpleShape*);
			bool		intersect();

			// Get's the result of the last intersection.
			bool		getResult();

		private:

			Scene*				mScene;
			SimpleShape*		mShape;
			NxShapesType		mShapeFilter;
			NxPlane*			mPlanes;
			NxU32				mNbPlanes;
			bool				mIntersectionValue;

	};

	/////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass CulledIntersection : public Actors, public NxUserEntityReport<NxShape*>  {

		public:

			CulledIntersection(Scene*, std::vector<SimplePlane*>, NxShapesType shapeFilter = NX_ALL_SHAPES);
			~CulledIntersection();

			virtual void intersect();
			bool onEvent(NxU32, NxShape**);

		private:

			Scene*				mScene;
			NxShapesType		mShapeFilter;
			NxPlane*			mPlanes;
			NxU32				mNbPlanes;

	};
	
	/////////////////////////////////////////////////////////////////////////////////////////

};

#endif
