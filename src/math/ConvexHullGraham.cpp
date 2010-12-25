// =============================================================================
//  ConvexHullGraham.cpp   version:  1.5
//  
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "math\ConvexHullGraham.h"
#include <float.h>
#include <math.h>

ConvexHullGraham::ConvexHullGraham(const std::vector<Ogre::Vector3>& points)
{
	mRawPoints = points;
}


/**-------------------------------------------------------------------------------
    partition_points

     The initial array of points is stored in vector mRawPoints. I first
     sort it, which gives me the far left and far right points of the hull.
     These are special values, and they are stored off separately in the left
     and right members.

     I then go through the list of mRawPoints, and one by one determine whether
     each point is above or below the line formed by the right and left points.
     If it is above, the point is moved into the mUpperPartitionPoints sequence. If it
     is below, the point is moved into the mLowerPartitionPoints sequence. So the output
     of this routine is the left and right points, and the sorted points that are in the
     upper and lower partitions.

    @brief
    @return void
---------------------------------------------------------------------------------*/
void ConvexHullGraham::partition_points()
{
	//
	// Step one in partitioning the points is to sort the raw data
	//
	std::sort(mRawPoints.begin(), mRawPoints.end());
	//
	// The the far left and far right points, remove them from the
	// sorted sequence and store them in special members
	//
	left = mRawPoints.front();
	mRawPoints.erase(mRawPoints.begin());
	right = mRawPoints.back();
	mRawPoints.pop_back();

	//
	// Now put the remaining points in one of the two output sequences
	//
	for (size_t i = 0 ; i < mRawPoints.size(); i++)
	{
		float dir = direction(left, right, mRawPoints[i]);

		if (dir < 0)
		{
			mUpperPartitionPoints.push_back(mRawPoints[i]);
		}
		else
		{
			mLowerPartitionPoints.push_back(mRawPoints[i]);
		}
	}
}


/**-------------------------------------------------------------------------------
    build_hull

    Building the hull consists of two procedures: building the lower and
    then the upper hull. The two procedures are nearly identical - the main
    difference between the two is the test for convexity. When building the upper
    hull, our rule is that the middle point must always be *above* the line formed
    by its two closest neighbors. When building the lower hull, the rule is that point
    must be *below* its two closest neighbors. We pass this information to the
    building routine as the last parameter, which is either -1 or 1.

    @brief
    @return std::vector<Ogre::Vector3>
---------------------------------------------------------------------------------*/
std::vector<Ogre::Vector3> ConvexHullGraham::build_hull()
{
	build_half_hull(mLowerPartitionPoints, mLowerHull, 1);
	build_half_hull(mUpperPartitionPoints, mUpperHull, -1);

	std::vector<Ogre::Vector3> ret;

	for (size_t i = 0 ; i < mLowerHull.size() ; i++)
	{
		ret.push_back(mLowerHull[i]);
	}

	for (std::vector<Ogre::Vector3>::reverse_iterator ii = mUpperHull.rbegin() + 1;
	        ii != mUpperHull.rend(); ++ii)
	{
		ret.push_back(*ii);
	}

	return ret;
}

/**-------------------------------------------------------------------------------
    build_half_hull

    This is the method that builds either the upper or the lower half convex
    hull. It takes as its input a copy of the input array, which will be the
    sorted list of points in one of the two halfs. It produces as output a list
    of the points in the corresponding convex hull.

    The factor should be 1 for the lower hull, and -1 for the upper hull.

    @brief
    @param input
    @param output
    @param factor
    @return void
---------------------------------------------------------------------------------*/
void ConvexHullGraham::build_half_hull(std::vector<Ogre::Vector3> input,
                                       std::vector<Ogre::Vector3>& output, float factor)
{
	//
	// The hull will always start with the left point, and end with the right
	// point. According, we start by adding the left point as the first point
	// in the output sequence, and make sure the right point is the last point
	// in the input sequence.
	//
	input.push_back(right);
	output.push_back(left);

	//
	// The construction loop runs until the input is exhausted
	//
	while (input.size() != 0)
	{
		//
		// Repeatedly add the leftmost point to the null, then test to see
		// if a convexity violation has occurred. If it has, fix things up
		// by removing the next-to-last point in the output sequence until
		// convexity is restored.
		//
		output.push_back(input.front());
		input.erase(input.begin());

		while (output.size() >= 3)
		{
			size_t end = output.size() - 1;

			if (factor * direction(output[ end - 2 ],
			                       output[ end ],
			                       output[ end - 1 ]) <= 0)
			{
				output.erase(output.begin() + end - 1);
			}
			else
			{
				break;
			}
		}
	}
}

/**-------------------------------------------------------------------------------
    getDistanceToPointSquared

    calculate point's p distance from line SEGMENT. Does not treat the line segment
    from point A to point B as an (infinite) line.

    @param A
    @param B
    @param p
    @return float
---------------------------------------------------------------------------------*/
float ConvexHullGraham::getDistanceToPointSquared(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p)
{
	float vx = A.x - p.x;
	float vy = A.z - p.z;
	float ux = B.x - A.x;
	float uy = B.z - A.z;
	float length = ux * ux + uy * uy;

	// if this is < 0 or > length then its outside the line segment
	float det = (-vx * ux) + (-vy * uy);

	if ((det < 0) || (det > length))
	{
		ux = B.x - p.x;
		uy = B.z - p.z;
		return std::min<float>(vx * vx + vy * vy, ux * ux + uy * uy);
	}

	det = ux * vy - uy * vx;
	return (det * det) / length;
}

/**-------------------------------------------------------------------------------
    getMinDistanceX

    return Euclidean grid distance x, between two points

    @brief
    @param A
    @param B
    @param p
    @return float
---------------------------------------------------------------------------------*/
float ConvexHullGraham::getMinDistanceX(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p)
{
	float ret=0;
	float x21 = B.x - A.x;
	float z21 = B.z - A.z;
	float z01 = p.z - A.z;

	if (fabs(z21) > 1e-9) {
		ret=z01 * x21 / z21 - p.x + A.x;
	} else {
		if ((fabs(B.z-A.z)<1e-9)&&(fabs(B.z-p.z)>1e-9)) {
			ret=FLT_MAX;
		} else if (fabs(p.x-A.x)<fabs(p.x-B.x)) {
			ret=p.x-A.x;
		} else {
			ret=p.x-B.x;
		}
	}
	return ret;
}

/**-------------------------------------------------------------------------------
    getMinDistanceY

    return Euclidean grid distance y, between two points

    @brief
    @param A
    @param B
    @param p
    @return float
---------------------------------------------------------------------------------*/
float ConvexHullGraham::getMinDistanceY(const Ogre::Vector3& A, const Ogre::Vector3& B, const Ogre::Vector3& p)
{
	float ret=0;
	float x21 = B.x - A.x;
	float z21 = B.z - A.z;
	float x01 = p.x - A.x;

	if (fabs(x21) > 1e-9) {
		ret=x01 * z21 / x21 - p.z + A.z;
	} else {
		if ((fabs(B.x-A.x)<1e-9)&&(fabs(B.x-p.x)>1e-9)) {
			ret=FLT_MAX;
		} else if (fabs(p.z-A.z)<fabs(p.z-B.z)) {
			ret=p.z-A.z;
		} else {
			ret=p.z-B.z;
		}
	}
	return ret;
}

/**-------------------------------------------------------------------------------
    getCenter of the convex hull convexHull as the center of the area
    (triangle summation)

    @brief
    @return Ogre::Vector3
---------------------------------------------------------------------------------*/
Ogre::Vector3 ConvexHullGraham::getCenter(const std::vector<Ogre::Vector3>& convexHull)
{
	Ogre::Vector3 result(0.0, 0.0, 0.0);
	double total_area = 0.0;

	// size-1 because last point should be the same as the first one (for built convex hull)
	for (unsigned i = 0; i < convexHull.size()-1; ++i)
	{
		int j = i % convexHull.size();
		int k = (i + 1) % convexHull.size();
		double triangle_area = 0.5 * (convexHull[j].x * convexHull[k].z - convexHull[j].z * convexHull[k].x);
		total_area += triangle_area;
		// In general, the center (of mass) of any right triangle will be 1/3 of the way out from
		// the right angle along both axis
		Ogre::Vector3 center((convexHull[j].x + convexHull[k].x)*(1.0 / 3.0), 0.0, (convexHull[j].z + convexHull[k].z)*(1.0 / 3.0));
		center = center * triangle_area;
		result = result + center;
	}

	if (total_area==0) {	
		UINT size=convexHull.size()-1;
		// collinear points - calculate center as the average
		for (unsigned i = 0; i < size; ++i)
		{
			result.x+=convexHull[i].x;
			result.z+=convexHull[i].z;
		}
		total_area=size;
	}
	return result/total_area;
}

/**-------------------------------------------------------------------------------
	getMargins (from point p)
	
	@brief
	@param convexHull
	@param p
	@return Ogre::Vector3
---------------------------------------------------------------------------------*/
Ogre::Vector3 ConvexHullGraham::getMargins(const std::vector<Ogre::Vector3>& convexHull, const Ogre::Vector3& p)
{
	Ogre::Vector3 ret(FLT_MAX,0,FLT_MAX);

	for (size_t i = 0; i < convexHull.size() - 1; ++i)
	{
		float dist = getMinDistanceX(convexHull[i], convexHull[i+1], p);
		if (fabs(dist) < fabs(ret.x)) { ret.x= dist; }
		dist = getMinDistanceY(convexHull[i], convexHull[i+1], p);

		if (fabs(dist) < fabs(ret.z)) { ret.z= dist; }
	}

	return ret;
}