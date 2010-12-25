// =============================================================================
//  sencilOpQueueListener.h   version:  1.0
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The project is licensed under MIT license.
// 
// =============================================================================
// stencil values
#define STENCIL_VALUE_FOR_FULL_GLOW 2
#define STENCIL_FULL_MASK 0xFFFFFFFF

// a Render queue listener to change the stencil mode
class StencilOpQueueListener : public Ogre::RenderQueueListener 
{ 
public: 
	/**----------------------------------------------------------------------------
	   Called when render queue is started. Change render parameters so select effect
	   is visible.
	   
	   \param queueGroupId (Ogre::uint8)
	   \param invocation (const Ogre::String &)
	   \param skipThisInvocation (bool &)
	   \return (void)
	 -----------------------------------------------------------------------------*/
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation) 
	{ 
		if (queueGroupId == 90)  // full glow - alpha glow
		{ 
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
			rendersys->setStencilCheckEnabled(true); 
			rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
				STENCIL_VALUE_FOR_FULL_GLOW,STENCIL_FULL_MASK, 
				Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);       
		} 

		if (queueGroupId == 91)  // full glow - glow
		{ 
			Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
			rendersys->setStencilCheckEnabled(true); 
			rendersys->setStencilBufferParams(Ogre::CMPF_EQUAL,
				STENCIL_VALUE_FOR_FULL_GLOW,STENCIL_FULL_MASK, 
				Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_ZERO,false);       
		}
	} 

	/**----------------------------------------------------------------------------
		Called after render queue is ended.
	   
		\param queueGroupId (Ogre::uint8)
		\param invocation (const Ogre::String &)
		\param repeatThisInvocation (bool &)
		\return (void)
	 -----------------------------------------------------------------------------*/
	virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation) 
	{ 
		if ((queueGroupId==91)) { 
			Ogre::RenderSystem* rendersys=Ogre::Root::getSingleton().getRenderSystem(); 
			rendersys->setStencilCheckEnabled(false); 
			rendersys->setStencilBufferParams(); 
		} 
	} 

};
