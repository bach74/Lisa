/** \file    NxOgreCloth.h
 *  \brief   Header for the ClothParams and Cloth classes, and Cloth struct.
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

#ifndef __NXOGRE_CLOTH_H__
#define __NXOGRE_CLOTH_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreParams.h"

#if 0

namespace NxOgre {

	class NxPublicClass ClothParams : public Params {

		public:

			ClothParams()						{
													setToDefault();
												}

			ClothParams(const char* p)			{
													process(p);
												}

			ClothParams(NxString p)				{
													process(p);
												}

			void			setToDefault();

			private:

			//! \internal
			void			parse(Parameters);

	}; //End of ClothParams class

	//////////////////////////////////////////////////////////////////

	class ClothStruct {
		
		public:

	};

	//////////////////////////////////////////////////////////////////

	class Cloth {

		public:

			/** \brief Cloth Constructor.
			*/
			Cloth(const NxString& identifier, const NxString& clothMeshIdentifier, Scene*, const Pose& pose, ClothParams = ClothParams());
			
			/** \brief Generic Cloth constructor for inheritables
			*/
			Cloth(const NxString& identifier, Scene*);

			/**
			*/
			~Cloth();
			
			void		 createCloth(NxClothMesh*, ClothParams, Pose pose);
			void		 destroyCloth();

			/** \brief Returns a pointer the cloth mesh used by the cloth.
			*/
			NxClothMesh* getClothMesh() const;

			/** \brief Returns a pointer to the cloth
			*/
			NxCloth* getNxCloth() const;
			
			/** \brief Sets the cloth bending stiffness in the range from 0 to 1.
			*/
			void setBendingStiffness(NxReal stiffness);

			/** \brief Retrieves the cloth bending stiffness.
			*/
			NxReal getBendingStiffness() const;

			/**	\brief Sets the cloth stretching stiffness in the range from 0 to 1.
			*/
			void setStretchingStiffness(NxReal stiffness);

			/** \brief Retrieves the cloth stretching stiffness.
			*/
			NxReal getStretchingStiffness() const;

			/** \brief Sets the damping coefficient in the range from 0 to 1.
			*/
			void setDampingCoefficient(NxReal dampingCoefficient);

			/** \brief Retrieves the damping coefficient.
			*/
			NxReal getDampingCoefficient() const;

			/** \brief Sets the cloth friction coefficient in the range from 0 to 1.
			*/
			void setFriction(NxReal friction);

			/** \brief Retrieves the cloth friction coefficient.
			*/
			NxReal getFriction() const;

			/** \brief Sets the cloth pressure coefficient (must be non negative).
			*/
			void setPressure(NxReal pressure);

			/** \brief Retrieves the cloth pressure coefficient.
			*/
			NxReal getPressure() const;

			/** \brief Sets the cloth tear factor (must be larger than one).
			*/
			void setTearFactor(NxReal factor);

			/** \brief Retrieves the cloth tear factor.
			*/
			NxReal getTearFactor() const;

			/** \brief Sets the cloth attachment tear factor (must be larger than one).
			*/
			void setAttachmentTearFactor(NxReal factor);

			/** \brief Retrieves the attachment cloth tear factor.
			*/
			NxReal getAttachmentTearFactor() const;

			/** \brief Sets the cloth thickness (must be positive).
			*/
			void setThickness(NxReal thickness);

			/** \brief Gets the cloth thickness.
			*/
			NxReal getThickness() const;

			/** \brief Gets the cloth density.
			*/
			NxReal getDensity() const;

			/** \brief Gets the relative grid spacing for the broad phase.
			The cloth is represented by a set of world aligned cubical cells in broad phase.
			The size of these cells is determined by multiplying the length of the diagonal
			of the AABB of the initial cloth size with this constant.
			*/
			NxReal getRelativeGridSpacing() const;

			/** \brief Retrieves the cloth solver iterations.
			*/
			NxU32 getSolverIterations() const;

			/** \brief Sets the cloth solver iterations.
			*/
			void setSolverIterations(NxU32 iterations);

			/** \brief Returns a world space AABB enclosing all cloth points.
			*/
			void getWorldBounds(NxBounds3& bounds) const;

			/** \brief Attaches the cloth to a shape. All cloth points currently inside the shape are attached.
			*/
			void attachToShape(const NxShape *shape, NxU32 attachmentFlags);

			/** \brief Attaches the cloth to all shapes, currently colliding. 
			*/
			void attachToCollidingShapes(NxU32 attachmentFlags);

			/** \brief Detaches the cloth from a shape it has been attached to before. 
			*/
			void detachFromShape(const NxShape *shape);

			/** \brief Attaches a cloth vertex to a local position within a shape.
			*/
			void attachVertexToShape(NxU32 vertexId, const NxShape *shape, const NxVec3 &localPos, NxU32 attachmentFlags);

			/** \brief Attaches a cloth vertex to a position in world space.
			*/
			void attachVertexToGlobalPosition(const NxU32 vertexId, const NxVec3 &pos);

			/** \brief Frees a previously attached cloth point.
			*/
			void freeVertex(const NxU32 vertexId);

			/** \brief Changes the weight of a vertex in the cloth solver for a period of time.

			If this method is called for some vertex, the cloth solver will, during a time
			period of length expirationTime, assign a different weight to the vertex
			while internal cloth constraints (i.e. bending & stretching) are being resolved.
			
			With a high dominanceWeight, the modified vertex will force neighboring vertices
			to strongly accommodate their positions while its own is kept fairly constant. 
			The reverse holds for smaller dominanceWeights. 
			
			Using a dominanceWeight of +infinity has a similar effect as temporarily attaching 
			the vertex to a global position. However, unlike using attachments, the velocity 
			of the vertex is kept intact when using this method.
			
			\note The current implementation will not support the full range of dominanceWeights.
			All dominanceWeights > 0.0 are treated equally as being +infinity.

			\note An expiration time of 0.0 is legal and will result in dominance being
			applied throughout one substep before being discarded immediately.

			\note Having a large number of vertices dominant at once may result in a performance penalty.

			\param[in] vertexId Index of the vertex.
			\param[in] expirationTime Time period where dominance will be active for this vertex.
			\param[in] dominanceWeight Dominance weight for this vertex.


			\see attachVertexToGlobalPosition()
			*/
			void dominateVertex(NxU32 vertexId, NxReal expirationTime, NxReal dominanceWeight);

			/**
			\brief Return the attachment status of the given vertex.

			\param[in] vertexId Index of the vertex.

			\see getVertexAttachmentShape() getVertexAttachmentPosition()
			*/
			NxClothVertexAttachmentStatus getVertexAttachmentStatus(NxU32 vertexId) const;

			/** \brief Returns the pointer to an attached shape pointer of the given vertex.

			If the vertex is not attached or attached to a global position, NULL is returned.

			\param[in] vertexId Index of the vertex.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getVertexAttachmentStatus() getVertexAttachmentPosition()
			*/
			NxShape* getVertexAttachmentShape(NxU32 vertexId) const;

			/** \brief Returns the attachment position of the given vertex.

			If the vertex is attached to shape, the position local to the shape's pose is returned.
			If the vertex is not attached, the return value is undefined.

			\param[in] vertexId Index of the vertex.

			\see getVertexAttachmentStatus() getVertexAttachmentShape()
			*/
			NxVec3 getVertexAttachmentPosition(NxU32 vertexId) const;

			/** \brief Attaches the cloth to an actor. 
			
			\note Call this function only once right after the cloth is created.
			Turning cloth into metal and vice versa during the simulation is not recommended.

			\note This feature is well suited for volumetric objects like barrels. 
			It cannot handle two dimensional flat pieces well.
			
			After this call, the cloth is infinitely stiff between collisions and simply 
			moves with the actor. At impacts with an impact impulse greater than impulseThreshold, 
			the cloth is plastically deformed. Thus, a cloth with a core behaves like a piece of metal.

			The core actor's geometry is adjusted automatically. Its size also depends on the 
			cloth thickness. Thus, it is recommended to choose small values for the thickness.
			At impacts, colliding objects are moved closer to the cloth by the value provided in 
			penetrationDepth which causes a more dramatic collision result.

			The core actor must have at least one shape, and currently supported shapes are 
			spheres, capsules, boxes and compounds of spheres.
			It is recommended to specify the density rather than the mass of the core body. 
			This way the mass and inertia tensor are updated when the core deforms.

			The maximal deviation of cloth particles from their initial positions
			(modulo the global rigid body transforms translation and rotation) can be
			specified via the parameter maxDeformationDistance. Setting this parameter to
			zero means that the deformation is not limited.  

			\param actor The core actor to attach the cloth to.
			\param impulseThreshold Threshold for when deformation is allowed.
			\param penetrationDepth Amount by which colliding objects are brought closer to the cloth.
			\param maxDeformationDistance Maximum deviation of cloth particles from initial position.

			*/
			void attachToCore(NxActor *actor, NxReal impulseThreshold, NxReal penetrationDepth = 0.0f, NxReal maxDeformationDistance = 0.0f);

			/** \brief Tears the cloth at a given vertex. 
			
			First the vertex is duplicated. The triangles on one side of the split plane keep 
			the original vertex. For all triangles on the opposite side the original vertex is 
			replaced by the new one. The split plane is defined by the world location of the 
			vertex and the normal provided by the user.

			Note: TearVertex performs a user defined vertex split in contrast to an automatic split
			that is performed when the flag NX_CLF_TEARABLE is set. Therefore, tearVertex works 
			even if NX_CLF_TEARABLE is not set in NxClothDesc.flags.

			Note: For tearVertex to work, the clothMesh has to be cooked with the flag
			NX_CLOTH_MESH_TEARABLE set in NxClothMeshDesc.flags.

			\param[in] vertexId Index of the vertex to tear.
			\param[in] normal The normal of the split plane.
			\return true if the split had an effect (i.e. there were triangles on both sides of the split plane)

			\see NxClothFlag, NxClothMeshFlags, NxClothDesc.flags NxSimpleTriangleMesh.flags

			*/
			bool tearVertex(const NxU32 vertexId, const NxVec3 &normal);

			/** \brief Executes a raycast against the cloth.

			\param[in] worldRay The ray in world space.
			\param[out] hit The hit position.
			\param[out] vertexId Index to the nearest vertex hit by the raycast.

			\return true if the ray hits the cloth.

			*/
			bool raycast(const NxRay& worldRay, NxVec3 &hit, NxU32 &vertexId);

			/** \brief Sets which collision group this cloth is part of.

			\param[in] collisionGroup The collision group for this cloth.

			\see NxCollisionGroup
			*/
			void setGroup(NxCollisionGroup collisionGroup);

			/** \brief Retrieves the value set with #setGroup().

			\return The collision group this cloth belongs to.

			\see NxCollisionGroup
			*/
			NxCollisionGroup getGroup() const;

			/**
			\brief Sets 128-bit mask used for collision filtering.

			\param[in] groupsMask The group mask to set for the cloth.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getGroupsMask() NxGroupsMask
			*/
			void setGroupsMask(const NxGroupsMask& groupsMask);

			/**
			\brief Sets 128-bit mask used for collision filtering.

			\return The group mask for the cloth.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setGroupsMask() NxGroupsMask
			*/
			 const NxGroupsMask getGroupsMask() const;

			/**
			\brief Sets the user buffer wrapper for the cloth mesh.

			\param[in,out] meshData User buffer wrapper.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxMeshData NxClothDesc.meshData
			*/
			 void setMeshData(NxMeshData& meshData);

			/**
			\brief Returns a copy of the user buffer wrapper for the cloth mesh.
			
			\return User buffer wrapper.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxMeshData setMeshData() NxClothDesc.meshData
			*/
			 NxMeshData getMeshData();

			/**
			\brief Sets the valid bounds of the cloth in world space.

			If the flag NX_CLF_VALIDBOUNDS is set, these bounds defines the volume
			outside of which cloth particle are automatically removed from the simulation. 

			\param[in] validBounds The valid bounds.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.validBounds getValidBounds() NxBounds3
			*/
			 void setValidBounds(const NxBounds3& validBounds);

			/**
			\brief Returns the valid bounds of the cloth in world space.

			\param[out] validBounds The valid bounds.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.validBounds setValidBounds() NxBounds3
			*/
			 void getValidBounds(NxBounds3& validBounds) const;

			/**
			\brief Sets the position of a particular vertex of the cloth.

			\param[in] position New position of the vertex.
			\param[in] vertexId Index of the vertex.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getPosition() setPositions() getPositions() setVelocity() getVelocity() getNumberOfParticles()
			*/
			 void setPosition(const NxVec3& position, NxU32 vertexId);

			/**
			\brief Sets the positions of the cloth.

			The user must supply a buffer containing all positions (i.e same number of elements as number of particles).

			\param[in] buffer The user supplied buffer containing all positions for the cloth.
			\param[in] byteStride The stride in bytes between the position vectors in the buffer. Default is size of NxVec3.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getPositions() setVelocities() getVelocities() getNumberOfParticles()
			*/
			 void setPositions(void* buffer, NxU32 byteStride = sizeof(NxVec3));

			/**
			\brief Gets the position of a particular vertex of the cloth.

			\param[in] vertexId Index of the vertex.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setPosition() setPositions() getPositions() setVelocity() getVelocity() getNumberOfParticles()
			*/
			 NxVec3 getPosition(NxU32 vertexId) const;

			/**
			\brief Gets the positions of the cloth.

			The user must supply a buffer large enough to hold all positions (i.e same number of elements as number of particles).

			\param[in] buffer The user supplied buffer to hold all positions of the cloth.
			\param[in] byteStride The stride in bytes between the position vectors in the buffer. Default is size of NxVec3.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setPositions() setVelocities() getVelocities() getNumberOfParticles()
			*/
			 void getPositions(void* buffer, NxU32 byteStride = sizeof(NxVec3));

			/**
			\brief Sets the velocity of a particular vertex of the cloth.

			\param[in] position New velocity of the vertex.
			\param[in] vertexId Index of the vertex.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setPosition() getPosition() getVelocity() setVelocities() getVelocities()  getNumberOfParticles()
			*/
			 void setVelocity(const NxVec3& velocity, NxU32 vertexId);
			
			/**
			\brief Sets the velocities of the cloth.

			The user must supply a buffer containing all velocities (i.e same number of elements as number of particles).

			\param[in] buffer The user supplied buffer containing all velocities for the cloth.
			\param[in] byteStride The stride in bytes between the velocity vectors in the buffer. Default is size of NxVec3.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getVelocities() setPositions() getPositions() getNumberOfParticles()
			*/
			 void setVelocities(void* buffer, NxU32 byteStride = sizeof(NxVec3));

			/**
			\brief Gets the velocity of a particular vertex of the cloth.

			\param[in] vertexId Index of the vertex.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setPosition() getPosition() setVelocity() setVelocities() getVelocities()  getNumberOfParticles()
			*/
			 NxVec3 getVelocity(NxU32 vertexId) const;
			
			/**
			\brief Gets the velocities of the cloth.

			The user must supply a buffer large enough to hold all velocities (i.e same number of elements as number of particles).

			\param[in] buffer The user supplied buffer to hold all velocities of the cloth.
			\param[in] byteStride The stride in bytes between the velocity vectors in the buffer. Default is size of NxVec3.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setVelocities() setPositions() getPositions() getNumberOfParticles()
			*/
			 void getVelocities(void* buffer, NxU32 byteStride = sizeof(NxVec3));

			/**
			\brief Gets the number of cloth particles.
			
			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see setVelocities() getVelocities() setPositions() getPositions() 
			*/
			 NxU32 getNumberOfParticles();

			/**
			\brief Queries the cloth for the currently interacting shapes. Must be called prior to saveStateToStream in order for attachments and collisons to be saved.
			
			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getShapePointers() setShapePointers() saveStateToStream() loadStateFromStream()
			*/
			 NxU32 queryShapePointers();

			/**
			\brief Gets the byte size of the current cloth state.
			
			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getNumberOfParticles()
			*/
			 NxU32 getStateByteSize();

			/**
			\brief Saves pointers to the currently interacting shapes to memory

			\param[in] shapePointers The user supplied array to hold the shape pointers.
			\param[in] flags         The optional user supplied array to hold the cloth attachment flags for each attached shape

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see queryShapePointers() setShapePointers() saveStateToStream() loadStateFromStream()
			*/
			 void getShapePointers(NxShape** shapePointers,NxU32 *flags=0);

			/**
			\brief Loads pointers to the currently interacting shapes from memory.

			\param[in] shapePointers The user supplied array that holds the shape pointers. Must be in the exact same order as the shapes were retrieved by getShapePointers.
			\param[in] numShapes The size of the supplied array.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see queryShapePointers() getShapePointers() saveStateToStream() loadStateFromStream()
			*/
			 void setShapePointers(NxShape** shapePointers,unsigned int numShapes);

			/**
			\brief Saves the current cloth state to a stream. 
			
			queryShapePointers must be called prior to this function in order for attachments and collisions to be saved. 
			Tearable and metal cloths are currently not supported.
			A saved state contains platform specific data and can thus only be loaded on back on the same platform.

			\param[in] stream The user supplied stream to hold the cloth state.
			\param[in] permute If true, the order of the vertices output will correspond to that of the associated
			NxClothMesh's saveToDesc mehod; if false (the default), it will correspond to the original NxClothMesh descriptor
			used to create the mesh. These may differ due to cooking.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see loadStateFromStream() queryShapePointers() getShapePointers() setShapePointers() 
			*/
			 void saveStateToStream(NxStream& stream, bool permute = false);

			/**
			\brief Loads the current cloth state from a stream. 
			
			setShapePointers must be called prior to this function if attachments and collisions are to be loaded. 
			Tearable and metal cloths are currently not supported.
			A saved state contains platform specific data and can thus only be loaded on back on the same platform.

			\param[in] stream The user supplied stream that holds the cloth state.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see saveStateToStream() queryShapePointers() getShapePointers() setShapePointers() 
			*/
			 void loadStateFromStream(NxStream& stream);

			/**
			\brief Sets the collision response coefficient.

			\param[in] coefficient The collision response coefficient (0 or greater).
			
			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.collisionResponseCoefficient getCollisionResponseCoefficient()
			*/
			 void setCollisionResponseCoefficient(NxReal coefficient);

			/**
			\brief Retrieves the collision response coefficient.

			\return The collision response coefficient.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.collisionResponseCoefficient setCollisionResponseCoefficient()
			*/
			 NxReal getCollisionResponseCoefficient() const;

			/**
			\brief Sets the attachment response coefficient

			\param[in] coefficient The attachment response coefficient in the range from 0 to 1.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.attachmentResponseCoefficient getAttachmentResponseCoefficient()
			*/
			 void setAttachmentResponseCoefficient(NxReal coefficient);

			/**
			\brief Retrieves the attachment response coefficient

			\return The attachment response coefficient.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.attachmentResponseCoefficient setAttachmentResponseCoefficient()
			*/
			 NxReal getAttachmentResponseCoefficient() const;

			/**
			\brief Sets the response coefficient for collisions from fluids to this cloth

			\param[in] coefficient The response coefficient 

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: No

			\see NxClothDesc.fromFluidResponseCoefficient getFromFluidResponseCoefficient()
			*/
			 void setFromFluidResponseCoefficient(NxReal coefficient);

			/**
			\brief Retrieves response coefficient for collisions from fluids to this cloth

			\return The response coefficient.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: No

			\see NxClothDesc.fromFluidResponseCoefficient setFromFluidResponseCoefficient()
			*/
			 NxReal getFromFluidResponseCoefficient() const;

			/**
			\brief Sets the response coefficient for collisions from this cloth to fluids

			\param[in] coefficient The response coefficient 

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: No

			\see NxClothDesc.toFluidResponseCoefficient getToFluidResponseCoefficient()
			*/
			 void setToFluidResponseCoefficient(NxReal coefficient);

			/**
			\brief Retrieves response coefficient for collisions from this cloth to fluids

			\return The response coefficient.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: No

			\see NxClothDesc.toFluidResponseCoefficient setToFluidResponseCoefficient()
			*/
			 NxReal getToFluidResponseCoefficient() const;

			/**
			\brief Sets an external acceleration which affects all non attached particles of the cloth

			\param[in] acceleration The acceleration vector (unit length / s^2)

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.externalAcceleration getExternalAcceleration()
			*/
			 void setExternalAcceleration(NxVec3 acceleration);

			/**
			\brief Retrieves the external acceleration which affects all non attached particles of the cloth

			\return The acceleration vector (unit length / s^2)

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.externalAcceleration setExternalAcceleration()
			*/
			 NxVec3 getExternalAcceleration() const;

			/**
			\brief Sets an acceleration acting normal to the cloth surface at each vertex.

			\param[in] acceleration The acceleration vector (unit length / s^2)

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.windAcceleration getWindAcceleration()
			*/
			 void setWindAcceleration(NxVec3 acceleration);

			/**
			\brief Retrieves the acceleration acting normal to the cloth surface at each vertex.

			\return The acceleration vector (unit length / s^2)

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.windAcceleration setWindAcceleration()
			*/
			 NxVec3 getWindAcceleration() const;

			/**
			\brief Returns true if this cloth is sleeping.

			When a cloth does not move for a period of time, it is no longer simulated in order to save time. This state
			is called sleeping. However, because the object automatically wakes up when it is either touched by an awake object,
			or one of its properties is changed by the user, the entire sleep mechanism should be transparent to the user.
			
			If a cloth is asleep after the call to NxScene::fetchResults() returns, it is guaranteed that the position of the cloth 
			vertices was not changed. You can use this information to avoid updating dependent objects.
			
			\return True if the cloth is sleeping.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see isSleeping() getSleepLinearVelocity() wakeUp() putToSleep()
			*/
			 bool isSleeping() const;

			/**
			\brief Returns the linear velocity below which a cloth may go to sleep.
			
			A cloth whose linear velocity is above this threshold will not be put to sleep.
		    
			\see isSleeping

			\return The threshold linear velocity for sleeping.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see isSleeping() getSleepLinearVelocity() wakeUp() putToSleep() setSleepLinearVelocity()
			*/
			 NxReal getSleepLinearVelocity() const;

			/**
			\brief Sets the linear velocity below which a cloth may go to sleep.
			
			A cloth whose linear velocity is above this threshold will not be put to sleep.
			
			If the threshold value is negative,	the velocity threshold is set using the NxPhysicsSDK's 
			NX_DEFAULT_SLEEP_LIN_VEL_SQUARED parameter.
		    
			\param[in] threshold Linear velocity below which a cloth may sleep. <b>Range:</b> (0,inf]

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see isSleeping() getSleepLinearVelocity() wakeUp() putToSleep()
			*/
			 void setSleepLinearVelocity(NxReal threshold);

			/**
			\brief Wakes up the cloth if it is sleeping.  

			The wakeCounterValue determines how long until the cloth is put to sleep, a value of zero means 
			that the cloth is sleeping. wakeUp(0) is equivalent to NxCloth::putToSleep().

			\param[in] wakeCounterValue New sleep counter value. <b>Range:</b> [0,inf]
			
			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see isSleeping() getSleepLinearVelocity() putToSleep()
			*/
			 void wakeUp(NxReal wakeCounterValue = NX_SLEEP_INTERVAL);

			/**
			\brief Forces the cloth to sleep. 
			
			The cloth will fall asleep.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see isSleeping() getSleepLinearVelocity() wakeUp()
			*/
			 void putToSleep();

			/**
			\brief Sets the flags, a combination of the bits defined by the enum ::NxClothFlag.

			\param[in] flags #NxClothFlag combination.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.flags NxClothFlag getFlags()
			*/
			 void setFlags(NxU32 flags);

			/**
			\brief Retrieves the flags.

			\return The cloth flags.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxClothDesc.flags NxClothFlag setFlags()
			*/
			 NxU32 getFlags() const;

			/**
			\brief Sets a name string for the object that can be retrieved with getName().
			
			This is for debugging and is not used by the SDK. The string is not copied by 
			the SDK, only the pointer is stored.

			\param[in] name String to set the objects name to.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see getName()
			*/
			 void setName(const char* name);

			/**
			\brief Applies a force (or impulse) defined in the global coordinate frame, to a particular 
			vertex of the cloth. 

			Because forces are reset at the end of every timestep, 
			you can maintain a total external force on an object by calling this once every frame.

			::NxForceMode determines if the force is to be conventional or impulsive.

			\param[in] force Force/impulse to add, defined in the global frame. <b>Range:</b> force vector
			\param[in] vertexId Number of the vertex to add the force at. <b>Range:</b> position vector
			\param[in] mode The mode to use when applying the force/impulse 
			(see #NxForceMode, supported modes are NX_FORCE, NX_IMPULSE, NX_ACCELERATION, NX_VELOCITY_CHANGE)

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxForceMode 
			*/
				void addForceAtVertex(const NxVec3& force, NxU32 vertexId, NxForceMode mode = NX_FORCE);

			/**
			\brief Applies a radial force (or impulse) at a particular position. All vertices
			within radius will be affected with a quadratic drop-off. 

			Because forces are reset at the end of every timestep, 
			you can maintain a total external force on an object by calling this once every frame.

			::NxForceMode determines if the force is to be conventional or impulsive.

			\param[in] position Position to apply force at.
			\param[in] magnitude Magnitude of the force/impulse to apply.
			\param[in] radius The sphere radius in which particles will be affected. <b>Range:</b> position vector
			\param[in] mode The mode to use when applying the force/impulse 
			(see #NxForceMode, supported modes are NX_FORCE, NX_IMPULSE, NX_ACCELERATION, NX_VELOCITY_CHANGE).

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxForceMode 
			*/
				void addForceAtPos(const NxVec3& position, NxReal magnitude, NxReal radius, NxForceMode mode = NX_FORCE);

			/**
			\brief Applies a directed force (or impulse) at a particular position. All vertices
			within radius will be affected with a quadratic drop-off. 

			Because forces are reset at the end of every timestep, 
			you can maintain a total external force on an object by calling this once every frame.

			::NxForceMode determines if the force is to be conventional or impulsive.

			\param[in] position Position to apply force at.
			\param[in] force Force to apply.
			\param[in] radius The sphere radius in which particles will be affected. <b>Range:</b> position vector
			\param[in] mode The mode to use when applying the force/impulse 
			(see #NxForceMode, supported modes are NX_FORCE, NX_IMPULSE, NX_ACCELERATION, NX_VELOCITY_CHANGE).

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxForceMode 
			*/
				void addDirectedForceAtPos(const NxVec3& position, const NxVec3& force, NxReal radius, NxForceMode mode = NX_FORCE);

			/**
			\brief Finds triangles touching the input bounds.

			\warning This method returns a pointer to an internal structure using the indices member. Hence the
			user should use or copy the indices before calling any other API function.

			\param[in] bounds Bounds to test against in world space. <b>Range:</b> See #NxBounds3
			\param[out] nb Retrieves the number of triangle indices touching the AABB.
			\param[out] indices Returns an array of touching triangle indices. 
			The triangle indices correspond to the triangles referenced to by NxClothDesc.meshdata (#NxMeshData).
			Triangle i has the vertices 3i, 3i+1 and 3i+2 in the array NxMeshData.indicesBegin.
			\return True if there is an overlap.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : No
			\li XB360: Yes

			\see NxBounds3 NxClothDesc NxMeshData
			*/
				bool overlapAABBTriangles(const NxBounds3& bounds, NxU32& nb, const NxU32*& indices) const;

			/**
			\brief Retrieves the scene which this cloth belongs to.

			\return Owner Scene.

			<b>Platform:</b>
			\li PC SW: Yes
			\li PPU  : Yes
			\li PS3  : Yes
			\li XB360: Yes

			\see NxScene
			*/
			 NxScene& getScene() const;


		protected:

			NxString				mName;
			Scene*					mOwner;
			NxCloth*				mCloth;
			NxClothMesh*			mClothMesh;

		private:

	};

	//////////////////////////////////////////////////////////////////

};// End of namespace

#endif 

//#endif
#endif
