/** \file    NxOgreManualHeightfield.h
 *  \brief   Header for the ManualHeightfield class.
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


#ifndef __NXOGRE_MANUAL_HEIGHTFIELD_H__
#define __NXOGRE_MANUAL_HEIGHTFIELD_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {
namespace Resources {

	class NxPublicClass ManualHeightfield {

		friend class Heightfield;

		public:

			enum TesselationType {
				TT_TopRight_to_BottomLeft = 0,
				TT_TopLeft_to_BottomRight = 1
			};

			/** \brief A Heightfield that can be built by hand.
				\note   Heightfields don't have any size until placed into a terrain.
			*/
			ManualHeightfield();
			~ManualHeightfield();

			void clear();
			void begin(int nbColumns, int nbRows);


			/** \brief Set the current Material0 for any smaples this point forward
			*/
			void setDefaultMaterial0(NxMaterialIndex);
			
			/** \brief Set the current Material0 for any smaples this point forward
			*/
			void setDefaultMaterial0(Material*);
			
			/** \brief Set the current Material0 for any smaples this point forward
			*/
			void setDefaultMaterial1(Material*);
			
			/** \brief Set the current Material0 for any smaples this point forward
			*/
			void setDefaultMaterial1(NxMaterialIndex);

			/** \brief Where the next sample will be as (X,Z) coordinates.
			*/
			int2 whereAmI() const;

			/** \brief Set the current tesselation for any samples this point forward.
			*/
			void setTesselation(TesselationType);

			/** \brief  Add a sample, with default material0, default material1 and default tesselation
			*/
			void sample(short height);

			/** \brief  Add a sample, with default material0, default material1 and default tesselation
			*/
			void sample(short height, NxMaterialIndex mat0);

			/** \brief  Add a sample.
			*/
			void sample(short height, NxMaterialIndex mat0, NxMaterialIndex mat1);

			/** \brief  Add a sample.
			*/
			void sample(short height, NxMaterialIndex mat0, NxMaterialIndex mat1, bool teselation_to_topleft_bottomright);
	
			/** \brief  Add a sample with default material0, default material1
			*/
			void sample(short height, bool teselation_to_topleft_bottomright);

			void sample(NxHeightFieldSample);

			/** \brief Finish generation, and cook to a mesh
			*/
			Heightfield* end(bool cleanup = true);

			/** \brief Is the mesh valid?
			*/
			bool isValid() const;

			/** \brief Why is the mesh not valid
			*/
			NxString isNotValidReasons() const;


			void   setVerticalExtent(NxReal);
			NxReal getVerticalExtent() const;

			void   setThickness(NxReal);
			NxReal getThickness() const;

			void   setConvexEdgeThreshold(NxReal);
			NxReal getConvexEdgeThreshold() const;

			void   setHasNoBoundaryEdges(bool);
			bool   getHasNoBoundaryEdges() const;


		protected:

			void endToHeightfield(Heightfield*);

			void reserve(NxU32);

			NxHeightField* _createHeightFieldMesh();

			Betajaen::Flat<NxHeightFieldSample>*  mSamples;

			NxU32                                 mNbRows,
			                                      mNbColumns;
			NxMaterialIndex                       mCurrentMaterial0,
			                                      mCurrentMaterial1;

			bool                                  mCurrentTesselation;
			NxReal                                mVerticalExtent;
			NxReal                                mThickness;
			NxReal                                mConvexEdgeThreshold;
			bool                                  mFlag_NX_HF_NO_BOUNDARY_EDGES;

	};

}; // End of Resources namespaces.
}; // End of NxOgre namespaces.

#endif
