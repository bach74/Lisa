/** \file    NxOgreSimpleShape.cpp
 *  \see     NxOgreSimpleShape.h
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
#include "NxOgreSimpleShape.h"
#include "NxOgreHelpers.h"

#include "OgreStringVector.h"

namespace NxOgre {

//////////////////////////////////////////////////////////////////////////////////////

SimpleShape*	SimpleShape::createFromString(const NxString& str) {
	Ogre::StringVector strings = Ogre::StringUtil::split(str, ":", 2);

	SimpleShape* shape = 0;

	if (strings.size() != 2)
		return shape;

	Ogre::StringUtil::toLowerCase(strings[0]);
	Ogre::StringUtil::trim(strings[0]);
	Ogre::StringUtil::trim(strings[1]);

	if (strings[0] == "cube" || strings[0] == "box") {
		NxVec3 size(1,1,1);
		size = NxFromString<NxVec3>(strings[1]);
		shape = new SimpleBox(size);
	}
	

	return shape;
}

//////////////////////////////////////////////////////////////////////////////////////

SimpleBox* SimpleShape::getAsBox() {
	return static_cast<SimpleBox*>(this);
}

//////////////////////////////////////////////////////////////////////////////////////

SimpleSphere* SimpleShape::getAsSphere() {
	return static_cast<SimpleSphere*>(this);
}

//////////////////////////////////////////////////////////////////////////////////////

SimpleCapsule* SimpleShape::getAsCapsule() {
	return static_cast<SimpleCapsule*>(this);
}

//////////////////////////////////////////////////////////////////////////////////////

SimpleConvex* SimpleShape::getAsConvex() {
	return static_cast<SimpleConvex*>(this);
}

//////////////////////////////////////////////////////////////////////////////////////

SimplePlane* SimpleShape::getAsPlane() {
	return static_cast<SimplePlane*>(this);
}

//////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
