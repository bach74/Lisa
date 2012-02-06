// =============================================================================
//  stdafx.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __STD_AFX_H__
#define __STD_AFX_H__

#define NOMINMAX

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows XP or later.
#define WINVER 0x0600       // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0600 // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS      // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE           // Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0700    // Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit


// atl stuff
#include <atlbase.h>
#include <atlcom.h>
#include <atlstr.h>

using namespace ATL;

// std library stuff
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <deque>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ostream>

// boost stuff
#define BOOST_LIB_DIAGNOSTIC
#define BOOST_THREAD_USE_LIB
#define BOOST_LIB_NAME boost_thread
#include <boost/config/auto_link.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

// ogre stuff
#include <Ogre.h>
#include <OgreStringConverter.h>
#include <OgreRenderWindow.h>
#include <OgreRenderQueueListener.h>
#include <sencilOpQueueListener.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreBorderPanelOverlayElement.h>

// nxOgre stuff
#include <NxOgre.h>

// OIS stuff
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>

#include <typeinfo>

// resource files should not be changed often in this project
#include "resource.h"

// collada file
#include "NXU_Helper.h"
#include "NXU_colladaimport.h"

// exception handling
#include "exception.h"

// support for logging (debugging purposes)
#include "debugLogger.h"

// delete helper objects
struct delete_object
{
	template <typename T>
	void operator()(T *ptr) { delete ptr; ptr=NULL; }
};

struct delete_object_map
{
	template <typename T1, typename T2>
	void operator()(std::pair<T1,T2>& ptr) { delete ptr.second; ptr.second=NULL; }
};

// converter function between two arbitrary types
template <class out_type, class in_type>
out_type convert(const in_type& inputVal)
{
	std::stringstream stream;
	out_type result;
	stream << inputVal;
	stream >> result;
	return result;
}

// converter function between two arbitrary types
template <class in_type>
std::string toString(const in_type& t)
{
	std::stringstream stream;
	stream << t;
	return stream.str();
}


// constants
#define OGRE_DEBUG_GROUP	"debugger"
#define THE_WORLD			"MainScene"

#endif