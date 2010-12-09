/** \file    NxOgreSheet.h
 *  \brief   Header for the Sheet class.
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

#ifndef __NXOGRE_SHEET_H__
#define __NXOGRE_SHEET_H__

#if 0

#include "NxOgrePrerequisites.h"
#include "NxOgreCloth.h"
#include "NxOgrePose.h"
#include "NxOgreRenderableSource.h"
#include "NxOgreRenderable.h"
#include "NxOgreMeshRenderable.h"

namespace NxOgre {

	class NxPublicClass Sheet : public Cloth, public RenderableSource {

		public:

			Sheet(const NxString& identifier, Scene*, NxReal width, NxReal height, NxReal verticesPerRow = 5, NxReal verticesPerColumn = 5, Pose = Pose(), ClothParams = ClothParams(), MeshRenderableParams = MeshRenderableParams());
			~Sheet();
		
			NxShortHashIdentifier	getType() const {return 999;}
			NxString				getStringType() const {return "9999";}

		protected:

			void					__renderSelf() {}

		protected:

			void __generateTextureCoordinatesAndNormals(NxReal w, NxReal wD, NxReal h, NxReal hD);
			DynamicClothMesh* __createSheet(NxReal w, NxReal wD, NxReal h, NxReal hD, const NxString& identifier);
			
			/////////////////////////////////////////////////

			DynamicClothMesh*	mDynamicMesh;
			MeshRenderable*		mMeshRenderable;

	};

};// End of namespace

//#endif
#endif

#endif
