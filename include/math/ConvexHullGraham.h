// =============================================================================
//  ConvexHullGraham.h   
//
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#pragma once

#include <OgreVector3.h>

/**-------------------------------------------------------------------------------
	This class uses the Graham scan algorithm to calculate the convex
	hull of a batch of points in 2D.

	The convex hull part of the code is based on the article from Dr. Dobb's Portal,
	September, 2007 by Mark Nelson

	instead of std::pair<float,float> Ogre::Vector3 is used with implicit y=0 (ground plane),
	that is .x and .z are convex hull vertices 
---------------------------------------------------------------------------------*/
class ConvexHullGraham
{
	public:
		ConvexHullGraham(const std::vector<Ogre::Vector3>& points);
		void partition_points();

		std::vector<Ogre::Vector3> build_hull();
		void build_half_hull(std::vector<Ogre::Vector3> input,
		                     std::vector<Ogre::Vector3>& output, float factor);

		// In this program we frequently want to look at three consecutive
		// points, p0, p1, and p2, and determine whether p2 has taken a turn
		// to the left or a turn to the right.
		//
		// We can do this by by translating the points so that p1 is at the origin,
		// then taking the cross product of p0 and p2. The result will be positive,
		// negative, or 0, meaning respectively that p2 has turned right, left, or
		// is on a straight line.
		static float direction(const Ogre::Vector3& p0, const Ogre::Vector3& p1, const Ogre::Vector3& p2)
		{
			return ((p0.x-p1.x)*(p2.z-p1.z))-((p2.x-p1.x)*(p0.z-p1.z));
		}

		float getDistanceToPointSquared(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p);

		float getMinDistanceX(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p);
		float getMinDistanceY(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p);

		Ogre::Vector3 getCenter(const std::vector<Ogre::Vector3>& convexHull);
		Ogre::Vector3 getMargins(const std::vector<Ogre::Vector3>& convexHull, const Ogre::Vector3& p);

	protected:
		// The raw data points generated by the constructor
		std::vector<Ogre::Vector3> mRawPoints;
		//
		// These values are used to represent the partitioned set. A special
		// leftmost and rightmost value, and the sorted set of upper and lower
		// partitioned points that lie inside those two points.
		//
		Ogre::Vector3 left;
		Ogre::Vector3 right;
		std::vector<Ogre::Vector3> mUpperPartitionPoints;
		std::vector<Ogre::Vector3> mLowerPartitionPoints;
		//
		// After the convex hull is created, the lower hull and upper hull
		// are stored in these sorted sequences. There is a bit of duplication
		// between the two, because both sets include the leftmost and rightmost point.
		//
		std::vector<Ogre::Vector3> mLowerHull;
		std::vector<Ogre::Vector3> mUpperHull;
};
