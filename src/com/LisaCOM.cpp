// =============================================================================
//  LisaCOM.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOM.h"
#include "atlsafe.h"
#include "simFacade.h"
#include "conversion.h"


/**-------------------------------------------------------------------------------
	get number of links

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::get_numLinks(SHORT* val)
{
	*val=SimFacade::Instance().getNumLinks();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get current simulation time

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::get_time(DOUBLE* pVal)
{
	*pVal=SimFacade::Instance().getCurrentTime();
	return S_OK;
}

/**-------------------------------------------------------------------------------
	pause or resume the simulation

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::Pause(SHORT pause)
{
	SimFacade::Instance().pauseSimulation(pause!=0);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th link mass

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getLinkMass(USHORT i, DOUBLE* value)
{
	*value=SimFacade::Instance().getLinkMass(i);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th link position

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getLinkPosition(USHORT i, VARIANT* val)
{
	CComVariant v(Conversion::Vector3toSAFEARRAY(SimFacade::Instance().getLinkPosition(i)));
	v.Detach(val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th link position

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getLinkPositionByName(BSTR name, VARIANT* val)
{
	USES_CONVERSION;
	CComVariant v(Conversion::Vector3toSAFEARRAY(SimFacade::Instance().getLinkPosition(std::string(OLE2A(name)))));
	v.Detach(val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th joint Cartesian coordinates

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getJointCoordinates(USHORT i, VARIANT* val)
{	
	CComVariant v(Conversion::Vector3toSAFEARRAY(SimFacade::Instance().getJointCoordinates(i)));
	v.Detach(val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get pressure data from the sensors
	get the center of pressure position

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getCOPPosition(VARIANT* point)
{
	CComVariant v(Conversion::Vector3toSAFEARRAY(SimFacade::Instance().getCOPPosition()));
	v.Detach(point);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get pressure data from the sensors
	get force acting on the center of pressure 

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getCOPForce(VARIANT* force)
{
	CComVariant v(Conversion::Vector3toSAFEARRAY(SimFacade::Instance().getCOPForce()));
	v.Detach(force);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	close the simulation

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::close()
{
	SimFacade::Instance().closeApplication();
	return S_OK;
}


/**-------------------------------------------------------------------------------
	return all link names 

	\param		
	\return	VARIANT(string) link names
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::enumerateLinks(VARIANT* val)
{
	USES_CONVERSION;
	
	int count=SimFacade::Instance().getNumLinks();
	// Define the array bound structure
	CComSafeArrayBound bound[1];
	bound[0].SetCount(count);
	bound[0].SetLowerBound(0);

	CComSafeArray<BSTR> sa(bound);
	for (int i=0;i<count;++i)
		sa.Add(A2OLE(SimFacade::Instance().getLinkName(i).c_str()));

	CComVariant v(sa);
	v.Detach(val);

	return S_OK;
}