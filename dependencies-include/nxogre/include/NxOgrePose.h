/** \file    NxOgrePose.h
 *  \brief   Header for the Pose class
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

#ifndef __NXOGRE_POSE_H__
#define __NXOGRE_POSE_H__

#include "NxOgrePrerequisites.h"
#include "BetajaenCC.h"

#if (NX_USE_OGRE == 1)
#  include "OgreVector3.h"
#  include "OgreQuaternion.h"
#endif

namespace NxOgre {

	class NxPublicClass Pose {

		public:

			Pose() { m.id();
			}

			Pose(const float3& vector) { m.id();
				m.t.x = vector.i; m.t.y = vector.j; m.t.z = vector.k;
			}

			Pose(const float4& quaternion) { m.id();
				NxQuat q; q.setWXYZ(quaternion.i, quaternion.j, quaternion.k, quaternion.l);
				m.M.fromQuat(q);
			}


			Pose(const float3& vector, const float4& quaternion) { m.id();
				m.t.x = vector.i; m.t.y = vector.j; m.t.z = vector.k;
				NxQuat q; q.setWXYZ(quaternion.i, quaternion.j, quaternion.k, quaternion.l);
				m.M.fromQuat(q);
			}

			Pose(const float4& quaternion, const float3& vector) { m.id();
				m.t.x = vector.i; m.t.y = vector.j; m.t.z = vector.k;
				NxQuat q; q.setWXYZ(quaternion.i, quaternion.j, quaternion.k, quaternion.l);
				m.M.fromQuat(q);
			}

#if (NX_USE_OGRE == 1)

			Pose(const Ogre::Vector3& vector) { m.id();
				m.t.set(vector.x, vector.y, vector.z);
			}

			Pose(const Ogre::Quaternion& quaternion) { m.id();
				NxQuat q; q.setWXYZ(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
				m.M.fromQuat(q);
			}

			Pose(const Ogre::Vector3& vector, const Ogre::Quaternion& quaternion) { m.id();
				m.t.set(vector.x, vector.y, vector.z);
				NxQuat q; q.setWXYZ(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
				m.M.fromQuat(q);
			}

			Pose(const Ogre::Quaternion& quaternion, const Ogre::Vector3& vector) { m.id();
				m.t.set(vector.x, vector.y, vector.z);
				NxQuat q; q.setWXYZ(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
				m.M.fromQuat(q);
			}

#endif

			Pose(const NxVec3& vector, const NxQuat& quaternion) { m.id();
				m.t = vector;
				m.M.fromQuat(quaternion);
			}

			Pose(const NxQuat& quaternion, const NxVec3& vector) { m.id();
				m.t = vector;
				m.M.fromQuat(quaternion);
			}

			Pose(const NxVec3& vector) { m.id();
				m.t = vector;
			}

			Pose(const NxQuat& quaternion) { m.id();
				m.M.fromQuat(quaternion);
			}

			Pose(const NxMat33& mat) {
				m.M = mat;
				m.t.zero();
			}

			Pose(const NxMat34& mat) {
				m = mat;
			}

			Pose(NxReal vectorX, NxReal vectorY, NxReal vectorZ) { m.id();
				m.t.set(vectorX, vectorY, vectorZ);
			}

			Pose(NxReal quaternionW, NxReal quaternionX, NxReal quaternionY, NxReal quaternionZ) { m.id();
				NxQuat q; q.setWXYZ(quaternionW, quaternionX, quaternionY, quaternionZ);
				m.M.fromQuat(q);
			}

			void zero() {
				m.zero();
			}

			void id() {
				m.id();
			}

			inline bool isZero() const {
				return (m.M.isZero() && m.t.isZero());
			}

			inline bool isIdentity() const {
				return (m.isIdentity());
			}

			Pose& operator=(const Pose& pose) {
				m.M = pose.m.M;
				m.t = pose.m.t;
				return *this;
			}

			Pose& operator=(const NxMat34& mat) {
				m.M = mat.M;
				m.t = mat.t;
				return *this;
			}

			operator NxMat34 (void) const {
				return m;
			}

			Pose& operator=(const NxMat33& mat) {
				m.M = mat;
				m.t.zero();
				return *this;
			}

			operator NxMat33 (void) const {
				return m.M;
			}

			Pose& operator=(const float3& vector) { m.id();
				m.t.x = vector.i; m.t.y = vector.j; m.t.z = vector.k;
				return *this;
			}

			operator float3 (void) const {
				return float3(m.t.x, m.t.y, m.t.z);
			}

			Pose& operator=(const float4& quaternion) { m.id();
				NxQuat q; q.setWXYZ(quaternion.i, quaternion.j, quaternion.k, quaternion.l);
				m.M.fromQuat(q);
				return *this;
			}

			operator float4 (void) const {
				NxQuat q; m.M.toQuat(q);
				return float4(q.w, q.x, q.y, q.z);
			}

#if (NX_USE_OGRE == 1)

			Pose& operator=(const Ogre::Vector3& vector) {  m.id();
				m.t.x = vector.x; m.t.y = vector.y; m.t.z = vector.z;
				return *this;
			}

			operator Ogre::Vector3 (void) const {
				return Ogre::Vector3(m.t.x, m.t.y, m.t.z);
			}

			Pose& operator=(const Ogre::Quaternion& quaternion) { m.id();
				NxQuat q; q.setWXYZ(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
				m.M.fromQuat(q);
				return *this;
			}

			operator Ogre::Quaternion(void) const {
				NxQuat q; m.M.toQuat(q);
				return  Ogre::Quaternion(q.w, q.x, q.y, q.z);
			}

#endif

			inline				NxString	toString() const {

				char str[250];
			
				NxQuat q; m.M.toQuat(q);

				sprintf(str, "vector %d %d %d quaternion %d %d %d %d", 
					m.t.x, m.t.y, m.t.z,
					q.w, q.x, q.y, q.z
					);

				return NxString(str);

			}

			NxMat34 m;

	};

};

#endif
