// =============================================================================
//  scene.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __SCENE_H__
#define __SCENE_H__

class ExtendedCamera;
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

		float getGridUnitSize()						{ return mGridUnitSize; }

	protected:
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowMouseWheel(Ogre::RenderWindow* rw, WPARAM wParam);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);

	private:

		void createDefaultViewport();
		void createResourceListener() {};
		void loadResources() {};
		void createGridVisuals(const Ogre::AxisAlignedBox& worldAABB);
		Ogre::AxisAlignedBox getSceneSize(Ogre::SceneNode* node);

		Scene() {};
		Ogre::SceneManager*         mSceneMgr;
		Ogre::RenderWindow*         mWindow;
		ExtendedCamera*             mCamera;
		Simulation*					mSimulation;

		// attributes
		Ogre::ShadowTechnique       mShadowType;
		float mGridUnitSize;
};

 #endif