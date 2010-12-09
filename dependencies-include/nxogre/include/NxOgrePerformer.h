/** \file    NxOgrePerformer.h
 *  \brief   Header for the Performer class.
 *  \version 1.0-20
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *            version 2.1 of the License, or (at your option) any later version.
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


#ifndef __NXOGRE_PERFORMER_H__
#define __NXOGRE_PERFORMER_H__

#include "NxOgrePrerequisites.h"

#if (NX_USE_LEGACY_NXCONTROLLER == 0)

#include "NxOgreCharacter.h"
#include "NxOgreRenderableSource.h"
#include "NxOgreRenderable.h"
#include "NxOgreNodeRenderable.h"

namespace NxOgre {
namespace CharacterSystem {

	/**	Performers are Characters with Visualations
	*/
	class NxPublicClass Performer : public Character, public RenderableSource {
		
		public:
		
			Performer(const VisualIdentifier&, const Pose&, CharacterModel*, const CharacterParams&, Scene*);
			Performer(const NxString&, const Pose&, CharacterModel*, const CharacterParams&, const NodeRenderableParams&, Scene*);
			~Performer();
		

			NxShortHashIdentifier	getType() const {return NxOgreClass_Performer;	/* "NxOgre-Example-Performer" */}
			NxString				getStringType() const {return "NxOgre-Example-Performer";}


		protected:

			Pose getSourcePose(const TimeStep&) const;

			NodeRenderable*			mNodeRenderable;
		
	};
		
	////////////////////////////////////////////

}; // End of CharacterSystem namespace.
}; // End of NxOgre namespace.

#endif
#endif
