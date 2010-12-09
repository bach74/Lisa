/** \file    NxOgreMeshRenderableSource.h
 *  \brief   Header for the MeshRenderable and MeshRenderableParams classes.
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

#ifndef __NXOGRE_MESH_RENDERABLE_H__
#define __NXOGRE_MESH_RENDERABLE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreRenderable.h"
#include "NxOgreParams.h"
#include "NxOgrePose.h"

namespace NxOgre {
	
		/** \brief MeshRenderableParams are a way to describe in abstract how a Mesh
			is roughly configured; names, positions and materials.
		*/
		class NxPublicClass MeshRenderableParams : public Params {

		public:


			MeshRenderableParams()				{
													setToDefault();
												}

			MeshRenderableParams(const char* p)	{
													process(p);
												}

			MeshRenderableParams(NxString p)				{
													process(p);
												}

			/** \brief Set's the Params to default based on NxActorDesc and NxBodyDesc defaults.
			*/
			void			setToDefault();

			/** Identifier for the Implementation of the Mesh.
				\note Leave blank for a random generated one.
				\default Blank String -> Random generated name when created.
				@string "identifier"
			*/
			NxString		ImplementationIdentifier;

			/** Usage of Implement; Create implementation, use a pre-existing one or none
				at all.
				@string "identifer-usage"
				\default IT_CREATE
			*/
			enum ImplementationIdentifierUsage {
				// "create"
				IT_CREATE,
				// "use"
				IT_USE,
				// "none" - Just make/modify the model do not implement.
				IT_NONE
			};

			ImplementationIdentifierUsage ImplementationIdentifierType;


			/** \brief The graphics model identifier
				@string "model-identifier"
				\note If the string is blank, then the identifier is generated for you.
			*/
			NxString		GraphicsModelIdentifier;

			/** \brief The initial pose.
				@string "position", "orientation"
			*/
			Pose			GraphicsModelPose;

			/** Offset from the center of the pose.
				@string "offset-position", "offset-orientation"
				\default Pose()
			*/
			Pose			GraphicsModelOffset;

			/** RenderMaterial Override
				@string "material"
				\default Blank String
			*/
			NxString		GraphicsModelMaterial;

			/** \brief For "SubNodeRenderable behaviour, allowing you to tell the NodeRenderable
					   or the SceneRender what the NodeRenderable is intended for, which then
					   the NodeRenderable/SceneRender can be more accommodating.

					   For most classes NodeRenderable in NxOgre, they may adjust the Parameters
					   to add their type into the Intent string for you, unless you've added 
					   it yourself.

			   \default Blank String, may be adjusted when Parameters are handed to a class.
			*/ 
			NxString		Intent;

			private:
			
			//! \internal
			void			parse(Parameters);

	}; // End of NodeRenderableParams class

	/** \brief Self-contained renderable, with a model that can be frequency moved around
		Similar to the Ogre system of a SceneNode with an Entity attached. Multiple models
		are subject to the RenderSystem the Renderable is working with.
		@abstract
	*/
	class NxPublicClass MeshRenderable : public Renderable {

		public:

			MeshRenderable(MeshRenderableParams, Resources::Mesh*, SceneRenderer*);

			virtual void renderMesh() = 0;

			virtual void setPose(const Pose&) = 0;
			virtual Pose getPose() const = 0;

//			virtual void setMaterial(const NxString&) = 0;
//			virtual NxString getMaterial() const = 0;

			virtual void setOffset(const Pose&) = 0;
			virtual Pose getOffset() const = 0;

			virtual NxString getType() {return "NxOgre-NodeRenderable";}
			virtual NxShortHashIdentifier getHashType() const {return 42719;}

			Resources::Mesh* mMesh;

	};
	
	//////////////////////////////////////////////////////////

};

#endif
