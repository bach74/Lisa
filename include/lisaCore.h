// =============================================================================
//  LisaCore.h   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#ifndef __LISA_CORE_H__
#define __LISA_CORE_H__

#include "singleton.h"
#include "Scene.h"
#include "simulation.h"


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

	Simulation* getSimulation() { return mScene->getSimulation(); }

private:
	LisaCore();
	virtual ~LisaCore();

	int init();
	int deinit();
	bool getOptions(VideoOptions& opts);

	Ogre::Root* mOgre;
	Ogre::RenderWindow* mWindow;
	Scene *mScene;

};

#endif