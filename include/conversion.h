// =============================================================================
//  Conversion.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONVERSION_H__
#define __CONVERSION_H__

class Conversion
{
public:
	Conversion(){};
	~Conversion(){};

	#ifdef _ATL

	static void vector2SAFEARRAY(const std::vector<double>& vect,SAFEARRAY** sa);
	static void SAFEARRAY2vector(SAFEARRAY& sa, std::vector<double>& vect);
	static SAFEARRAY* Vector3toSAFEARRAY(const Ogre::Vector3& vect);

	#endif

};

 #endif