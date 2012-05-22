// =============================================================================
//  misc.h   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================
#ifndef __MISC_H__
#define __MISC_H__


void DumpNodes(std::stringstream &ss, Ogre::Node *n, int level);
std::string DumpNodes(Ogre::Node *n);

std::string getStringFromResource(UINT resourceID);
std::wstring getStringFromResourceW(UINT resourceID);

class VideoInitializationException {
public:
	VideoInitializationException(const std::string& desc){
		MessageBox(NULL,desc.c_str(),_T("Video Initialization"),MB_ICONEXCLAMATION);
	};
	VideoInitializationException(const TCHAR* desc){
		MessageBox(NULL,desc,_T("Video Initialization"),MB_ICONEXCLAMATION);
	};
};


class HighlightQueueListener : public Ogre::RenderQueueListener
{
public:
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation)
	{
		//RenderQueue containing the object to be highlighted
		if (queueGroupId == 90)
		{
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem();

			rendersys->clearFrameBuffer(Ogre::FBT_STENCIL);
			rendersys->setStencilCheckEnabled(true);
			rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,1,0xFFFFFFFF,
				Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);      
		}

		//RenderQueue containing the outline
		if (queueGroupId == 91)
		{
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem();

			rendersys->setStencilCheckEnabled(true);
			rendersys->setStencilBufferParams(Ogre::CMPF_NOT_EQUAL,1,0xFFFFFFFF,
				Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_KEEP,false);      
		}
	}

	virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation)
	{
		if (( queueGroupId == 90 ) || ( queueGroupId == 91 ))
		{
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem();
			rendersys->setStencilCheckEnabled(false);
			rendersys->setStencilBufferParams();
		}
	}

}; 

#endif