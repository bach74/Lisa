#pragma once

class DrawingCoord : public Ogre::ManualObject
{
	public:
		DrawingCoord(Ogre::SceneNode* sceneNode, const std::string& name,
			float scale, const Ogre::ColourValue& col=Ogre::ColourValue::Black);

		~DrawingCoord(void);

		void setPosition(const Ogre::Vector3& pos)  { getParentNode()->setPosition(pos); }
		void setOrientation(const Ogre::Quaternion& q)  { getParentNode()->setOrientation(q); }
		void setVisible(bool visible)               { ManualObject::setVisible(visible); }

	private:
		Ogre::SceneNode* mRoot;
};
