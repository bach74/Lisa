/** \file    NxOgreContactStream.h
 *  \brief   Header for the ContactStream class.
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

#ifndef __NXOGRE_CONTACTSTREAM_H__
#define __NXOGRE_CONTACTSTREAM_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"		// An intersection is a container of actors.

namespace NxOgre {

	/////////////////////////////////////////////////////////////////////////////////////////

	class NxPublicClass ContactStream {
		
		public:

			ContactStream(NxConstContactStream&);
			~ContactStream();


			/** \brief Goes on to the next pair, silently skipping invalid pairs. 
			*/
			inline bool goNextPair()							{return mIterator->goNextPair();}


			/** \brief Goes on to the next patch (contacts with the same normal). 
			*/
			inline bool goNextPatch()							{return mIterator->goNextPatch();}


			/** \brief Goes on to the next contact point. 
			*/
			inline bool goNextPoint()							{return mIterator->goNextPoint();}


			/** \brief Returns the number of pairs in the structure.
			*/
			inline NxU32 getNumPairs()							{return mIterator->getNumPairs();}


			/** \brief Retrieves the <em>shapes</em> for the current pair. 
			*/
			inline NxShape* getNxShape(NxU32 shapeIndex)		{return mIterator->getShape(shapeIndex);}


			/** \brief Gets the NxOgre shape for that shapeIndex
			*/
			inline Shape* getShape(NxU32 shapeIndex);


			/** \brief Get the Actor from the shapeIndex
			*/
			inline Actor* getActor(NxU32 shapeIndex);


			/** \brief Get the NxOgre Actor from the shapeIndex
			*/
			inline NxActor* getNxActor(NxU32 shapeIndex);


			/** \brief Retrieves the shape flags for the current pair.
			*/
			inline NxU16 getShapeFlags()						{return mIterator->getShapeFlags();}


			/** \brief Retrieves the number of patches for the current pair. 
			*/
			inline NxU32 getNumPatches ()						{return mIterator->getNumPatches();}


			/** \brief Retrieves the number of remaining patches.
			*/
			inline NxU32 getNumPatchesRemaining()				{return mIterator->getNumPatchesRemaining();}


			/** \brief Retrieves the patch normal.
			*/
			inline const Ogre::Vector3&	getPatchNormal();
			

			/** \brief Retrieves the patch normal as NxVec3
			*/
			inline const NxVec3&	getPatchNormalAsNxVec3()	{return mIterator->getPatchNormal();}


			/** \brief Retrieves the number of points in the current patch. 
			*/
			inline NxU32 getNumPoints()							{return mIterator->getNumPoints();}


			/** \brief Retrieves the number of points remaining in the current patch.
			*/
			inline NxU32 getNumPointsRemaining()				{return mIterator->getNumPointsRemaining();}


			/** \brief Returns the contact point position.
			*/
			inline const Ogre::Vector3& getPoint(); 

			/** \brief Returns the contact point position as NxVec3.
			*/
			inline const NxVec3& getPointAsNxVec3()				{return mIterator->getPoint();}


			/** \brief Return the separation for the contact point. 
			*/
			inline NxReal getSeparation()						{return mIterator->getSeparation();}


			/** \brief Retrieves the feature index. 
			*/
			inline NxU32  getFeatureIndex0()					{return mIterator->getFeatureIndex0();}


			/** \brief Retrieves the feature index. 
			*/ 
			inline NxU32  getFeatureIndex1()					{return mIterator->getFeatureIndex1();}
 
			/** \brief  Retrieves the point normal force. 
			*/
			inline NxReal  getPointNormalForce()				{return mIterator->getPointNormalForce();}

		protected:

			void parse();

		private:
			
			NxContactStreamIterator* mIterator;
			
	};

};

#endif
