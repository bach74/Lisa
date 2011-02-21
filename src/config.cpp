// =============================================================================
//  Config.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "config.h"

/**-------------------------------------------------------------------------------
	load configuration from ini file

	\return (void)
-----------------------------------------------------------------------------*/
Config::Config()
{
	mShowForces=false;
	mShowZMP=false;
	mShowCOG=false;
	mShowCOP=false;
	mShowFRI=false;
	mLoggingSensors=false;
	mLoggingControllers=false;

	mVisualDebugScale=1.0f;
	mDrawingScaleCOG=1.0f;
	mDrawingScaleCOP=1.0f;
	mDrawingScaleFRI=1.0f;
	mDrawingScaleZMP=1.0f;

	mCameraZoomSpeed=0.01f;
	mCameraRotateSpeed=0.01f;
	mCameraTranslateSpeed=0.003f;
	mActuatorSteppingTime=0.03f;

	mKeepAlive=false;
	mControllerZMP=false;
	mSelectedObjectGlows=true;
	mPhysXEnabled=true;

	TCHAR path[MAX_PATH+1];
	int i=GetCurrentDirectory(MAX_PATH,path);
	path[i]='\\';
	path[i+1]='\0';

	TCHAR res[1024];
	LoadString(NULL,IDS_CONFIG_FILE_NAME,res,1024);
	strcat_s(path,MAX_PATH,res);

	Ogre::ConfigFile cf;
	cf.load(path);

	Ogre::ConfigFile::SectionIterator seci=cf.getSectionIterator();
	while (seci.hasMoreElements())
	{
		Ogre::String secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *csettings = seci.getNext();
		if (secName=="options")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i=csettings->begin();

			for (; i!=csettings->end(); ++i)
			{
				bool val=(i->second=="true");
				if (i->first=="showForces") mShowForces=val;
				else if (i->first=="showZMP")   mShowZMP=val;
				else if (i->first=="showCOG")   mShowCOG=val;
				else if (i->first=="showCOP")   mShowCOP=val;
				else if (i->first=="showFRI")   mShowFRI=val;
				else if (i->first=="keepAlive") mKeepAlive=val;
				else if (i->first=="PhysXEnabled") mPhysXEnabled=val;
				else throw Exception(std::string("config value is not supported: ")+secName+i->first,"config.cpp");
			}
		}
		if (secName=="log")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i=csettings->begin();

			for (; i!=csettings->end(); ++i)
			{
				bool val=(i->second=="true");
				if (i->first=="logging_sensors") mLoggingSensors=val;
				else if (i->first=="logging_controllers") mLoggingControllers=val;
				else throw Exception(std::string("config value is not supported: ")+secName+i->first,"config.cpp");
			}
		}
		else if (secName=="drawing")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i=csettings->begin();

			for (; i!=csettings->end(); ++i)
			{
				float val=convert<float,std::string>(i->second);
				if (i->first=="VISUALIZATION_DEBUG_SCALE") mVisualDebugScale=val;
				else if (i->first=="DRAWINGS_SCALE_COG") mDrawingScaleCOG=val;
				else if (i->first=="DRAWINGS_SCALE_COP") mDrawingScaleCOP=val;
				else if (i->first=="DRAWINGS_SCALE_ZMP") mDrawingScaleZMP=val;
				else if (i->first=="DRAWINGS_SCALE_FRI") mDrawingScaleFRI=val;
				else if (i->first=="CAMERA_ROTATE_SPEED") mCameraRotateSpeed=val;
				else if (i->first=="CAMERA_TRANSLATE_SPEED") mCameraTranslateSpeed=val;
				else if (i->first=="CAMERA_ZOOM_SPEED") mCameraZoomSpeed=val;
				else if (i->first=="SELECTED_OBJECT_GLOWS") mSelectedObjectGlows=(i->second=="true");
				else throw Exception(std::string("config value is not supported: ")+secName+i->first,"config.cpp");
			}
		}

		else if (secName=="controller")
		{
			Ogre::ConfigFile::SettingsMultiMap::iterator i=csettings->begin();
			for (; i!=csettings->end(); ++i)
			{
				float val=convert<float,std::string>(i->second);
				if (i->first=="ACTUATOR_STEPPING_TIME") mActuatorSteppingTime=val;
				else if (i->first=="CONTROLLER_ZMP") mControllerZMP=(i->second=="true");
				else throw Exception(std::string("config value is not supported: ")+secName+i->first,"config.cpp");
			}
		}
	}
}

Config::~Config(void)
{
}

