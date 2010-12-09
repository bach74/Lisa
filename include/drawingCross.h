#pragma once

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
