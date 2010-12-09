// =============================================================================
//  LisaCOM.cpp   version:  1.0
//  
//	Implementation of LisaCOM
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOM.h"
#include "atlsafe.h"
#include "simFacade.h"

/**----------------------------------------------------------------------------
	Convert function, vector3 to safearray.
   
	\param vect (Ogre::Vector3 &)
	\return (SAFEARRAY*)
 -----------------------------------------------------------------------------*/
SAFEARRAY* Vector3toSAFEARRAY(Ogre::Vector3& vect)
{
	SAFEARRAY* sa=new SAFEARRAY();

	SAFEARRAYBOUND saBound[1];
	saBound[0].lLbound=0;
	saBound[0].cElements=3;

	sa=SafeArrayCreate(VT_R8,1,saBound);

	long ind=0;
	double v[3]={vect.x,vect.y,vect.z};
	SafeArrayPutElement(sa,&ind,(void*)&v[0]);
	ind++;
	SafeArrayPutElement(sa,&ind,(void*)&v[1]);
	ind++;
	SafeArrayPutElement(sa,&ind,(void*)&v[2]);

	return sa;
}



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
	pause or unpause the simulation

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
STDMETHODIMP LisaCOM::getLinkMass(SHORT i, DOUBLE* value)
{
	*value=SimFacade::Instance().getLinkMass(i);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th link position

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getLinkPosition(SHORT i, VARIANT* val)
{
	CComVariant v(Vector3toSAFEARRAY(SimFacade::Instance().getLinkPosition(i)));
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
	CComVariant v(Vector3toSAFEARRAY(SimFacade::Instance().getLinkPosition(std::string(OLE2A(name)))));
	v.Detach(val);
	return S_OK;
}

/**-------------------------------------------------------------------------------
	get i-th joint Cartesian coordinates

	\param		
	\return	HRESULT
--------------------------------------------------------------------------------*/
STDMETHODIMP LisaCOM::getJointCoordinates(SHORT i, VARIANT* val)
{	
	CComVariant v(Vector3toSAFEARRAY(SimFacade::Instance().getJointCoordinates(i)));
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
	CComVariant v(Vector3toSAFEARRAY(SimFacade::Instance().getCOPPosition()));
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
	CComVariant v(Vector3toSAFEARRAY(SimFacade::Instance().getCOPForce()));
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