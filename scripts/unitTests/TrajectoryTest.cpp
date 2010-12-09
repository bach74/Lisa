#include "StdAfx.h"
#include <cfixcc.h>
#include <boost/shared_ptr.hpp>
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

// mock classes
typedef float NxReal;
class NxJointDesc;
class NxJointType{};
class NxVec3 {
public:
	NxVec3(){};
	NxVec3(double,double,double){}
	NxVec3 operator*(double){return NxVec3();}
};
class NxActor {
public:
	void addForce(NxVec3,int){};
};

class NxD6JointDesc {
	public:
	struct TwistDrive {
		int driveType;
	} twistDrive;
	NxActor** actor;
};
const int NX_D6JOINT_DRIVE_POSITION	= 1<<0;
const int NX_D6JOINT_DRIVE_VELOCITY	= 1<<1;

enum NxForceMode {
	NX_IMPULSE,
	NX_FORCE
};

class Exception {
public:
	Exception(std::string, std::string){};
};
class NxJoint {
public:
	NxVec3 getGlobalAnchor()	{return NxVec3();}
	NxVec3 getGlobalAxis()		{return NxVec3();}
	NxJointType getType()		{return NxJointType();}
	std::string getName()		{return mName;}
	void setName(const std::string& name) {mName=name;}
private:
	std::string mName;

};


namespace NxOgre {
	template <typename Type> Type NxFromString(const std::string& s);
	template <> NxVec3 NxFromString<NxVec3>(const std::string& s){return NxVec3();}
}

#include "trajectory.h"
#include "..\src\trajectory.cpp"
#include "..\src\logger.cpp"
#include "..\src\trajectoryQueue.cpp"

Config::Config(){};
Config::~Config(){};


class TrajectoryTest : public cfixcc::TestFixture
{
private:

	// Mock classes
	class MyJoint : public Joint {
		public:
			MyJoint(const std::string& name):Joint(new NxJoint()){mJoint->setName(name);}
			virtual void updateJoint(float sampleTime){}
			virtual void getDesc(NxJointDesc** desc){ *desc=(NxJointDesc*)new NxD6JointDesc();}
			virtual void setDesc(NxJointDesc* desc){}
	};

	class MyController : public Controller<double> {
		public:
			virtual double calculate(double sample_time){return 0;}
			virtual double calculate(double error, double sample_time){return 0;}
	};

	class MyActuator : public Actuator {
		public:
			MyActuator(const std::string& name) : Actuator(new MyJoint(name), new MyController(), NULL){}
			virtual void update(double currentTime, double sampleTime) {}
	};

public:
	/**-------------------------------------------------------------------------------
		Test
		
		@brief
		@return void
	---------------------------------------------------------------------------------*/
	void Test()
	{
		std::vector<boost::shared_ptr<Actuator > > actuators;

		Trajectory* trajectory=new Trajectory("");
		MyActuator myActuator("tibia-ankle");

		trajectory->addQueue(boost::shared_ptr<TrajectoryQueue>(new QueueElementSP(myActuator,1.0,1)));
		trajectory->addQueue(boost::shared_ptr<TrajectoryQueue>(new QueueElementSP(myActuator,2.0,2)));
		trajectory->addQueue(boost::shared_ptr<TrajectoryQueue>(new QueueElementSP(myActuator,1.5,10)));
		trajectory->addQueue(boost::shared_ptr<TrajectoryQueue>(new QueueElementSP(myActuator,0.5,0)));

		trajectory->setTime(1);
		trajectory->update();
	}

	/**-------------------------------------------------------------------------------
		Test2
		
		@brief
		@return void
	---------------------------------------------------------------------------------*/
	void Test2() {
		
		std::vector<boost::shared_ptr<Actuator > > actuators;
		boost::shared_ptr<Actuator> a(new MyActuator("tibia-ankle"));
		actuators.push_back(a);
		boost::shared_ptr<Actuator> a2(new MyActuator("knee-tibia"));
		actuators.push_back(a2);

		SetCurrentDirectory("..\\..\\..\\bin\\Debug");

		Trajectory* trajectory=new Trajectory("resources\\rn101_4_1.dae");
		trajectory->load(actuators);
	}
};

CFIXCC_BEGIN_CLASS(TrajectoryTest)
	CFIXCC_METHOD(Test)
	CFIXCC_METHOD(Test2)
CFIXCC_END_CLASS()

