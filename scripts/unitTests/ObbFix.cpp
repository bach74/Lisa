#include "StdAfx.h"
#include <cfixcc.h>
#include "FloatMath.h"

#pragma warning(disable:4996)

#define TEST_COUNT 64

class ObbFix : public cfixcc::TestFixture
{
	private:

		float ranf(void)
		{
			int v = rand() & 0x32767;
			float fv = (float)v * (1.0f / 32767.0f);
			return fv;
		}

		class Vec3
		{
			public:
				Vec3(float x=0,float y=0,float z=0):x(x),y(y),z(z){}

				float x;
				float y;
				float z;
		};

		class Quat
		{
			public:
				float x;
				float y;
				float z;
				float w;
		};

	public:
		void Test1()
		{
			Vec3 points[TEST_COUNT];
			float matrix[16];
			Quat quat;
			fm_eulerToQuat(1, 0, 0, &quat.x);
			fm_quatToMatrix(&quat.x, matrix);

			for (int i = 0; i < TEST_COUNT; i++)
			{
				Vec3 v;
				v.x = ranf();
				v.y = ranf();
				v.z = ranf();

				Vec3 t;
				fm_transform(matrix, &v.x, &t.x);

				points[i] = t;

			}

			Vec3 sides;

			fm_computeBestFitOBB(TEST_COUNT, &points[0].x, sizeof(Vec3), &sides.x, matrix, true);

//			CFIXCC_LOG("Sides: %0.4f,%0.4f,%0.4f", sides.x, sides.y, sides.z);
		}

		void Test2()
		{
			CFIXCC_LOG("Test2-------------------");

			Vec3 points[4];
			points[0]=Vec3(1,1,0);			
			points[1]=Vec3(-1,1,0);
			points[2]=Vec3(-1,-1,0);
			points[3]=Vec3(1,-1,0);

			Vec3 sides;
			float matrix[16];

			fm_computeBestFitOBB(4, &points[0].x, sizeof(Vec3), &sides.x, matrix, true);

			CFIXCC_LOG("Sides: %0.4f,%0.4f,%0.4f", sides.x, sides.y, sides.z);
			for (int i=0;i<4;++i) {
				CFIXCC_LOG("Matrix: %0.4f %0.4f %0.4f %0.4f", matrix[0+i], matrix[4+i], matrix[8+i], matrix[12+i]);
			}

		}

		void Test3()
		{
			CFIXCC_LOG("Test3-------------------");

			Vec3 points[4];
			points[0]=Vec3(1,0,1);			
			points[1]=Vec3(-1,0,1);
			points[2]=Vec3(-1,0,-1);
			points[3]=Vec3(1,0,-1);

			Vec3 sides;
			float matrix[16];

			fm_computeBestFitOBB(4, &points[0].x, sizeof(Vec3), &sides.x, matrix, true);

			CFIXCC_LOG("Sides: %0.4f,%0.4f,%0.4f", sides.x, sides.y, sides.z);
			for (int i=0;i<4;++i) {
				CFIXCC_LOG("Matrix: %0.4f %0.4f %0.4f %0.4f", matrix[0+i], matrix[4+i], matrix[8+i], matrix[12+i]);
			}

		}

		void Test4()
		{
			CFIXCC_LOG("Test4-------------------");

			Vec3 points[4];
			points[0]=Vec3(1,0,0);			
			points[1]=Vec3(0,1,0);
			points[2]=Vec3(-1,0,0);
			points[3]=Vec3(0,-1,0);

			Vec3 sides;
			float matrix[16];

			fm_computeBestFitOBB(4, &points[0].x, sizeof(Vec3), &sides.x, matrix, true);

			CFIXCC_LOG("Sides: %0.4f,%0.4f,%0.4f", sides.x, sides.y, sides.z);
			for (int i=0;i<4;++i) {
				CFIXCC_LOG("Matrix: %0.4f %0.4f %0.4f %0.4f", matrix[0+i], matrix[4+i], matrix[8+i], matrix[12+i]);
			}

		}

		void Test5()
		{
			CFIXCC_LOG("Test5-------------------");

			Vec3 points[4];
			points[0]=Vec3(2,1,0);			
			points[1]=Vec3(1,2,0);
			points[2]=Vec3(0,1,0);
			points[3]=Vec3(1,0,0);

			Vec3 sides;
			float matrix[16];

			fm_computeBestFitOBB(4, &points[0].x, sizeof(Vec3), &sides.x, matrix, true);

			CFIXCC_LOG("Sides: %0.4f,%0.4f,%0.4f", sides.x, sides.y, sides.z);
			for (int i=0;i<4;++i) {
				CFIXCC_LOG("Matrix: %0.4f %0.4f %0.4f %0.4f", matrix[0+i], matrix[4+i], matrix[8+i], matrix[12+i]);
			}
		}
};

CFIXCC_BEGIN_CLASS(ObbFix)
	CFIXCC_METHOD(Test1)
	CFIXCC_METHOD(Test2)
	CFIXCC_METHOD(Test3)
	CFIXCC_METHOD(Test4)
	CFIXCC_METHOD(Test5)
CFIXCC_END_CLASS()

