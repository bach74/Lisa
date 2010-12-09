#pragma once

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

	private:
		Config(void);

		bool mShowForces;
		bool mShowZMP;
		bool mShowCOG;
		bool mShowCOP;
		bool mShowFRI;
		bool mLoggingSensors;
		bool mLoggingControllers;
		bool mKeepAlive;
		bool mControllerZMP;
		bool mSelectedObjectGlows;

		float mVisualDebugScale;
		float mDrawingScaleCOG;
		float mDrawingScaleCOP;
		float mDrawingScaleZMP;
		float mDrawingScaleFRI;
		float mCameraZoomSpeed;
		float mCameraRotateSpeed;
		float mCameraTranslateSpeed;
		float mActuatorSteppingTime;
};
