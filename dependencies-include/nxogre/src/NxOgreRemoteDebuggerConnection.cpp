/** \file    NxOgreRemoteDebuggerConnection.cpp
 *  \see     NxOgreRemodeDebuggerConnection.h
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
#include "NxOgreRemoteDebuggerConnection.h"

#ifndef NX_SMALL

#include "NxOgrePhysXDriver.h"
#include "NxOgreHelpers.h"
#include "NxOgreContainer.h"

#include "OgreCamera.h"

namespace NxOgre {
	
////////////////////////////////////////////////////////////

RemoteDebuggerConnection::RemoteDebuggerConnection(const NxString& address, unsigned int port, PhysXDriver* driver) {
	
	mNextID = 0x00100000;
	mDriver = driver;
	mDebugger = mDriver->getSDK()->getFoundationSDK().getRemoteDebugger();
	mDebugger->connect(address.c_str(), port);

	std::stringstream ss;
	if (mDebugger->isConnected()) {
		NxDebug("Remote Debugger Connected");
	} else {
		NxThrow("Remote Debugger Connection failed!");
	}

}

////////////////////////////////////////////////////////////

RemoteDebuggerConnection::~RemoteDebuggerConnection() {
	mDebugger->disconnect();
	if (!mDebugger->isConnected()) {
		NxDebug("Remote Debugger disconnected.");
	}
}

////////////////////////////////////////////////////////////

void RemoteDebuggerConnection::simulate(NxReal) {
	if (!mDebugger->isConnected()) {
		return;
		//NxThrow_Warning("Remote Debugger disconnected.");
	}

	for(List<Camera>::Iterator i = mCameras.items.begin();i != mCameras.items.end();++i) {
//			(*i).
			//(*i)->setMotorTorque(torque);
//			NX_DBG_CREATE_PARAMETER(mCameraPos, this, "Origin", mCameraID);
//			NX_DBG_CREATE_PARAMETER(mCameraTarget, this, "Target", mCameraID);
		
			NxVec3 origin = NxConvert<NxVec3, Ogre::Vector3>((*i).mCamera->getPosition());
			NxVec3 target = NxConvert<NxVec3, Ogre::Vector3>((*i).mCamera->getRealDirection() * 10);

			NX_DBG_SET_PARAMETER(origin, this, "Origin", (*i).mID);
			NX_DBG_SET_PARAMETER(target, this, "Target", (*i).mID);

	}

	//NX_DBG_CREATE_PARAMETER(mCameraPos, this, "Origin", mCameraID);
	//NX_DBG_CREATE_PARAMETER(mCameraTarget, this, "Target", mCameraID);
}

////////////////////////////////////////////////////////////

void RemoteDebuggerConnection::addCamera(Ogre::Camera* cam) {
// NX_DBG_OBJECTTYPE_CAMERA

	Camera c;
	c.mID = mNextID++;
	c.mCamera = cam;

	mCameras.insert(c);

	//"Origin" (NxVec3, required)  The origin of the camera. 
	//"Target" (NxVec3, required)  The target point of the camera, i.e. a point the camera will look at 
	//"Up" (NxVec3, optional)  The up vector of the camera, i.e. a direction the camera will try to align its y-axis with. 
	
	NX_DBG_CREATE_OBJECT(this, NX_DBG_OBJECTTYPE_CAMERA, cam->getName().c_str(), c.mID);
	
	NxVec3 mCameraPos = NxConvert<NxVec3, Ogre::Vector3>(cam->getPosition());
	NxVec3 mCameraTarget = NxConvert<NxVec3, Ogre::Vector3>(cam->getRealDirection());

	NX_DBG_CREATE_PARAMETER(mCameraPos, this, "Origin", c.mID);
	NX_DBG_CREATE_PARAMETER(mCameraTarget, this, "Target", c.mID);

}

////////////////////////////////////////////////////////////

}
#endif
