#include "StdAfx.h"
#include <cfixcc.h>
#include "jfuzzyqt.h"
#include <math.h>

class FuzzySingleton : public cfixcc::TestFixture
{
	private:

	public:

		static void SetUp()
		{
			AllocConsole();   // Create a new console window
			freopen("CONIN$","rb",stdin);   // reopen stdin handle as console window input
			freopen("CONOUT$","wb",stdout);  // reopen stout handle as console window output
			freopen("CONOUT$","wb",stderr); // reopen stderr handle as console window output
			fprintf(stderr,"Starting test...");
		}

		static void TearDown()
		{
			FreeConsole();  // Close the console window
		}

		void Test() {
			QString filePathFCL("E:\\development\\fuzzy\\jfuzzyqt-src-1.08\\fcl\\singleton.fcl");
			jfuzzyqt::JFuzzyQt model;
			model.load(filePathFCL);			

			model.setVariable("xpos", -0.5);
			model.evaluate();
			double result = model.getValue("uc");

			CFIXCC_LOG("%f", result);
		}
};

CFIXCC_BEGIN_CLASS(FuzzySingleton)
	CFIXCC_METHOD(Test)
CFIXCC_END_CLASS()

