/** \file    NxOgreBody.h
 *  \brief   Header for the Body class.
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

#ifndef __NXOGRE_BODY_H__
#define __NXOGRE_BODY_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreActor.h"                  // For: Body inherits Actor
#include "NxOgrePose.h"                   // For: getSourcePose()
#include "NxOgreRenderableSource.h"       // For: Body inherits RenderableSource
#include "NxOgreRenderable.h"             // For: Body uses a Renderable (Abstract).
#include "NxOgreNodeRenderable.h"         // For: Body uses a NodeRenderable

namespace NxOgre {

	/** \brief Body is an example of an Actor using a NodeRenderable
	    \note  This is merely an example on how to uses visualisation in NxOgre, it shouldn't
	           be used for serious things.
	*/
	class NxPublicClass Body : public Actor, public RenderableSource {

		public:


			/** \brief Body constructor with limited short-hand visualisation specification.
			           How the body is visualised is built into the identifier.
			                                                                             
			        - "myBody"
			            No Visualisation
			                                                                             
			        - "myBody; cow.mesh"
			            Visualisation as "cow.mesh" as the graphics model loading it from
			            the rendersystems resource system.
			            (Default behaviour)
			                                                                              
			        - "myBody; (reference) cow.mesh"
			            Visualisation as "cow.mesh" from a pre-existing model that has
			            already been loaded and in the scene already.
			            (Moving it from one visualisation node to this one)
			*/
			Body(const VisualIdentifier&, Scene*, Shape*, const Pose&, const ActorParams&);


			/** \brief Body constructor with full visualisation.
			    \example
			     <code>
			      mSceneMgr->createBody("myBody", new CubeShape(2,2,2), Vector3(0,5,0), "model: cube.1m.mesh, scale: 2 2 2", "mass: 10");
			     </code>
			*/
			Body(const NxString&, Scene*, Shape*, const Pose&, const NodeRenderableParams&, const ActorParams&);


			/** \brief Body destructor. If you hate memory leaks and crashes, use mScene->destroyActor(...);
			*/
			virtual ~Body();


			/** \brief Get HashType of this class
			*/
			NxShortHashIdentifier  getType() const {
				return NxOgreClass_Body;
			}


			/** \brief Get String type of this class
			*/
			NxString  getStringType() const {
				return "NxOgre-Example-Body";
			}

		protected:

			/** \brief Get the Source Pose of this class
			    \internal
			*/
			Pose              getSourcePose(const TimeStep&) const;

		protected:

			NodeRenderable*   mNodeRenderable;

	}; // End of Body class.

}; // End of NxOgre namespace.

#endif
