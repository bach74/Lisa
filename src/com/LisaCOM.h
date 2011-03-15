// =============================================================================
//  LisaCOM.h   version:  1.5
//  
//	Declaration of the LisaCOM
//
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================

#pragma once
#include "Lisa50.h"
#include "_ILisaComEvents_CP.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// LisaCOM

class ATL_NO_VTABLE LisaCOM :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<LisaCOM, &CLSID_LisaCOM>,
	public IConnectionPointContainerImpl<LisaCOM>,
	public CProxy_ILisaCOMEvents<LisaCOM>,
	public IDispatchImpl<ILisaCOM, &IID_ILisaCOM, &LIBID_Lisa50Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	LisaCOM()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LISACOM)


BEGIN_COM_MAP(LisaCOM)
	COM_INTERFACE_ENTRY(ILisaCOM)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(LisaCOM)
	CONNECTION_POINT_ENTRY(__uuidof(_ILisaCOMEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		close();
	}

public:

	STDMETHOD(getLinkMass)(USHORT i, DOUBLE* value);
	STDMETHOD(getLinkPosition)(USHORT i, VARIANT* val);
	STDMETHOD(getJointCoordinates)(USHORT i, VARIANT* val);
	STDMETHOD(getCOPPosition)(VARIANT* points);
	STDMETHOD(getCOPForce)(VARIANT* points);
	STDMETHOD(close)(void);
	STDMETHOD(get_numLinks)(SHORT* val);
	STDMETHOD(enumerateLinks)(VARIANT* val);
	STDMETHOD(getLinkPositionByName)(BSTR name, VARIANT* val);
	STDMETHOD(get_time)(DOUBLE* pVal);
	STDMETHOD(pause)(SHORT pause);
	STDMETHOD(isPaused)(SHORT* val);
};

OBJECT_ENTRY_AUTO(__uuidof(LisaCOM), LisaCOM)
