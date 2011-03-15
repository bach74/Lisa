// =============================================================================
//  scene.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "scene.h"
#include "extendedCamera.h"
#include "PhyExtendedCamera.h"
#include "simulation.h"
#include "simulationImpl.h"
#include "misc.h"
#include "contactReporter.h"
#include "lisaAPI.h"
#include "config.h"

/**-------------------------------------------------------------------------------
	ctor for Scene class
	It sets a default camera and a viewport, and registers a
	framelistener to the Ogre.

	\param wnd (Ogre::RenderWindow *)
	\return ()
 -----------------------------------------------------------------------------*/
Scene::Scene(Ogre::RenderWindow* wnd) throw(): mWindow(wnd), mSceneMgr(NULL), mCamera(NULL), mSimulation(NULL)
{
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	// first step, create a basic scenemanager
	mSceneMgr = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, getStringFromResource(IDS_APPNAME));

	// Set default MIPMAP level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(1);
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	//MaterialManager::getSingleton().setDefaultAnisotropy(8);

	// initialize the resources after initializing the ogre window
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//mSceneMgr->setFog(FOG_LINEAR, ColourValue::Black, 0.0005f, 4000,4500);
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));
	mSceneMgr->setShadowTechnique(mShadowType);

	// default light
	// TODO lights in XML file
	Ogre::Light* mLight = mSceneMgr->createLight("SunLight");
	//mLight->setType(Light::LT_DIRECTIONAL);
	//mLight->setDirection(-0.5,0,-1);
	mLight->setPosition(Ogre::Vector3(250, 300, 350));

	// initialize input manager
	InputManager& inputMgr = InputManager::Instance();
	inputMgr.initialise(mWindow);
};

/**-------------------------------------------------------------------------------
	dtor for Scene class
	De-initialize scene and destroy variables initialized in init

	\return ()
 -----------------------------------------------------------------------------*/
Scene::~Scene()
{
	delete mSimulation;
	mSimulation = NULL;

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

	delete mCamera;
}

/**-------------------------------------------------------------------------------
	Adjust mouse clipping area

	\param rw (RenderWindow *)
	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::windowResized(Ogre::RenderWindow* rw)
{
	UINT width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = InputManager::Instance().getMouse()->getMouseState();
	ms.width = width;
	ms.height = height;
}

/**-------------------------------------------------------------------------------
	Detach OIS before window shutdown.

	\param rw (RenderWindow *)
	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS
	if (rw == mWindow)
	{
		;
		/*if( m_)
		{
			mInputManager->destroyInputObject( mMouse );
			mInputManager->destroyInputObject( mKeyboard );
			mInputManager->destroyInputObject( mJoy );

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}*/
	}
}

/**-------------------------------------------------------------------------------
	intercept mouse wheel messages.

	\param rw (RenderWindow *)
	\param wParam (WPARAM)
	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::windowMouseWheel(Ogre::RenderWindow* rw, WPARAM wParam)
{
	//TODO - loose coupling
	((SimulationImpl*)mSimulation)->simulateZoom((short)HIWORD(wParam));
}

/**-------------------------------------------------------------------------------
	intercept focus change messages.

	\param rw (RenderWindow *)
	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::windowFocusChange(Ogre::RenderWindow* rw)
{
	bool active = mWindow->isActive();

	if (!active)
	{
		mWindow->setActive(true);
	}
}

/**-------------------------------------------------------------------------------
	Create default viewport

	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::createDefaultViewport()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera->getOgreCamera());

	// Alter the camera aspect ratio to match the viewport
	mCamera->getOgreCamera()->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// set default background colour
	vp->setBackgroundColour(Ogre::ColourValue::Black);
}

/**-------------------------------------------------------------------------------
	Load Scene <filename> from an OgreSceneFile .osm

	\param filename (const char *)
	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::loadScene(const char* filename)
{
	// load Scene
	// note that load Scene creates cameras and viewports also

	// create nice looking grid
	// this is only the visual representation, the physics is defined elsewhere
	Ogre::StaticGeometry* mStaticGeom;
	mStaticGeom = mSceneMgr->createStaticGeometry("Grid");
	Ogre::Entity* entFloor = mSceneMgr->createEntity("nx.floor", "nx.floor.mesh");
	entFloor->setCastShadows(false);
	mStaticGeom->addEntity(entFloor, Ogre::Vector3(0, -0.05f, 0));
	Ogre::Entity* entAxis = mSceneMgr->createEntity("nx.axis", "nx.body.axis.mesh");
	entAxis->setCastShadows(false);
	mStaticGeom->addEntity(entAxis, Ogre::Vector3(0, 0.01f, 0));
	mStaticGeom->build();
	mStaticGeom->setCastShadows(false);

	// create and set simulation state to STARTUP
	// simulation class also takes care of the input handling
	mSimulation = new SimulationImpl(this);

	mCamera = new PhyExtendedCamera("MainCamera", mSceneMgr, mSimulation->getPhyScene());
	mCamera->getOgreCamera()->setPosition(Ogre::Vector3(30, 30, 50));
	mCamera->getOgreCamera()->lookAt(Ogre::Vector3(0, 0, 0));

	createDefaultViewport();

	//TODO:
	((SimulationImpl*)mSimulation)->loadScene(std::string(filename));

}

/**-------------------------------------------------------------------------------
	Main Scene loop function
	Render one frame until termination event is received

	\return (void)
 -----------------------------------------------------------------------------*/
void Scene::run()
{
	MSG msg;
	float desiredDelta = 10; //ms - 0.01s - 100 FPS
	int   rendererMult = 3; //(3+1)*desiredDelta = 40 = 25ms

	Ogre::Root* root = Ogre::Root::getSingletonPtr();
	root->setFrameSmoothingPeriod(0);

	HWND hWnd;
	mWindow->getCustomAttribute("WINDOW", &hWnd);

	long currentTicks = root->getTimer()->getMilliseconds();
	long lastTicks = currentTicks;
	float lastTicksFPS = currentTicks/1000.0f;
	long deltaMs = 0;
	float deltaFPS = 0;
	int  renderCount = 0;

	while (mSimulation->getCurrentState() != Simulation::SHUTDOWN)
	{
		// Sleep(1);
		currentTicks = root->getTimer()->getMilliseconds();
		deltaMs = currentTicks - lastTicks;

		if (deltaMs >= desiredDelta)
		{
			mSimulation->setFrameTime(currentTicks/1000.0f);
			float deltaTime = deltaMs/1000.0f;

			// pass external parameters
			LisaAPI::Instance().getStates();
			
			if (Config::Instance().getPhysxEnabled()) {
				// simulate physics
				mSimulation->simulate(deltaTime);
			}

			// set external parameters
			LisaAPI::Instance().setStates();

			// and render occasionally - 1/(renderMult+1) x simulation Td 
			if (renderCount >= rendererMult)
			{
				deltaFPS = mSimulation->getFrameTime() - lastTicksFPS;
				mSimulation->setTimeSinceLastRenderFrame(deltaFPS);

				root->_fireFrameStarted();
				root->_updateAllRenderTargets();
				root->_fireFrameEnded();

				// capture input devices
				mSimulation->capture();
				renderCount = 0;
				lastTicksFPS = mSimulation->getFrameTime();
			}
			else
			{
				renderCount++;
			}

			lastTicks = currentTicks;

			PeekMessage(&msg, hWnd, 0, 0, PM_NOREMOVE);
			Ogre::WindowEventUtilities::messagePump();

			while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
			{
				if ((msg.message == WM_CLOSE) || (msg.message == WM_DESTROY) || (msg.message == WM_QUIT))
				{
					mSimulation->requestStateChange(Simulation::SHUTDOWN);
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			// seems like Ogre does not post WM_QUIT upon clicking X, so we have to check
			// if the render window is closed
			if (mWindow->isClosed())
			{
				mSimulation->requestStateChange(Simulation::SHUTDOWN);
			}
		}
	}
}
