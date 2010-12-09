/** \file    NxOgreOgreSceneRenderer.h
 *  \brief   Header for the OgreSceneRenderer class.
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

#ifndef __NXOGRE_OGRE_SCENE_RENDERER_H__
#define __NXOGRE_OGRE_SCENE_RENDERER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"
#include "NxOgrePose.h"
#include "NxOgreNodeRenderable.h"			// For: NodeRenderableParams
#include "NxOgreMeshRenderable.h"			// For: MeshRenderableParams
#include "NxOgreSceneRenderer.h"

namespace NxOgre {

	//////////////////////////////////////////////////////////////////////////////
	
	/** \brief SceneRenderer for the Ogre3D Rendering Engine.
		
		\note rendererUserData requires the name of the SceneManager
			  to use, in the format of "name", otherwise
			  the SceneRenderer will use the First SceneManager known.

	*/
	class NxPublicClass OgreSceneRenderer : public SceneRenderer {

		friend class Scene;
			
		public:
			
			/** \brief SceneRenderer Constructor


				\note rendererUserData string params combinations

						name		- Use this scenemanager with this name.
						#first		- Use the first scenemanager created.
						#last		- Use the last scenemanager created.

			*/
			OgreSceneRenderer(Scene* s, NxString rendererUserData);
			virtual ~OgreSceneRenderer();
			
			/** \brief Create a specific NodeRenderable to the SceneRender.
				\note With the "Intent" param different sub-types of the NodeRenderable
					  can be made and used. For example with Wheels you may wish
					  to dynamically add the springs and steering to the graphics model.
					  With the intent param being "NxOgre-Wheel" you can know that and 
					  use a "OgreWheelNodeRenderable", instead of "OgreNodeRenderable".

					  Of course this is a suggestion, the implementation if you choose
					  to use it, is purely up to you.
			*/
			virtual NodeRenderable* createNodeRenderable(NodeRenderableParams);

			/** \brief Create a specific MeshRenderable to the MeshRenderable

			*/
			virtual MeshRenderable* createMeshRenderable(MeshRenderableParams, Resources::Mesh*);

			// Nothing special with these, so we just use the defaults.
			//void renderAll();
			//void renderNxTransform(Actors*, Characters*); /** and so on */
			//void renderSources();
			
			Ogre::SceneManager* getSceneMgr() {
				return mSceneMgr;
			}

			virtual void setCustom(const NxString& identifier, void* ptr);
			virtual void setCustom(const NxString& identifier, const NxString& value);
			void*        getCustom(const NxString& identifier);

		protected:

			Ogre::SceneManager* mSceneMgr;

		private:
	};

	//////////////////////////////////////////////////////////////////////////////


};

#endif
	