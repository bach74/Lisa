// =============================================================================
//  actuatorDCMotor.h   version:  1.0
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
//
// =============================================================================
#pragma once

#include "rk4solver.h"
#include "actuator.h"
#include "controllerPID.h"


// TODO rewrite completely - as of now this class is USELESS
// actuator DC-> DC_torqu, DC_current, DC_vel
class ActuatorDCMotor: public Actuator, public func
{
		enum {CURRENT = 0, CURRENT_HALL_SENSOR, THETA};

	public:

		ActuatorDCMotor(Joint* node, ControllerPID* controllerCurrent, ControllerPID* controllerPosition, eControlType type);

		virtual ~ActuatorDCMotor();

		
		/**-------------------------------------------------------------------------------
			Motor model calculations
		--------------------------------------------------------------------------------*/
		std::vector<double> operator()(std::vector<double>& x, double tttt);

	private:

		/**-------------------------------------------------------------------------------
			Update actuator internal values and states.
			Should be done each time sampling interval.

			\param      sample_time
			\return controller output
		--------------------------------------------------------------------------------*/
		virtual void update(double current_time, double sample_time);

		double Ra;          // armature resistance (Ohm)
		double La;          // inductance (H)
		double Ke;          // speed constant (V/rad/s)
		double Kt;          // torque constant (Nm/A)
		double J;           // rotor inertia    (kgm^2)
		double b;           // speed/torque gradient (Nm/rad/s)
		double Tf;          // current filter constant (s)
		double T_ext;       // external torque      (Nm)
		double U_ci;        // current regulator set-point  (V)
		double N;           // gear reduction ratio

		ControllerPID* mCurrentPID;         // add 2nd controller (current)
		ControllerPID* mPositionPID;        // add 3rd controller (position)

		RK4solver mSolver;
		eControlType mControlType;
		std::vector<double> mState_motor;   // state-space vector
};

