// =============================================================================
//  LisaCOMController.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOMController.h"
#include "SimFacade.h"
#include "conversion.h"

/**-------------------------------------------------------------------------------
	Get version
	\params BSTR version
	\return HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getVersion(BSTR* version)
{
	CComBSTR v="version 1.2";
	*version=v.Detach();

	return S_OK;
}

/**-------------------------------------------------------------------------------
	Get total number of available actuators
	\param pVal	returns pVal number of actuators implemented
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::get_number(SHORT* pVal)
{
	*pVal=SimFacade::Instance().getControllerNum();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	Get parameters of the actuator. The parameters can be PID gains, or
	any other generic parameters contained in the SAFEARRAY. Client should be 
	responsible for interpreting the results.

	\param i		i-th actuator 
	\param params	return VARIANT(SAFEARRAY) of actuator parameters
	\return		HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getParameters(USHORT i, VARIANT* params)
{
	std::vector<double> vectParams = SimFacade::Instance().getActuatorParams(i);
	SAFEARRAY* sa=new SAFEARRAY();
	Conversion::vector2SAFEARRAY(vectParams,&sa);
	CComVariant v(sa);
	v.Detach(params);

	return S_OK;
}

/**-------------------------------------------------------------------------------
	Set parameters of the actuator. The parameters can be PID gains, or
	any other generic parameters contained in the SAFEARRAY. Client should be 
	responsible for interpreting the results.

	\param i		i-th actuator 
	\param params	VARIANT(SAFEARRAY) of actuator parameters
	\return		HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::setParameters(USHORT i, VARIANT* params)
{
	SAFEARRAY* sa=params->parray;
	std::vector<double> vectParams;
	Conversion::SAFEARRAY2vector(*sa,vectParams);
	SimFacade::Instance().setActuatorParams(i, vectParams);	

	return S_OK;
}

/**-------------------------------------------------------------------------------
	Set one parameter of the actuator. The parameter can be PID gains, or
	any other generic parameters contained in the SAFEARRAY. Client should be 
	responsible for interpreting the results.

	\param i		i-th actuator 
	\param params	VARIANT(SAFEARRAY) of actuator parameters
	\return		HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::setParameter(USHORT i, USHORT nParam, DOUBLE val)
{
	SimFacade::Instance().setActuatorParam(i, nParam, val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator position

	\param i	i-th actuator 
	\param pVal	returned position (angle)
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getPosition(USHORT i, DOUBLE* pVal)
{
	*pVal=SimFacade::Instance().getJointAngle(i);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	set i-th actuator reference

	\param i		i-th actuator 
	\param numRef	numRef-th actuator 
	\param Val		set-point
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::setReference(USHORT i, USHORT numRef, DOUBLE Val)
{
	SimFacade::Instance().setJointSetpoint(i,numRef,Val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator reference

	\param i		i-th actuator 
	\param numRef	i-th actuator 
	\param retVal	returned reference value
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getReference(USHORT i, USHORT numRef, DOUBLE* retVal)
{
	*retVal=SimFacade::Instance().getJointSetpoint(i,numRef);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator velocity

	\param i	i-th actuator 
	\param pVal	returned velocity 
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getVelocity(USHORT i, DOUBLE* pVal)
{ 
	*pVal=SimFacade::Instance().getJointVelocity(i);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator torque

	\param i	i-th actuator 
	\param pVal	returned velocity 
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getTorque(USHORT i, DOUBLE* pVal)
{ 	
	*pVal=SimFacade::Instance().getJointTorque(i);
	return S_OK;	
}
