// =============================================================================
//  LabelWidget.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "LabelWidget.h"
#include "exception.h"

/**-------------------------------------------------------------------------------
	LabelWidget
	
	@brief
	@param pContainer
	@param uniqueName
	@param parentLeft
	@param parentTop
	@param parentRight
	@param parentBottom
	@param xprop
	@param yprop
	@param text
	@return 
---------------------------------------------------------------------------------*/
LabelWidget::LabelWidget(Ogre::OverlayContainer* pContainer, const char* uniqueName, float parentLeft, float parentTop, float parentRight, float parentBottom, float xprop, float yprop, const char* text)
{
	mXPos = 100.0f;
	mYPos = 100.0f;
	mCharHeight = 16;

	if (!pContainer)
	{
		throw Exception("ERROR: LabelWidget parent container is NULL", "LabelWidget");
	}

	mXProp = xprop;
	mYProp = yprop;
	mParentBoundLeft = parentLeft;
	mParentBoundRight = parentRight;
	mParentBoundTop = parentTop;
	mParentBoundBottom = parentBottom;

	Ogre::OverlayElement* baseElement = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", uniqueName);

	if (!baseElement)
	{
		throw Exception("ERROR: LabelWidget not initialized","LabelWidget");
	}

	textPtr = static_cast<Ogre::TextAreaOverlayElement*>(baseElement);

	textPtr->setMetricsMode(Ogre::GMM_PIXELS);
	textPtr->setCaption(text);
	textPtr->setFontName("Lucida");
	textPtr->setCharHeight(static_cast<Ogre::Real>(mCharHeight));
	textPtr->setSpaceWidth(0.5f * mCharHeight);
	defineParentBounds(mParentBoundLeft, mParentBoundTop, mParentBoundRight, mParentBoundBottom); // provide boundaries and move widget into place
	pContainer->addChild(baseElement);
}

/**-------------------------------------------------------------------------------
	~LabelWidget
	
	@brief
	@return 
---------------------------------------------------------------------------------*/
LabelWidget::~LabelWidget()
{
	Ogre::OverlayManager::getSingleton().destroyOverlayElement(textPtr);
}

 
/**-------------------------------------------------------------------------------
	defineParentBounds
	
	@brief Define boundaries (in pixels) of the widget that this one is nested in (so that proportions work properly)
	@param left
	@param top
	@param right
	@param bottom
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::defineParentBounds(float left, float top, float right, float bottom)
{
	mParentBoundLeft = left;
	mParentBoundRight = right;
	mParentBoundTop = top;
	mParentBoundBottom = bottom;

	moveWidget(mXProp, mYProp);
}

/**-------------------------------------------------------------------------------
	moveWidget
	
	@brief Move the position of the label
	@param xprop
	@param yprop
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::moveWidget(float xprop, float yprop)
{
	mXProp = xprop;
	mYProp = yprop;

	// set position - can't just change metrics mode because all the size attributes are in pixels
	mXPos = (mParentBoundRight - mParentBoundLeft) * xprop; // get screen-proportionate position
	mYPos = (mParentBoundBottom - mParentBoundTop) * yprop; // get screen-proportionate position
	textPtr->setLeft(mXPos);
	textPtr->setTop(mYPos);
}

/**-------------------------------------------------------------------------------
	setAlignment
	
	@brief
	@param top
	@param left
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::setAlignment(const char* top, const char* left)
{
	// multi-dialect spell checking
	if (strcmp(top, "centre") == 0)
	{
		textPtr->setVerticalAlignment(Ogre::GVA_CENTER);
	}
	else if (strcmp(top, "center") == 0)
	{
		textPtr->setVerticalAlignment(Ogre::GVA_CENTER);
	}
	else if (strcmp(top, "bottom") == 0)
	{
		textPtr->setVerticalAlignment(Ogre::GVA_BOTTOM);
	}
	else
	{
		textPtr->setVerticalAlignment(Ogre::GVA_TOP);
	}

	if (strcmp(left, "centre") == 0)
	{
		textPtr->setHorizontalAlignment(Ogre::GHA_CENTER);
	}
	else if (strcmp(left, "center") == 0)
	{
		textPtr->setHorizontalAlignment(Ogre::GHA_CENTER);
	}
	else if (strcmp(left, "right") == 0)
	{
		textPtr->setHorizontalAlignment(Ogre::GHA_RIGHT);
	}
	else
	{
		textPtr->setHorizontalAlignment(Ogre::GHA_LEFT);
	}
}

/**-------------------------------------------------------------------------------
	setColour
	
	@brief
	@param r
	@param g
	@param b
	@param a
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::setColour(float r, float g, float b, float a)
{
	Ogre::ColourValue cv(r, g, b, a);
	textPtr->setColour(cv);
}

/**-------------------------------------------------------------------------------
	setFont
	
	@brief
	@param fontName
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::setFont(const char* fontName)
{
	textPtr->setFontName(fontName);
}

/**-------------------------------------------------------------------------------
	setSize
	
	@brief
	@param charHeight
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::setSize(int charHeight)
{
	mCharHeight = charHeight;
	textPtr->setCharHeight(static_cast<Ogre::Real>(charHeight));
}

/**-------------------------------------------------------------------------------
	centreText
	
	@brief
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::centreText()
{
	int capLen = textPtr->getCaption().length_Characters();
	textPtr->setLeft(mXPos + capLen / 2 *(-0.5f * mCharHeight));
}

/**-------------------------------------------------------------------------------
	setText
	
	@brief
	@param text
	@return bool
---------------------------------------------------------------------------------*/
void LabelWidget::setText(const char* text)
{
	textPtr->setCaption(text);
}

/**-------------------------------------------------------------------------------
	getText
	
	@brief
	@return char*
---------------------------------------------------------------------------------*/
const char* LabelWidget::getText()
{
	return textPtr->getCaption().asUTF8_c_str();
}


