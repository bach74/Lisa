/** \file    NxOgreMaterial.cpp
 *  \see     NxOgreMaterial.h
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
#include "NxOgreMaterial.h"
#include "NxOgreScene.h"			// For: CreateMaterial in NxScene
#include "NxOgreHelpers.h"			// For: Ogre::Vector3 to NxVec3 conversion.
#include "NxOgreResource.h"

namespace NxOgre {

//////////////////////////////////////////////////////////////////////

Material::Material(const NxString& identifier, Scene* scene) : mName(identifier), mScene(scene) {
	NxMaterialDesc d;
	d.setToDefault();
	mMaterial = scene->getNxScene()->createMaterial(d);
	mMaterialIndex = mMaterial->getMaterialIndex();
	scene->_registerMaterial(identifier, this);
}

//////////////////////////////////////////////////////////////////////


Material::Material(NxMaterialIndex index, const NxString& identifier, Scene* scene) : mName(identifier), mScene(scene) {
	mMaterialIndex = index;
	mMaterial = mScene->getNxScene()->getMaterialFromIndex(index);
	scene->_registerMaterial(identifier, this);
}

//////////////////////////////////////////////////////////////////////

Material::~Material() {
	if (mMaterialIndex == 0)
		return;

	mScene->getNxScene()->releaseMaterial(*mMaterial);
	mScene->_unregisterMaterial(mName);
}

//////////////////////////////////////////////////////////////////////

NxMaterialIndex	Material::getMaterialIndex() {
	return mMaterialIndex;
}

//////////////////////////////////////////////////////////////////////

void Material::setAll(NxReal bounce, NxReal dFriction, NxReal sFriction) {
	mMaterial->setRestitution(bounce);
	mMaterial->setDynamicFriction(dFriction);
	mMaterial->setStaticFriction(sFriction);
}

//////////////////////////////////////////////////////////////////////

void Material::setDynamicFriction(NxReal coef) {
	mMaterial->setDynamicFriction(coef);
}

//////////////////////////////////////////////////////////////////////

NxReal Material::getDynamicFriction() const {
	return mMaterial->getDynamicFriction();
}

//////////////////////////////////////////////////////////////////////

void Material::setStaticFriction(NxReal coef) {
	mMaterial->setStaticFriction(coef);
}

//////////////////////////////////////////////////////////////////////

NxReal Material::getStaticFriction() const {
	return mMaterial->getStaticFriction();
}

//////////////////////////////////////////////////////////////////////

void Material::setRestitution(NxReal rest) {
	mMaterial->setRestitution(rest);
}

//////////////////////////////////////////////////////////////////////

NxReal Material::getRestitution() const {
	return mMaterial->getRestitution();
}

//////////////////////////////////////////////////////////////////////

void Material::setDynamicFrictionV(NxReal coef) {
	mMaterial->setDynamicFrictionV(coef);
}

//////////////////////////////////////////////////////////////////////

NxReal Material::getDynamicFrictionV() const {
	return mMaterial->getDynamicFrictionV();
}

//////////////////////////////////////////////////////////////////////

void Material::setStaticFrictionV(NxReal coef) {
	mMaterial->setStaticFrictionV(coef);
}

//////////////////////////////////////////////////////////////////////

NxReal Material::getStaticFrictionV() const {
	return mMaterial->getStaticFrictionV();
}

//////////////////////////////////////////////////////////////////////

void Material::setDirOfAnisotropy(const Ogre::Vector3 &vec) {
	mMaterial->setDirOfAnisotropy(NxConvert<NxVec3, Ogre::Vector3>(vec));
}

//////////////////////////////////////////////////////////////////////

NxVec3 Material::getDirOfAnisotropy() const {
	return mMaterial->getDirOfAnisotropy();
}

//////////////////////////////////////////////////////////////////////

void Material::setFlags(NxU32 flags) {
	mMaterial->setFlags(flags);
}

//////////////////////////////////////////////////////////////////////

NxU32 Material::getFlags() const {
	return mMaterial->getFlags();
}

//////////////////////////////////////////////////////////////////////

void Material::setFrictionCombineMode(NxCombineMode combMode) {
	mMaterial->setFrictionCombineMode(combMode);
}

//////////////////////////////////////////////////////////////////////

NxCombineMode Material::getFrictionCombineMode() const {
	return mMaterial->getFrictionCombineMode();
}

//////////////////////////////////////////////////////////////////////

void Material::setRestitutionCombineMode(NxCombineMode combMode) {
	mMaterial->setRestitution(combMode);
}

//////////////////////////////////////////////////////////////////////

NxCombineMode Material::getRestitutionCombineMode() {
	return mMaterial->getRestitutionCombineMode();
}

#if 0

//////////////////////////////////////////////////////////////////////

MaterialAlias::MaterialAlias(ResourceStreamPtr rs, bool deleteResourceStream) {
	load(rs, deleteResourceStream);
}

//////////////////////////////////////////////////////////////////////

MaterialAlias::MaterialAlias() {

}

//////////////////////////////////////////////////////////////////////
				
void MaterialAlias::add(NxMaterialIndex index, const NxString& identifier) {
	mAliases[identifier] = index;
}

//////////////////////////////////////////////////////////////////////

void MaterialAlias::remove(const NxString& identifier) {
	mAliases.erase(identifier);
}

//////////////////////////////////////////////////////////////////////

void MaterialAlias::dumpToConsole() {
	for (std::map<NxString, NxMaterialIndex>::iterator it = mAliases.begin(); it != mAliases.end();++it) {
		std::cout << (*it).second << " => " << (*it).first << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////

void MaterialAlias::load(ResourceStreamPtr rs, bool deleteResourceStream) {

	rs->seek(0);

	NxString headerCheck = rs->getString();

	if (headerCheck != "NXM") {
		NxThrow("Not a Material Alias file");
		rs->close();
		return;
	}
	
	NxU32 nbAliases = rs->getUInt();

	for (NxU32 i=0;i < nbAliases;i++) {
		NxMaterialIndex index = rs->getUInt();
		std::string identifier = rs->getString();
		add(index, identifier);
	}

	rs->close();

}

//////////////////////////////////////////////////////////////////////

void MaterialAlias::save(ResourceStreamPtr rs, bool deleteResourceStream) {
	
	rs->writeString("NXM");

	NxU32 nbAliases = mAliases.size();
	rs->writeUInt(mAliases.size());

	for (std::map<NxString, NxMaterialIndex>::iterator it = mAliases.begin(); it != mAliases.end();++it) {
		rs->writeUInt((*it).second);
		rs->writeString((*it).first);
	}

	rs->close();

}

//////////////////////////////////////////////////////////////////////

NxMaterialIndex MaterialAlias::get(const NxString& identifier) {

	std::map<NxString, NxMaterialIndex>::iterator it = mAliases.find(identifier);
	if (it == mAliases.end())
		return 0;

	return (*it).second;
}

//////////////////////////////////////////////////////////////////////

#endif

}; //End of NxOgre namespace.
