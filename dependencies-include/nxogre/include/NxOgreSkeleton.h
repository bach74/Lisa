#if 0
/** \file    NxOgreSkeleton.h
 *  \brief   Header for the Skeleton, CubeSkeleton, SphereSkeleton classes.
 *  \version 1.0-20
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

#ifndef __NXOGRE_SKELETON_H__
#define __NXOGRE_SKELETON_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

namespace NxOgre {

	////////////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass Skeleton {

		public:

			Skeleton() {mSkeleton = 0;}
			virtual ~Skeleton() {}

			NxCCDSkeleton* getSkeleton() {return mSkeleton;}

		protected:

			NxCCDSkeleton* mSkeleton;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass CubeSkeleton : public Skeleton {

		public:

			
			CubeSkeleton(NxVec3 size, NxMat33 rot);
			~CubeSkeleton();

	};

	////////////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass SphereSkeleton : public Skeleton {

		public:

			
			SphereSkeleton(NxReal radius, NxMat33 rot);
			~SphereSkeleton();

	};

	////////////////////////////////////////////////////////////////////////////////////////////////

};

#endif
#endif