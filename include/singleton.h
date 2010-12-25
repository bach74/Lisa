// =============================================================================
//  singleton.h   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <class T>
class Singleton
{
	public:
		static T& Instance()
		{
			static T _instance;
			return _instance;
		}
	protected:
		Singleton(){};       // ctor hidden
		~Singleton(){};       // dtor hidden
		Singleton(Singleton const&);   // copy ctor hidden
		Singleton& operator=(Singleton const&); // assign op hidden
};

#endif