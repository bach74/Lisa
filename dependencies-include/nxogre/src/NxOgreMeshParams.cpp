/** \file    NxOgreMeshParams.cpp
 *  \see     NxOgreMeshParams.h
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
#include "NxOgreMeshParams.h"
#include "NxOgreContainer.h"
#include "NxOgreHelpers.h"

namespace NxOgre {
namespace Resources {

/////////////////////////////////////////////////////////////

void MeshParams::setToDefault() {

	mLocalPose.id();
	mTextureCoordinateScale = float2(1,1);

}

/////////////////////////////////////////////////////////////

void MeshParams::parse(Parameters params) {

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

		//

	}

}

/////////////////////////////////////////////////////////////

void MeshParams::MeshFlags::fromNxU32(NxU32 flag) {

	if (flag & NX_MF_FLIPNORMALS)
		mFlipNormals = true;

}

/////////////////////////////////////////////////////////////

NxU32 MeshParams::MeshFlags::toNxU32() const {
	
	NxU32 flag = 0;

	if (mFlipNormals)
		flag |= NX_MF_FLIPNORMALS;

	return flag;
}

/////////////////////////////////////////////////////////////

void  MeshParams::MeshFlags::parse(const NxString& flag_str) {

	Container<unsigned int, NxString> str_flags;
	str_flags = NxStringTokenize(flag_str, "+", true);

	if (str_flags.count() == 0)
		return;

	for (NxU32 i=0;i < str_flags.count();i++) {

		NxString flag_str = str_flags[i];

		NxStringTrim(flag_str);
		NxStringToLower(flag_str);
	
		if (set("flip-normals", flag_str, mFlipNormals)) continue;
		if (set("fp", flag_str, mFlipNormals)) continue;

	}

}

/////////////////////////////////////////////////////////////

}; // End of Resources namespace.
}; // End of NxOgre namespace.
