/** \file    NxOgreTesting.h
 *  \brief   Header for the Test class.
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


#ifndef __NXOGRE_TESTING_H__
#define __NXOGRE_TESTING_H__

#include "NxOgrePrerequisites.h"

#if 0

#include "NxOgreContainer.h"

namespace NxOgre {

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass Test {

		public:

			///////////////////////////////////////////////////////////////////////

			class NxPublicClass TestCase {

				public:

					TestCase()										{}
					virtual ~TestCase()								{}
					virtual void Start(World*, NxPhysicsSDK*, Ogre::SceneManager*)		{}
					virtual void Stop()								{} 
					virtual bool getResult()						{return mResult;}
					virtual NxString getComments()					{return mComments;}
					virtual NxString getID()						{return NxString("Test Case Base");}

					bool mResult;
					NxString mComments;
			};

			///////////////////////////////////////////////////////////////////////

			class NxPublicClass TestCase_NxOgreCore : public TestCase {

				public:

					TestCase_NxOgreCore()							{mMaxScenes = 48;}
					virtual ~TestCase_NxOgreCore()					{}
					virtual void Start(World*, NxPhysicsSDK*, Ogre::SceneManager*);
					virtual void Stop();
					virtual NxString getID()						{return NxString("NxOgre Core Check");}

					World* mWorld;
					NxPhysicsSDK* mSDK;
					std::vector<Scene*> mScenes;
					NxU32 mMaxScenes;

			};
			
			///////////////////////////////////////////////////////////////////////

			class NxPublicClass TestCase_RigidActors : public TestCase {

				public:

					TestCase_RigidActors()							{mMaxScenes = 8;mMaxActors=128;}
					virtual ~TestCase_RigidActors()					{}
					virtual void Start(World*, NxPhysicsSDK*, Ogre::SceneManager*);
					virtual void Stop();
					virtual NxString getID()						{return NxString("NxOgre Rigid Actors and Shapes Check");}

					World* mWorld;
					NxPhysicsSDK* mSDK;
					std::vector<Scene*> mScenes;
					NxU32 mMaxScenes;
					NxU32 mMaxActors;

			};
			
			///////////////////////////////////////////////////////////////////////

			class NxPublicClass TestCase_Cooking : public TestCase {

				public:

					TestCase_Cooking()								{}
					virtual ~TestCase_Cooking()						{}
					virtual void Start(World*, NxPhysicsSDK*, Ogre::SceneManager*)		{}
					virtual void Stop()								{}
					virtual bool getResult()						{return false;}
					virtual NxString getComments()					{return NxString("");}
					virtual NxString getID()						{return NxString("NxOgre Cooking Check");}

			};
			
			///////////////////////////////////////////////////////////////////////

			Test(World*, Ogre::SceneManager*);
			~Test();
			void addTestCases();
			void addTestCase(TestCase*);
			
			void startTesting();
			void stopTesting();

			void save(NxString filename);
			void saveToLog();

			///////////////////////////////////////////////////////////////////////

		protected:

			std::vector<TestCase*> mTestCases;

			struct TestResult {
				NxString mCaseID;
				bool	 mCaseResult;
				NxString mCaseComments;
			};

			std::vector<TestResult> mTestResults;

			World*				mWorld;
			Ogre::SceneManager*	mSceneMgr;
		//	Ogre::Timer*		mTimer;
		//	unsigned long		mStopTime;
			
		private:

	};

	

};

#endif
#endif
