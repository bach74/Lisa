/** \file    NxOgreOgreMeshRenderable.cpp
 *  \see     NxOgreOgreMeshRenderable.h
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
#include "NxOgreOgreMeshRenderable.h"
#include "NxOgreMeshRenderable.h"
#include "NxOgreOgreSceneRenderer.h"
#include "NxOgrePose.h"
#include "NxOgreHelpers.h"

#include <OgreCamera.h>
#include <OgreHardwareBufferManager.h>

namespace NxOgre {

/////////////////////////////////////////////////////////////////////

OgreMeshRenderable::OgreMeshRenderable(MeshRenderableParams params,
                                       Resources::Mesh* mesh, OgreSceneRenderer* renderer)
                                      : MeshRenderable(params, mesh, renderer)
{
	mSceneMgr = renderer->getSceneMgr();
	mOgreRenderer = renderer;
	initialize(Ogre::RenderOperation::OT_TRIANGLE_LIST, true);
	//MeshRenderable::setMaterial("BaseWhiteNoLighting");	// temp

}

/////////////////////////////////////////////////////////////////////

OgreMeshRenderable::~OgreMeshRenderable() {
	delete mRenderOp.vertexData;
	delete mRenderOp.indexData;
}

/////////////////////////////////////////////////////////////////////

void OgreMeshRenderable::initialize(Ogre::RenderOperation::OperationType operationType, bool useIndices)
{
  // Initialize render operation
  mRenderOp.operationType = operationType;
  mRenderOp.useIndexes = useIndices;
  mRenderOp.vertexData = new Ogre::VertexData;
  if (mRenderOp.useIndexes)
    mRenderOp.indexData = new Ogre::IndexData;

  // Reset buffer capacities
  mVertexBufferCapacity = 0;
  mIndexBufferCapacity = 0;

  // Create vertex declaration
  createVertexDeclaration();

}

/////////////////////////////////////////////////////////////////////

void OgreMeshRenderable::prepareHardwareBuffers(size_t vertexCount, 
                                               size_t indexCount)
{
  // Prepare vertex buffer
  size_t newVertCapacity = mVertexBufferCapacity;
  if ((vertexCount > mVertexBufferCapacity) ||
      (!mVertexBufferCapacity))
  {
    // vertexCount exceeds current capacity!
    // It is necessary to reallocate the buffer.

    // Check if this is the first call
    if (!newVertCapacity)
      newVertCapacity = 1;

    // Make capacity the next power of two
    while (newVertCapacity < vertexCount)
      newVertCapacity <<= 1;
  }
  else if (vertexCount < mVertexBufferCapacity>>1) {
    // Make capacity the previous power of two
    while (vertexCount < newVertCapacity>>1)
      newVertCapacity >>= 1;
  }
  if (newVertCapacity != mVertexBufferCapacity) 
  {
    mVertexBufferCapacity = newVertCapacity;
    // Create new vertex buffer
	Ogre::HardwareVertexBufferSharedPtr vbuf =
     Ogre:: HardwareBufferManager::getSingleton().createVertexBuffer(
        mRenderOp.vertexData->vertexDeclaration->getVertexSize(0),
        mVertexBufferCapacity,
        Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?

    // Bind buffer
    mRenderOp.vertexData->vertexBufferBinding->setBinding(0, vbuf);
  }
  // Update vertex count in the render operation
  mRenderOp.vertexData->vertexCount = vertexCount;

  if (mRenderOp.useIndexes)
  {
    OgreAssert(indexCount <= std::numeric_limits<unsigned short>::max(), "indexCount exceeds 16 bit");

    size_t newIndexCapacity = mIndexBufferCapacity;
    // Prepare index buffer
    if ((indexCount > newIndexCapacity) ||
        (!newIndexCapacity))
    {
      // indexCount exceeds current capacity!
      // It is necessary to reallocate the buffer.

      // Check if this is the first call
      if (!newIndexCapacity)
        newIndexCapacity = 1;

      // Make capacity the next power of two
      while (newIndexCapacity < indexCount)
        newIndexCapacity <<= 1;

    }
    else if (indexCount < newIndexCapacity>>1) 
    {
      // Make capacity the previous power of two
      while (indexCount < newIndexCapacity>>1)
        newIndexCapacity >>= 1;
    }

    if (newIndexCapacity != mIndexBufferCapacity)
    {
      mIndexBufferCapacity = newIndexCapacity;
      // Create new index buffer
      mRenderOp.indexData->indexBuffer =
        Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
          Ogre::HardwareIndexBuffer::IT_16BIT,
          mIndexBufferCapacity,
          Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY); // TODO: Custom HBU_?
    }

    // Update index count in the render operation
    mRenderOp.indexData->indexCount = indexCount;
  }
}

/////////////////////////////////////////////////////////////////////

Ogre::Real OgreMeshRenderable::getBoundingRadius(void) const
{
  return Ogre::Math::Sqrt(std::max(mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength()));
}

/////////////////////////////////////////////////////////////////////

Ogre::Real OgreMeshRenderable::getSquaredViewDepth(const Ogre::Camera* cam) const
{
   Ogre::Vector3 vMin, vMax, vMid, vDist;
   vMin = mBox.getMinimum();
   vMax = mBox.getMaximum();
   vMid = ((vMin - vMax) * 0.5) + vMin;
   vDist = cam->getDerivedPosition() - vMid;

   return vDist.squaredLength();
}

/////////////////////////////////////////////////////////////////////

void OgreMeshRenderable::createVertexDeclaration() {
	Ogre::VertexDeclaration* vertex_declaration = mRenderOp.vertexData->vertexDeclaration;
	vertex_declaration->addElement(VE_POSITION, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
}

/////////////////////////////////////////////////////////////////////

void OgreMeshRenderable::fillHardwareBuffers() {
#if 0
	std::cout << "fill" << std::endl;
	
	prepareHardwareBuffers(mMesh->mNbVertices, mMesh->mNbIndices);
	
	std::cout << "fill.a" << std::endl;
	
	// Temp.
	Ogre::Vector3 max, min;
	max = Ogre::Vector3(100,100,100);
	min = Ogre::Vector3(-100,-100,-100);

	std::cout << "fill.b" << std::endl;
	
	Ogre::HardwareVertexBufferSharedPtr position_buf = mRenderOp.vertexData->vertexBufferBinding->getBuffer(VE_POSITION);
	position_buf->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	//position_buf->writeData(0, mMesh->mNbVertices * sizeof(NxVec3), mMesh->mVertices, false);
	Ogre::Real *p = static_cast<Ogre::Real*>(position_buf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	
	for (unsigned int i=0; i < mMesh->mNbVertices;i++) {
		*p++ = mMesh->mVertices[i].x;
		*p++ = mMesh->mVertices[i].y;
		*p++ = mMesh->mVertices[i].z;
	}

	position_buf->unlock();

	std::cout << "fill.c" << std::endl;
	
	Ogre::HardwareIndexBufferSharedPtr index_buf = mRenderOp.indexData->indexBuffer;
	index_buf->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	//index_buf->writeData(0, mMesh->mNbIndices * sizeof(NxU32), mMesh->mIndices, false);
	unsigned int *t = static_cast<unsigned int*>(index_buf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	for (unsigned int i=0; i < mMesh->mNbIndices;i++) {
		*t++ = mMesh->mIndices[i];
	}

	index_buf->unlock();
	std::cout << "fill.d" << std::endl;
	
	mBox.setExtents(min, max);
	std::cout << "fill.e" << std::endl;
#endif
}

/////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
