#include "StdAfx.h"
#include <cfixcc.h>

// mock class
class Simulation
{
};

#include "sensor.h"
#include "sensorDecorator.h"

class SensorTest : public cfixcc::TestFixture
{
	private:
		template <typename T>
		class MySensor : public Sensor<T>
		{
			public:
				MySensor(Simulation* s, const std::string& name):Sensor(s,name){};
			void update() {};
		};

		template <typename T>
		class MySensorDecorator : public SensorDecorator<T> {
		public:
			MySensorDecorator(Sensor* s):SensorDecorator(s){};
			void update() {};
		};

	public:
		void Test()
		{

			std::vector<double> v1;
			v1.push_back(1.444);
			v1.push_back(9.999);
			std::vector<double> v2=v1;

			CFIX_LOG("%d",&v1);
			CFIX_LOG("%d",&v2);

			MySensor<std::vector<double> >* sensor = new MySensor<std::vector<double> >(NULL,"test");

			std::vector<double>* val= new std::vector<double>();
			val->push_back(1);
			val->push_back(2);
			val->push_back(3.33);
			sensor->setValue(*val);
			delete val;
			val=NULL;

			std::vector<double> val2;
			sensor->getValue(val2);

			CFIXCC_ASSERT_EQUALS(3,(int)val2.size());
			CFIXCC_ASSERT_EQUALS(1.0, val2[0]);
			CFIXCC_ASSERT_EQUALS(2.0, val2[1]);
			CFIXCC_ASSERT_EQUALS(3.33, val2[2]);

			CFIXCC_ASSERT_EQUALS("test", sensor->getSensorName().c_str());

			delete sensor;
		}

		void TestDecorator() 
		{
			MySensor<std::vector<double> >* sensor = new MySensor<std::vector<double> >(NULL,"test");
			MySensorDecorator<std::vector<double> >* sensorDecorator = new MySensorDecorator<std::vector<double> >(sensor);

			std::vector<double> val(3);
			val[0]=1;
			val[1]=2;
			val[2]=3.33;
			sensor->setValue(val);

			std::vector<double> val2;
			sensorDecorator->getValue(val2);

			CFIXCC_ASSERT_EQUALS(3,(int)val2.size());
			CFIXCC_ASSERT_EQUALS(1.0, val2[0]);
			CFIXCC_ASSERT_EQUALS(2.0, val2[1]);
			CFIXCC_ASSERT_EQUALS(3.33, val2[2]);

			CFIXCC_ASSERT_EQUALS("test", sensorDecorator->getSensorName().c_str());

			delete sensorDecorator;
		}
};

CFIXCC_BEGIN_CLASS(SensorTest)
	CFIXCC_METHOD(Test)
	CFIXCC_METHOD(TestDecorator)
CFIXCC_END_CLASS()

