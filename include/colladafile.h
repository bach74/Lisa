// =============================================================================
//  colladafile.h   version:  1.0
//	Collada physics Importer/Exporter for nxOgre. Based on
//	a serialization sample for the PhysX Physics SDK showing explicit export
//	and import of a scene by Stephen Hatcher, based on work by Pierre Terdiman
//	(01.01.04) and others
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#ifndef __COLLADAFILE_H__
#define __COLLADAFILE_H__

class NxuOgre : public NXU_userNotify, public NXU_errorReport
{
	public:

		NxuOgre(NxPhysicsSDK* physxSDK, NxScene* scene): mPhysicsSDK(physxSDK), mScene(scene) {};

		bool LoadScene(NxOgre::World* world, const char *pFilename, NXU::NXU_FileType type=NXU::FT_COLLADA);
		void SaveScene(const char *SaveFilename, NXU::NXU_FileType type=NXU::FT_COLLADA, bool bDefaults=false);

	private:

		NxPhysicsSDK	*mPhysicsSDK;
		NxScene			*mScene;

		virtual void NXU_errorMessage(bool isError, const char *str);

		virtual NxScene *NXU_preNotifyScene(unsigned int sno, NxSceneDesc &scene, const char *userProperties) {	return 0; }
		virtual bool NXU_preNotifyJoint(NxJointDesc &joint, const char *userProperties)			{ return true; }
		virtual bool NXU_preNotifyActor(NxActorDesc &actor, const char *userProperties);
		virtual bool NXU_preNotifyCloth(NxClothDesc &cloth, const char *userProperties)			{ return true; }
		virtual bool NXU_preNotifyTriangleMesh(NxTriangleMeshDesc &t,const char *userProperties){ return true; }
		virtual bool NXU_preNotifyConvexMesh(NxConvexMeshDesc &t,const char *userProperties)	{ return true; }
		virtual bool NXU_preNotifyClothMesh(NxClothMeshDesc &t,const char *userProperties)		{ return true; }
		virtual bool NXU_preNotifyCCDSkeleton(NxSimpleTriangleMesh &t,const char *userProperties){ return true; }
		virtual bool NXU_preNotifyHeightField(NxHeightFieldDesc &t,const char *userProperties)	{ return true; }
		virtual bool NXU_preNotifySceneInstance(const char *name,const char *sceneName,const char *userProperties,NxMat34 &rootNode,NxU32 depth) { return true; }

		virtual void NXU_notifyScene(NxU32 sno, NxScene *scene, const char *userProperties) {};
		virtual void NXU_notifyJoint(NxJoint *joint, const char *userProperties) {};
		virtual void NXU_notifyActor(NxActor *actor, const char *userProperties) {};
		virtual void NXU_notifyCloth(NxCloth *cloth, const char *userProperties) {};
		virtual void NXU_notifyFluid(NxFluid *fluid, const char *userProperties) {};
		virtual void NXU_notifyTriangleMesh(NxTriangleMesh *t, const char *userProperties){};
		virtual void NXU_notifyConvexMesh(NxConvexMesh *c, const char *userProperties) {};
		virtual void NXU_notifyClothMesh(NxClothMesh *t, const char *userProperties) {};
		virtual void NXU_notifyCCDSkeleton(NxCCDSkeleton *t, const char *userProperties) {};
		virtual void NXU_notifyHeightField(NxHeightField *t,const char *userProperties) {};

		virtual void NXU_notifySceneFailed(unsigned int sno, NxSceneDesc &scene, const char *userProperties) {};
		virtual void NXU_notifyJointFailed(NxJointDesc &joint, const char *userProperties) {};
		virtual void NXU_notifyActorFailed(NxActorDesc &actor, const char *userProperties) {};
		virtual void NXU_notifyClothFailed(NxClothDesc &cloth, const char *userProperties) {};
		virtual void NXU_notifyTriangleMeshFailed(NxTriangleMeshDesc &t,const char *userProperties) {};
		virtual void NXU_notifyConvexMeshFailed(NxConvexMeshDesc &t,const char *userProperties)	{};
		virtual void NXU_notifyClothMeshFailed(NxClothMeshDesc &t,const char *userProperties) {};
		virtual void NXU_notifyCCDSkeletonFailed(NxSimpleTriangleMesh &t,const char *userProperties) {};
		virtual void NXU_notifyHeightFieldFailed(NxHeightFieldDesc &t,const char *userProperties) {};
};



#endif