/** \file    NxOgreSkeleton.cpp
 *  \see     NxOgreSkeleton.h
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

#include "NxOgreStable.h"
#if 0
#include "NxOgreSkeleton.h"
#include "NxOgreShapeBlueprintPrimitives.h"
#include "NxOgreResourceManager.h"

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////////////////

CubeSkeleton::CubeSkeleton(NxVec3 size, NxMat33 rot) : Skeleton() {
	
	NxPhysicsSDK* mSDK = NxGetPhysicsSDK();

	if (mSDK == 0)
		return;


	NxU32 triangles[3 * 12] = { 
		0,1,3,
		0,3,2,
		3,7,6,
		3,6,2,
		1,5,7,
		1,7,3,
		4,6,7,
		4,7,5,
		1,0,4,
		5,1,4,
		4,0,2,
		4,2,6
	};

	NxVec3 points[8];

	// Static mesh
	points[0].set( size.x, -size.y, -size.z);
	points[1].set( size.x, -size.y,  size.z);
	points[2].set( size.x,  size.y, -size.z);
	points[3].set( size.x,  size.y,  size.z);

	points[4].set(-size.x, -size.y, -size.z);
	points[5].set(-size.x, -size.y,  size.z);
	points[6].set(-size.x,  size.y, -size.z);
	points[7].set(-size.x,  size.y,  size.z);

	NxSimpleTriangleMesh stm;
	stm.numVertices = 8;
	stm.numTriangles = 6*2;
	stm.pointStrideBytes = sizeof(NxVec3);
	stm.triangleStrideBytes = sizeof(NxU32)*3;

	stm.points = points;
	stm.triangles = triangles;
	stm.flags |= NX_MF_FLIPNORMALS;


	mSkeleton = mSDK->createCCDSkeleton(stm);

}

////////////////////////////////////////////////////////////////////////////////////////////////

CubeSkeleton::~CubeSkeleton() {
	NxPhysicsSDK* mSDK = NxGetPhysicsSDK();
	
	if (mSDK == 0)
		return;

	mSDK->releaseCCDSkeleton(*mSkeleton);

}

////////////////////////////////////////////////////////////////////////////////////////////////

SphereSkeleton::SphereSkeleton(NxReal size, NxMat33 offset) : Skeleton() {
	
	NxPhysicsSDK* mSDK = NxGetPhysicsSDK();

	if (mSDK == 0)
		return;


	NxSimpleTriangleMesh stm;



	mSkeleton = mSDK->createCCDSkeleton(stm);

}

////////////////////////////////////////////////////////////////////////////////////////////////

SphereSkeleton::~SphereSkeleton() {

	NxPhysicsSDK* mSDK = NxGetPhysicsSDK();
	
	if (mSDK == 0)
		return;

	mSDK->releaseCCDSkeleton(*mSkeleton);

}

////////////////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
#endif
