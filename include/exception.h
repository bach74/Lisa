// =============================================================================
//  Exception.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

class Exception : public std::runtime_error
{
	public:
		Exception(std::string description, std::string where): mDescription(description), mWhere(where), std::runtime_error(description) {};
		~Exception(void) {};

		const char* getDescription() { return mDescription.c_str(); }

	private:
		Exception();

		std::string mDescription;
		std::string mWhere;
};

 #endif