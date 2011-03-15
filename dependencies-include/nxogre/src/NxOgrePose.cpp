/** \file    NxOgrePose.cpp
 *  \see     NxOgrePose.h
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
#include "NxOgrePose.h"
#include "NxOgreHelpers.h"

#include "OgreStringConverter.h"

namespace NxOgre {

#if 0

//////////////////////////////////////////////////////////

Pose::Pose() {
	v.zero();
	q.id();
}

//////////////////////////////////////////////////////////

Pose::Pose(const Ogre::Vector3& _v) {
	v.set(_v.x,_v.y,_v.z);
	q.id();
}

//////////////////////////////////////////////////////////

Pose::Pose(const Ogre::Vector3& _v, const Ogre::Quaternion& _q) {
	v.set(_v.x,_v.y,_v.z);
	q.setWXYZ(_q.w,_q.x,_q.y,_q.z);
}

//////////////////////////////////////////////////////////

Pose::Pose(const NxVec3& _v, const NxQuat& _q) {
	v.set(_v.x,_v.y,_v.z);
	q.setWXYZ(_q.w,_q.x,_q.y,_q.z);
}

//////////////////////////////////////////////////////////

Pose::Pose(const Ogre::Quaternion& _q) {
	v.zero();
	q.setWXYZ(_q.w,_q.x,_q.y,_q.z);
}

//////////////////////////////////////////////////////////

Pose::Pose(NxReal _x, NxReal _y, NxReal _z) {
	v.set(_x,_y,_z);
	q.id();
}

//////////////////////////////////////////////////////////

Pose::Pose(NxReal _w, NxReal _x, NxReal _y, NxReal _z) {
	v.zero();
	q.setWXYZ(_w,_x,_y,_z);
}

//////////////////////////////////////////////////////////

Pose::Pose(const NxVec3& vec) {
	v.set(vec.x, vec.y, vec.z);
	q.id();
}

//////////////////////////////////////////////////////////

Pose::Pose(const NxQuat& quat) {
	v.zero();
	q.setWXYZ(quat.w,quat.x,quat.y,quat.z);
}

//////////////////////////////////////////////////////////

void Pose::id() {
	v.zero();
	q.id();
}

//////////////////////////////////////////////////////////

void Pose::set(const Ogre::Vector3& _v) {
	v.set(_v.x,_v.y,_v.z);
}

//////////////////////////////////////////////////////////

void Pose::set(const Ogre::Quaternion& _q) {
	q.setWXYZ(_q.w,_q.x,_q.y,_q.z);
}

//////////////////////////////////////////////////////////

Ogre::Vector3 Pose::getVector3() const {
	return Ogre::Vector3(v.x,v.y,v.z);
}

//////////////////////////////////////////////////////////

Ogre::Quaternion Pose::getQuaternion() const {
	return Ogre::Quaternion(q.w,q.x,q.y,q.z);
}

//////////////////////////////////////////////////////////

NxVec3 Pose::getVec3() const {
	return v;
}

//////////////////////////////////////////////////////////

NxQuat Pose::getQuat() const {
	return q;
}

//////////////////////////////////////////////////////////

bool Pose::isZero() {
	return ((1 == q.w && 0 == q.x && 0 == q.y && 0 == q.z) && (v.x == 0 && v.y == 0 && v.z == 0));
}

//////////////////////////////////////////////////////////

void Pose::fromMat34(const NxMat34 &m) {
	v.set(m.t);
	m.M.toQuat(q);
}

//////////////////////////////////////////////////////////

NxMat34 Pose::toMat34() const {
	NxMat34 m;
	m.t.set(v);
	m.M.fromQuat(q);
	return m;
}

//////////////////////////////////////////////////////////

void Pose::fromMat33(const NxMat33& m) {
	m.toQuat(q);
}

//////////////////////////////////////////////////////////

NxMat33 Pose::toMat33() const {
	NxMat33 m;
	m.fromQuat(q);
	return m;
}

//////////////////////////////////////////////////////////

NxString Pose::toString() const {
		return	Ogre::StringConverter::toString(v.x) + "," +
				Ogre::StringConverter::toString(v.y) + "," +
				Ogre::StringConverter::toString(v.z) + " " +
				Ogre::StringConverter::toString(q.w) + "," +
				Ogre::StringConverter::toString(q.x) + "," +
				Ogre::StringConverter::toString(q.y) + "," +
				Ogre::StringConverter::toString(q.z);
}

//////////////////////////////////////////////////////////

#endif

}; //End of NxOgre namespace.
