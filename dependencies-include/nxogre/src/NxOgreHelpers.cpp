/** \file    NxOgreHelpers.cpp
 *  \see     NxOgreHelpers.h
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
#include "NxOgreHelpers.h"
#include "NxOgrePose.h"
#include "NxOgreContainer.h"

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "OgreMatrix3.h"
#include "OgreMatrix4.h"

#include <sstream>

namespace NxOgre {

//////////////////////////////////////////////////////////////////////////////////
/*
inline NxExtendedVec3 toNxExtendedVec3(const Ogre::Vector3& v) {
	return NxExtendedVec3(v.x,v.y,v.z);
}
*/
//////////////////////////////////////////////////////////////////////////////////

// Generates a 8 digit ID, based on groupCount and type of object (typeHash)
NxString NxCreateID(unsigned int groupCount, NxString typeHash) {
	std::stringstream ss;
	ss << typeHash << "-" << std::hex << (rand() % 1024) << "-" << groupCount;
	return ss.str();
}

//////////////////////////////////////////////////////////////////////////////////

inline NxMat33 toNxMat33(const Ogre::Matrix3& matrix) {
	
	NxReal* c = new NxReal[9];
	c[0] = matrix[0][0];	c[1] = matrix[1][0];		c[2] = matrix[2][0];
	c[3] = matrix[0][1];	c[4] = matrix[1][1];		c[5] = matrix[2][1];
	c[6] = matrix[0][2];	c[7] = matrix[1][2];		c[8] = matrix[2][2];

	NxMat33 m;
	m.id();
	m.setColumnMajor(c);

	delete [] c;

	return m;
}

//////////////////////////////////////////////////////////////////////////////////

inline NxMat34 toNxMat34(const Ogre::Matrix4& matrix) {
	
	NxUnderConstruction;

	NxMat34 m;
	m.id();
	
	return m;
}

//////////////////////////////////////////////////////////////////////////////////

NxVec3 operator* (const NxQuat& q, const NxVec3& v) {
	return q.rot(v);
}

////////////////////////////////////////////////////////////////

std::vector<NxString> NxStringSplit(const NxString& string, char delimiter, unsigned int maxSplits, bool trim) {

	std::vector<NxString> strings;
	std::istringstream stream(string);
	NxString element;

	int i=0;
	while (std::getline(stream, element, delimiter)) {
		
		if (maxSplits != 0 && i == maxSplits)
			break;

		if (trim) {
			static const NxString delims = " \t\r";
			element.erase(element.find_last_not_of(delims)+1);		// trim right
			element.erase(0, element.find_first_not_of(delims));	// trim left
		}

		strings.push_back(element);
		
		i++;
	}

	return strings;

}

////////////////////////////////////////////////////////////////

template <typename Type>
	NxString NxToString(const Type& type)
{
	std::stringstream stream;
	stream << type;
	return stream.str();
}

//////////////////////////////////////////////////////////////////////////////////

template <> NxString
	NxToString<NxVec3>(const NxVec3& vec3)
{
	std::stringstream stream;
	stream << vec3.x << " " << vec3.y << " " << vec3.z;
	return stream.str();
}

////////////////////////////////////////////////////////////////

template <> NxString
	NxToString<NxQuat>(const NxQuat& quat)
{
	std::stringstream stream;
	stream << quat.w << " " << quat.x << " " << quat.y << " " << quat.z;
	return stream.str();
}

////////////////////////////////////////////////////////////////

template <> NxString
	NxToString<Ogre::Vector3>(const Ogre::Vector3& vec3)
{
	std::stringstream stream;
	stream << vec3.x << " " << vec3.y << " " << vec3.z;
	return stream.str();
}

////////////////////////////////////////////////////////////////

template <> NxString
	NxToString<Ogre::Quaternion>(const Ogre::Quaternion& quat)
{
	std::stringstream stream;
	stream << quat.w << " " << quat.x << " " << quat.y << " " << quat.z;
	return stream.str();
}

////////////////////////////////////////////////////////////////

template <typename Type>
	Type NxFromString(const NxString& string)
{
	std::istringstream str(string);
	Type val = 0;
	str >> val;
	return val;
}

////////////////////////////////////////////////////////////////

template <>
	unsigned int NxPublicFunction NxFromString<unsigned int>(const NxString& string) {
	std::istringstream str(string);
	unsigned int val = 0;
	str >> val;
	return val;
}

////////////////////////////////////////////////////////////////

template <>
	bool NxPublicFunction NxFromString<bool>(const NxString& str) {
		if (str.substr(0, 1) == "y" || str.substr(0, 1) == "t" || str.substr(0, 1) == "Y" || str.substr(0, 1) == "T" || str.substr(0, 1) == "1")
			return true;
		return false;
}

////////////////////////////////////////////////////////////////

template <> 
  NxVec3 NxFromString<NxVec3>(const NxString &string) {
	
	NxVec3 vector(0,0,0);
	std::vector<NxString> units = NxStringSplit(string, ' ', 3, true);
	
	if (units.size() != 3)
		return vector;

	vector.x = NxFromString<NxReal>(units[0]);
	vector.y = NxFromString<NxReal>(units[1]);
	vector.z = NxFromString<NxReal>(units[2]);

	return vector;
}

////////////////////////////////////////////////////////////////

template <>
  NxQuat NxFromString<NxQuat>(const NxString &string) {
	
	NxQuat quaternion;
	quaternion.id();
	std::vector<NxString> units = NxStringSplit(string, ' ', 4, true);
	
	if (units.size() != 4)
		return quaternion;

	quaternion.w = NxFromString<NxReal>(units[0]);
	quaternion.x = NxFromString<NxReal>(units[1]);
	quaternion.y = NxFromString<NxReal>(units[2]);
	quaternion.z = NxFromString<NxReal>(units[3]);

	return quaternion;

}

////////////////////////////////////////////////////////////////

template <>
  Ogre::Vector3 NxPublicClass NxFromString<Ogre::Vector3>(const NxString& string) {

	Ogre::Vector3 vector(0,0,0);
	std::vector<NxString> units = NxStringSplit(string, ' ', 3, true);
	
	if (units.size() != 3)
		return vector;

	vector.x = NxFromString<NxReal>(units[0]);
	vector.y = NxFromString<NxReal>(units[1]);
	vector.z = NxFromString<NxReal>(units[2]);

	return vector;
}

////////////////////////////////////////////////////////////////

template <>	
  Ogre::Quaternion NxPublicClass NxFromString<Ogre::Quaternion>(const NxString& string) {

	Ogre::Quaternion quat(1,0,0,0);
	std::vector<NxString> units = NxStringSplit(string, ' ', 4, true);
	
	if (units.size() != 4)
		return quat;

	quat.w = NxFromString<NxReal>(units[0]);
	quat.x = NxFromString<NxReal>(units[1]);
	quat.y = NxFromString<NxReal>(units[2]);
	quat.z = NxFromString<NxReal>(units[3]);

	return quat;

}

////////////////////////////////////////////////////////////////

NxHashIdentifier NxCreateHashFromString(const NxString& str) {
	// djb2 by Dan Bernstein
	NxHashIdentifier hash = 5381;
	int c; 
	for (NxU32 i=0;i < str.length();i++) {
		c = str[i];
		hash = ((hash << 5) + hash) + c; // hash*33 + c
	}
	return hash;
}

////////////////////////////////////////////////////////////////

NxShortHashIdentifier NxCreateShortHashFromString(const NxString& str) {
	// djb2 by Dan Bernstein
	NxShortHashIdentifier hash = 5381;
	int c; 
	for (NxU32 i=0;i < str.length();i++) {
		c = str[i];
		hash = ((hash << 5) + hash) + c; // hash*33 + c
	}
	return hash;
}

////////////////////////////////////////////////////////////////

NxQuat NxQuat_nlerp(NxReal fT, const NxQuat& rkP, const NxQuat& rkQ, bool shortestPath) {
	NxQuat result, rkT;
	NxReal fCos = rkP.dot(rkQ);
	result = rkP;

	if (fCos < 0.0f && shortestPath)
		rkT = (-rkQ);    // result = rkP + fT * ((-rkQ) - rkP);
	else
		rkT = rkQ;       // result = rkP + fT * (rkQ - rkP);

	rkT -= rkP;
	rkT *= fT;
	result += rkT;

	result.normalize();
	return result;
}

////////////////////////////////////////////////////////////////

Pose NxInterpolate(Pose First, Pose Second, NxReal c) {

	Pose r;
	r.m.t = c * (Second.m.t - First.m.t) + First.m.t;

	NxQuat q1, q2, q3;
	First.m.M.toQuat(q1); Second.m.M.toQuat(q2);
	q3 = NxQuat_nlerp(c, q1, q2, true);

	r.m.M.fromQuat(q3);

	return r;

}

////////////////////////////////////////////////////////////////

void NxPublicFunction NxStringToLower(NxString& s) {
	std::transform(s.begin(),s.end(),s.begin(),tolower);
}

////////////////////////////////////////////////////////////////

void NxPublicFunction NxStringToUpper(NxString& s) {
	std::transform(s.begin(),s.end(),s.begin(),toupper);
}

////////////////////////////////////////////////////////////////

void NxPublicFunction NxStringTrim(NxString& s) {
	static const std::string delims = " \t\r";
	s.erase(s.find_last_not_of(delims) + 1);
	s.erase(0, s.find_first_not_of(delims));
}

////////////////////////////////////////////////////////////////

NxString NxPublicFunction NxStringSubstr(const NxString& string, unsigned int pos) {
	return string.substr(pos, string.length() - pos);
}

////////////////////////////////////////////////////////////////

NxString NxPublicFunction NxStringSubstr(const NxString& string, unsigned int pos, unsigned int length) {
	return string.substr(pos, length);
}

////////////////////////////////////////////////////////////////

NxString NxPublicFunction NxStringSubstrLeft(NxString& string, unsigned int length) {
	return string.substr(0, length);
}

////////////////////////////////////////////////////////////////

NxString NxPublicFunction NxStringSubstrRight(NxString& string, unsigned int length) {
	return string.substr(string.length() - length, length);
}

////////////////////////////////////////////////////////////////

void NxPublicFunction NxStringSplit(const NxString& s, char delimiter, NxString& a, NxString &b) {
	NxU32 d = s.find_first_of(delimiter);

	a = s.substr(0,d);
	b = s.substr(d + 1, s.length() - d - 1);
}

////////////////////////////////////////////////////////////////

bool NxPublicClass NxStringStartsWith(const NxString& string, const NxString& pattern, bool lowercaseCheck) {
	
	if (string.length() < pattern.length() || pattern.length() == 0)
		return false;

	NxString firstBit = string.substr(0, pattern.length());
	
	if (lowercaseCheck)
		NxStringToLower(firstBit);

	return (firstBit == pattern);

}

////////////////////////////////////////////////////////////////

bool NxPublicClass NxStringEndsWith(const NxString& string, const NxString& pattern, bool lowercaseCheck) {
	
	if (string.length() < pattern.length() || pattern.length() == 0)
		return false;

	NxString lastBit = string.substr(string.length() - pattern.length(), pattern.length());
	
	if (lowercaseCheck)
		NxStringToLower(lastBit);

	return (lastBit == pattern);

}

////////////////////////////////////////////////////////////////

NxU32 NxStringWhereIs(const NxString& string, const NxString& pattern) {
	return string.find_first_of(pattern);
}

////////////////////////////////////////////////////////////////

Container<NxU32, NxString> NxStringTokenize(const NxString& str, const NxString& pattern, bool trim) {

	Container<NxU32, NxString> strings;
#if 1

	NxString::size_type lastPos = str.find_first_not_of(pattern, 0);
	NxString::size_type pos = str.find_first_of(pattern, lastPos);

	while(NxString::npos != pos || NxString::npos != lastPos) {
		
		NxString token = str.substr(lastPos, pos - lastPos);

		if (trim)
			NxStringTrim(token);
		strings.insert(strings.count(), token);

		lastPos = str.find_first_not_of(pattern, pos);
		pos = str.find_first_of(pattern, lastPos);
	}


#else
	size_t start, pos;
	start = 0;
	NxU32 id = 0;

	do {

		pos = str.find_first_of(pattern, start);
		
		if (pos == start) {
			start = pos + 1;
		}
		else if (pos == NxString::npos) {
			NxString tstring(str.substr(start));
			if (trim) NxStringTrim(tstring);
			strings.insert(id, tstring);
			id++;
			break;
		}
		else {
			NxString tstring(str.substr(start, pos - start));
			if (trim) NxStringTrim(tstring);
			strings.insert(id, tstring);
			id++;
			start = pos + 1;
		}

		start = str.find_first_not_of(pattern, start);
		
	} while (pos != NxString::npos);
#endif

	return strings;
}

////////////////////////////////////////////////////////////////

void NxPublicFunction NxStringTokenize2(const NxString& string, const NxString& pattern, NxString& first, NxString& second, bool trim) {
	
	size_t slice_point = string.find_first_of(pattern);

	// Split
	first = string.substr(0, slice_point);
	second = string.substr(slice_point + 1, string.length() - slice_point - 1);
	
	if (trim) {
		static const std::string delims = " \t\r";
		first.erase(first.find_last_not_of(delims)+1 );
		first.erase(0, first.find_first_not_of(delims)) ;
		
		second.erase( second.find_last_not_of(delims) + 1 );
		second.erase(0,  second.find_first_not_of(delims) );
	}

}

////////////////////////////////////////////////////////////////

NxReal NxStringToReal(const NxString& string) {
	std::istringstream istream(string);
	NxReal return_real = 0;
	istream >> return_real;
	return return_real;
}

////////////////////////////////////////////////////////////////

NxString NxStringFromReal(NxReal r) {
	std::ostringstream ostream;
	ostream << r;
	return ostream.str();
}

////////////////////////////////////////////////////////////////

void NxStringFindAndReplace(NxString& str, const NxString& search, const NxString& replacement) {
	std::string::size_type found_at = str.find( search );
	while( std::string::npos != found_at ) {
		str.replace( found_at, 1, replacement );
		found_at = str.find( search, found_at + 1 );
	}
}

////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
