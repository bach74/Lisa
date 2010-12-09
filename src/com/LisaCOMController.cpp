// =============================================================================
//  LisaCOMController.cpp   version:  1.0
//  
//	Implementation of CLisaCOMController
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOMController.h"
#include "SimFacade.h"

#ifdef _ATL
/**-------------------------------------------------------------------------------
	Convert vector to SAFEARRAY

	\param		vector vect
	\param		SAFEARRAY sa
	\return	nothing
--------------------------------------------------------------------------------*/
void vector2SAFEARRAY(const std::vector<double>& vect,SAFEARRAY** sa)
{

	SAFEARRAYBOUND *saBound=new SAFEARRAYBOUND[1];
	saBound[0].lLbound=0;
	saBound[0].cElements=(vect.size()>0)?vect.size():0;

	*sa=SafeArrayCreate(VT_R8,1,saBound);

	// initialize the data
	double HUGEP* pData;
	SafeArrayAccessData(*sa,(void**)&pData);
		for (std::vector<double>::const_iterator it=vect.begin();it!=vect.end();++it) {
			*pData++=(*it);
		}
	SafeArrayUnaccessData(*sa);

}

/**-------------------------------------------------------------------------------
	Convert vector to SAFEARRAY

	\param		SAFEARRAY sa
	\param		vector vect
	\return	nothing
--------------------------------------------------------------------------------*/
void SAFEARRAY2vector(SAFEARRAY& sa, std::vector<double>& vect)
{
	double* pData;
	SafeArrayAccessData(&sa,(void**)&pData);
		for (unsigned int i=0;i<sa.rgsabound[0].cElements;++i)
		{
			vect.push_back(double());
			vect.back()=*pData++;
		}
	SafeArrayUnaccessData(&sa);
}
#endif


/**-------------------------------------------------------------------------------
	Get version
	\params BSTR version
	\return HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getVersion(BSTR* version)
{
	CComBSTR v="version 1.1";
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
	*pVal=SimFacade::Instance().getSimulation()->getActuators()->size();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	Get parameters of the actuator. The parameters can be PID gains, or
	any other genereic parameters contained in the SAFEARRAY. Client should be 
	responsable for interpreting the results.

	\param i		i-th actuator 
	\param params	return VARIANT(SAFEARRAY) of actuator parameters
	\return		HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getParameters(SHORT i, VARIANT* params)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	std::vector<double> vectParams;
	//jCtlr->getController()->getParameter(vectParams); TODO
	//vectParams.push_back(jCtlr->getController()->getFeedbackPort());
	SAFEARRAY* sa=new SAFEARRAY();
	vector2SAFEARRAY(vectParams,&sa);
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
STDMETHODIMP CLisaCOMController::setParameters(SHORT i, VARIANT* params)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);	
	SAFEARRAY* sa=params->parray;
	std::vector<double> vectParams;
	SAFEARRAY2vector(*sa,vectParams);
	//jCtlr->getController()->setParameters(vectParams);
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
STDMETHODIMP CLisaCOMController::setParameter(SHORT i, SHORT nParam, DOUBLE Val)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);	
	//(nParam==4)?jCtlr->getController()->setParameter(nParam,(int)Val):jCtlr->getController()->setParameter(nParam,Val);
	//throw Exception("Not implemented!","LisaCOMController");
	return S_OK;
}


/**-------------------------------------------------------------------------------
	get i-th actuator position

	\param i	i-th actuator 
	\param pVal	returned position (angle)
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getPosition(SHORT i, DOUBLE* pVal)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	*pVal=jCtlr->getJoint()->getAngle();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	set i-th actuator reference

	\param i		i-th actuator 
	\param numRef	numRef-th actuator 
	\param Val		set-point
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::setReference(SHORT i, SHORT numRef, DOUBLE Val)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	jCtlr->getController()->setSetpoint(Val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator reference

	\param i		i-th actuator 
	\param numRef	i-th actuator 
	\param retVal	returned reference value
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getReference(SHORT i, SHORT numRef, DOUBLE* retVal)
{
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	jCtlr->getController()->getSetpoint(*retVal);
	return S_OK;
}


/**-------------------------------------------------------------------------------
	get i-th actuator velocity

	\param i	i-th actuator 
	\param pVal	returned velocity 
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getVelocity(SHORT i, DOUBLE* pVal)
{ 
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	*pVal=jCtlr->getJoint()->getVelocity();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th actuator torque

	\param i	i-th actuator 
	\param pVal	returned velocity 
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMController::getTorque(SHORT i, DOUBLE* pVal)
{ 
	Actuator* const jCtlr=SimFacade::Instance().getActuator(i);
	*pVal=jCtlr->getJoint()->getTorque();
	return S_OK;	
}
