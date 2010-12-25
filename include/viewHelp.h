// =============================================================================
//  ViewHelp.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __VIEWHELP_H__
#define __VIEWHELP_H__

#include "simulation.h"

class ViewHelp: public Ogre::FrameListener
{
	public:


		/**-------------------------------------------------------------------------------
		    ViewHelp

		    @brief
		    @param simulation
		    @return
		---------------------------------------------------------------------------------*/
		ViewHelp(Simulation* simulation);

		/**-------------------------------------------------------------------------------
		    ~ViewHelp

		    @brief
		    @return
		---------------------------------------------------------------------------------*/
		~ViewHelp();

		/**-------------------------------------------------------------------------------
		 frameEnded is FrameListener callback

		 @brief
		 @param evt
		 @return void
		---------------------------------------------------------------------------------*/
		virtual bool frameEnded(const Ogre::FrameEvent& evt);


	private:

		Simulation*                     mSimulation;

		// debugging helpers
		Ogre::Overlay*                  mOverlay;
		Ogre::OverlayContainer*         mHelpOverlay;
		Ogre::OverlayElement*           mHelpOverlayText;

		ViewHelp();

};

 #endif