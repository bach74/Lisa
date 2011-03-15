/** \file    NxOgreOgreSceneRenderer.cpp
 *  \see     NxOgreOgreSceneRenderer.h
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
#include "NxOgreOgreSceneRenderer.h"
#include "NxOgreScene.h"
#include "NxOgreOgreNodeRenderable.h"
#include "NxOgreOgreMeshRenderable.h"
#include "NxOgreHelpers.h"

#include "OgreRoot.h"
#include "OgreSceneManager.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////////////

OgreSceneRenderer::OgreSceneRenderer(Scene* scene, NxString rendererUserData)
: SceneRenderer(scene, rendererUserData) {
	
	if (rendererUserData.size() == 0) {
		Ogre::SceneManagerEnumerator::SceneManagerIterator it = 
		Ogre::Root::getSingleton().getSceneManagerIterator();
		mSceneMgr = it.getNext();
	}
	else if (rendererUserData == "#first") {
		Ogre::SceneManagerEnumerator::SceneManagerIterator it = 
		Ogre::Root::getSingleton().getSceneManagerIterator();
		mSceneMgr = it.getNext();
	}
	else if (rendererUserData == "#last") {
		Ogre::SceneManagerEnumerator::SceneManagerIterator it = 
		Ogre::Root::getSingleton().getSceneManagerIterator();
		while(it.hasMoreElements()) {
			mSceneMgr = it.getNext();
		}
	}
	else {
		mSceneMgr = Ogre::Root::getSingleton().getSceneManager(rendererUserData);
	}
}

/////////////////////////////////////////////////////////////////////

OgreSceneRenderer::~OgreSceneRenderer() {

}

/////////////////////////////////////////////////////////////////////

NodeRenderable* OgreSceneRenderer::createNodeRenderable(NodeRenderableParams params) {
	OgreNodeRenderable* renderable = new OgreNodeRenderable(params, this);
	return renderable;
}

/////////////////////////////////////////////////////////////////////

MeshRenderable* OgreSceneRenderer::createMeshRenderable(MeshRenderableParams params, Resources::Mesh* mesh) {
	OgreMeshRenderable* renderable = new OgreMeshRenderable(params, mesh, this);
	return renderable;
}

/////////////////////////////////////////////////////////////////////

void OgreSceneRenderer::setCustom(const NxString& identifier, void* ptr) {
	
	if (identifier == "scenemanager") {
		mSceneMgr = static_cast<Ogre::SceneManager*>(ptr);
		return;
	}

}

/////////////////////////////////////////////////////////////////////

void OgreSceneRenderer::setCustom(const NxString& identifier, const NxString& value) {

	if (identifier == "scenemanager") {
		mSceneMgr = Ogre::Root::getSingleton().getSceneManager(value);
		return;
	}

}

/////////////////////////////////////////////////////////////////////

void* OgreSceneRenderer::getCustom(const NxString& identifier) {

	if (identifier == "scenemanager") {
		return (void*) mSceneMgr;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////


}; //End of NxOgre namespace.
