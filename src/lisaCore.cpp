// =============================================================================
//  LisaCore.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "resource.h"
#include "misc.h"
#include "inputmanager.h"
#include "lisaCore.h"
#include "config.h"


/**-------------------------------------------------------------------------------
	construct and initialize LisaCore elements
--------------------------------------------------------------------------------*/
LisaCore::LisaCore()
{
	mWindow=NULL;
	mOgre=NULL;
	mScene=NULL;
	Config::Instance();
}

/**-------------------------------------------------------------------------------
	destroy LisaCore elements
--------------------------------------------------------------------------------*/
LisaCore::~LisaCore()
{
	delete mScene;
	mScene=NULL;

	delete mWindow;
	mWindow=NULL;

	delete mOgre;
	mOgre=NULL;

}

/**-------------------------------------------------------------------------------
	setup graphics OGRE window and resources
   
	\return (int)	success?
 -----------------------------------------------------------------------------*/
int LisaCore::init()
{
	int ret=NO_ERROR;

	// wrangle a pointer to the Root Ogre object 
	// the first param is the name of the plugins cfg file, the second is the name of the ogre cfg file
	// we are not using either here, so provide them as empty strings to let Ogre know not to load them
	// The third param is the name of the Ogre.log diagnostic file; leave it default for now
	mOgre=new Ogre::Root("","","Ogre.log");
	
	try {

		// add resource directory (under the program's root directory) to resources
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("resources","FileSystem","General");		
		// add all zip resources from the resource directory to the resources

		WIN32_FIND_DATA findData;
		HANDLE hFile=FindFirstFile("resources\\*.zip",&findData);
		while (hFile!=INVALID_HANDLE_VALUE) {						
			std::string dir("resources\\");
			std::string fileName(findData.cFileName);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dir+fileName,"Zip","GUI");
			if (FindNextFile(hFile,&findData)==0) break;
		}

		Ogre::ResourceGroupManager::getSingleton().createResourceGroup(OGRE_DEBUG_GROUP);
		//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("c:\\windows\\fonts","FileSystem","GUI");

		/*DWORD dwDirectXVersion=0;
		DWORD dwDirectXVersionMinor=0;
		TCHAR wcDirectXVersionLetter;
		HRESULT hr=GetDXVersion(&dwDirectXVersion, &dwDirectXVersionMinor, &wcDirectXVersionLetter);
		if (SUCCEEDED(hr)) { 
			std::ostringstream dxinfoStream; 
			dxinfoStream << "DirectX version: " << dwDirectXVersion<<"."<<dwDirectXVersionMinor<<wcDirectXVersionLetter; 
			Ogre::LogManager::getSingleton().logMessage(dxinfoStream.str());
			if(dwDirectXVersion >= 9) { */
				try {
					#if _DEBUG
						mOgre->loadPlugin("plugin\\RenderSystem_Direct3D9_d"); 
					#else
						mOgre->loadPlugin("plugin\\RenderSystem_Direct3D9"); 
					#endif
				} 
				catch(Ogre::Exception& e) { 
					Ogre::LogManager::getSingleton().logMessage(std::string("Unable to create D3D9 RenderSystem: ") + e.getFullDescription()); 
				}
			//}
		//}

		// load common plugins
		#if _DEBUG
			mOgre->loadPlugin("plugin\\RenderSystem_GL_d");
			mOgre->loadPlugin("plugin\\Plugin_CgProgramManager_d");
			mOgre->loadPlugin("plugin\\Plugin_OctreeSceneManager_d");
		#else
			mOgre->loadPlugin("plugin\\RenderSystem_GL");
			mOgre->loadPlugin("plugin\\Plugin_CgProgramManager");
			mOgre->loadPlugin("plugin\\Plugin_OctreeSceneManager");
		#endif	

		// get video options from configuration file
		VideoOptions opts;
		getOptions(opts);

		std::cout<<"Render Device = '"<<opts["device"]<<"'"<<std::endl;

		Ogre::RenderSystem* selectedRenderSystem=NULL;
		Ogre::RenderSystemList pRenderSystemList=mOgre->getAvailableRenderers(); 
		Ogre::RenderSystemList::iterator pRenderSystem=pRenderSystemList.begin(); 

		for (;pRenderSystem!=pRenderSystemList.end();++pRenderSystem)  {
			if ((*pRenderSystem)->getName() == opts["renderSystem"]) {
				selectedRenderSystem = *pRenderSystem;
				break;
			}
		}
		if (pRenderSystem==pRenderSystemList.end()) {
			throw VideoInitializationException("Specified render system ("+opts["renderSystem"]+") does not exist");
		}


		mOgre->setRenderSystem(selectedRenderSystem);

		selectedRenderSystem->setConfigOption("Full Screen", opts["fullscreen"]);
		selectedRenderSystem->setConfigOption("VSync", opts["vsync"]);
		

		if (opts["renderSystem"]=="Direct3D9 Rendering Subsystem") {
			selectedRenderSystem->setConfigOption("Video Mode",opts["resolution"]+" @ "+opts["colourDepth"] + "-bit colour");
			selectedRenderSystem->setConfigOption("FSAA","Level "+opts["FSAA"]);
		} else {
			selectedRenderSystem->setConfigOption("Video Mode",opts["resolution"]);
			selectedRenderSystem->setConfigOption("Colour Depth",opts["colourDepth"]);
			selectedRenderSystem->setConfigOption("FSAA", opts["FSAA"]);
		}


		mWindow=mOgre->initialise(true,getStringFromResource(IDS_APPNAME));

		// change default icon
		// Get window handle
		HWND hWnd;
		mWindow->getCustomAttribute("WINDOW", &hWnd);

		//HICON hIcon=::LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDI_LISA);
		//::SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		HICON hIcon=::LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDI_LISA_SMALL);
		::SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		//::SendMessage(hWnd, WM_SETICON, ICON_SMALL2, (LPARAM)hIcon);

	}
	catch (Ogre::Exception &e) {
		std::string msg=e.getFullDescription();
		std::cerr<<msg<<std::endl;
		throw;
	}

	return ret;
}

/**-------------------------------------------------------------------------------
	release memory
   
	\return (int)
 -----------------------------------------------------------------------------*/
int LisaCore::deinit()
{
	Ogre::ResourceGroupManager::getSingletonPtr()->removeResourceLocation("resources","General");
	Ogre::ResourceGroupManager::getSingletonPtr()->removeResourceLocation("resources/resources.zip","GUI");
	//Ogre::ResourceGroupManager::getSingletonPtr()->removeResourceLocation("c:\\windows\\fonts","GUI");

	Ogre::ResourceGroupManager::getSingletonPtr()->clearResourceGroup("General");
	Ogre::ResourceGroupManager::getSingletonPtr()->clearResourceGroup("GUI");
	Ogre::ResourceGroupManager::getSingletonPtr()->clearResourceGroup(OGRE_DEBUG_GROUP);

	mOgre->detachRenderTarget(mWindow);

	return 0;
}

/**-------------------------------------------------------------------------------
	load options from a configuration file. Configuration file is a plain .ini file.
   
	\param opts (VideoOptions &)	video options parsed from a config file
	\return (bool)
 -----------------------------------------------------------------------------*/
bool LisaCore::getOptions(VideoOptions& opts)
{
	// read these from the ubiquitous config file...on Win32 we have a nice handy
	// API to read config files; on other platforms we'll need to fake one
	TCHAR path[MAX_PATH+1];

	try {
		int i=GetCurrentDirectory(MAX_PATH,path);
		path[i]='\\';
		path[i+1]='\0';

		TCHAR res[1024];
		LoadString(NULL,IDS_CONFIG_FILE_NAME,res,1024);
		strcat_s(path,MAX_PATH,res);

		Ogre::ConfigFile cf;
		cf.load(path);
	
		Ogre::ConfigFile::SectionIterator seci=cf.getSectionIterator();
		while (seci.hasMoreElements()) {
			Ogre::String secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *csettings = seci.getNext();
			if (secName=="display") {
				Ogre::ConfigFile::SettingsMultiMap::iterator i=csettings->begin();

				for (;i!=csettings->end(); ++i) {
					opts.insert(VideoOptions::value_type(i->first,i->second));
				}
				break;
			}
		}
	} 
	catch(...) {
		throw VideoInitializationException(_T("Cannot read video settings"));
	}
	
	return true;
}

/**-------------------------------------------------------------------------------
	main simulator loop, break on exit
   
	\return (void)
 -----------------------------------------------------------------------------*/
void LisaCore::go()
{
	init();
	
	//create Scene
	mScene=new Scene(mWindow);

	// get video options from configuration file
	VideoOptions opts;
	getOptions(opts);

	// setup scene (load scene)
	std::string val=opts.find("model")->second;
	mScene->loadScene(val.c_str());

	// get shadow options
	val=opts.find("shadows")->second;
	mScene->setShadowTechnique((val=="true")?Ogre::SHADOWTYPE_STENCIL_ADDITIVE:Ogre::SHADOWTYPE_NONE);
	//mScene->setShadowTechnique((val=="true")?SHADOWTYPE_TEXTURE_ADDITIVE:SHADOWTYPE_NONE);

	// start simulation
	mScene->run();

	// clean up
	delete mScene;
	mScene=NULL;
	deinit();
}

/**----------------------------------------------------------------------------
	try to exit the application.
   
	\return (void)
 -----------------------------------------------------------------------------*/
void LisaCore::stop()
{
	HWND hWnd=::FindWindow(NULL,getStringFromResource(IDS_APPNAME).c_str());
	SendMessage(hWnd,WM_CLOSE,0,0);
}
