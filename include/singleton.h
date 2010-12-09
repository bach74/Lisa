// =============================================================================
//  singleton.h   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
// singleton.h
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