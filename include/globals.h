#pragma once

class Globals : public Singleton<Globals>
{
public:
	Globals():mScene(NULL){};
	~Globals(){};

	Ogre::Vector3 getGravity();
	void setScene(NxOgre::Scene *scene) {mScene=scene;}

private:
	NxOgre::Scene* mScene;
};
