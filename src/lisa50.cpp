// =============================================================================
//  lisa50.cpp   
//  
//	main program cpp file
//		- main loop
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "resource.h"
#include "com\Lisa50.h"
#include <OIS\OIS.h>
#include "lisaCore.h"


/**-------------------------------------------------------------------------------
	ATL Application module class
	contains code that supports creating an EXE, processing the command line,
	registering class objects, running the message loop, and cleaning up on exit.
--------------------------------------------------------------------------------*/
class CLisa50Module : public CAtlExeModuleT< CLisa50Module >
{
public :
	DECLARE_LIBID(LIBID_Lisa50Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LISA50, "{D16CE158-9724-4EA0-8029-3E0661B86DA8}")
	
	// Overriding methods to customize the message loop
public:
	HRESULT PreMessageLoop(int /*nShowCmd*/) throw();
	void RunMessageLoop() throw();
	HRESULT PostMessageLoop() throw();
private:
	HANDLE hMutex;
};



/**-------------------------------------------------------------------------------
	One and only application object
--------------------------------------------------------------------------------*/
CLisa50Module _mainModule;

/**-------------------------------------------------------------------------------
	Application entry point, Main Windows function
--------------------------------------------------------------------------------*/
INT WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _mainModule.WinMain(nShowCmd);
}


/**-------------------------------------------------------------------------------
	Pre-message loop override function
	Check if application is already started, report an error if so, otherwise
	call the base class message loop and proceed
--------------------------------------------------------------------------------*/
HRESULT CLisa50Module::PreMessageLoop(int nShowCmd)
{
	HRESULT hr=__super::PreMessageLoop(nShowCmd);

	// Get start directory by cutting off the executable name from full path.
	TCHAR ansiPath[MAX_PATH];
	// If app is started by the COM engine, GetCurrentDirectory() returns c:\windows\system32,
	// so we use ::GetModuleFileName() instead to get the path of the executable. 
	::GetModuleFileName(NULL, ansiPath, MAX_PATH);
	TCHAR *pc=strrchr(ansiPath,'\\');
	*pc='\0';
	SetCurrentDirectory(ansiPath);

	return hr;
}


/**-------------------------------------------------------------------------------
	Main message loop override function
	create LisaCore object and start it
--------------------------------------------------------------------------------*/
void CLisa50Module::RunMessageLoop()
{
	HRESULT hr = S_OK;

	// check if Lisa is already started
	hMutex = CreateMutex(NULL,true,_T("Lisa_application_run"));
	if (GetLastError()==ERROR_INVALID_HANDLE) {
		MessageBox(NULL,_T("Cannot create application or unknown system error !"),
			_T("Lisa Start error"),MB_OK|MB_ICONEXCLAMATION);
	}
	else if (GetLastError()==ERROR_ALREADY_EXISTS) {
		MessageBox(NULL,_T("Application already started \n There can be only one instance\n of L.i.S.a. currently active !\n")
			,_T("Lisa Start error"), MB_OK|MB_ICONEXCLAMATION);
	} 
	else if (SUCCEEDED(hr)) {

		try {		
			// create application object
			LisaCore& lisa=LisaCore::Instance();
			lisa.go();
		} 
		catch (Exception& e) {
			MessageBox(NULL,e.getDescription(),_T("An exception has occured!"),MB_OK|MB_ICONERROR|MB_TASKMODAL);
		}
		// catch OGRE exceptions
		catch (Ogre::Exception& e) {
			//TCHAR buf[1024];
			//MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,e.getFullDescription().c_str(),-1,buf,1024);
			MessageBox(NULL,e.getFullDescription().c_str(),_T("An OGRE exception has occured!"),MB_OK|MB_ICONERROR|MB_TASKMODAL);
		}
		// Catch any OIS exceptions
		catch (OIS::Exception &oe)
		{
			MessageBox(NULL,oe.eText,_T("OIS Exception!"),MB_OK|MB_ICONERROR|MB_TASKMODAL);
		}
		// Catch any thing else that might have thrown... Perhaps CEGUI...
		catch(...)
		{
			 MessageBox(NULL,_T("Unknown exception"),_T("Exception!"),MB_OK|MB_ICONERROR|MB_TASKMODAL);
		}
	}
}

/**-------------------------------------------------------------------------------
	Post-message loop override function
	release the mutex and call the base class postmessageloop
--------------------------------------------------------------------------------*/
HRESULT CLisa50Module::PostMessageLoop()
{
	HRESULT hr=S_OK;
	
	ReleaseMutex(hMutex);
	hr=__super::PostMessageLoop();

	return hr;
}
