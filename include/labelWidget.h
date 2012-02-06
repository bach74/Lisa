// =============================================================================
//  LabelWidget.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __LABELWIDGET_H__
#define __LABELWIDGET_H__

class LabelWidget
{
	public:
		LabelWidget(Ogre::OverlayContainer* pContainer, const char* uniqueName, float parentLeft, float parentTop, float parentRight, float parentBottom, float xprop, float yprop, const char* text);
		~LabelWidget();

		// tell this widget what the parent's dimensions are. Needs to be called if parent moved.
		void defineParentBounds(float left, float top, float right, float bottom);

		void show() {textPtr->show();}
		void hide() {textPtr->hide();}

		void moveWidget(float xprop, float yprop);  // note xpos and ypos are 0.0-0.1
		void setAlignment(const char* top, const char* left);
		void setColour(float r, float g, float b, float a);
		void setSize(int charHeight);
		void setFont(const char* fontName);
		void centreText();
		
		void setText(const char* text);
		const char* getText();

	private:
		float mParentBoundLeft;
		float mParentBoundRight;
		float mParentBoundTop;
		float mParentBoundBottom;
		float mXProp;
		float mYProp;
		float mXPos;
		float mYPos;
		int mCharHeight;
		Ogre::TextAreaOverlayElement* textPtr;
};

 #endif