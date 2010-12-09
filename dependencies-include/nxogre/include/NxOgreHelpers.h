/** \file    NxOgreHelpers.h
 *  \brief   Header for the many type conversion functions, NxString handling, ID
 *           generation and hash generation functions.
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

#ifndef __NXOGRE_HELPERS_H__
#define __NXOGRE_HELPERS_H__

#include "NxOgrePrerequisites.h"
//#include "NxExtended.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"

namespace NxOgre {

//	NxVec3 NxPublicFunction NxConvert<NxVec3, Ogre::Vector3>(const Ogre::Vector3& v);
//	Ogre::Vector3 NxPublicFunction NxConvert<Ogre::Vector3, NxVec3>(const NxVec3& v);
//	Ogre::Quaternion NxPublicFunction NxConvert<Ogre::Quaternion, NxQuat>(const NxQuat& q);
//	NxQuat NxPublicFunction NxConvert<NxQuat, Ogre::Quaternion>(const Ogre::Quaternion& q);

///// Removed from NxOgre (due to ignoring of character system).
/////	NxExtendedVec3 NxPublicFunction toNxExtendedVec3(const Ogre::Vector3& v);
	NxMat33 toNxMat33(const Ogre::Matrix3&);
	NxMat34 toNxMat34(const Ogre::Matrix4&);
	NxString NxPublicFunction NxCreateID(unsigned int groupCount, NxString typeHash);

	/////////////////////////////////////////////////////////////

	/** \brief	Generates a quick hash based on a string. Collisions are probable
				but it's intended use is for quick string checking or identification.
	*/
	NxHashIdentifier NxPublicFunction NxCreateHashFromString(const NxString& str);

	/** \brief	Generates a quick short hash based on a string. Collisions are probable
				but it's intended quick identification of Actor types.
	*/
	NxShortHashIdentifier NxPublicFunction NxCreateShortHashFromString(const NxString& str);

	/** \brief  Interpolates 
	*/
	Pose NxPublicFunction NxInterpolate(Pose First, Pose Second, NxReal c = 0.5f);

	/** \brief To Lower
	*/
	void NxPublicFunction NxStringToLower(NxString&);

	/** \brief To Upper
	*/
	void NxPublicFunction NxStringToUpper(NxString&);

	/** \brief Trim String
	*/
	void NxPublicFunction NxStringTrim(NxString& string);

	/** \brief Get parts of a string
	*/
	NxString NxPublicFunction NxStringSubstr(const NxString& string, unsigned int pos);

	/** \brief Get parts of a string
	*/
	NxString NxPublicFunction NxStringSubstr(const NxString& string, unsigned int pos, unsigned int length);

	/** \brief Get the first x characters of a string
	*/
	NxString NxPublicFunction NxStringSubstrLeft(NxString& string, unsigned int length);

	/** \brief Get the last x characters of a string
	*/
	NxString NxPublicFunction NxStringSubstrRight(NxString& string, unsigned int length);

	/** \brief Split
	*/
	void NxPublicFunction NxStringSplit(const NxString& s, char delimiter, NxString& a, NxString &b);

	/** \brief String starts with
	*/
	bool NxPublicFunction NxStringStartsWith(const NxString& string, const NxString& pattern, bool ignoreCase = true);

	/** \brief String ends with
	*/
	bool NxPublicFunction NxStringEndsWith(const NxString& string, const NxString& pattern, bool ignoreCase = true);

	/** \brief String has
	*/
	NxU32 NxPublicFunction NxStringWhereIs(const NxString& string, const NxString& pattern);

	/** \brief String tokenize
	*/
	Container<NxU32, NxString> NxPublicFunction NxStringTokenize(const NxString& string, const NxString& pattern, bool trim = true);

	/** \brief Splits a string into two.
	*/
	void NxPublicFunction NxStringTokenize2(const NxString& string, const NxString& pattern, NxString& first, NxString& second, bool trim = true);

	/** \brief String to Real
	*/
	NxReal NxPublicFunction NxStringToReal(const NxString& string);

	/** \brief Real to String
	*/
	NxTemplateFunction NxString NxPublicFunction NxStringFromReal(NxReal r);

	/////////////////////////////////////////////////////////////

	void NxPublicFunction NxCookTriMeshToDisk(const Ogre::String& meshName);
	void NxPublicFunction NxCookConvexToDisk(const Ogre::String& meshName);

	//
	// String Functions
	//


	/** \brief Tokenizes a string into a stl vector of strings based of a delimiter
		
		\param The String to split up
		\param A single character delimiter
		\param Maximum number of splits. 0 is infinite.
		\param Remove excess spaces and tabs before and after each split string.
	
		\example
			<code>
				std::vector<NxString> strings = NxSplitString("1,2,3 , 4", ',', 0, true);
				// Results in:
				//		[0] -> "1"
				//		[1] -> "2"
				//		[2] -> "3"
				//		[3] => "4"
			</code>
		\return The vector of strings
	*/
	std::vector<NxString> NxPublicFunction NxStringSplit(const NxString& string, char delimiter, unsigned int maxSplits = 0, bool trim = false);
	

	/** \brief Joins a String together using a seperator and an optional final seperator.

	*/
	template <typename Type>
	NxString NxPublicFunction NxStringJoin(std::vector<Type>, const NxString& seperator, const NxString& lastSeperator = "");


	//
	// Operators
	//


	/** \brief Quaternion by NxVec3 work around. Equilvent to NxQuat::rot(NxVec3)
		\example
			<code>
				NxVec3 result = quaternion * vector;
			</code>
		@result	The rotated vector
	*/
	NxVec3 NxPublicFunction operator* (const NxQuat&, const NxVec3&);


	// To Strings

	/** \brief Generic class/integral to String.
		\note Uses STL stringstream for conversion.
		\example
			<code>
				NxString str = NxToString<float>(1.2345f);
			</code>
		@result The converted string
	*/
	template <typename Type> NxString NxPublicFunction NxToString(const Type& type);


	/** \brief NxVec3 to String, NxVec3(1, -3.3f, 4) => "1 -3.3 4".
		\example
			<code>
				NxString str = NxToString<NxVec3>(NxVec3(1, -3.3, 4));
			</code>
		@result The converted String
	*/
	template <> NxString NxPublicFunction NxToString<NxVec3>(const NxVec3& vec3);
	

	/** \brief NxQuat to String, NxQuat(1, 0, 0, 0.7f) => "1 0 0 0.7".
		\example
			<code>
				NxString str = NxToString<NxQuat>(NxQuat(1, 0, 0, 0.7f));
			</code>
		@result The converted String
	*/
	template <> NxString NxPublicFunction NxToString<NxQuat>(const NxQuat& quat);


	/** \brief Vector3 to String, NxVec3(1, -3.3f, 4) => "1 -3.3 4".
		\example
			<code>
				NxString str = NxToString<Vector3>(Vector3(1, -3.3, 4));
			</code>
		@result The converted String
	*/
	template <> NxString NxPublicFunction NxToString<Ogre::Vector3>(const Ogre::Vector3& vec3);


	/** \brief Quaternion to String, NxQuat(1, 0, 0, 0.7f) => "1 0 0 0.7".
		\example
			<code>
				NxString str = NxToString<Quaternion>(Quaternion(1, 0, 0, 0.7f));
			</code>
		@result The converted String
	*/
	template <> NxString NxPublicFunction NxToString<Ogre::Quaternion>(const Ogre::Quaternion& quat);


	//
	// From Strings
	//


	/** \brief String to generic class or intergral from NxString.
		
		\note Converted using the STL stringstream interface.
		
		\example
			<code>
				NxString luggageCombination("12345");
				int number = NxFromString<int>(luggageCombination);
			</code>

		\param String to convert
		
	*/
	template <typename Type> NxPublicFunction Type NxFromString(const NxString&);


	template <> unsigned int NxPublicFunction NxFromString<unsigned int>(const NxString&);

	template <> bool NxPublicFunction NxFromString<bool>(const NxString&);

	/** \brief String to NxVec3. Coordinates seperated by spaces.

		\example
			<code>
				NxVec3 vector = NxFromString<NxVec3>("-10.21 2.324 3");
			</code>

		@result The parsed NxVec3 
	*/
	template <> NxVec3	NxPublicFunction NxFromString<NxVec3>(const NxString &);


	/** \brief String to NxQuat. Coordinates seperated by spaces.

		\example
			<code>
				NxQuat quaternion = NxFromString<NxQuat>("1 0 0 0.4");
			</code>

		@result The parsed NxQuat
	*/
	template <> NxQuat	NxPublicFunction NxFromString<NxQuat>(const NxString &);


	/** \brief String to Ogre::Vector3. Coordinates seperated by spaces.

		\example
			<code>
				Ogre::Vector3 vector = NxFromString<Ogre::Vector3>("10.21 -2.324 3");
			</code>

		@result The parsed Ogre::Vector3
	*/
	template <>	Ogre::Vector3 NxPublicFunction NxFromString<Ogre::Vector3>(const NxString&);
	

	/** \brief String to Ogre::Quaternion. Coordinates seperated by spaces.

		\example
			<code>
				Ogre::Quaternion quaternion = NxFromString<Ogre::Quaternion>("1 0 0 0.4");
			</code>

		@result The parsed Ogre::Quaternion
	*/
	template <>	Ogre::Quaternion NxPublicFunction NxFromString<Ogre::Quaternion>(const NxString&);


	//
	// Class Conversions
	//


	/** \brief Generic NxConvert. Do not use.
	*/
	template<typename A, typename B>	NxTemplateFunction A		NxConvert(const B&);

	/** \brief NxString to int
	*/
	template<>	NxTemplateFunction
		int NxConvert<int, NxString>(const NxString& string) {
			std::istringstream str(string);
			int val = 0;
			str >> val;
			return val;
	}

	/** \brief NxString to unsigned int
	*/
	template<>	NxTemplateFunction
		unsigned int NxConvert<unsigned int, NxString>(const NxString& string) {
			std::istringstream str(string);
			unsigned int val = 0;
			str >> val;
			return val;
	}

	/** \brief NxString to bool
	*/
	template<>	NxTemplateFunction
		bool NxConvert<bool, NxString>(const NxString& str) {
			if (str.substr(0, 1) == "y" || str.substr(0, 1) == "t" || str.substr(0, 1) == "Y" || str.substr(0, 1) == "T" || str.substr(0, 1) == "1")
				return true;
			return false;
	}

	/** \brief NxString to unsigned int
	*/
	template<>	NxTemplateFunction
		float NxConvert<float, NxString>(const NxString& string) {
			std::istringstream str(string);
			float val = 0;
			str >> val;
			return val;
	}

	/** \brief Ogre::Vector3 to NxVec3
		\example NxVec3 v = NxConvert<NxVec3, Ogre::Vector3>(vector);
	*/
	template<>	NxTemplateFunction
		NxVec3 NxConvert<NxVec3, Ogre::Vector3>(const Ogre::Vector3& v) {
			return NxVec3(v.x, v.y, v.z);
	}


	/** \brief NxVec3 to Ogre::Vector3
		\example
			<code>
				Ogre::Vector3 v = NxConvert<Ogre::Vector3, NxVec3>(vector);
			</code>
	*/
	template<>	NxTemplateFunction
		Ogre::Vector3 NxConvert<Ogre::Vector3, NxVec3>(const NxVec3& v) {
			return Ogre::Vector3(v.x, v.y, v.z);
	}

	
	/** \brief Ogre::Quaternion to NxQuat
		\example
			<code>
				NxQuat q = NxConvert<NxQuat, Ogre::Quaternion>(quaternion);
			</code>
	*/
	template<>	NxTemplateFunction
		NxQuat NxConvert<NxQuat, Ogre::Quaternion>(const Ogre::Quaternion& q) {
			NxQuat rq; rq.setWXYZ(q.w, q.x, q.y, q.z);
			return rq;
	}


	/** \brief NxQuaternion to Ogre::Quaternion
		\example
			<code>
				Ogre::Quaternion q = NxConvert<Ogre::Quaternion, NxQuat>(quaternion);
			</code>
	*/
	template<>	NxTemplateFunction
		Ogre::Quaternion NxConvert<Ogre::Quaternion, NxQuat>(const NxQuat& q) {
			return Ogre::Quaternion(q.w, q.x, q.y, q.z);
	}


	/** \brief NxVec3 to NxString
		<code>
			NxString s = NxConvert(NxString, NxVec3>(vector);
		</code>
	*/
	template<>	NxTemplateFunction
		NxString NxConvert<NxString, NxVec3>(const NxVec3& v) {
			NxString s;
			s.append(NxStringFromReal(v.x));
			s.append(" ");
			s.append(NxStringFromReal(v.y));
			s.append(" ");
			s.append(NxStringFromReal(v.z));
			return s;
	}

	////

	void NxPublicFunction NxStringFindAndReplace(NxString& str, const NxString& search, const NxString& replacement);



};

#endif
