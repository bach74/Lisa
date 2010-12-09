/** \file    NxOgreSceneController.h
 *  \brief   Header for the SceneController, NullSceneController, VariableScene-
 *           Controller, FixedSceneController and AccumulatorSceneController classes.
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

#ifndef __NXOGRE_SCENE_CONTROLLER_H__
#define __NXOGRE_SCENE_CONTROLLER_H__

#include "NxOgrePrerequisites.h"

#ifdef WIN32 
	#define NOMINMAX
	#include <windows.h>
#endif

namespace NxOgre {

	class NxPublicClass SceneController {

		friend class Scene;

		public:

			SceneController(Scene*);
			virtual ~SceneController();

			virtual TimeStep Simulate(NxReal);
			virtual NxString getType() const {return NxString("SceneController");}

		protected:

			virtual void setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void init(NxScene*);

			Scene*		mScene;
			NxScene*	mNxScene;

		private:

	};

	//////////////////////////////////////////////////////////////////////////////

	class NxPublicClass VariableSceneController : public SceneController {

		friend class Scene;

		public:

			VariableSceneController(Scene*);
			virtual ~VariableSceneController();

			//////////////////////////////////////////////////////////////////////////////

			virtual NxString getType() const {return NxString("Variable");}

			virtual void setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void init(NxScene*);
			virtual TimeStep Simulate(NxReal);


	};

	//////////////////////////////////////////////////////////////////////////////

	class NxPublicClass FixedSceneController : public SceneController {

		friend class Scene;

		public:

			FixedSceneController(Scene*);
			virtual ~FixedSceneController();

			//////////////////////////////////////////////////////////////////////////////

			virtual NxString getType() const {return NxString("Fixed");}

			virtual void setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void init(NxScene*);
			virtual TimeStep Simulate(NxReal);

			NxReal	mTiming_MaxStep;
			NxReal	mTiming_CurrentStep;
			bool	mRenderFrame;

			//////////////////////////////////////////////////////////////////////////////

	};

	//////////////////////////////////////////////////////////////////////////////

	class NxPublicClass AccumulatorSceneController : public SceneController {

		friend class Scene;

		public:

			AccumulatorSceneController(Scene*);
			virtual ~AccumulatorSceneController();
			
			//////////////////////////////////////////////////////////////////////////////

			virtual NxString getType() const {return NxString("Accumulator");}
			virtual void setTiming(NxSceneDesc &desc, NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void setTiming(NxReal maxTimestep, NxU32 matIter, NxU32 numSubSteps);
			virtual void init(NxScene*);
			virtual TimeStep Simulate(NxReal);

			Timer*    mTimer;

		private:

			NxF64     mMaxStep;
			NxF64     mAccumulator;
			NxReal    mAlpha;
			NxU32     mPreviousTime;

			
			//////////////////////////////////////////////////////////////////////////////

	};


};

#endif
