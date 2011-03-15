/** \file    NxOgreDebugRenderer.cpp
 *  \see     NxOgreDebugRenderer.h
 *  \version 1.0-20
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
#include "NxOgreDebugRenderer.h"

#if (NX_USE_DEBUG_RENDERER_API == 1)

#include "OgreSceneManager.h"
#include "OgreMaterialManager.h"
#include "OgreMaterial.h"
#include "OgreHardwareBufferManager.h"
#include "OgreSingleton.h"
#include "OgreRoot.h"

namespace NxOgre {

	
//////////////////////////////////////////////////////////////////////

DebugRenderer::DebugRenderer(Ogre::SceneManager *_mgr) {

	mSceneMgr = _mgr;
	mName = "NxDebugRenderer";
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
	mNode->attachObject(this);

	if(!Ogre::MaterialManager::getSingleton().resourceExists("NxOgre.DebugRenderer")) {
	
		Ogre::MaterialPtr debugMat = Ogre::MaterialManager::getSingleton().create("NxOgre.DebugRenderer", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		debugMat->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT|Ogre::TVC_DIFFUSE);
		debugMat->getTechnique(0)->getPass(0)->setDepthWriteEnabled(true);
		debugMat->getTechnique(0)->getPass(0)->setLightingEnabled(false);
		debugMat->getTechnique(0)->getPass(0)->setShadingMode(Ogre::SO_FLAT);
	}

	this->setMaterial("NxOgre.DebugRenderer");

	mRenderOp.vertexData = new Ogre::VertexData();

	mNode->setVisible(true);
	this->setCastShadows(false);

	setVisible(true);

}

//////////////////////////////////////////////////////////////////////

DebugRenderer::~DebugRenderer() {
	delete mRenderOp.vertexData;
		
	mNode->detachAllObjects();
	mSceneMgr->getRootSceneNode()->removeAndDestroyChild(mName);

}

//////////////////////////////////////////////////////////////////////

void DebugRenderer::start() {
	mPoints.clear();
	//mPoints.reserve(4096);
	delete mRenderOp.vertexData;

	mRenderOp.vertexData = new Ogre::VertexData();

}

//////////////////////////////////////////////////////////////////////

void DebugRenderer::render(const NxDebugRenderable& data) {
	
	if (&data == 0)
		return;
	
	// Render lines
	
	NxU32 NbLines = data.getNbLines();

	const NxDebugLine *Lines = data.getLines();

	while(NbLines--) {
		addLine(Lines->p0,Lines->p1, ((Lines->color << 8) | 0xFF));
		Lines++;
	}


	// Render triangles
	NxU32 NbTris = data.getNbTriangles();
	const NxDebugTriangle *Triangles = data.getTriangles();

	
	while(NbTris--) {
		addLine(Triangles->p0,Triangles->p1,((Lines->color << 8) | 0xFF));
		addLine(Triangles->p1,Triangles->p2,((Lines->color << 8) | 0xFF));
		addLine(Triangles->p2,Triangles->p0,((Lines->color << 8) | 0xFF));
		Triangles++;
	}


	// Render lines
	NxU32 NbPoints = data.getNbPoints();
	const NxDebugPoint *Points = data.getPoints();

	while(NbPoints--) {
		addLine(Points->p,Points->p, ((Points->color << 8) | 0xFF));
		Points++;
	}

}

//////////////////////////////////////////////////////////////////////

unsigned int DebugRenderer::stop() {

	unsigned int vertexCount = mPoints.size();

	if (vertexCount > 3) {

		mRenderOp.indexData = 0;
		mRenderOp.vertexData->vertexCount = vertexCount;
		mRenderOp.vertexData->vertexStart = 0;
		mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_LIST;
		mRenderOp.useIndexes = false;

		Ogre::VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
		Ogre::VertexBufferBinding *bind = mRenderOp.vertexData->vertexBufferBinding;

		decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		decl->addElement(1, 0, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);

		Ogre::HardwareVertexBufferSharedPtr vbuf =
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			decl->getVertexSize(0),
			mRenderOp.vertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

		bind->setBinding(0, vbuf);

		// Drawing stuff
		size_t size = mPoints.size();
#if OGRE_VERSION_MINOR <=2 
		Ogre::Vector3 vaabMin = Ogre::Vector3(mPoints[0].first.x,mPoints[0].first.y,mPoints[0].first.z);
		Ogre::Vector3 vaabMax = Ogre::Vector3(mPoints[0].first.x,mPoints[0].first.y,mPoints[0].first.z);
#endif

		Ogre::Real *prPos = static_cast<Ogre::Real*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		for(size_t i = 0; i < size; ++i)
		{
			*prPos++ = mPoints[i].first.x;
			*prPos++ = mPoints[i].first.y;
			*prPos++ = mPoints[i].first.z;
		}

		vbuf->unlock();

		// Colouring stuff
		vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			decl->getVertexSize(1), 
			mRenderOp.vertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);

		bind->setBinding(1,vbuf);

		Ogre::RGBA* pClr = static_cast<Ogre::ABGR*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
		Ogre::ColourValue cv;
		Ogre::RGBA clr;

		for (size_t i = 0; i < size; ++i) {

			cv = Ogre::ColourValue(
				(Ogre::Real)((mPoints[i].second & 0xff000000) >> 24)/255.0f,
				(Ogre::Real)((mPoints[i].second & 0x00ff0000) >> 16)/255.0f,
				(Ogre::Real)((mPoints[i].second & 0x0000ff00) >> 8)/255.0f,
				(Ogre::Real)(mPoints[i].second & 0x000000ff)/255.0f
			);


			// Because I like black.
			if (cv == Ogre::ColourValue::White)
				cv = Ogre::ColourValue::Black;

			Ogre::Root::getSingleton().convertColourValue(cv, &clr);
			
			*pClr++ = clr;
		}
		vbuf->unlock();

		mBox.setInfinite();

	}

	return vertexCount;
}

//////////////////////////////////////////////////////////////////////

void DebugRenderer::addLine(NxVec3 a, NxVec3 b, unsigned int col) {
	mPoints.push_back(std::pair<Ogre::Vector3,unsigned int>(Ogre::Vector3(a.x,a.y,a.z) , col));
	mPoints.push_back(std::pair<Ogre::Vector3,unsigned int>(Ogre::Vector3(b.x,b.y,b.z) , col));
}

//////////////////////////////////////////////////////////////////////


}; //End of NxOgre namespace.

#endif
