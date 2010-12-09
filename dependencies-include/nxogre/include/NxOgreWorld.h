/** \file    NxOgreWorld.h
 *  \brief   Header for the World class
 *  \version 1.0-21
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

#ifndef __NXOGRE_WORLD_H__
#define __NXOGRE_WORLD_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"				// For: mScenes
#include "NxOgrePhysXDriver.h"				// For: World::World() & World::mDriver
#include "NxOgreScene.h"					// For: SceneParams

namespace NxOgre {

	/** \brief The container of all Scenes and everything therein.
		  World is the top-most NxOgre class, it's similar to Ogre's Root. It is the
		  first NxOgre class to be created and the last to be destroyed.

		  <pre><code>
		    World* mWorld = new World();                 \n
		    //                                           \n
		    delete mWorld;                               \n
		  </code></pre>
	*/
	class NxPublicClass World {

		friend class PhysXDriver;
		friend class Error;
		friend class Scene;

		public:

			/** \brief Starts up World, and creates the PhysXDriver singleton.
				\param PhysXParams    Inital parameters and customisation of the PhysXSDK.
				\param loadResources  Load the default Resource systems and load in resources.
				\see PhysXParams
			*/
			World(PhysXParams = PhysXParams(), bool loadResources = true);


			/** \brief Completely shuts down NxOgre.
				  Destroys the entire World and shut's down PhysX.All owned Scenes and 
				  owned instances of classes in the scene will be deleted. All custom classes, 
				  or custom storage types should delete them before deleting World.
			*/
			~World();

			/** \brief Creates a Scene.
				  Creates a new Scene within NxOgre, as well as default Groups, Materials, etc. Depending
				  on the SceneParams it may create a static Actor with a ground shape for the floor and
				  assign some gravity.

				\note  A Scene is a sub-section of a World. Although a Scene is infinite in size like World. 
				       Scenes are considered to be seperate from each other. Actors from one scene cannot 
				       interact with ones from another. Scenes have also their own Materials, Groups, etc. 
				       which cannot be shared.	Scenes are used in containers. Creating a Scene through the World factory method makes the Scene "owned"
				       by NxOgre, on deletion of the Scene it will remove the presence of the Scene and delete the pointer.
				       Manually creating the Scene "<code>new Scene()</code>" will only add a presence, it is up to you to delete it at the
				       correct time.

				\param Identifier       Unique identifier of the Scene
				\param SceneParams      SceneParams for this Scene to use.
				\return Scene           The scene itself.
				\see SceneParams
			 */
			Scene*   createScene(const NxString& Identifier, SceneParams = SceneParams());


			/** \brief Deprecated. Creates a Scene (For Ogre)
				  Creates a new Scene within NxOgre, as well as default Groups, Materials, etc. Depending
				  on the SceneParams it may create a static Actor with a ground shape for the floor and
				  assign some gravity.

				\note	A Scene is a sub-section of a World. Although a Scene is infinite in size like World. 
						Scenes are considered to be seperate from each other. Actors from one scene cannot 
						interact with ones from another. Scenes have also their own Materials, Groups, etc. 
						which cannot be shared.	Scenes are used in containers. Creating a Scene through the World factory method makes the Scene "owned"
						by NxOgre, on deletion of the Scene it will remove the presence of the Scene and delete the pointer.
						Manually creating the Scene "<code>new Scene()</code>" will only add a presence, it is up to you to delete it at the
						correct time.

				\param Identifier			Unique identifier of the Scene
				\param Ogre::SceneManager*	SceneManager for this Scene to Use.
				\param SceneParams			SceneParams for this Scene to use.
				\see SceneParams
				\return Scene				The scene itself.
			 */
			Scene*   createScene(const NxString& Identifier, Ogre::SceneManager*, SceneParams = SceneParams());


			/** \brief Destroys the Scene and the contents therein. 

				Destroys the entire contents of the scene with every owned object inside; Actors, Shapes, Groups,
				Materials, ForceFields, Triggers, etc.

				\note If the Scene is owned by NxOgre use World::SceneDestroy, if not then use "delete mScene".
				\see World::destroyScene
			*/
			void   destroyScene(const NxString& name);

			/** \brief Destroys all of the Scenes and the contents therein. 

				Destroys the entire contents of every scene with every owned object inside; Actors, Shapes, Groups,
				Materials, ForceFields, Triggers, etc.

				\note If the Scene is owned by NxOgre use World::SceneDestroy, if not then use "delete mScene".
				\see World::destroyScene
			*/
			
			void   destroyAllScenes();


			/** \brief Gets the PhysXDriver.
			
				Returns the PhysX Driver t he in between PhysX and NxOgre, and the class responsible
				for frame by frame operations. Automatically created during the construction
				of the World.

			 \return The PhysXDriver
			 */
			PhysXDriver*   getPhysXDriver()  {
			                                  return mDriver;
			                                 }

			/** \brief Returns the PhysX SDK instance.
				\warning Thar be sea monsters.
				\return The NxPhysicsSDK instance
			 */
			NxPhysicsSDK*   getSDK();

			/** \brief Advances the state of the scene by x seconds. 
			
				This is automatically controlled by PhysXDriver if NxOgre is attached to a frameListener. 
				To advance the simulation by hand or without an attached FrameListener; Provide a 
				<code>"FrameListener: no"</code> params to the World constructor, and advance the simulation in 
				<code>PhysXDriver::simulate(..)</code>.

				\param time Seconds passed since last simulate
				\see PhysXDriver::simulate

			 */
			void   simulate(float time);
			
			/** \brief Renders the new state of the scene.
			
				This is automatically controlled by PhysXDriver if NxOgre is attached to a frameListener. 
				To render the simulation by	hand or without an attached FrameListener. Provide a 
				<code>"FrameListener: no"</code> params to the World constructor, and call 
				<code>PhysXDriver::render(..).</code>

				\param time Seconds passed since last simulate. Must be as the same as the previous simulate.
				\see PhysXDriver::render
			 */
			void   render(float time);


			/** \brief Get a container of pointers of all the Scenes used with NxOgre.
			*/
			Scenes*   getScenes();

#if (NX_USE_DEBUG_RENDERER_API == 1)

			/** \brief Creates the Debug renderer on the screen.
				\param scenemanager		SceneManager to render to. This should be active
										scenemanager on the screen.
			*/
			void   createDebugRenderer(Ogre::SceneManager* scenemanager);
			
			/** \brief Destroys the current Debug Renderer.
			*/
			void   destroyDebugRenderer();

#endif

			/** \brief Enables or Disabled Continuous Collision Detection, with an epsilon value
			*/
			void   setCCD(bool enabled, NxReal epsilon = 0.01f);

			/** \brief Gets if CCD is enabled or not.
				\return If the CCD is enabled.
			*/
			bool   getCCD();

			/** \brief Gets the epsilon value of Continous Collision Detection.
				\return Epsilon of CCD.
			*/
			NxReal   getCCDEpsilon();

			/** \brief Get's the number of frames simulated so far
			*/

			unsigned int getNbFrames() const {
				return mNbFrames;
			}

		protected:

			void   _registerScene(const NxString& name, Scene*);
			void   _unregisterScene(const NxString&);
			void   shutdown();


		protected:

			// \brief First PhysXDriver instance.
			PhysXDriver*				mDriver;

			// \brief Container of all of the NxOgre Scenes.
			Scenes						mScenes;

			// \brief Number of frames simulated.
			NxU32						mNbFrames;

#if (NX_USE_DEBUG_RENDERER_API == 1)
			// \brief DebugRenderer
			DebugRenderer*				mDebugRenderer;
#endif

	};

};

#endif
