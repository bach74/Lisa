/** \file    NxOgreMaterial.h
 *  \brief   Header for the Material and MaterialAlias classes.
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

#ifndef __NXOGRE_MATERIAL_H__
#define __NXOGRE_MATERIAL_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	class NxPublicClass Material {

		public:

			/** \brief Material Constructor
			    Creates a material for a shape, and automatically assign a NxMaterialIndex to it.

			Containers and Garbage Collection
				Materials are used in containers. Creating a Material through the Scene factory method makes the Material "owned"
				by NxOgre, on deletion of the Material it will remove the presence of theMaterial and delete the pointer.
				Manually creating the Material "new Material()" will only add a presence, it is up to you to delete it at the
				correct time.

			\param	Identifier		Unique identifier of the Material
			\param Material*		Scene pointer which would contain the Material.

			\see Scene::createMaterial
			*/
			Material(const NxString& identifier, Scene*);


			/** \brief Material Constructor
			     Creates a material for a shape, with a specific NxMaterialIndex

			Containers and Garbage Collection
				Materials are used in containers. Creating a Material through the Scene factory method makes the Material "owned"
				by NxOgre, on deletion of the Material it will remove the presence of theMaterial and delete the pointer.
				Manually creating the Material "new Material()" will only add a presence, it is up to you to delete it at the
				correct time.

			\param	NxMaterialIndex			MaterialIndex to use.
			\param	Identifier				Unique identifier of the Material
			\param Material*				Scene pointer which would contain the Material.

			\see Scene::createMaterial
			*/
			Material(NxMaterialIndex, const NxString&, Scene*);

			/** Material Destructor
				 Removes the material class from the Scene. (See Note)

			    Containers and Garbage Collection
					Materials are used in containers. Creating a Material through the Scene factory method makes the Material "owned"
					by NxOgre, on deletion of the Material it will remove the presence of theMaterial and delete the pointer.
					Manually creating the Material "new Material()" will only add a presence, it is up to you to delete it at the
					correct time.
			
				\note Although the material class will be destroyed, the presence of the material index
				      will remain in the Scene, as any shapes assigned to the material index will not be
					  changed to another. This index may be recycled later, and may cause unexpected
					  effects to shapes using the old index.
			*/
			~Material();


			/** getMaterialIndex
				 Returns the NxMaterialIndex assigned to this Material.

				 \return The material index
			*/
			NxMaterialIndex	getMaterialIndex();
	

			/** getName
				 Returns the NxOgre identifier of this material
			*/
			NxString		getName() const							{
																		return mName;
																	}


			/** getScene
				 Returns the Scene that this material belongs to.
				 \return Return the Scene used.
			*/
			Scene*			getScene()								{
																		return mScene;
																	}

			/** setAll
				Set Restitution, Dynamic Friction and Static Friction at once.
				\param bounce Resitution of the material (0..1)
				\param dFriction Dynamic Friction of the material (0..inf)
				\param sFriction Static Friction of the material (0..inf)

				\see Material::setDynamicFriction
				\see Material::getDynamicFriction
				\see Material::setStaticFriction
				\see Material::getStaticFriction
				\see Material::setRestitution
				\see Material::getRestitution
			*/
			void			setAll(NxReal bounce, NxReal dFriction, NxReal sFriction);


			/** setDynamicFriction
				Set's the dynamic friction of the material
				\param coef Dynamic Friction to set (0..inf)
			*/
			void			setDynamicFriction(NxReal coef);
			

			/** setDynamicFriction
				Set's the dynamic friction of the material
				\param coef Dynamic Friction to set (0..inf)
			*/
			NxReal			getDynamicFriction() const;
			

			/** setStaticFriction
				Set's the dynamic friction of the material
				\param coef Dynamic Friction to set (0..inf)
			*/
			void			setStaticFriction(NxReal coef);



			/** getStaticFriction
				Returns the dynamic friction of the material
			*/
			NxReal			getStaticFriction() const;


			/** setRestitution
				Set's the Restitution (bounce) of the material
				\param rest The restitution (0..inf)
			*/
			void			setRestitution(NxReal rest);

			/** getRestitution
				Gets the Restitution (bounce) of the material
			*/
			NxReal			getRestitution() const;


			/** setDynamicFrictionV
				Sets the dynamic friction along the secondary (V) axis, used when anistropic
				friction is assigned to the material.

				\param coef Amount of Dynamic Friction to apply (0..1)
			*/
			void			setDynamicFrictionV(NxReal coef);


			/** getDynamicFrictionV
				Gets the dynamic friction along the secondary (V) axis

				\see Material::setDynamicFrictionV
			*/
			NxReal			getDynamicFrictionV() const;


			/** setStaticFrictionV
				Sets the static friction along the secondary (V) axis, used when anistropic
				friction is assigned to the material.

				\param coef Amount of static friction to apply (0..1)
			*/
			void			setStaticFrictionV(NxReal coef);


			/** getStaticFrictionV
				Gets the static friction along the secondary (V) axis

				\see Material::setStaticFrictionV
			*/
			NxReal			getStaticFrictionV() const;


			/** setDirOfAnisotropy
				Sets the shape space direction (unit vector) of anisotropy. Only applies
				when the material is anisotrophic.

				\see Material::setDirOfAnisotropy
			*/
			void			setDirOfAnisotropy(const Ogre::Vector3 &vec);
			

			/** setDirOfAnisotropy
				Sets the shape space direction (unit vector) of anisotropy. Only applies
				when the material is anisotrophic.

				\see Material::setDirOfAnisotropy
			*/			
			void			setDirOfAnisotropy(const NxVec3& vec);



			/** getDirOfAnisotropy
				Returns the vector of anistrophy of the material.

				\see Material::getDirOfAnisotropy
			*/
			NxVec3			getDirOfAnisotropy() const;

			/** setFlags
				Sets flags of the material
				
				\see NxMaterialFlag
				\param Flag to apply
			*/
			void			setFlags(NxU32 flags);

			/** getFlags
				Gets flags of the material

				\see NxMaterialFlag
			*/
			NxU32			getFlags() const;
			

			void			setFrictionCombineMode(NxCombineMode combMode);
			NxCombineMode	getFrictionCombineMode() const;
			void			setRestitutionCombineMode(NxCombineMode combMode) ;
			NxCombineMode	getRestitutionCombineMode();

		protected:

			NxMaterial*		mMaterial;
			NxMaterialIndex mMaterialIndex;
			NxString		mName;
			Scene*			mScene;


	};

	/*
			NXM Schema

			-begin
				write "N"
				write "X"
				write "M"
				write null
				write size of aliases
				write null
				- for alias_name, alias_index as material alias
					write alias_index
					write alias_name
					write null
				- endfor
			- end

			Example:
			N:X:M:<null>:3:<null>0:D:e:f:a:u:l:t:<Null>:1:S:to:n:e:<Null>

	*/

#if 0
	/** \brief A list of MaterialIndexes matched to a string identifier.

		A material alias is a way to handle saved meshes with material indexes per face. As it is likely
		that materials will vary from application to appliaction, particually the material indexes. By
		saving a list of indexes with the string identifier, the mesh loaded can change the faces material
		index of the to the material used in the scene with the same identifier in the material alias.

		In short it makes things happy.

	*/
	class NxPublicClass MaterialAlias {

		public:

				MaterialAlias();
				MaterialAlias(ResourceStreamPtr, bool deleteResourceStream = true);
				
				void add(NxMaterialIndex, const NxString&);
				void remove(const NxString&);

				void load(ResourceStreamPtr, bool deleteResourceStream = true);
				void save(ResourceStreamPtr, bool deleteResourceStream = true);
				NxMaterialIndex get(const NxString&);
				void dumpToConsole();

				MaterialConversionList	generateConversionList();

				std::map<NxString, NxMaterialIndex>* getAll()			{
																			return &mAliases;
																		}

		protected:

			std::map<NxString, NxMaterialIndex> mAliases;

	};
#endif

};

#endif
