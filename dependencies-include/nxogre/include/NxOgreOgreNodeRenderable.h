/** \file    NxOgreOgreNodeRenderable.h
 *  \brief   Header for the OgreNodeRenderable class.
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

#ifndef __NXOGRE_OGRE_NODE_RENDERABLE_H__
#define __NXOGRE_OGRE_NODE_RENDERABLE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreRenderable.h"
#include "NxOgreNodeRenderable.h"

namespace NxOgre {

	enum {
		NxOgreClass_OgreNodeRenderable = 51417
	};

	/** \brief SceneNode/Entity combination implementation of NodeRenderable for Ogre.
			
		\note NodeRenderableParams specific to Ogre.
			
		* GraphicsModel	refers to the name of the mesh or entity.
		* GraphicsModelType
			-> GMT_FILE						Not used.
			-> GMT_RESOURCE_IDENTIFIER		Mesh is in ResourceSystem use that.
			-> GMT_EXISTING_REFERENCE		Model is an entity use that.
		* Identifier refers to the name of the SceneNode
		* IdentifierType refers to usage of that name.		
			-> IT_CREATE					Create a SceneNode with that name.
			-> IT_USE						Use an existing SceneNode with that name.
		* GraphicsMaterial refers to the Ogre Material used.
		* GraphicsScale refers to the scale of the Node.
			
		\example
			
			- Create a SceneNode, using a OgreHead.mesh as mesh, scale it 2,2,2 and assign 
			  a material.
				"model: OgreHead.mesh, scale: 2 2 2, material: PureWhite"
			
			- Use an existing Entity
				"model: myEntity, model-type: reference"
			
			- Use an existing SceneNode
				"identifier: myNode, identifier-usage: reference"
			
	*/
	class NxPublicClass OgreNodeRenderable : public NodeRenderable {

		public:


			/** \brief NodeRenderer constructor. Creates a node, and a offset node (depending
				if there is an offset specified), and attaches an entity (based on the Graphical
				Model params), or other movable objects provided by the OgreNodeRenderable methods.
			*/
			OgreNodeRenderable(NodeRenderableParams, OgreSceneRenderer*);


			/** \brief NodeRenderer destructor. Will destroy node, offset node and everything
				attached to it, except for cameras which will be moved to the root scenenode.
			*/
			~OgreNodeRenderable();


			/** \brief Set the Pose of the Node
			*/
			void setPose(const Pose&);


			/** \brief Get the Pose of the Node
			*/
			Pose getPose() const;


			/** \brief Set's every entity of the node to the same material
			*/
			void setMaterial(const NxString&);


			/** \brief Gets the material of the first sub-mesh of the mesh of the first entity
			*/	
			NxString getMaterial() const;


			/** \brief Set the Scale of the node
			*/
			void setScale(const Ogre::Vector3&);


			/** \brief Set the scale of the node from a NxVec3
			*/
			void setScale(const NxVec3&);

			/** \brief Set the scale of the node from a float3
			*/
			void setScale(const float3&);

			/** \brief Get the known scale of the node as a Vector3
			*/
			Ogre::Vector3 getScaleAsOgreVector3() const;

			/** \brief Get the known scale of the node as a NxVec3
			*/
			NxVec3 getScaleAsNxVec3() const;

			/** \brief Get the known scale of the node as a float3
			*/
			float3 getScaleAsFloat3() const;

			/** \brief Set the offset of the node
			*/
			void setOffset(const Pose&);


			/** \brief Get the offset of the node
			*/
			Pose getOffset() const;


			/** \brief Get the Type identifier as a string
			*/
			NxString getType() {return "Ogre-NodeRenderable";}


			/** \brief Get the Type identifier as a NxShortHashIdentifier
			*/
			NxShortHashIdentifier getHashType() const {return NxOgreClass_OgreNodeRenderable;}

			/** \brief Create a child scene node
			*/
			Ogre::SceneNode* createSceneNode(const NxString& name, const Ogre::Vector3& = Ogre::Vector3::ZERO, const Ogre::Quaternion& = Ogre::Quaternion::IDENTITY);

			/** \brief Add a pre-existing node to the node or offset node.
				\note If this node is a child of another, it will remove the node for you.
			*/
			void addSceneNode(Ogre::SceneNode*);


			/** \brief Add a pre-existing node to the node or offset node using a string as an
					   identifier.
				\note If this node is a child of another, it will remove the node for you.
			*/
			void addSceneNode(const NxString&);


			/** \brief Add a pre-existing entity to the node or offset node.
				\note If this entity is already attached to another scenenode it
					  will remove it for you.
			*/
			void addEntity(Ogre::Entity*);


			/** \brief Add a movable object to this node or offset node
				\note If this movable object is already attached to another scenenode it
					  will remove it for you.
			*/
			void addMovableObject(Ogre::MovableObject*);


			/** \brief Removes a node from the node or offsetnode
			*/
			void removeSceneNode(Ogre::SceneNode*);


			/** \brief Removes a node from the node or offsetnode using a string as an identifier
			*/
			void removeSceneNode(const NxString&);


			/** \brief Remove an entity from the node or offset node, but don't delete it
			*/
			void removeEntity(Ogre::Entity*);


			/** \brief Remove an entity from the node or offset node, but don't delete it,
				using a string as an identifier.
			*/
			void removeEntity(const NxString&);


			/** \brief Destroys an entity from the node or offset node.
			*/
			void destroyEntity(Ogre::Entity*);


			/** \brief Destroys an entity from the node or offset node, using a string as
				an identifier.
			*/
			void destroyEntity(const NxString&);


			/** \brief Remove an MovableObject from the node or offset node, but don't delete
					   it.
			*/
			void removeMovableObject(Ogre::MovableObject*);


			/** \brief Remove an MovableObject from the node or offset node, but don't delete
					   it, using a string as an identifier.
			*/
			void removeMovableObject(const NxString&);


			/** \brief Destroys an MovableObject from the node or offset node.
			*/
			void destroyMovableObject(Ogre::MovableObject*);


			/** \brief Destroys an MovableObject from the node or offset node.
			*/
			void destroyMovableObject(const NxString&);


			/** \brief Get's the Node.
			*/
			Ogre::SceneNode* getNode();


			/** \brief Get's the offset node. If there is no offset, then NULL is returned.
			*/
			Ogre::SceneNode* getOffsetNode();


		protected:


			void __createNode(const NxString& identifier, const Pose& pose);
			void __createOffsetNode(const NxString& identifier, const Pose& pose);
			Ogre::Entity* __getEntity(const NxString& identifier, bool CreateOrGet, const NxString& mesh = "");
			void __destroyObjects(Ogre::SceneNode*);
			inline void __parseEntity(Ogre::Entity*);
			inline void __parseMovableObject(Ogre::MovableObject*);

			Ogre::SceneNode*	mNode;
			Ogre::SceneNode*	mOffsetNode;
			NxVec3				mKnownScale;
			Ogre::SceneManager*	mSceneMgr;
			OgreSceneRenderer*	mOgreRenderer;


		private:


	};
	
};

#endif
