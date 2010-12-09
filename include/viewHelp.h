#pragma once

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
