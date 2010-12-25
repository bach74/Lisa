// =============================================================================
//  scene.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SCENE_H__
#define __SCENE_H__

#include "ExtendedCamera.h"

class Simulation;

/// Scene class
class Scene : public Ogre::WindowEventListener
{
	public:

		Scene(Ogre::RenderWindow* wnd);
		virtual ~Scene();

		void run();
		void loadScene(const char* filename);

		Ogre::RenderWindow&     getWindow()         { return *mWindow;  }
		Ogre::SceneManager&     getSceneManager()   { return *mSceneMgr; }
		ExtendedCamera&			getCamera()			{ return *mCamera;  }
		Simulation*				getSimulation()		{ return mSimulation; }

		// attributes
		void setShadowTechnique(Ogre::ShadowTechnique st) { mShadowType=st; }
		Ogre::ShadowTechnique getShadowTechnique()   { return mShadowType; }

	protected:
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowMouseWheel(Ogre::RenderWindow* rw, WPARAM wParam);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);

	private:

		void createDefaultViewport();
		void createResourceListener() {};
		void loadResources() {};

		Scene() {};

		Ogre::SceneManager*         mSceneMgr;
		Ogre::RenderWindow*         mWindow;
		ExtendedCamera*             mCamera;
		Simulation*					mSimulation;

		// attributes
		Ogre::ShadowTechnique       mShadowType;
};

 #endif