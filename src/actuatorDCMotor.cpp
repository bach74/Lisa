#include "stdafx.h"
#include "actuatorDCMotor.h"
#include "config.h"


/**-------------------------------------------------------------------------------
	ctor
	initialize structures
--------------------------------------------------------------------------------*/
ActuatorDCMotor::ActuatorDCMotor(Joint* node, ControllerPID* controllerCurrent, ControllerPID* controllerPosition, eControlType type) : Actuator(node, NULL)
{
	// state-space vector
	mState_motor.push_back(0.0);            // I
	//mState_motor.push_back(0.0);      // omega
	mState_motor.push_back(0.0);            // Ihs
	mState_motor.push_back(0.0);            // theta

	J = 1.35e-5;       // kgm^2
	b = 1.1478e-3;     // Nm/(rad/s)
	Kt = 33.5e-3;      // Nm/A
	Ra = 0.978;        // Ohm
	La = 0.573e-3;     // H
	Ke = 0.0335;       // V/(rad/s)
	Tf = 1e-3;         // ms
	N = 120;           // gear reduction ratio

	// create motor
	T_ext = 0;
	U_ci = 0;

	// current regulator
	mCurrentPID = controllerCurrent;
	mPositionPID = controllerPosition;

	//mCurrentPID=new controllerPID(0.5,0.01,0,15);
	//velocityPID=new controllerPID(0.003,0.05,1.667e-4,15*Kt);
	//torquePID=new controllerPID(0.01,1e-5,0,15*Kt);

	// controller type. Default is velocity control
	mControlType = type;
}

/**-------------------------------------------------------------------------------
	dtor
	clear all structures and release the memory
--------------------------------------------------------------------------------*/
ActuatorDCMotor::~ActuatorDCMotor()
{
	delete mPositionPID;
	mPositionPID = NULL;
	delete mCurrentPID;
	mCurrentPID = NULL;
}

/**-------------------------------------------------------------------------------
	Motor model calculations
--------------------------------------------------------------------------------*/
std::vector<double> ActuatorDCMotor::operator()(std::vector<double>& x, double tttt)
{
	double I = x[CURRENT];
	//double omega=x[OMEGA];
	double omega = mController->getInput(0);
	double Ihs = x[CURRENT_HALL_SENSOR];
	//double theta=x[THETA];
	//double theta=getInput(1);

	std::vector<double> res;
	res.push_back(1 / La*(-Ra * I - Ke * omega + U_ci));
	//res.push_back(1/J*(Kt*I-b*omega+T_ext));
	res.push_back(1 / Tf*(I - Ihs));
	res.push_back(omega);

	return res;
}

/**-------------------------------------------------------------------------------
	Update actuator internal values and states.
	Should be done each time sampling interval.

	\param      sample_time
	\return controller output
--------------------------------------------------------------------------------*/
void ActuatorDCMotor::update(double current_time, double sample_time)
{
	// TODO
	if (mJoint->getType() == NX_JOINT_REVOLUTE)
	{
		double SP = mController->getSetpoint(0);
		double omega = mController->getInput(0) * N;
		double theta = mController->getInput(1);

		if (Config::Instance().getLoggingControllers())
		{
			mLogBuffer << std::fixed
					   << current_time << "\t"
					   << mState_motor[CURRENT] << "\t"
					   << omega << "\t"
					   << mState_motor[CURRENT_HALL_SENSOR] << "\t"
					   << mState_motor[THETA] << "\t"
					   << SP << "\t"
					   << theta;
		}

		// calculate velocity reference
		double velSP = SP;

		if (mControlType == POSITION_CONTROL)
		{
			velSP = mPositionPID->calculate(SP - theta, sample_time);
		}

		// sample time for the model
		double Ts = 1e-3;

		for (double time = 0; time < sample_time; time += Ts)
		{
			// calculate reference current (set-point) (A)
			double I_ref = (mControlType != TORQUE_CONTROL) ? 1 / Kt * mController->calculate(velSP - omega / N, Ts) : 1 / Kt * mController->calculate(SP - mState_motor[CURRENT_HALL_SENSOR] * Kt, Ts);
			U_ci = mCurrentPID->calculate(I_ref - mState_motor[CURRENT_HALL_SENSOR], Ts);
			mSolver.solve(Ts, mState_motor, time, *this);
		}

		// calculate torque (input to the mechanical part)
		double Uc = mState_motor[0] * Kt;

		// make sure that actor1 has following set
		//revDesc.actor[1]->setAngularDamping(1);
		//revDesc.actor[1]->setMaxAngularVelocity(700);

		NxRevoluteJointDesc revDesc;
		((NxRevoluteJoint*)mJoint)->saveToDesc(revDesc);
		// apply torque to the motor
		NxVec3 t = revDesc.localAxis[1] * Uc * N;
		revDesc.actor[1]->addLocalTorque(-t / 2, NX_SMOOTH_VELOCITY_CHANGE);
		t = revDesc.localAxis[0] * Uc * N;
		revDesc.actor[0]->addLocalTorque(t / 2, NX_SMOOTH_VELOCITY_CHANGE);

		if (Config::Instance().getLoggingControllers())
		{
			mLogBuffer << std::fixed << "\t" << Uc << "\t" << t.x << "\t" << t.y << "\t" << t.z << std::endl;
		}
	}
}
