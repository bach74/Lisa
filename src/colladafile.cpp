// =============================================================================
//  colladafile.cpp   version:  1.0
//
//   Collada physics Importer/Exporter for nxOgre. Based on
//   Scene Export: This program shows how to export and import a scene to
//   and from a special file format (Collada, Ageia binary, ....)
//
//   Written by Stephen Hatcher, based on work by Pierre Terdiman (01.01.04)
//   and others. Edited by Bob Schade, 9-15-06.
//
//
//  Copyright (C) 2006 by Bach - All Rights Reserved
//
// ===============================================================================

#include "stdafx.h"
#include "ColladaFile.h"


/**----------------------------------------------------------------------------
    create error message

    \param isError (bool)
    \param str (const char *)
    \return (void)
 -----------------------------------------------------------------------------*/
void NxuOgre::NXU_errorMessage(bool isError, const char *str)
{
	if (isError)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(std::string("NxuStream ERROR: "+std::string(str)+"\r\n"));
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(std::string("NxuStream WARNING: "+std::string(str)+"\r\n"));
	}
}

/**----------------------------------------------------------------------------
    event called before actors are created

    \param actor (NxActorDesc &)
    \param userProperties (const char *)
    \return (bool)
 -----------------------------------------------------------------------------*/
bool NxuOgre::NXU_preNotifyActor(NxActorDesc &actor, const char *userProperties)
{
	for (NxU32 i=0; i<actor.shapes.size(); i++)
	{
		NxShapeDesc *s = actor.shapes[i];
		s->shapeFlags|=NX_SF_VISUALIZATION; // make sure the shape visualization flags are on so we can see things!
	}

	return true;
};


/**----------------------------------------------------------------------------
    Calls the importer to load the state of the currently selected scene from a file

    \param pFilename (const char *)
    \param type (NXU::NXU_FileType)
    \return (bool)
 -----------------------------------------------------------------------------*/
bool NxuOgre::LoadScene(NxOgre::World* world, const char *pFilename, NXU::NXU_FileType type)
{
	bool success=false;

	try
	{
		if (mPhysicsSDK)
		{

			NXU::NxuPhysicsCollection *c = NXU::loadCollection(pFilename, type);

			if (c)
			{
				/*  if (mScene) {
				        // Release old scene
				        m_PhysicsSDK->releaseScene(*mScene);
				        mScene=NULL;
				    }*/

				// different axis 3D studio and OGRE (swapped y & z)
				NxMat34 instanceFrame;
				//instanceFrame.M.rotX(-90);
				instanceFrame.t=NxVec3(0,16,0);
				success = NXU::instantiateCollection(world, c, *mPhysicsSDK, mScene, &instanceFrame, this);

				NXU::releaseCollection(c);
			}
			else {}
		}

		if (success)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage(std::string("Scene loaded from file "+std::string(pFilename)+"\n"));
		}
	}
	catch (Exception ex) {
		MessageBox(NULL,ex.getDescription(),"Error loading scene",MB_ICONERROR);
	}
	catch (Ogre::Exception ex)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(ex.getDescription()+"\n");
		MessageBox(NULL,ex.getFullDescription().c_str(),"Error loading scene",MB_ICONERROR);
	}
	return success;
}

/**----------------------------------------------------------------------------
    Calls the exporter to save out the state of the currently selected scene to a file

    \param SaveFilename (const char *)
    \param type (NXU::NXU_FileType)
    \param bDefaults (bool)
    \return (void)
 -----------------------------------------------------------------------------*/
void NxuOgre::SaveScene(const char* SaveFilename, NXU::NXU_FileType type, bool bDefaults)
{

	NXU::NxuPhysicsCollection *cltn=NXU::extractCollectionScene(mScene);

	if (cltn)
	{

		switch (type)
		{
			case NXU::FT_XML:
				Ogre::LogManager::getSingletonPtr()->logMessage(std::string("Saving NxuStream XML file to "+std::string(SaveFilename)+"\n"));
				NXU::saveCollection(cltn, SaveFilename, NXU::FT_XML, false, false);
				break;
			case NXU::FT_BINARY:
				Ogre::LogManager::getSingletonPtr()->logMessage(std::string("Saving NxuStream BINARY file (.nxb) to "+std::string(SaveFilename)+"\n"));
				NXU::saveCollection(cltn, SaveFilename, NXU::FT_BINARY, true, true);
				break;
			case NXU::FT_COLLADA:
				Ogre::LogManager::getSingletonPtr()->logMessage(std::string("Saving COLLADA Physics 1.4.1 file (.dae) to "+std::string(SaveFilename)+"\n"));
				NXU::saveCollection(cltn, SaveFilename, NXU::FT_COLLADA, bDefaults, false);
				break;
		}

		NXU::releaseCollection(cltn);
	}
}