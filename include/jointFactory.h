#pragma once
#include "joint.h"

class JointFactory
{
	public:
		static Joint* createJoint(NxJoint* joint);
		~JointFactory(void);
	private:
		JointFactory();
};
