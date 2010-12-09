/** \file    NxOgreDebugRenderer.h
 *  \brief   Header for the DebugRenderer class.
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

#ifndef __NXOGRE_DEBUG_RENDERER_H__
#define __NXOGRE_DEBUG_RENDERER_H__


#include "NxOgrePrerequisites.h"

#if (NX_USE_DEBUG_RENDERER_API == 1)

#include "OgreSimpleRenderable.h"
#include "OgreMovableObject.h"
#include "OgreRenderable.h"
#include "OgreAxisAlignedBox.h"
#include "OgreCamera.h"

namespace NxOgre {


	class NxPublicClass DebugRenderer : public Ogre::SimpleRenderable {

	public:

		DebugRenderer(Ogre::SceneManager *_mgr);
		~DebugRenderer();

		void start();
		unsigned int stop();
		void addLine(NxVec3 a, NxVec3 b, unsigned int col);
		void render(const NxDebugRenderable& data);

		Ogre::Real getSquaredViewDepth(const Ogre::Camera *cam) const {
			Ogre::Vector3 vMin, vMax, vMid, vDist;
			vMin = mBox.getMinimum();
			vMax = mBox.getMaximum();
			vMid = ((vMin - vMax) * 0.5) + vMin;
			vDist = cam->getDerivedPosition() - vMid;

			return vDist.squaredLength();
		}

		Ogre::Real getBoundingRadius() const {
			return Ogre::Math::Sqrt(std::max(mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength()));
		}

		

		std::vector< std::pair< Ogre::Vector3, unsigned int > > mPoints;

		Ogre::SceneNode *mNode;
		Ogre::SceneManager *mSceneMgr;

		Ogre::String mName;
	};


};
#endif
#endif
