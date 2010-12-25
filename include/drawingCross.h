// =============================================================================
//  DrawingCross.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __DRAWINGCROSS_H__
#define __DRAWINGCROSS_H__

class DrawingCross : public Ogre::ManualObject
{
	public:
		DrawingCross(Ogre::SceneNode* sceneNode, const std::string& name, const Ogre::ColourValue& color, float scale);
		~DrawingCross(void);

		void setPosition(const Ogre::Vector3& pos)	{ getParentNode()->setPosition(pos); }
		void setVisible(bool visible)				{ ManualObject::setVisible(visible); }

	private:
		Ogre::SceneNode* mRoot;
};

 #endif