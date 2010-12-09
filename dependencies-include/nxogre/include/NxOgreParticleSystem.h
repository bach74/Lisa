/** \file    NxOgreParticleSystem.h
 *  \brief   Header for the ParticleSystem class.
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

#ifndef __NXOGRE_PARTICLE_SYSTEM_H__
#define __NXOGRE_PARTICLE_SYSTEM_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	////////////////////////////////////////////////////////////////////////

	class NxPublicClass ParticleSystem {
	
		public:

			// ParticleSystem
			//	ParticleSource (Fluid, NxActor, Point, Multi-Point)
			//		ParticleCreator		(creates Particles from Source)
			//		ParticleDestroyer	(destroy Particles)
			//		Particle			(represented for Particle)
			//
			//
			//	Fluid: Fluid System
			//	NxActor: Simple NxActor based system using shared SimpleShapes. With NO Modification.
			//	(????): Like NxActor, but has modification gravity, forces, or own ForceFields.
			//	Point: Point Based particle System (dots using tiny spheres with CCD)
			//	Multi-Point: Multiple points sharing the same shape (but randomises direction/movement slighty)
			//				 with CCD.
			//


	};

	////////////////////////////////////////////////////////////////////////

};// End of namespace

#endif