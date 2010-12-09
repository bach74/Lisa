/** \file    NxOgreRenderableSource.h
 *  \brief   Header for the RenderableSource class.
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

#ifndef __NXOGRE_RENDERABLE_SOURCE_H__
#define __NXOGRE_RENDERABLE_SOURCE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgrePose.h"
#include "NxOgreTimeStep.h"

namespace NxOgre {

	/** \brief A Renderable source owns and controls a "Renderable"; a thing which is considered
	           visible thus be rendered through the RenderSystem. NxOgre classes which need to be
	           rendered inherit the RenderableSource class and set up their own Rendersystem specific
	           Renderable.
	*/
	class NxPublicClass RenderableSource {

		/* best */ friend class SceneRenderer;

		public:

			/** \brief RenderFunction function signature. Used with setCustomRenderMode
			*/
			typedef void (RenderableSource::*RenderFunctionPtr)(const TimeStep&);

			/** \brief Type of mode (and function used to Render)
			*/
			enum RenderMode {
				RM_Absolute     = 0,
				RM_Interpolate  = 1,
				RM_Custom       = 2
			};

			/** \brief Set the render mode used.
			*/
			void setRenderMode(RenderMode);
			
			/** \brief Ignore the types of RenderModes and use your own.
			    \note  Function siganture must be the same as RenderFunctionPtr, thus
			           your function must be inside a derrivate of RenderableSource.
			*/
			void setCustomRenderMode(RenderFunctionPtr);

			/** \brief Replaces the current Renderable with a new one.
			    \note  Inproper usage will result in sudden hair loss and stress.
			*/
			void setRenderable(Renderable*);

			/** \brief Returns the renderable associated with this RenderableSource.
			*/
			Renderable* getRenderable();

			/** \brief What exactly the Renderable is.
			*/
			NxString getRenderableType() const;

			/** \brief What exactly the Renderable is as a hash.
			*/
			NxShortHashIdentifier getRenderableTypeHash();

			/** \brief "Render" the Renderable.
			*/
			void render(const TimeStep&);

			void reset();

			/** \brief Get the pose from the source
			*/
			virtual Pose getSourcePose(const TimeStep&) const = 0;

		protected:

			/** \brief Set's the render pose to absolute
			    \internal
			*/
			void render_Absolute(const TimeStep&);

			/** \brief Set's the render pose to interpolated pose.
			    \internal
			*/
			void render_Interpolate(const TimeStep&);

			NxU32                   mRenderableSourceID;
			Renderable*             mRenderable;
			RenderFunctionPtr       mRenderFunction;
			RenderMode              mRenderMode;
			Pose                    mRenderPose;
			Pose                    mAlphaPose;

	};


};

#endif
