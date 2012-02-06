// =============================================================================
//  viewHelp.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "ViewHelp.h"
#include "scene.h"


/**-------------------------------------------------------------------------------
    ViewHelp
    Create help mOverlay and connect to a help renderer

    @brief
    @param simulation
    @return
---------------------------------------------------------------------------------*/
ViewHelp::ViewHelp(Simulation* simulation)
{
	mSimulation = simulation;

	//Initialize help GUI system
	int height = mSimulation->getScene()->getWindow().getHeight();
	int width = mSimulation->getScene()->getWindow().getWidth();

	mOverlay = Ogre::OverlayManager::getSingleton().create("Simulation.Help");

	mHelpOverlay = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement(
	                   "Panel", "Simulation.HelpWindow"));
	mOverlay->add2D(mHelpOverlay);

	mHelpOverlayText = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "Simulation.HelpWindowText");
	mHelpOverlayText->setMetricsMode(Ogre::GMM_PIXELS);
	mHelpOverlayText->setLeft(10);
	mHelpOverlayText->setTop(height/3.0f);
	mHelpOverlayText->setWidth(static_cast<Ogre::Real>(width));
	mHelpOverlayText->setHeight(height/3.0f*2);
	mHelpOverlayText->setParameter("font_name", "Lucida");
	mHelpOverlayText->setParameter("char_height", "14");
	mHelpOverlayText->setParameter("horz_align", "left");
	mHelpOverlayText->setCaption("");
	mHelpOverlayText->setColour(Ogre::ColourValue(0.8f, 0.8f, 1.0f));

	mHelpOverlay->addChild(mHelpOverlayText);

	// show help info mOverlay
	mOverlay->show();

	// add this window to frame listeners
	Ogre::Root::getSingletonPtr()->addFrameListener(this);
}

/**-------------------------------------------------------------------------------
    ~ViewHelp

    @brief
    @param
    @return
---------------------------------------------------------------------------------*/
ViewHelp::~ViewHelp(void)
{
	// remove frame listener
	Ogre::Root::getSingletonPtr()->removeFrameListener(this);

	// delete help info mOverlay
	mOverlay->hide();

	Ogre::OverlayManager::getSingleton().destroyOverlayElement(mHelpOverlayText);
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(mHelpOverlay);
	Ogre::OverlayManager::getSingleton().destroy(mOverlay);
}

/**-------------------------------------------------------------------------------
    Frame started event
    update help info

    \param deltaTime (float)
    \return (void)
-----------------------------------------------------------------------------*/
bool ViewHelp::frameEnded(const Ogre::FrameEvent& evt)
{
	// update help window

	std::stringstream helpText;

	helpText << "HELP\n" << "----------------------------------------------------------------------------------\n";
	helpText << "ESC - exit program\n";
	helpText << "F1 - help (this screen) \n\n";
	helpText << "F2 - toggle debug window\n";
	helpText << "F3 - show graphs\n";
	helpText << "F4 - start/pause simulation \n\n";
	helpText << "LCTRL - change camera movement type\n\n";
	helpText << "DEBUG commands (F2 debug window shown)\n" << "----------------------------------------------------------------------------------\n";
	helpText << "TAB - change force mode\n";
	helpText << "LEFTSHIFT - cycle through available force/moment types\n";
	helpText << "MINUS/PLUS - decrease/increase force/moment strength\n";
	helpText << "0-7 toggle active debug visuals\n";
	helpText << "9 - cycle through active debug visual\n";
	helpText << "F11/F12 - decrement/increment debug visual element's scaling\n";
	helpText << "UP/DOWN -z/+z force/moment on the currently selected object\n";
	helpText << "LEFT/RIGHT -x/+x force/moment on the currently selected object\n";
	helpText << "Q/A +y/-y force/moment on the currently selected object\n";
	helpText << "BACKSPACE - show complete debug text";
	helpText << "\n\n\n\n (c) 2010 by Bach - version 5.6";

	mHelpOverlayText->setCaption(helpText.str());

	return true;
}

