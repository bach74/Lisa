#include "stdafx.h"
#include <cfixcc.h>
#include "controller.h"

class ControllerTest : public cfixcc::TestFixture
{
	private:

	public:

		// mock
		class MyControllerDouble : public Controller<double> {
		public:
			double calculate(double sample_time){
				mOutput=mSetpoint+mInput;
				return 0;
			};
			double calculate(double error, double sample_time) {
				return calculate(sample_time);
			};
		};

		//mock
		class MyControllerVector : public Controller<std::vector<double> > {
		public:
			MyControllerVector() {
				mOutput.push_back(0);
				mOutput.push_back(0);
				mOutput.push_back(0);
			}
			double calculate(double sample_time){
				for (unsigned int i=0;i<mInput.size();++i) {
					mOutput[i]=mSetpoint[i]+mInput[i];
				}
				return 0;
			};
			double calculate(double error, double sample_time) {
				return calculate(sample_time);
			};
		};
		
		/**-------------------------------------------------------------------------------
			TestValuesDouble
			
			@brief
			@return void
		---------------------------------------------------------------------------------*/
		void TestValuesDouble()
		{

			MyControllerDouble controller;
			
			controller.setSetpoint(10);
			controller.setInput(1);
			controller.calculate(0,0);

			double ret;
			controller.getOutput(ret);
			CFIXCC_ASSERT_EQUALS(11.0,ret);

			controller.getSetpoint(ret);
			CFIXCC_ASSERT_EQUALS(10.0,ret);

			controller.getInput(ret);
			CFIXCC_ASSERT_EQUALS(1.0,ret);

		}		

		/**-------------------------------------------------------------------------------
			TestValuesVector
			
			@brief
			@return void
		---------------------------------------------------------------------------------*/
		void TestValuesVector() 
		{
			MyControllerVector controller;

			std::vector<double> sp;
			std::vector<double>* pv=new std::vector<double>();
			std::vector<double> ret;

			sp.push_back(1);
			sp.push_back(2);
			sp.push_back(3);
			controller.setSetpoint(sp);
			pv->push_back(1);
			pv->push_back(2);
			pv->push_back(10);
			controller.setInput(*pv);
			pv->clear();
			delete pv;
			pv=NULL;

			controller.calculate(0,0);

			controller.getOutput(ret);
			CFIXCC_ASSERT_EQUALS(ret[0],2.0);
			CFIXCC_ASSERT_EQUALS(ret[1],4.0);
			CFIXCC_ASSERT_EQUALS(ret[2],13.0);

			controller.getInput(ret);
			CFIXCC_ASSERT_EQUALS(ret[0],1.0);
			CFIXCC_ASSERT_EQUALS(ret[1],2.0);
			CFIXCC_ASSERT_EQUALS(ret[2],10.0);

			controller.getSetpoint(ret);
			CFIXCC_ASSERT_EQUALS(ret[0],1.0);
			CFIXCC_ASSERT_EQUALS(ret[1],2.0);
			CFIXCC_ASSERT_EQUALS(ret[2],3.0);

		}
};

CFIXCC_BEGIN_CLASS(ControllerTest)
	CFIXCC_METHOD(TestValuesDouble)
	CFIXCC_METHOD(TestValuesVector)
CFIXCC_END_CLASS()

