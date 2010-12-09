/** \file    NxOgreOgreMeshRenderable.h
 *  \brief   Header for the OgreMeshRenderable class.
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

#ifndef __NXOGRE_OGRE_MESH_RENDERABLE_H__
#define __NXOGRE_OGRE_MESH_RENDERABLE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreRenderable.h"
#include "NxOgreMeshRenderable.h"

#include "OgreSimpleRenderable.h"

namespace NxOgre {

	// "OgreMeshRenderable"
	enum {
		NxOgreClass_OgreMeshRenderable = 51360
	};

	/** \brief Ogre Mesh representive of DynamicMesh, with an optional SceneNode/Entity
			   combination.

			   From http://www.ogre3d.org/wiki/index.php/DynamicGrowingBuffers
	*/
	class NxPublicClass OgreMeshRenderable : public MeshRenderable, public Ogre::SimpleRenderable {

		public:

			NxString getType() {return "Ogre-MeshRenderable";}
			NxShortHashIdentifier getHashType() const {return NxOgreClass_OgreMeshRenderable;}
		
			OgreMeshRenderable(MeshRenderableParams, Resources::Mesh*, OgreSceneRenderer*);
			~OgreMeshRenderable();

			enum VertexElements{
				VE_POSITION = 0,
				VE_NORMAL = 1,
				VE_TEXTURE = 2
			};

			/** Initializes the dynamic renderable.
			   @remarks
				  This function should only be called once. It initializes the
				  render operation, and calls the abstract function
				  createVertexDeclaration().
			   \param operationType The type of render operation to perform.
			   \param useIndices Specifies whether to use indices to determine the
					  vertices to use as input. */
			  void initialize(Ogre::RenderOperation::OperationType operationType,
							  bool useIndices);

			  /// Implementation of Ogre::SimpleRenderable
			  virtual Ogre::Real getBoundingRadius(void) const;
			  /// Implementation of Ogre::SimpleRenderable
			  virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const;

			public:

			  /// Maximum capacity of the currently allocated vertex buffer.
			  size_t mVertexBufferCapacity;
			  /// Maximum capacity of the currently allocated index buffer.
			  size_t mIndexBufferCapacity;

			  /** Creates the vertex declaration.
			   @remarks
				  Override and set mRenderOp.vertexData->vertexDeclaration here.
				  mRenderOp.vertexData will be created for you before this method
				  is called. */
			  virtual void createVertexDeclaration();

			  /** Prepares the hardware buffers for the requested vertex and index counts.
			   @remarks
				  This function must be called before locking the buffers in
				  fillHardwareBuffers(). It guarantees that the hardware buffers
				  are large enough to hold at least the requested number of
				  vertices and indices (if using indices). The buffers are
				  possibly reallocated to achieve this.
			   @par
				  The vertex and index count in the render operation are set to
				  the values of vertexCount and indexCount respectively.
			   \param vertexCount The number of vertices the buffer must hold.

			   \param indexCount The number of indices the buffer must hold. This
					  parameter is ignored if not using indices. */
			  void prepareHardwareBuffers(size_t vertexCount, size_t indexCount);

			  /** Fills the hardware vertex and index buffers with data.
			   @remarks
				  This function must call prepareHardwareBuffers() before locking
				  the buffers to ensure the they are large enough for the data to
				  be written. Afterwards the vertex and index buffers (if using
				  indices) can be locked, and data can be written to them. */
			  virtual void fillHardwareBuffers();

			/////////////////////////

			// TEMP FOR ALL OF THESE.
			void renderMesh() {}

			void setPose(const Pose&) {}
			Pose getPose() const {return Pose();}

			//void setMaterial(const NxString&) {}
			//NxString getMaterial() const {return NxString("");}

			void setOffset(const Pose&) {}
			Pose getOffset() const {return Pose();}

		protected:

			Ogre::SceneManager*	mSceneMgr;
			OgreSceneRenderer*	mOgreRenderer;


		private:


	};
	
};

#endif
