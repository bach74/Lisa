/** \file    NxOgreMachine.cpp
 *  \see     NxOgreMachine.h
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
#include "NxOgreMachine.h"
#include "NxOgreScene.h"

namespace NxOgre {

/////////////////////////////////////

Machine::Machine() : mScene(0), mMachineID(0) {}

/////////////////////////////////////

Machine::Machine(Scene* scene) : mScene(0), mMachineID(0) {
	registerMachine(scene);
}

/////////////////////////////////////

void Machine::registerMachine(Scene* s) {
	mScene = s;
	mScene->registerMachine(this);
}

/////////////////////////////////////

void Machine::unregisterMachine() {
	mScene->unregisterMachine(this);
}

/////////////////////////////////////

Machine::~Machine() {
	if (mScene)
		unregisterMachine();
}

/////////////////////////////////////

NxMachineID Machine::getMachineID() {
	return mMachineID;
}

/////////////////////////////////////

NxString Machine::getIdentifierType() {
	return "NxOgre-Machine";
}

/////////////////////////////////////

NxShortHashIdentifier Machine::getIdentifierTypeHash() const {
	return 22170;
}

/////////////////////////////////////

};  //End of NxOgre namespace.
