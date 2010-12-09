/** \file    NxOgreSceneRenderer.h
 *  \brief   Header for the SceneRenderer, NullSceneRenderer and Renderable classes
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

#ifndef __NXOGRE_SCENE_RENDERER_H__
#define __NXOGRE_SCENE_RENDERER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"
#include "NxOgrePose.h"
#include "NxOgreRenderableSource.h"
#include "BetajaenCC.h"
#include "NxOgreNodeRenderable.h"			// For: NodeRenderableParams
#include "NxOgreMeshRenderable.h"			// For: MeshRenderableParams

namespace NxOgre {

	//////////////////////////////////////////////////////////////////////////////

	class NxPublicClass RenderEvent {
		public:
			NxReal Delta;
			NxReal Accumulated;
	};

	//////////////////////////////////////////////////////////////////////////////

	class NxPublicClass Renderables {
			
		public:

			Actors			actors;
			Characters		characters;
			//Cloths		cloths
			//...
	};
		
	//////////////////////////////////////////////////////////////////////////////
	
	class NxPublicClass SceneRenderer {
		
		friend class Scene;
		
		public:
			
			SceneRenderer(Scene*, NxString rendererUserData);
			virtual ~SceneRenderer();
			void render(const TimeStep&);

			void registerSource(RenderableSource*);
			void unregisterSource(RenderableSource*);

			enum RenderAccuracy {

				/** \brief Everything gets rendered, regardless if it has changed or not.
					Most accurate, but slowest form of rendering.
				*/
				RA_ALL,
				/** \brief Things get rendered according to NxTransform from Scene
				*/
				RA_NX_TRANSFORM,
				/** \brief Things get rendered according to known moved sources.
					\default
				*/
				RA_SOURCES
			};

			void setAccuracy(RenderAccuracy);

			virtual NodeRenderable* createNodeRenderable(NodeRenderableParams) = 0;
			virtual MeshRenderable* createMeshRenderable(MeshRenderableParams, Resources::Mesh*) = 0;


			virtual void setCustom(const NxString& identifier, void* ptr) = 0;
			virtual void setCustom(const NxString& identifier, const NxString& value) = 0;
			virtual void* getCustom(const NxString& identifier) = 0;

		protected:
			
			Scene*					mScene;
			NxScene*				mNxScene;
			RenderAccuracy			mRenderAccuracy;

			typedef Betajaen::SharedList<RenderableSource>				RenderableSources;

			RenderableSources		mSources;
			
	
		private:
			
	};
		
	//////////////////////////////////////////////////////////////////////////////
	
	class NxPublicClass NullSceneRenderer : public SceneRenderer {
	
		friend class Scene;
			
		public:
			
			NullSceneRenderer(Scene* s, NxString rud) : SceneRenderer(s, rud) {}
			~NullSceneRenderer() {}
			
			NodeRenderable* createNodeRenderable(NodeRenderableParams) {
				return NULL;
			}

			MeshRenderable* createMeshRenderable(MeshRenderableParams, Resources::Mesh*) {
				return NULL;
			}
			
			void setCustom(const NxString& identifier, void* ptr) {}
			void setCustom(const NxString& identifier, const NxString& value) {}
			void* getCustom(const NxString& identifier) {return 0;}

		protected:

		private:
			
	};


};

#endif
