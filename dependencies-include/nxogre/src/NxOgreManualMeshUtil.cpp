/** \file    NxOgreManualMesh.cpp
 *  \see     NxOgreManualMesh.h
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

#include "NxOgreStable.h"

#ifndef NX_SMALL

#include "NxOgreManualMeshUtil.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

/*

// Cube with normals.

const float sqrt13 = 0.577350269f;
const float size = 2;

cube_test->vertex(-size,size,-size);		//0 position
cube_test->vertex(size,size,-size);			//1 position
cube_test->vertex(size,-size,-size);		//2 position
cube_test->vertex(-size,-size,-size);		//3 position
cube_test->vertex(-size,size,size);			//4 position
cube_test->vertex(size,size,size);			//5 position
cube_test->vertex(size,-size,size);			//6 position
cube_test->vertex(-size,-size,size);		//7 position

cube_test->normal(-sqrt13,sqrt13,-sqrt13);	//0 normal
cube_test->normal(sqrt13,sqrt13,-sqrt13);	//1 normal
cube_test->normal(sqrt13,-sqrt13,-sqrt13);	//2 normal
cube_test->normal(-sqrt13,-sqrt13,-sqrt13); //3 normal
cube_test->normal(-sqrt13,sqrt13,sqrt13);	//4 normal
cube_test->normal(sqrt13,sqrt13,sqrt13);	//5 normal
cube_test->normal(sqrt13,-sqrt13,sqrt13);	//6 normal
cube_test->normal(-sqrt13,-sqrt13,sqrt13);	//7 normal

cube_test->triangle(0,2,3);
cube_test->triangle(0,1,2);
cube_test->triangle(1,6,2);
cube_test->triangle(1,5,6);
cube_test->triangle(4,6,5);
cube_test->triangle(4,7,6);
cube_test->triangle(0,7,4);
cube_test->triangle(0,3,7);
cube_test->triangle(0,5,1);
cube_test->triangle(0,4,5);
cube_test->triangle(2,7,3);
cube_test->triangle(2,6,7);

*/

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.

#endif
