/** \file    NxOgreParams.cpp
 *  \see     NxOgreParams.h
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
#include "NxOgreParams.h"
#include "NxOgreHelpers.h"
#include "NxOgreContainer.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

void Params::process(const NxString& str) {
	
	setToDefault();

	if (str.size() == 0)
		return;

	Parameters pm = fromString(str);
	parse(pm);

}

/////////////////////////////////////////////////////////////

bool Params::isYes(const NxString& yes) const {
	
	if (yes.size() == 0)
		return false;

	NxString y = NxStringSubstr(yes, 0, 1);
	return (y == "y" || y == "Y" || y == "t" || y == "T" || "1");

}

/////////////////////////////////////////////////////////////

Params::Parameters Params::fromString(const NxString& _string) {

	Container<unsigned int, NxString> str_params;
	str_params = NxStringTokenize(_string, ",\n", true);
	
	Parameters params;

	if (str_params.count() == 0)
		return params;

	for (NxU32 i=0;i < str_params.count();i++) {
		Parameter* param = new Parameter();
		NxStringTokenize2(str_params[i], ":", param->i, param->j, true);
		NxStringToLower(param->i);
		params.Insert(param);
	}

	return params;

}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, int &t) const {
	if (d->i == i) {
		t = NxConvert<int, NxString>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, unsigned int &t) const {
	if (d->i == i) {
		t = NxConvert<unsigned int, NxString>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxMaterialIndex &t) const {
	if (d->i == i) {
		t = NxFromString<unsigned int>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, bool &t) const {
	if (d->i == i) {
		t = NxFromString<bool>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxReal &t) const {
	if (d->i == i) {
		t = NxFromString<NxReal>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxVec3& t) const {
	if (d->i == i) {
		t = NxFromString<NxVec3>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString &i , Parameter *d, NxQuat& t) const {
	if (d->i == i) {
		t = NxFromString<NxQuat>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString &i, Parameter *d, NxMat33& t) const {
	if (d->i == i) {
		NxQuat q; q = NxFromString<NxQuat>(d->j);
		t.fromQuat(q);
		return true;
	}
	return false;
}

#if (NX_USE_OGRE == 1)

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, Ogre::Vector3 &t) const {
	if (d->i == i) {
		t = NxFromString<Ogre::Vector3>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, Ogre::Quaternion &t) const {
	if (d->i == i) {
		t = NxFromString<Ogre::Quaternion>(d->j);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

#endif

bool Params::Set(const NxString& i, Parameter *d, NxString &t) const {
	if (d->i == i) {
		t = d->j;
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxOgre::NxString& i, Parameter *d, NxHeightFieldAxis &t) const {
	if (d->i == i) {

		NxString tp = d->j.substr(0,1);
		NxStringToLower(tp);

		if (tp == "x") {
			t = NX_X;
			return true;
		}
		else if (tp == "y") {
			t = NX_Y;
			return true;
		}
		else if (tp == "z") {
			t = NX_Z;
			return true;
		}

		return false;
	}
	
	return false;

}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter * d, NxU32& t, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr) const {
	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == enumAStr)
			t = enumA;
		else if (j_lower == enumBStr)
			t = enumB;

		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxU32& t, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr) const {

	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == enumAStr)
			t = enumA;
		else if (j_lower == enumBStr)
			t = enumB;
		else if (j_lower == enumCStr)
			t = enumC;

		return true;
	}
	return false;

}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter * d, NxU32& t, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr) const  {

	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == enumAStr)
			t = enumA;
		else if (j_lower == enumBStr)
			t = enumB;
		else if (j_lower == enumCStr)
			t = enumC;
		else if (j_lower == enumDStr)
			t = enumD;

		return true;
	}
	return false;

}


/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxU32& t, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr, NxU32 enumE, NxString enumEStr) const  {

	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == enumAStr)
			t = enumA;
		else if (j_lower == enumBStr)
			t = enumB;
		else if (j_lower == enumCStr)
			t = enumC;
		else if (j_lower == enumDStr)
			t = enumD;
		else if (j_lower == enumEStr)
			t = enumE;

		return true;
	}
	return false;

}

/////////////////////////////////////////////////////////////

bool Params::Set(const NxString&i, Parameter *d, NxU32& t, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr, NxU32 enumE, NxString enumEStr, NxU32 enumF, NxString enumFStr) const {

	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == enumAStr)
			t = enumA;
		else if (j_lower == enumBStr)
			t = enumB;
		else if (j_lower == enumCStr)
			t = enumC;
		else if (j_lower == enumDStr)
			t = enumD;
		else if (j_lower == enumEStr)
			t = enumE;
		else if (j_lower == enumFStr)
			t = enumF;

		return true;
	}
	return false;

}


/////////////////////////////////////////////////////////////

bool Params::Set(const NxString& i, Parameter *d, NxThreadPriority& t) const {
	
	if (d->i == i) { 
		
		NxString j_lower = d->j;
		NxStringToLower(j_lower);

		if (j_lower == "high")
			t = NX_TP_HIGH;
		else if (j_lower == "above-normal")
			t = NX_TP_ABOVE_NORMAL;
		else if (j_lower == "normal")
			t = NX_TP_NORMAL;
		else if (j_lower == "below-normal")
			t = NX_TP_BELOW_NORMAL;
		else if (j_lower == "low")
			t = NX_TP_LOW;

		return true;
	}
	return false;

}

/////////////////////////////////////////////////////////////

bool Params::is(const NxString& i, Parameter* d) {
	return (i == d->i);
}

/////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.

