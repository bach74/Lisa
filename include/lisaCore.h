// =============================================================================
//  LisaCore.h   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================
#ifndef __LISA_CORE_H__
#define __LISA_CORE_H__

#include "singleton.h"
class Scene;
class Simulation;


typedef std::map<std::string,std::string> VideoOptions;

/**-------------------------------------------------------------------------------
	Lisa Core class
	
	Main starting class, sets up OGRE, creates rendering devices, 
	sets up PHYSX and nxOgre world, and of course cleans stuff after the program is terminated.
	This class will create a Lisa scene	where all "action" is taking place.
	NOTE: This class is singleton-type class.
--------------------------------------------------------------------------------*/
class LisaCore : public ::Singleton<LisaCore>
{
public:

	friend ::Singleton<LisaCore>;

	void go();
	void stop();

	const Simulation* getSimulation() const;

private:
	LisaCore();
	virtual ~LisaCore();

	int init();
	int deinit();
	bool getOptions(VideoOptions& opts) const;

	std::auto_ptr<Ogre::Root> mOgre;
	std::auto_ptr<Ogre::RenderWindow> mWindow;
	std::auto_ptr<Scene> mScene;

};

#endif