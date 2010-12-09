/** \file    NxOgreRaycaster.h
 *  \brief   Header for the RayCastHist struct and RayCaster class.
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

#ifndef __NXOGRE_RAYCASTER_H__
#define __NXOGRE_RAYCASTER_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"			// For: mActors

#include "OgreVector3.h"				// For HitImpacts and HitNormal
namespace NxOgre {

	struct NxPublicClass RayCastHit {

			NxRaycastHit	mRaycastHit;

			Actor*			mActor;
			CharacterSystem::Character*		mCharacter;
			Ogre::Vector3	mWorldImpact;
			Ogre::Vector3	mWorldNormal;

	};

	class NxPublicClass RayCaster : public NxUserRaycastReport {
		
		friend class Scene;

	public:

		enum RayCastType {
			RCT_ANY,
			RCT_CLOSEST,
			RCT_ALL,
		};


		enum ActorFilter {
			AF_STATIC_ONLY = NX_STATIC_SHAPES,
			AF_DYNAMIC_ONLY = NX_DYNAMIC_SHAPES,
			AF_NONE = NX_ALL_SHAPES
		};
		

		/// Raycast with a specific type of raycast.
		/// Simply return true if the ray that is specified hits any shape’s axis aligned bounding box, or the shape itself. 
		/// No actor is returned.
		/// \param origin Origin of the ray
		/// \param direction Direction of the ray
		/// \param distance maxDistance The furthest the ray will go.
		/// \param RayCastType Type of ray cast
		/// \param Scene* Scene to ray cast into.
		/// 
		/// Use RayCaster::cast() to cast the ray, and the result will be if the ray hit anything or not.
		RayCaster(Ogre::Vector3 origin, Ogre::Vector3 direction, NxReal maxDistance, Scene*);
		
		/// Raycast with a specific type of raycast.
		/// Any - Just returns if the ray hit anything or not, which is the result of RayCaster::cast.
		/// Closest - Same as above but the actor is returned through RayCaster::getClosestActor();
		/// All - Same as above but with all actors the ray went through, Use RayCaster::mActors to access them.
		/// \param origin Origin of the ray
		/// \param direction Direction of the ray
		/// \param distance maxDistance The furthest the ray will go.
		/// \param RayCastType Type of ray cast
		/// \param Scene* Scene to ray cast into.
		RayCaster(Ogre::Vector3 origin, Ogre::Vector3 direction, NxReal maxDistance, RayCastType, Scene*);

		/// RayCaster destructor
		~RayCaster();

		/// Cast to the shape (more accurate)
		/// Depending on the type of raycast, three things will result.
		/// Any - Use the boolean value returned to determine if the cast hit anything or not.
		/// Closest - Use the boolean value returned to determine if the cast hit anything or not, and getClosestActor() to access it.
		/// All - Same as above, except mActors will contain all of the actors the ray hit.
		bool castShape(ActorFilter f);
		
		/// Raycast to the bounds (less accurate)
		/// Depending on the type of raycast, three things will result.
		/// Any - Use the boolean value returned to determine if the cast hit anything or not.
		/// Closest - Use the boolean value returned to determine if the cast hit anything or not, and getClosestActor() to access it.
		/// All - Same as above, except mActors will contain all of the actors the ray hit.
		
		bool castBounds(ActorFilter f);

		/// Set the origin to a new position
		void setOrigin(const Ogre::Vector3&);
		
		/// Set the direction to a new one.
		/// The vector should be normalised before passing into setDirection (Ogre::Vector3::normalise)
		void setDirection(const Ogre::Vector3&);

		/// Set Max Distance
		void setMaxDistance(NxReal);

		/// Returns the most closest actor hit (Use with Closest or All).
		Actor* getClosestActor();

		CharacterSystem::Character* getClosestCharacter();

		RayCastHit getClosestRaycastHit();

		/// All of the actors raycast, the first RayCastHit in the std::map is the most closest.
		RayCastReport mReport;	


	protected:

		bool _castAny(ActorFilter);
		NxU32 _castAll(ActorFilter);
		bool _castClosest(ActorFilter);

		
		Scene *mScene;
		RayCastType mType;
		
		NxRay mRay;
		NxReal mRayDistance;

		NxVec3 mHitNormal;
		NxVec3 mHitImpact;
		RayCastHit mHit;

		bool onHit(const NxRaycastHit& hits);

	private:

	};

};

#endif
