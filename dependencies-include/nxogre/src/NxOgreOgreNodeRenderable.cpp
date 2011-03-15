/** \file    NxOgreOgreNodeRenderable.cpp
 *  \see     NxOgreOgreNodeRenderable.h
 *  \version 1.0-21
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *           version 2.1 of the License, or (at your option) any later version.
 *           
 *           This library is distributed in the hope that it will be useful,
 *           but WITHOUT ANY WARRANTY; without even the implied warranty of
 *           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received a copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NxOgreStable.h"
#include "NxOgreOgreNodeRenderable.h"
#include "NxOgreNodeRenderable.h"
#include "NxOgreOgreSceneRenderer.h"
#include "NxOgrePose.h"
#include "NxOgreHelpers.h"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreNode.h"
#include "OgreMovableObject.h"
#include "OgreEntity.h"
#include "OgreStaticGeometry.h"
#include "OgreStringConverter.h"
#include "OgreMesh.h"
#include "OgreSubmesh.h"
#include "OgreIteratorWrappers.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////////////

OgreNodeRenderable::OgreNodeRenderable(NodeRenderableParams params, OgreSceneRenderer* renderer)
: NodeRenderable(params, renderer) , mNode(0), mOffsetNode(0) {

	mSceneMgr = renderer->getSceneMgr();
	mOgreRenderer = renderer;

	if (params.mIdentifierUsage == NodeRenderableParams::IU_Use) {
		mNode = renderer->getSceneMgr()->getSceneNode(params.mIdentifier);
		return;
	}

	Ogre::SceneNode* entityNode = 0;

	__createNode(params.mIdentifier, params.mGraphicsModelPose);

	if (mNode == 0)
		return;

	// modified bach -> create always offset node
	//if (!params.mGraphicsModelOffset.isIdentity()) {
		__createOffsetNode(params.mIdentifier + "-offset", params.mGraphicsModelOffset);

		if (mOffsetNode)
			entityNode = mOffsetNode;
	//}
	//else {
	//	entityNode = mNode;
	//} end-bach

	if (params.mGraphicsModel.size() && entityNode) {

		Ogre::Entity* e = 0;

		if (params.mGraphicsModelType == NodeRenderableParams::GMU_Reference)
			e = __getEntity(params.mGraphicsModel, false);
		else
			e = __getEntity(mNode->getName() + "-entity", true, params.mGraphicsModel);

		if (e) {

//			e->setNormaliseNormals(true);
//			e->setCastShadows(true);
			entityNode->attachObject(e);
		}

		if (params.mGraphicsModelMaterial.size()) {
			e->setMaterialName(params.mGraphicsModelMaterial);
		}
	}

	if (params.mGraphicsModelScale != NxVec3(1,1,1))
		mNode->scale(NxConvert<Ogre::Vector3, NxVec3>(params.mGraphicsModelScale));


	mKnownScale = params.mGraphicsModelScale;


}

/////////////////////////////////////////////////////////////////////

OgreNodeRenderable::~OgreNodeRenderable() {

	if (mNode == 0 && mOffsetNode == 0)
		return;

	__destroyObjects(mOffsetNode);
	__destroyObjects(mNode);

	mNode = 0;
	mOffsetNode = 0;

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::__createNode(const NxString& identifier, const Pose& pose) {

	if (identifier.size() == 0)
		mNode = mSceneMgr->createSceneNode();
	else
		mNode = mSceneMgr->createSceneNode(identifier);

	if (mNode == NULL) {
		NxThrow(NxString("Scenenode with identifier '" + identifier + "' could not be created!").c_str());
		return;
	}

	mNode->setPosition(pose);
	mNode->setOrientation(pose);

	mSceneMgr->getRootSceneNode()->addChild(mNode);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::__createOffsetNode(const NxString& identifier, const Pose& pose) {

	if (identifier.size() == 0)
		mOffsetNode = mSceneMgr->createSceneNode();
	else
		mOffsetNode = mSceneMgr->createSceneNode(identifier);

	if (mNode == NULL) {
		NxThrow(NxString("Scenenode with identifier '" + identifier + "' could not be created!").c_str());
		return;
	}

	mOffsetNode->setPosition(pose);
	mOffsetNode->setOrientation(pose);

	mNode->addChild(mOffsetNode);

}

/////////////////////////////////////////////////////////////////////

Ogre::Entity* OgreNodeRenderable::__getEntity(const NxString& identifier, bool CreateOrGet, const NxString& mesh) {

	Ogre::Entity* entity = NULL;

	if (CreateOrGet)
		entity = mSceneMgr->createEntity(identifier, mesh);
	else {
		entity = mSceneMgr->getEntity(identifier);
		if (entity->isAttached()) {
			Ogre::SceneNode* parentNode = entity->getParentSceneNode();
			parentNode->detachObject(entity);
		}
	}

	return entity;

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setPose(const Pose& pose) {
	
	if (mNode == 0)
		return;

	mNode->setPosition(pose);
	mNode->setOrientation(pose);

}

/////////////////////////////////////////////////////////////////////

Pose OgreNodeRenderable::getPose() const {
	
	if (mNode == 0)
		return Pose();

	return Pose(mNode->getPosition(), mNode->getOrientation());

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setMaterial(const NxString& materialIdentifier) {
	
	if (mNode) {

		Ogre::SceneNode::ObjectIterator object_it = mNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;
		
		while(object_it.hasMoreElements()) {
			
			m = object_it.getNext();

			if (m->getMovableType() == "Entity") {
				Ogre::Entity* ent = static_cast<Ogre::Entity*>(m);
				ent->setMaterialName(materialIdentifier);
			}
			
		}
	}
	
	if (mOffsetNode) {

		Ogre::SceneNode::ObjectIterator object_it = mOffsetNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;
		
		while(object_it.hasMoreElements()) {
			
			m = object_it.getNext();
			if (m->getMovableType() == "Entity") {
				Ogre::Entity* ent = static_cast<Ogre::Entity*>(m);
				ent->setMaterialName(materialIdentifier);
			}
			
		}
	}

}

/////////////////////////////////////////////////////////////////////

NxString OgreNodeRenderable::getMaterial() const {

	Ogre::SceneNode::ObjectIterator object_it = mNode->getAttachedObjectIterator();
	Ogre::MovableObject *m;
	
	while(object_it.hasMoreElements()) {
		
		m = object_it.getNext();
		
		if (m->getMovableType() == "Entity") {
			Ogre::Entity* ent = static_cast<Ogre::Entity*>(m);
			return ent->getMesh()->getSubMesh(0)->getMaterialName();
		}
		
	}

	return NxString("");
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setScale(const float3& val) {
	mNode->scale(val.i, val.j, val.k);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setScale(const Ogre::Vector3& val) {
	mNode->scale(val);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setScale(const NxVec3& val) {
	mNode->scale(NxConvert<Ogre::Vector3, NxVec3>(val));
}

/////////////////////////////////////////////////////////////////////

Ogre::Vector3 OgreNodeRenderable::getScaleAsOgreVector3() const {
	return mNode->getScale();
}

/////////////////////////////////////////////////////////////////////

NxVec3 OgreNodeRenderable::getScaleAsNxVec3() const {
	return NxConvert<NxVec3, Ogre::Vector3>(mNode->getScale());
}

/////////////////////////////////////////////////////////////////////

float3 OgreNodeRenderable::getScaleAsFloat3() const {
	Ogre::Vector3 scale = mNode->getScale();
	return float3(scale.x, scale.y, scale.z);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::setOffset(const Pose& pose) {
	
	if (mNode == 0)
		return;

	if (mOffsetNode == 0) {
		__createOffsetNode(mNode->getName() + "-offset", pose);
		// For every movable object move out of mNode and put them into mOffsetNode
		//mNode->getChildIterator();
		Ogre::Node::ChildNodeIterator it = mNode->getChildIterator();
		Ogre::Node	*n;
		while(it.hasMoreElements()) {
			n = it.getNext();
			mNode->removeChild(n);
			mOffsetNode->addChild(n);
		}

	}
	
	mOffsetNode->setPosition(pose);
	mOffsetNode->setOrientation(pose);
}

/////////////////////////////////////////////////////////////////////

Pose OgreNodeRenderable::getOffset() const {
	return Pose(mOffsetNode->getPosition(), mOffsetNode->getOrientation());
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::__destroyObjects(Ogre::SceneNode* node) {

	if (node == 0)
		return;

	Ogre::SceneNode::ObjectIterator object_it = node->getAttachedObjectIterator();
	Ogre::MovableObject *m;

	while(object_it.hasMoreElements()) {

		m = object_it.getNext();

		// Move Cameras to RootSceneNodes
		if (m->getMovableType() == "Camera") {
			node->detachObject(m);
			mSceneMgr->getRootSceneNode()->attachObject(m);
		}
		// Everything else gets destroyed.
		else {
			mSceneMgr->destroyMovableObject(m);
		}

	}

	node->detachAllObjects();
	node->removeAndDestroyAllChildren();

#if (OGRE_VERSION_MAJOR >= 1) && (OGRE_VERSION_MINOR >= 5)
	mSceneMgr->destroySceneNode(node);
#else
	mSceneMgr->destroySceneNode(node->getName());
#endif
	

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::__parseEntity(Ogre::Entity* entity) {
	
	if (entity == 0)
		return;

	if (entity->isAttached()) {
		Ogre::SceneNode* node = 0;
		node = entity->getParentSceneNode();
		node->detachObject(entity);
	}

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::__parseMovableObject(Ogre::MovableObject* mo) {
	
	if (mo == 0)
		return;

	if (mo->isAttached()) {
		Ogre::SceneNode* node = 0;
		node = mo->getParentSceneNode();
		node->detachObject(mo);
	}

}

/////////////////////////////////////////////////////////////////////

Ogre::SceneNode* OgreNodeRenderable::createSceneNode(const NxString& name, const Ogre::Vector3& vec, const Ogre::Quaternion& quat) {
	
	if (mNode == 0)
		return NULL;

	Ogre::SceneNode* node = mNode->createChildSceneNode(name, vec, quat);

	return node;
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::addSceneNode(const NxOgre::NxString &identifier) {

	if (!mSceneMgr->hasSceneNode(identifier))
		return;

	Ogre::SceneNode* node = mSceneMgr->getSceneNode(identifier);
	Ogre::SceneNode* pnode = node->getParentSceneNode();

	if (pnode)
		pnode->removeChild(node);

	if (mOffsetNode) {
		mOffsetNode->addChild(node);
	}
	else {
		mNode->addChild(node);
	}

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::addEntity(Ogre::Entity* entity) {
	
	__parseEntity(entity);

	if (mOffsetNode) {
		mOffsetNode->attachObject(entity);
		return;
	}

	mNode->attachObject(entity);

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::addMovableObject(Ogre::MovableObject* mo) {

	__parseMovableObject(mo);

	if (mOffsetNode) {
		mOffsetNode->attachObject(mo);
		return;
	}

	mNode->attachObject(mo);

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeSceneNode(const NxString& identifier) {
	
	if (!mSceneMgr->hasSceneNode(identifier))
		return;

	Ogre::SceneNode* node = mSceneMgr->getSceneNode(identifier);
	Ogre::SceneNode* pnode = node->getParentSceneNode();

	if (pnode == 0)
		return;

	if (pnode == mNode || pnode == mOffsetNode)
		pnode->removeChild(node);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeSceneNode(Ogre::SceneNode *node) {

	if (node == 0)
		return;

	Ogre::SceneNode* pnode = node->getParentSceneNode();

	if (pnode == 0)
		return;

	if (pnode == mNode || pnode == mOffsetNode)
		pnode->removeChild(node);

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeEntity(Ogre::Entity* entity) {
	removeMovableObject(entity);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeEntity(const NxString& identifier) {
	removeMovableObject(identifier);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::destroyEntity(Ogre::Entity* entity) {
	destroyMovableObject(entity);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::destroyEntity(const NxString& identifier) {
	destroyMovableObject(identifier);
}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeMovableObject(Ogre::MovableObject* mo) {
	
	if (mo == 0)
		return;

	if (mOffsetNode) {
		if (mo->getParentSceneNode() == mOffsetNode) {
			mOffsetNode->detachObject(mo->getName());
			return;
		}
	}

	if (mo->getParentSceneNode() == mNode)
		mOffsetNode->detachObject(mo->getName());

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::removeMovableObject(const NxString& identifier) {
	
	if (mOffsetNode) {
		Ogre::SceneNode::ObjectIterator object_it = mOffsetNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;

		while(object_it.hasMoreElements()) {
			m = object_it.getNext();
			if (m->getName() == identifier) {
				mOffsetNode->detachObject(m);
				return;
			}
		}
	}
	else {

		Ogre::SceneNode::ObjectIterator object_it = mNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;

		while(object_it.hasMoreElements()) {
			m = object_it.getNext();
			if (m->getName() == identifier) {
				mNode->detachObject(m);
				return;
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::destroyMovableObject(Ogre::MovableObject* mo) {

	if (mo == 0)
		return;

	if (mOffsetNode) {
		if (mo->getParentSceneNode() == mOffsetNode) {
			mOffsetNode->detachObject(mo);
			mSceneMgr->destroyMovableObject(mo);
			return;
		}
	}

	if (mo->getParentSceneNode() == mNode) {
		mOffsetNode->detachObject(mo);
		mSceneMgr->destroyMovableObject(mo);
	}

}

/////////////////////////////////////////////////////////////////////

void OgreNodeRenderable::destroyMovableObject(const NxString& identifier) {
	
	if (mOffsetNode) {

		Ogre::SceneNode::ObjectIterator object_it = mOffsetNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;

		while(object_it.hasMoreElements()) {
			m = object_it.getNext();
			if (m->getName() == identifier) {
				mOffsetNode->detachObject(m);
				mSceneMgr->destroyMovableObject(m);
				return;
			}
		}
	}
	else {

		Ogre::SceneNode::ObjectIterator object_it = mNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;

		while(object_it.hasMoreElements()) {
			m = object_it.getNext();
			if (m->getName() == identifier) {
				mNode->detachObject(m);
				mSceneMgr->destroyMovableObject(m);
				return;
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////

Ogre::SceneNode* OgreNodeRenderable::getNode() {
	return mNode;
}

/////////////////////////////////////////////////////////////////////

Ogre::SceneNode* OgreNodeRenderable::getOffsetNode() {
	return mOffsetNode;
}

/////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
