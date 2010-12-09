#pragma once

class Joint
{
	public:
		Joint(NxJoint* joint): mJoint(joint), mVelocityPrev(0),mVelocity(0),mAcceleration(0),mAngularMomentumPrev(0),
								mTorque(0),mAngularMomentum(0),mAngle(0){};
		virtual ~Joint(void) {};

		NxVec3 getGlobalAnchor() { return mJoint->getGlobalAnchor(); }
		NxVec3 getGlobalAxis()	 { return mJoint->getGlobalAxis(); }
		NxJointType getType()    { return mJoint->getType(); }
		std::string getName()    { return mJoint->getName(); }
		
		NxReal getAngle() { return mAngle; }
		NxReal getVelocity() { return mVelocity; } 
		NxReal getAcceleration() { return mAcceleration; }
		NxReal getTorque() { return mTorque; }
		NxReal getAngularMomentum() {return mAngularMomentum; }
		
		virtual void	getDesc(NxJointDesc** desc) = 0;
		virtual void	setDesc(NxJointDesc* desc) = 0;

		/// should be called every sample-time step, so all the joint values are calculated 
		/// only once (for performance reasons) and updated so subsequent calls to getAcceleration,
		/// getTorque, getXXX are valid
		virtual void updateJoint(float sampleTime)=0;

	protected:		
		NxJoint* mJoint;
		NxReal mVelocityPrev;	
		NxReal mVelocity;
		NxReal mAcceleration;
		NxReal mTorque;
		NxReal mAngularMomentum;
		NxReal mAngularMomentumPrev;
		NxReal mAngle;
};
