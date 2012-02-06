// =============================================================================
//  contactReporter.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONTACTREPORTER_H__
#define __CONTACTREPORTER_H__

#include "logger.h"


/**-------------------------------------------------------------------------------
	Custom contact reporter		
---------------------------------------------------------------------------------*/
class MyContactReporter :	public NxOgre::GroupCallback::InheritedCallback, 
							public LoggerWriter<MyContactReporter>
{

	friend class SensorCOP;

	public:
	
		MyContactReporter(std::string name);
		~MyContactReporter();

		// Body2 has just started touching Body1.
		// Note: This will only be called ONCE when it starts touching.
		void onStartTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream);

		// Body2 has just stopped touching Body1.
		// Note: This will only be called ONCE when it stops touching.
		void onEndTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream);

		// Body2 is touching Body1.
		// Note: This will only be called every frame.
		void onTouch(NxOgre::Actor *a, NxOgre::Actor *b, NxOgre::ContactStream* stream);

		// return true if there are contact
		bool hasContact() { return numContactPairs>0; }

		// get/set COP position
		NxVec3 getCOPpos() const { return mCOPpos; }
		void setCOPpos(NxVec3 val) { mCOPpos = val; }

		// get/set COP force
		NxVec3 getCOPforce() const { return mCOPforce; }
		void setCOPforce(NxVec3 val) { mCOPforce = val; }

		// logging
		void updateLog();

	private:

		NxVec3 mCOPforce;
		NxVec3 mCOPpos;

		int numContactPairs;
		std::vector<NxVec3> mContactPoints;
		std::vector<NxVec3> mContactForces;

		int mIterationNum;

		MyContactReporter(){};
};

#endif