/** \file    NxOgreCloth.cpp
 *  \see     NxOgreCloth.h
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
#include "NxOgreCloth.h"

#if 0

#include "NxOgreScene.h"				// For Cloth::mOwner
///#include "NxOgreDynamicMesh.h"			// For Dynamic Cloth Mesh
#include "NxOgreResourceManager.h"		// For Dynamic Cloth fetching

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////////////////

void ClothParams::setToDefault() {
	

}

////////////////////////////////////////////////////////////////////////////////////////////////

void ClothParams::parse(Parameters params) {

	setToDefault();

	for (Parameter* parameter = params.Begin(); parameter = params.Next();) {

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

Cloth::Cloth(const NxString& identifier, const NxString& clothMeshIdentifier, Scene* owner, const Pose& pose, ClothParams params) 
: mOwner(owner), mName(identifier), mCloth(0)
{

	DynamicClothMesh* mesh = ResourceManager::getSingleton()->getDynamicClothMesh(clothMeshIdentifier);

	if (mesh == 0) {
		NxThrow(NxString("Cloth mesh '" + clothMeshIdentifier + "' could not be found with usage of the cloth '" + identifier + "'").c_str());
		return;
	}

	createCloth(mesh->getMeshPtr(), params, pose);

}

////////////////////////////////////////////////////////////////////////////////////////////////

Cloth::Cloth(const NxString& identifier, Scene* owner)
: mOwner(owner), mName(identifier), mCloth(0)
{
	// Nothing goes in here.
}

////////////////////////////////////////////////////////////////////////////////////////////////

Cloth::~Cloth() {
	destroyCloth();
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Cloth::createCloth(NxClothMesh* mesh, ClothParams params, Pose pose) {

	if (mesh == 0) {
		NxThrow(NxString("Cloth mesh could not be used with usage of the cloth '" + mName + "'").c_str());
		return;
	}

	mClothMesh = mesh;

	NxClothDesc description;
	description.setToDefault();
	description.clothMesh = mClothMesh;
	description.globalPose = pose;

	// etc.

	if (!description.isValid()) {
		
		std::stringstream ss;
		ss << "Cloth description is invalid. Reason(s) are:" << std::endl;

		if(!description.clothMesh)
			ss << "+ Cloth mesh pointer is null" << std::endl;
		
		if(!description.globalPose.isFinite())
			ss << "+ Global pose is infinite" << std::endl;
		
		if(description.thickness < 0.0f)
			ss << "+ Has negative thickness" << std::endl;
		
		if(description.density <= 0.0f)
			ss << "+ Has negative density" << std::endl;
		
		if(description.bendingStiffness < 0.0f || description.bendingStiffness > 1.0f)
			ss << "+ Bending stiffness is out of range (0..1)" << std::endl;

		if(description.stretchingStiffness <= 0.0f || description.stretchingStiffness > 1.0f)
			ss << "+ Stretching stiffness is out of range (0..1)" << std::endl;

		if(description.pressure < 0.0f)
			ss << "+ Has negative pressure" << std::endl;
		
		if(description.tearFactor <= 1.0f)
			ss << "+ Tear factor is less or equal to 1" << std::endl;
		
		if(description.attachmentTearFactor <= 1.0f)
			ss << "+ Attachment tear factor is less or equal to 1" << std::endl;
		
		if(description.solverIterations < 1)
			ss << "+ Number of solver iterations is less than 1" << std::endl;

		if(description.friction < 0.0f || description.friction > 1.0f)
			ss << "+ Friction is out of range" << std::endl;

		if(!description.meshData.isValid())
			ss << "+ Mesh data is invalid" << std::endl;
		
		if(description.dampingCoefficient < 0.0f || description.dampingCoefficient > 1.0f)
			ss << "+ Damping coefficient is out of range (0..1)" << std::endl;

		if(description.collisionResponseCoefficient < 0.0f)
			ss << "+ Collision response coefficient is less than 0" << std::endl;
		
		if(description.wakeUpCounter < 0.0f)
			ss << "+ WakeUp counter is less than 0" << std::endl;

		if(description.attachmentResponseCoefficient < 0.0f)
			ss << "+ Attachment response coefficient is less than 0" << std::endl;

		if(description.toFluidResponseCoefficient < 0.0f)
			ss << "+ To fluid response coefficient is less than 0" << std::endl;
		
		if(description.fromFluidResponseCoefficient < 0.0f)
			ss << "+ From fluid response coefficient is less than 0" << std::endl;
		
		if(description.relativeGridSpacing < 0.01f)
			ss << "+ Relative grid spacing is less than 0.01" << std::endl;
		
		if(description.collisionGroup >= 32)
			ss << "+ Collision group number is more or equal to 32" << std::endl; // We only support 32 different collision groups
		
		if(description.compartment && (!(description.flags & NX_CLF_HARDWARE)))
			ss << "+ Software cloth cannot be used in compartments" << std::endl; //only hw cloth can go in compartments

		NxThrow(ss.str().c_str());
		
	}	

	mCloth = mOwner->getNxScene()->createCloth(description);

	if (mCloth == 0) {
		NxThrow(NxString("Cloth '" + mName + "' was NOT created.").c_str());
		return;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////

void Cloth::destroyCloth() {
	// Code goes here.
}

////////////////////////////////////////////////////////////////////////////////////////////////

} //End of NxOgre namespace.

////#endif

#endif