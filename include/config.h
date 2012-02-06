// =============================================================================
//  Config.h   
//
//  Copyright (C) 2007-2012 by Bach
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "singleton.h"

/**-------------------------------------------------------------------------------
	Class that takes care of configuration parameters

---------------------------------------------------------------------------------*/
class Config : public Singleton<Config>
{
	public:
		friend Singleton<Config>;

		~Config(void);

		bool getShowForces() const { return mShowForces; }
		void setShowForces(bool val) { mShowForces = val; }

		bool getShowZMP() const { return mShowZMP; }
		void setShowZMP(bool val) { mShowZMP = val; }

		bool getShowCOG() const { return mShowCOG; }
		void setShowCOG(bool val) { mShowCOG = val; }

		bool getShowCOP() const { return mShowCOP; }
		void setShowCOP(bool val) { mShowCOP = val; }

		bool getShowFRI() const { return mShowFRI; }
		void setShowFRI(bool val) { mShowFRI = val; }

		bool getLoggingControllers() const { return mLoggingControllers; }
		void setLoggingControllers(bool val) { mLoggingControllers = val; }

		bool getLoggingSensors() const { return mLoggingSensors; }
		void setLoggingSensors(bool val) { mLoggingSensors = val; }

		bool getLoggingPositions() const { return mLoggingPositions; }
		void setLoggingPositions(bool val) { mLoggingPositions = val; }
		
		bool getLoggingControllerZMP() const { return mLoggingControllerZMP; }
		void setLoggingControllerZMP(bool val) { mLoggingControllerZMP = val; }

		float getVisualDebugScale() const { return mVisualDebugScale; }
		void setVisualDebugScale(float val) { mVisualDebugScale = val; }

		float getDrawingScaleCOG() const { return mDrawingScaleCOG; }
		void setDrawingScaleCOG(float val) { mDrawingScaleCOG = val; }

		float getDrawingScaleCOP() const { return mDrawingScaleCOP; }
		void setDrawingScaleCOP(float val) { mDrawingScaleCOP = val; }

		float getDrawingScaleZMP() const { return mDrawingScaleZMP; }
		void setDrawingScaleZMP(float val) { mDrawingScaleZMP = val; }

		float getDrawingScaleFRI() const { return mDrawingScaleFRI; }
		void setDrawingScaleFRI(float val) { mDrawingScaleFRI = val; }

		float getCameraZoomSpeed() const { return mCameraZoomSpeed; }
		void setCameraZoomSpeed(float val) { mCameraZoomSpeed = val; }

		float getCameraRotateSpeed() const { return mCameraRotateSpeed; }
		void setCameraRotateSpeed(float val) { mCameraRotateSpeed = val; }

		float getCameraTranslateSpeed() const { return mCameraTranslateSpeed; }
		void setCameraTranslateSpeed(float val) { mCameraTranslateSpeed = val; }

		float getActuatorSteppingTime() const { return mActuatorSteppingTime; }
		void setActuatorSteppingTime(float val) { mActuatorSteppingTime = val; }

		bool getKeepAlive() const { return mKeepAlive; }
		void setKeepAlive(bool val) { mKeepAlive = val; }

		bool getControllerZMP() const { return mControllerZMP; }
		void setControllerZMP(bool val) { mControllerZMP = val; }

		bool getSelectedObjectGlows() const { return mSelectedObjectGlows; }
		void setSelectedObjectGlows(bool val) { mSelectedObjectGlows = val; }

		bool getPhysxEnabled() const { return mPhysXEnabled; }
		void setPhysxEnabled(bool val) { mPhysXEnabled = val; }

		float getPhysicsSampleTime() const { return mPhysicsSamplingTime; }
		void setPhysicsSampleTime(float sampleTime) { mPhysicsSamplingTime = sampleTime; }

		short getRenderEveryNthFrame() const { return mRenderEveryNthFrame; }
		void setRenderEveryNthFrame(short val) { mRenderEveryNthFrame = val; }

	private:
		Config(void);
		bool mShowForces;
		bool mShowZMP;
		bool mShowCOG;
		bool mShowCOP;
		bool mShowFRI;
		bool mKeepAlive;
		bool mControllerZMP;
		bool mSelectedObjectGlows;
		bool mPhysXEnabled;

		float mVisualDebugScale;
		float mDrawingScaleCOG;
		float mDrawingScaleCOP;
		float mDrawingScaleZMP;
		float mDrawingScaleFRI;
		float mCameraZoomSpeed;
		float mCameraRotateSpeed;
		float mCameraTranslateSpeed;
		float mActuatorSteppingTime;

		float mPhysicsSamplingTime;
		short mRenderEveryNthFrame;

		bool mLoggingSensors;
		bool mLoggingControllers;
		bool mLoggingControllerZMP;
		bool mLoggingPositions;
};

#endif