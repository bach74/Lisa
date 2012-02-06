// =============================================================================
//  contactReporter.cpp   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "contactReporter.h"
#include "config.h"


MyContactReporter::MyContactReporter(std::string name)
{
	mContactPoints.clear();
	mContactForces.clear();
	mCOPpos.set(0,0,0);
	mCOPforce.set(0,0,0);
	numContactPairs=0;
	mIterationNum=0;
	mName="logs\\"+name+".log";
}

MyContactReporter::~MyContactReporter()
{
}

/**-------------------------------------------------------------------------------
	Body2 has just started touching Body1.
	Note: This will only be called ONCE when itPoints starts touching.

	\param a (NxOgre::Actor *)
	\param b (NxOgre::Actor *)
	\return (bool)
--------------------------------------------------------------------------------*/
void MyContactReporter::onStartTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream)
{
	numContactPairs++;
}

/**-------------------------------------------------------------------------------
	Body2 has just stopped touching Body1.
	Note: This will only be called ONCE when itPoints stops touching.

	\param a (NxOgre::Actor *)
	\param b (NxOgre::Actor *)
	\return (bool)
 -----------------------------------------------------------------------------*/
void MyContactReporter::onEndTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream)
{
	numContactPairs--;
}

/**-------------------------------------------------------------------------------
	Body2 is touching Body1.
	Note: This will only be called every frame.

	\param a (NxOgre::Actor *)
	\param b (NxOgre::Actor *)
	\return (bool)
 -----------------------------------------------------------------------------*/
void MyContactReporter::onTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream)
{

	if (stream!=NULL)
	{
		// next iteration
		mIterationNum++;

		mContactPoints.clear();
		mContactForces.clear();
		mCOPpos.set(0,0,0);
		mCOPforce.set(0,0,0);

		NxReal sumXtimesXf=0;
		NxReal sumYtimesYf=0;
		NxReal sumZtimesZf=0;
		NxVec3 sumForce(0,0,0);
		NxVec3 sumPos(0,0,0);
		int numPoints=0;

		// user can call getNumPairs() here
		while (stream->goNextPair())
		{
			// user can also call getShape() and getNumPatches() here
			while (stream->goNextPatch())
			{
				//user can also call getPatchNormal() and getNumPoints() here
				NxVec3 contactNormal = stream->getPatchNormalAsNxVec3();
				while (stream->goNextPoint())
				{
					// get contact point
					mContactPoints.push_back(stream->getPointAsNxVec3());
					// get contact force
					mContactForces.push_back(contactNormal*stream->getPointNormalForce());
					//contactArrowForceTip.push_back(contactPoint.back()+contactForce.back()*0.1f);
					//contactArrowFrictionTip.push_back(contactPoint.back()+pair.sumFrictionForce*0.1f);                    // the friction
					//contactArrowPenetrationTip.push_back(contactPoint.back()-contactNormal*i.getSeparation()*20.0f);      // penetration part

					sumXtimesXf+=mContactPoints.back().x*mContactForces.back().x;
					sumYtimesYf+=mContactPoints.back().y*mContactForces.back().y;
					sumZtimesZf+=mContactPoints.back().z*mContactForces.back().z;
					sumForce+=mContactForces.back();
					sumPos+=mContactPoints.back();
					numPoints++;
				}
			}
		}

		// calculate center of pressure
		// center of pressure point
		//  cop=[sum(x.*xf)/sum(xf) sum(y.*yf)/sum(yf) sum(z.*zf)/sum(zf)];
		if ((sumForce.x!=0)&&(sumForce.y!=0)&&(sumForce.z!=0))
		{
			mCOPpos.set(sumXtimesXf/sumForce.x, sumYtimesYf/sumForce.y, sumZtimesZf/sumForce.z);
		}

		// center of pressure force
		// copF=[sum(x.*xf)/sum(x) sum(y.*yf)/sum(y) sum(z.*zf)/sum(z)];
		// no division is necessary, since physx already does it it self
		// mCOPforce.set(sumXtimesXf/sumPos.x, sumYtimesYf/sumPos.y, sumZtimesZf/sumPos.z);
		mCOPforce=sumForce;

		// writeLog to a log
		if (Config::Instance().getLoggingSensors()) {
			updateLog();
		}
	}

}


/**-------------------------------------------------------------------------------
	Make a log with contacts data for later analysis

	\return (void)
 -----------------------------------------------------------------------------*/
void MyContactReporter::updateLog()
{
	mLogBuffer.setf(std::ios::fixed);
	mLogBuffer.setf(std::ios::showpoint);
	mLogBuffer<<std::setw(3)<<mIterationNum<<"\n";
	std::vector<NxVec3>::iterator itPoints=mContactPoints.begin();
	std::vector<NxVec3>::iterator itForces=mContactForces.begin();

	for (; itPoints!=mContactPoints.end(); ++itPoints,++itForces)
	{
		mLogBuffer<<"   CP: "<<std::setprecision(6)<<std::setw(10)<<itPoints->x<<"\t";
		mLogBuffer<<std::setprecision(6)<<std::setw(10)<<itPoints->y<<"\t";
		mLogBuffer<<std::setprecision(6)<<std::setw(10)<<itPoints->z<<"\t";
		mLogBuffer<<"   FP: "<<std::setprecision(6)<<std::setw(10)<<itForces->x<<"\t";
		mLogBuffer<<std::setprecision(6)<<std::setw(10)<<itForces->y<<"\t";
		mLogBuffer<<std::setprecision(6)<<std::setw(10)<<itForces->z<<"\n";
	}
	mLogBuffer<<"   COP "<<std::setprecision(6)<<std::setw(10)<<mCOPpos.x<<"\t";
	mLogBuffer<<std::setprecision(6)<<std::setw(10)<<mCOPpos.y<<"\t";
	mLogBuffer<<std::setprecision(6)<<std::setw(10)<<mCOPpos.z<<"\n";
	mLogBuffer<<"   COF "<<std::setprecision(6)<<std::setw(10)<<mCOPforce.x<<"\t";
	mLogBuffer<<std::setprecision(6)<<std::setw(10)<<mCOPforce.y<<"\t";
	mLogBuffer<<std::setprecision(6)<<std::setw(10)<<mCOPforce.z<<"\n";
}
