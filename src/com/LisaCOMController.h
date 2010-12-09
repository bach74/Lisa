// =============================================================================
//  LisaCOMController.h   version:  1.0
//  
//	Declaration of the CLisaCOMController
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================
#pragma once

#include "Lisa50.h"
#include "_ILisaCOMControllerEvents_CP.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

/// CLisaCOMController 
class ATL_NO_VTABLE CLisaCOMController :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLisaCOMController, &CLSID_LisaCOMController>,
	public IConnectionPointContainerImpl<CLisaCOMController>,
	public CProxy_ILisaCOMControllerEvents<CLisaCOMController>,
	public IDispatchImpl<ILisaCOMController, &IID_ILisaCOMController, &LIBID_Lisa50Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CLisaCOMController()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_LISACOMCONTROLLER)


	BEGIN_COM_MAP(CLisaCOMController)
		COM_INTERFACE_ENTRY(ILisaCOMController)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CLisaCOMController)
		CONNECTION_POINT_ENTRY(__uuidof(_ILisaCOMControllerEvents))
	END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(getVersion)(BSTR* version);
	STDMETHOD(get_number)(SHORT* pVal);
	STDMETHOD(getParameters)(SHORT i, VARIANT* params);
	STDMETHOD(getPosition)(SHORT i, DOUBLE* pVal);
	STDMETHOD(setParameter)(SHORT i, SHORT numParam, DOUBLE val);
	STDMETHOD(getVelocity)(SHORT i, DOUBLE* pVal);
	STDMETHOD(setReference)(SHORT i, SHORT numRef, DOUBLE val);
	STDMETHOD(setParameters)(SHORT i, VARIANT* params);
	STDMETHOD(getTorque)(SHORT i, DOUBLE* pVal);
	STDMETHOD(getReference)(SHORT i, SHORT numRef, DOUBLE* retVal);

};

OBJECT_ENTRY_AUTO(__uuidof(LisaCOMController), CLisaCOMController)
