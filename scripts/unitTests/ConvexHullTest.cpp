#include "StdAfx.h"
#include <cfixcc.h>
#include "math\ConvexHullGraham.h"
#include <math.h>

#define eps 1e-6f

class ConvexHullTest : public cfixcc::TestFixture
{
	private:

	public:
		void Test()
		{
			std::vector<Ogre::Vector3> points;

			float x[4] = {1, 1, -1, -1};
			float y[4] = {1, -1, -1, 1};

			for (int i = 0; i < 4; ++i)
			{
				points.push_back(Ogre::Vector3(x[i], 0, y[i]));
			}

			ConvexHullGraham g(points);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			CFIXCC_ASSERT_LESS(fabs(1 - ret[0].x), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[0].z), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[1].x), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[1].z), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[2].x), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[2].z), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[3].x), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[3].z), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[4].x), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[4].z), eps);


			float xd=g.getMinDistanceX(Ogre::Vector3(1,0,1),Ogre::Vector3(-1,0,1), Ogre::Vector3(0.5f,0,0.2f));
			xd=g.getMinDistanceX(Ogre::Vector3(-1,0,-1),Ogre::Vector3(-1,0,1), Ogre::Vector3(-1,0,0));

			Ogre::Vector3 p = Ogre::Vector3(0.0f, 0.0f, 0.0f);

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getDistanceToPointSquared(ret[i], ret[i+1], p);
				CFIXCC_ASSERT_EQUALS(dist, 1.0f);
			}

			std::vector<float> distancesX;
			std::vector<float> distancesY;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getMinDistanceX(ret[i], ret[i+1], p);
				distancesX.push_back(dist);
				dist = g.getMinDistanceY(ret[i], ret[i+1], p);
				distancesY.push_back(dist);
			}

			std::sort(distancesX.begin(), distancesX.end());
			CFIXCC_ASSERT_EQUALS(fabs(distancesX[0]), 1.0f);
			std::sort(distancesY.begin(), distancesY.end());
			CFIXCC_ASSERT_EQUALS(fabs(distancesY[0]), 1.0f);

			Ogre::Vector3 b=g.getCenter(ret);
			CFIXCC_ASSERT_EQUALS(b.x,0.0f);
			CFIXCC_ASSERT_EQUALS(b.y,0.0f);

			// distanceX and distanceY are at a center so
			// we assume largest ones
			Ogre::Vector3 mCenter=g.getMargins(ret,b);
			if (mCenter.x<0) mCenter.x=-mCenter.x;
			if (mCenter.z<0) mCenter.z=-mCenter.z;
			Ogre::Vector3 mPoint1=g.getMargins(ret,Ogre::Vector3(0.5f,0,0.2f));

			CFIXCC_ASSERT_EQUALS(mPoint1.x/mCenter.x,0.5f);
			CFIXCC_ASSERT_EQUALS(mPoint1.z/mCenter.z,0.8f);
		}

		void Test2()
		{
			std::vector<Ogre::Vector3> points;

			float x[4] = {1, 0, -1, 0};
			float y[4] = {0, 1, 0, -1};

			for (int i = 0; i < 4; ++i)
			{
				points.push_back(Ogre::Vector3(x[i], 0, y[i]));
			}

			ConvexHullGraham g(points);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			CFIXCC_ASSERT_LESS(fabs(1 - ret[0].x), eps);
			CFIXCC_ASSERT_LESS(fabs(0 - ret[0].z), eps);
			CFIXCC_ASSERT_LESS(fabs(0 - ret[1].x), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[1].z), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[2].x), eps);
			CFIXCC_ASSERT_LESS(fabs(0 - ret[2].z), eps);
			CFIXCC_ASSERT_LESS(fabs(0 - ret[3].x), eps);
			CFIXCC_ASSERT_LESS(fabs(-1 - ret[3].z), eps);
			CFIXCC_ASSERT_LESS(fabs(1 - ret[4].x), eps);
			CFIXCC_ASSERT_LESS(fabs(0 - ret[4].z), eps);

			Ogre::Vector3 p = Ogre::Vector3(0.5f, 0.0f, 0.5f);

			std::vector<float> distances;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getDistanceToPointSquared(ret[i], ret[i+1], p);
				distances.push_back(dist);
			}

			std::sort(distances.begin(), distances.end());
			CFIXCC_ASSERT_EQUALS(distances[0], 0.0f);

			std::vector<float> distancesX;
			std::vector<float> distancesY;
			p = Ogre::Vector3(0.0f, 0.0f, 0.0f);

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getMinDistanceX(ret[i], ret[i+1], p);
				CFIXCC_ASSERT_EQUALS(fabs(dist), 1.0f);
				dist = g.getMinDistanceY(ret[i], ret[i+1], p);
				CFIXCC_ASSERT_EQUALS(fabs(dist), 1.0f);
			}


			Ogre::Vector3 b = g.getCenter(ret);
			CFIXCC_ASSERT_EQUALS(b.x,0.0f);
			CFIXCC_ASSERT_EQUALS(b.y,0.0f);

		}

		void Test3()
		{
			std::vector<Ogre::Vector3> points;

			float x[4] = {2, 0, -2, 0};
			float y[4] = {0, 1, 0, -1};

			for (int i = 0; i < 4; ++i)
			{
				points.push_back(Ogre::Vector3(x[i], 0, y[i]));
			}

			ConvexHullGraham g(points);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			Ogre::Vector3 p = Ogre::Vector3(1.0f, 0.0f, 0.0f);

			std::vector<float> distances;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getDistanceToPointSquared(ret[i], ret[i+1], p);
				distances.push_back(dist);
			}

			std::sort(distances.begin(), distances.end());
			CFIXCC_ASSERT_EQUALS(distances[0], 0.2f);

			std::vector<float> distancesX;
			std::vector<float> distancesY;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getMinDistanceX(ret[i], ret[i+1], p);
				distancesX.push_back(dist);
				dist = g.getMinDistanceY(ret[i], ret[i+1], p);
				distancesY.push_back(dist);
			}

			CFIXCC_ASSERT_EQUALS(distancesX[0], 1.0f);
			CFIXCC_ASSERT_EQUALS(distancesY[0], 0.5f);

			Ogre::Vector3 b=g.getCenter(ret);
			CFIXCC_ASSERT_EQUALS(b.x,0.0f);
			CFIXCC_ASSERT_EQUALS(b.y,0.0f);
		}


		void Test4()
		{

			std::vector<Ogre::Vector3> points;

			float x[4] = { -6.3951168f, -6.3851147f, -1.5870258f, -1.5970277f};
			float y[4] = {5.3782315f, -2.3468137f, -2.3406014f, 5.3844428f};

			for (int i = 0; i < 4; ++i)
			{
				points.push_back(Ogre::Vector3(x[i], 0, y[i]));
			}

			ConvexHullGraham g(points);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			Ogre::Vector3 p = Ogre::Vector3(-4.6299214f, 0, 2.9168518f);

			std::vector<float> distancesX;
			std::vector<float> distancesY;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getMinDistanceX(ret[i], ret[i+1], p);
				distancesX.push_back(dist);
				dist = g.getMinDistanceY(ret[i], ret[i+1], p);
				distancesY.push_back(dist);
			}

			// get margins
			float minDistanceX = FLT_MAX;
			float minDistanceZ = FLT_MAX;

			for (size_t i = 0; i < ret.size() - 1; ++i)
			{
				float dist = g.getMinDistanceX(ret[i], ret[i+1], p);

				if (fabs(dist) < fabs(minDistanceX)) { minDistanceX = dist; }

				dist = g.getMinDistanceY(ret[i], ret[i+1], p);

				if (fabs(dist) < fabs(minDistanceZ)) { minDistanceZ = dist; }
			}

			CFIXCC_ASSERT_EQUALS(minDistanceX, -1.7620084f);
			CFIXCC_ASSERT_EQUALS(minDistanceZ, 2.4636648f);
		}

		void Test5()
		{
			Ogre::Vector3 points[4] = {Ogre::Vector3(1.0, 0.0, 0.0), Ogre::Vector3(3.0, 0.0, 2.0), Ogre::Vector3(1.0, 0.0, 2.0), Ogre::Vector3(0.0, 0.0, 1.0)};
			std::vector<Ogre::Vector3> polygon;
			for (int i=0;i<4;++i) {
				polygon.push_back(points[i]);
			}

			ConvexHullGraham g(polygon);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			Ogre::Vector3 b=g.getCenter(ret);
			CFIXCC_ASSERT_LESS(b.x-1.33333333333333,1e-6);
			CFIXCC_ASSERT_LESS(b.y-1.22222222222222,1e-6);

		}

		void Test6()
		{
			Ogre::Vector3 points[2] = {Ogre::Vector3(1.0, 0.0, -1.0), Ogre::Vector3(-1.0, 0.0, -1.0)};
			std::vector<Ogre::Vector3> polygon;
			for (int i=0;i<2;++i) {
				polygon.push_back(points[i]);
			}

			ConvexHullGraham g(polygon);

			g.partition_points();
			std::vector<Ogre::Vector3> ret = g.build_hull();

			Ogre::Vector3 b=g.getCenter(ret);
			CFIXCC_ASSERT_EQUALS(b,Ogre::Vector3(0,0,-1));
			g.getMargins(ret,Ogre::Vector3(0,0,-1));
		}
};

CFIXCC_BEGIN_CLASS(ConvexHullTest)
	CFIXCC_METHOD(Test)
	CFIXCC_METHOD(Test2)
	CFIXCC_METHOD(Test3)
	CFIXCC_METHOD(Test4)
	CFIXCC_METHOD(Test5)
	CFIXCC_METHOD(Test6)
CFIXCC_END_CLASS()

