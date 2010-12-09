/** \file    NxOgreNodeRenderableSource.h
 *  \brief   Header for the NodeRenderable and NodeRenderableParams classes.
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

#ifndef __NXOGRE_NODERENDERABLE_H__
#define __NXOGRE_NODERENDERABLE_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreRenderable.h"
#include "NxOgreParams.h"
#include "NxOgrePose.h"
#include "NxOgreRenderableSource.h"

namespace NxOgre {

	/** \brief NodeRenderableParams a string or class abstract way of describing how a NodeRenderable
		generally looks to the RenderSystem.
	*/
	class NxPublicClass NodeRenderableParams : public Params {

		public:


			/** \brief NodeRenderableParams constructor for "class params".
			*/
			NodeRenderableParams()  {
									 setToDefault();
									}


			/** \brief NodeRenderableParams constructor for "string params".
				\param _params Full string of params.
			*/
			NodeRenderableParams(const char* _params)  {
														setToDefault();
														process(_params);
													   }


			/** \brief NodeRenderableParams constructor for "string params" using an NxString.
				\param _params Full string of params.
			*/
			NodeRenderableParams(const NxString& _params)  {
															setToDefault();
															process(_params);
														   }


			/** \brief Set's the member variables to the default values according to NxOgre.
			*/
			void setToDefault();


			/** \brief NodeRenderable identifier to the RenderSystem, works along with mIdentifierUsage.
				\see NodeRenderableParams::mIdentifier
				\default <blank string>
				\examples
				  C++     ->  mParams.mIdentifier = "Teapot"
				  String  ->  "identifier: Teapot"
			 */
			NxString  mIdentifier;


			/** \brief NodeRenderable identifier to the RenderSystem, works along with IdentifierType
			 */
			enum IdentifierUsage {
				// "create"
				IU_Create,
				// "use"
				IU_Use
			};


			/** \brief NodeRenderable identifier to the RenderSystem.
				\default IT_Create
				\examples
				  C++     ->  mParams.mIdentifierUsage = IT_Use
				  String  ->  "identifier-usage = use"         (or)
				  String  ->  "usage = use" 
						{ IT_Create = "create", IT_Use = "use" }
			 */
			IdentifierUsage  mIdentifierUsage;


			/** \brief Graphics model identifier to use with the NodeRenderable.
				\default <blank string>
				\examples
				  C++     ->  mParams.mGraphicsModel = "Teapot.mesh"
				  String  ->  "model = Teapot.mesh"
			 */
			NxString  mGraphicsModel;


			/** \brief What the model identifier is to the RenderSystem, works along with mGraphicsModelUsage.
			 */
			enum GraphicsModelIdentifierUsage {
				/** \brief "resource" */
				GMU_Resource,
				/** \brief "file" */
				GMU_File,
				/** \brief "reference" */
				GMU_Reference
			};


			/** \brief Graphic model identifier usage according to the render system.
				\default GMT_Resource
				\examples
				  C++     ->  mParams.mIdentifierUsage = IT_File
				  String  ->  "model-usage = file"
						{ GMT_Resource = "resource", GMT_File = "file", GMT_Reference = "reference" }
			 */
			GraphicsModelIdentifierUsage  mGraphicsModelType;


			/** \brief Scale the model based on coordinatse
				\default 1 1 1
				\examples
				  C++     ->  mParams.mGraphicsModelScale.set(2,2,2)
				  String  ->  "scale: 2 2 2"
			 */
			NxVec3  mGraphicsModelScale;


			/** \brief Scale the model based on the RenderableSource. Overrides model scale.
				\default false
				\examples
				  C++     ->  mParams.mGraphicsModelScaleInherit = 1
				  String  ->  "scale: inherit"
			 */
			bool  mGraphicsModelScaleInherit;


			/** \brief Initial model pose.
				\default Pose.id()
				\examples
				  C++     ->  mParams.mGraphicsModelPose = Pose(...)
				  String  ->  "position: 1 1 1" (and/or)
				  String  ->  "orientation: 1 0 0 0"
			 */
			Pose  mGraphicsModelPose;


			/** \brief Offset model pose.
				\default Pose.id()
				\examples
				  C++     ->  mParams.mGraphicsModelOffset = Pose(...)
				  String  ->  "offset-position: 1 1 1" (and/or)
				  String  ->  "offset-orientation: 1 0 0 0"
			 */
			Pose  mGraphicsModelOffset;


			/** \brief Model material override; Rendersystem specific.
				\default <blank string>
				\examples
				  C++     ->  mParams.mGraphicsModelMaterial = "teapot"
				  String  ->  "material: teapot"
			 */
			NxString  mGraphicsModelMaterial;


			/** \brief For "SubNodeRenderable behaviour, allowing you to tell the NodeRenderable
			           or the SceneRender what the NodeRenderable is intended for, which then
			           the NodeRenderable/SceneRender can be more accommodating.
			                                                                                    
			           For most classes NodeRenderable in NxOgre, they may adjust the Parameters
			           to add their type into the Intent string for you, unless you've added 
			           it yourself.
			   \default Blank String
			   \note This may be altered when is handed to a RenderableSource
			*/ 
			NxString  mIntent;

			/** \brief Renderable's parent (RenderableSource) render mode.
				\default See RenderableSource of class you are using this params with.
				\examples
				  C++     ->  mParams.mMode = RenderableSource::RM_Interpolate
				  String  ->  "mode: interpolate"
					 { RM_Absolute = "absolute", RM_Interpolate = "interpolate" }
			 */
			RenderableSource::RenderMode  mMode;

		protected:

			void parse(Parameters);

	}; // End of NodeRenderableParams class


	/** \brief Self-contained renderable, with a model that can be frequently moved around.
		Similar to the Ogre system of a SceneNode with an Entity attached. Multiple models
		are subject to the RenderSystem the Renderable is working with.
	*/
	class NxPublicClass NodeRenderable : public Renderable {

		public:

			NodeRenderable(const NodeRenderableParams&, SceneRenderer*);

			virtual void            setPose(const Pose&)            = 0;
			virtual Pose            getPose() const                 = 0;
			virtual void            setMaterial(const NxString&)    = 0;
			virtual NxString        getMaterial() const             = 0;
			virtual void            setScale(const NxVec3&)         = 0;
			virtual void            setScale(const float3&)         = 0;
			virtual NxVec3          getScaleAsNxVec3() const        = 0;
			virtual float3          getScaleAsFloat3() const        = 0;
			virtual void            setOffset(const Pose&)          = 0;
			virtual Pose            getOffset() const               = 0;

#if NX_USE_OGRE == 1
			virtual Ogre::Vector3   getScaleAsOgreVector3() const   = 0;
			virtual void            setScale(const Ogre::Vector3&)  = 0;
#endif

			virtual NxString getType() {
			                            return "NxOgre-NodeRenderable";
			                           }

			virtual NxShortHashIdentifier getHashType() const {
			                                                   return 42719;
			                                                  }

	};


};

#endif
