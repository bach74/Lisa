/** \file    NxOgreForceField.h
 *  \brief   Header for the ForceFieldForumula struct, the ForceFieldParams
 *           and ForceField classes
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

#ifndef __NXOGRE_FORCEFIELD_H__
#define __NXOGRE_FORCEFIELD_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreActor.h"
#include "NxOgreSimpleActor.h"
#include "NxOgreEffectsSystem.h"
#include "NxOgreParams.h"
#include "NxOgrePose.h"

namespace NxOgre {

	/* \brief A collection of constants which are used in the following equation
		f_i = [K + M_p(P-p) + Mv(V-v) + N a_noise]_i / [1 + l_i|P_i-p_i| + qi(P_i-p_i)^2]
		to calculate the velocity of a single actor within the forcefield equation
		shape.
	*/
	class NxPublicClass ForceFieldFunction {

		public:

			/** \brief Constant(K) part of the function.
			*/
			NxVec3  Constant;
			/** \brief Position Dependence Matrix(Mp) part of the function.
				\see   NxForceFieldDesc::position 
			*/
			NxMat33 PositionDependence;

			/** \brief Position Target (P)
				\see   NxForceFieldDesc::positionTarget 
			*/
			NxVec3  PositionTarget;

			/** \brief Velocity Dependence Matrix (Mv)
				\see   NxForceFieldDesc::velocityMultiplier
			*/
			NxMat33 VelocityDependence;

			/** \brief V is the velocity target, from NxForceFieldDesc.velocityTarget 
			*/
			NxVec3  VelocityTarget;

			/** \brief Noise is the noise multiplier, from NxForceFieldDesc.noise 
			*/
			NxVec3  Noise;

			/** \brief l is the linear falloff term, from NxForceFieldDesc.falloffLinear 
			*/
			NxVec3  LinearFalloff;

			/** \brief q is the quadratic falloff term, from NxForceFieldDesc.falloffQuadratic 
			*/
			NxVec3  QuadraticFalloff;

			/** \brief Coordinate system to use
			*/
			NxForceFieldCoordinates CoordinateSystem;

			static ForceFieldFunction Tornado();
			static ForceFieldFunction Explosion();

	};
	
	class NxPublicClass ForceField : public SimpleActor, public EffectsSystem {

		public:

			ForceField(SimpleShape* inclusion_shape, Scene* scene, ForceFieldFunction constants)  : SimpleActor(scene) {}
			~ForceField() {}


	};

}; // End of NxOgre namespace

#endif 

#if 0

	// Helper Class for ForceFieldParams.
	// fi = [K + Mp(P-p) + Mv(V-v) + N anoise]i / [1 + li|Pi-pi| + qi(Pi-pi)^2]
	struct NxPublicClass ForceFieldFormula {


		NxForceFieldCoordinates coords;

		/////////////////////////////////////////////////////////////////

		void zero() {
			K.zero();
			Mp.zero();
			P.zero();
			Mv.zero();
			V.zero();
			Anoise.zero();
			l.zero();
			q.zero();
			coords = NX_FFC_CARTESIAN;
		}

		void asExplosive(NxReal explosiveConstant, Ogre::Vector3 velocityTarget, Ogre::Vector3 noise = Ogre::Vector3(1,1,1));

	};

	/////////////////////////////////////////////////////////////////

	class NxPublicClass ForceFieldParams : public Params {

		public:

			ForceFieldParams() {}
			ForceFieldParams(const char* p) {process(p);}
			ForceFieldParams(NxString p) {process(p);}
			ForceFieldParams(const ForceFieldFormula& f){setToDefault();parseFormula(f);}

			void			setToDefault();
			void			parse(Parameters);			
			void			parseFormula(const ForceFieldFormula&);
			
			NxMat34					pose;					//!< Global or (if actor is set) actor relative transformation of the force field.
			NxActor*				actor;					//!< The field is attached to move with an actor. If null, the field is static.
			NxForceFieldCoordinates	coordinates;			//!< Coordinate space of the field.

			// Filtering:
			NxCollisionGroup		group;					//!< Collision group used for collision filtering.
			NxGroupsMask			groupsMask;				//!< Groups mask used for collision filtering. 

			// Function parameters:
			NxVec3					constant;				//!< Constant part of force field function
			NxMat33					positionMultiplier;		//!< Coefficient of force field function position term
			NxVec3					positionTarget;			//!< Force field position target			
			NxMat33					velocityMultiplier;		//!< Coefficient of force field function velocity term
			NxVec3					velocityTarget;			//!< Force field velocity target

			NxVec3					falloffLinear;			//!< Force field velocity target
			NxVec3					falloffQuadratic;		//!< Force field velocity target

			NxReal					torusRadius;			//!< Radius for NX_FFC_TOROIDAL type coordinates.

			NxVec3					noise;					//<! Noise scaling

			NxReal					fluidScale;				//!< Force scale factor for fluids
			NxReal					clothScale;				//!< Force scale factor for cloth
			NxReal					softBodyScale;			//!< Force scale factor for soft bodies
			NxReal					rigidBodyScale;			//!< Force scale factor for rigid bodies

			NxU32					flags;					//!< Force field flags; \see NxForceFieldShapeFlags


	}; // End of ActorParams class

	//////////////////////////////////////////////////////////

	class NxPublicClass ForceField : public Actor {

		friend class Scene;

		public:

			ForceField(const NxString& Identifier, Scene*);
			// identifier, this, pose, actorShape, aparams, fparams
			ForceField(const NxString& identifier, Scene*, const Pose&, Shape* actorShape, ActorParams = "", ForceFieldParams = "");
			~ForceField();

			//////////////////////////////////////////////////////////

			void _createActor(Shape *shape, const Pose& pose, ActorParams params);
			void _destroyActor();
			void _createForceField(ForceFieldParams params);
			void _destroyForceField();

			//////////////////////////////////////////////////////////

			void addForceFieldShape(SimpleShape*, bool Inclusion);

			//////////////////////////////////////////////////////////

			
			StringPairList saveCustom();
			void restoreCustom(StringPairList);

			NxForceField* mForceField;

	};
	
	//////////////////////////////////////////////////////////



};

#endif
