

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Jan 07 02:25:47 2012
 */
/* Compiler settings for ..\src\com\Lisa50.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Lisa50_h__
#define __Lisa50_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILisaCOMController_FWD_DEFINED__
#define __ILisaCOMController_FWD_DEFINED__
typedef interface ILisaCOMController ILisaCOMController;
#endif 	/* __ILisaCOMController_FWD_DEFINED__ */


#ifndef __ILisaCOMTrajectory_FWD_DEFINED__
#define __ILisaCOMTrajectory_FWD_DEFINED__
typedef interface ILisaCOMTrajectory ILisaCOMTrajectory;
#endif 	/* __ILisaCOMTrajectory_FWD_DEFINED__ */


#ifndef __ILisaCOM_FWD_DEFINED__
#define __ILisaCOM_FWD_DEFINED__
typedef interface ILisaCOM ILisaCOM;
#endif 	/* __ILisaCOM_FWD_DEFINED__ */


#ifndef ___ILisaCOMControllerEvents_FWD_DEFINED__
#define ___ILisaCOMControllerEvents_FWD_DEFINED__
typedef interface _ILisaCOMControllerEvents _ILisaCOMControllerEvents;
#endif 	/* ___ILisaCOMControllerEvents_FWD_DEFINED__ */


#ifndef __LisaCOMController_FWD_DEFINED__
#define __LisaCOMController_FWD_DEFINED__

#ifdef __cplusplus
typedef class LisaCOMController LisaCOMController;
#else
typedef struct LisaCOMController LisaCOMController;
#endif /* __cplusplus */

#endif 	/* __LisaCOMController_FWD_DEFINED__ */


#ifndef __LisaCOMTrajectory_FWD_DEFINED__
#define __LisaCOMTrajectory_FWD_DEFINED__

#ifdef __cplusplus
typedef class LisaCOMTrajectory LisaCOMTrajectory;
#else
typedef struct LisaCOMTrajectory LisaCOMTrajectory;
#endif /* __cplusplus */

#endif 	/* __LisaCOMTrajectory_FWD_DEFINED__ */


#ifndef ___ILisaCOMEvents_FWD_DEFINED__
#define ___ILisaCOMEvents_FWD_DEFINED__
typedef interface _ILisaCOMEvents _ILisaCOMEvents;
#endif 	/* ___ILisaCOMEvents_FWD_DEFINED__ */


#ifndef __LisaCOM_FWD_DEFINED__
#define __LisaCOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class LisaCOM LisaCOM;
#else
typedef struct LisaCOM LisaCOM;
#endif /* __cplusplus */

#endif 	/* __LisaCOM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ILisaCOMController_INTERFACE_DEFINED__
#define __ILisaCOMController_INTERFACE_DEFINED__

/* interface ILisaCOMController */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILisaCOMController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2316E6F0-C3AA-41DA-A9CC-71AE7821356F")
    ILisaCOMController : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVersion( 
            /* [retval][out] */ BSTR *version) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_number( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getParameters( 
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *params) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getPosition( 
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setSetpoint( 
            /* [in] */ USHORT i,
            /* [in] */ USHORT numRef,
            /* [in] */ DOUBLE Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getVelocity( 
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setParameter( 
            /* [in] */ USHORT i,
            /* [in] */ USHORT numParam,
            /* [in] */ DOUBLE Val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setParameters( 
            /* [in] */ USHORT i,
            /* [in] */ VARIANT *params) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTorque( 
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getSetpoint( 
            /* [in] */ USHORT i,
            USHORT numRef,
            /* [retval][out] */ DOUBLE *retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILisaCOMControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILisaCOMController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILisaCOMController * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILisaCOMController * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILisaCOMController * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILisaCOMController * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILisaCOMController * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILisaCOMController * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getVersion )( 
            ILisaCOMController * This,
            /* [retval][out] */ BSTR *version);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_number )( 
            ILisaCOMController * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getParameters )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *params);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getPosition )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setSetpoint )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [in] */ USHORT numRef,
            /* [in] */ DOUBLE Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getVelocity )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setParameter )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [in] */ USHORT numParam,
            /* [in] */ DOUBLE Val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setParameters )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [in] */ VARIANT *params);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getTorque )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getSetpoint )( 
            ILisaCOMController * This,
            /* [in] */ USHORT i,
            USHORT numRef,
            /* [retval][out] */ DOUBLE *retVal);
        
        END_INTERFACE
    } ILisaCOMControllerVtbl;

    interface ILisaCOMController
    {
        CONST_VTBL struct ILisaCOMControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILisaCOMController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILisaCOMController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILisaCOMController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILisaCOMController_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILisaCOMController_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILisaCOMController_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILisaCOMController_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILisaCOMController_getVersion(This,version)	\
    ( (This)->lpVtbl -> getVersion(This,version) ) 

#define ILisaCOMController_get_number(This,pVal)	\
    ( (This)->lpVtbl -> get_number(This,pVal) ) 

#define ILisaCOMController_getParameters(This,i,params)	\
    ( (This)->lpVtbl -> getParameters(This,i,params) ) 

#define ILisaCOMController_getPosition(This,i,pVal)	\
    ( (This)->lpVtbl -> getPosition(This,i,pVal) ) 

#define ILisaCOMController_setSetpoint(This,i,numRef,Val)	\
    ( (This)->lpVtbl -> setSetpoint(This,i,numRef,Val) ) 

#define ILisaCOMController_getVelocity(This,i,pVal)	\
    ( (This)->lpVtbl -> getVelocity(This,i,pVal) ) 

#define ILisaCOMController_setParameter(This,i,numParam,Val)	\
    ( (This)->lpVtbl -> setParameter(This,i,numParam,Val) ) 

#define ILisaCOMController_setParameters(This,i,params)	\
    ( (This)->lpVtbl -> setParameters(This,i,params) ) 

#define ILisaCOMController_getTorque(This,i,pVal)	\
    ( (This)->lpVtbl -> getTorque(This,i,pVal) ) 

#define ILisaCOMController_getSetpoint(This,i,numRef,retVal)	\
    ( (This)->lpVtbl -> getSetpoint(This,i,numRef,retVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILisaCOMController_INTERFACE_DEFINED__ */


#ifndef __ILisaCOMTrajectory_INTERFACE_DEFINED__
#define __ILisaCOMTrajectory_INTERFACE_DEFINED__

/* interface ILisaCOMTrajectory */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILisaCOMTrajectory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B49CAF7A-3149-4894-97DB-B6009D136F7D")
    ILisaCOMTrajectory : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadTrajectory( 
            /* [in] */ BSTR filename) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILisaCOMTrajectoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILisaCOMTrajectory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILisaCOMTrajectory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILisaCOMTrajectory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILisaCOMTrajectory * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILisaCOMTrajectory * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILisaCOMTrajectory * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILisaCOMTrajectory * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadTrajectory )( 
            ILisaCOMTrajectory * This,
            /* [in] */ BSTR filename);
        
        END_INTERFACE
    } ILisaCOMTrajectoryVtbl;

    interface ILisaCOMTrajectory
    {
        CONST_VTBL struct ILisaCOMTrajectoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILisaCOMTrajectory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILisaCOMTrajectory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILisaCOMTrajectory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILisaCOMTrajectory_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILisaCOMTrajectory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILisaCOMTrajectory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILisaCOMTrajectory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILisaCOMTrajectory_LoadTrajectory(This,filename)	\
    ( (This)->lpVtbl -> LoadTrajectory(This,filename) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILisaCOMTrajectory_INTERFACE_DEFINED__ */


#ifndef __ILisaCOM_INTERFACE_DEFINED__
#define __ILisaCOM_INTERFACE_DEFINED__

/* interface ILisaCOM */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILisaCOM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4878F5AA-2913-4C1F-AE81-939AF4F2B3F6")
    ILisaCOM : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLinkMass( 
            USHORT i,
            /* [retval][out] */ DOUBLE *value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLinkPosition( 
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getJointCoordinates( 
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getCOPPosition( 
            /* [retval][out] */ VARIANT *point) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getCOPForce( 
            /* [retval][out] */ VARIANT *force) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_numLinks( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE enumerateLinks( 
            /* [retval][out] */ VARIANT *val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLinkPositionByName( 
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT *val) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_time( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE pause( 
            /* [in] */ SHORT pause) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE isPaused( 
            /* [retval][out] */ SHORT *pause) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILisaCOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILisaCOM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILisaCOM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILisaCOM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILisaCOM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILisaCOM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILisaCOM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILisaCOM * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLinkMass )( 
            ILisaCOM * This,
            USHORT i,
            /* [retval][out] */ DOUBLE *value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLinkPosition )( 
            ILisaCOM * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getJointCoordinates )( 
            ILisaCOM * This,
            /* [in] */ USHORT i,
            /* [retval][out] */ VARIANT *val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getCOPPosition )( 
            ILisaCOM * This,
            /* [retval][out] */ VARIANT *point);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *close )( 
            ILisaCOM * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getCOPForce )( 
            ILisaCOM * This,
            /* [retval][out] */ VARIANT *force);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_numLinks )( 
            ILisaCOM * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *enumerateLinks )( 
            ILisaCOM * This,
            /* [retval][out] */ VARIANT *val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLinkPositionByName )( 
            ILisaCOM * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ VARIANT *val);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_time )( 
            ILisaCOM * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pause )( 
            ILisaCOM * This,
            /* [in] */ SHORT pause);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *isPaused )( 
            ILisaCOM * This,
            /* [retval][out] */ SHORT *pause);
        
        END_INTERFACE
    } ILisaCOMVtbl;

    interface ILisaCOM
    {
        CONST_VTBL struct ILisaCOMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILisaCOM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILisaCOM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILisaCOM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILisaCOM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILisaCOM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILisaCOM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILisaCOM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILisaCOM_getLinkMass(This,i,value)	\
    ( (This)->lpVtbl -> getLinkMass(This,i,value) ) 

#define ILisaCOM_getLinkPosition(This,i,val)	\
    ( (This)->lpVtbl -> getLinkPosition(This,i,val) ) 

#define ILisaCOM_getJointCoordinates(This,i,val)	\
    ( (This)->lpVtbl -> getJointCoordinates(This,i,val) ) 

#define ILisaCOM_getCOPPosition(This,point)	\
    ( (This)->lpVtbl -> getCOPPosition(This,point) ) 

#define ILisaCOM_close(This)	\
    ( (This)->lpVtbl -> close(This) ) 

#define ILisaCOM_getCOPForce(This,force)	\
    ( (This)->lpVtbl -> getCOPForce(This,force) ) 

#define ILisaCOM_get_numLinks(This,pVal)	\
    ( (This)->lpVtbl -> get_numLinks(This,pVal) ) 

#define ILisaCOM_enumerateLinks(This,val)	\
    ( (This)->lpVtbl -> enumerateLinks(This,val) ) 

#define ILisaCOM_getLinkPositionByName(This,name,val)	\
    ( (This)->lpVtbl -> getLinkPositionByName(This,name,val) ) 

#define ILisaCOM_get_time(This,pVal)	\
    ( (This)->lpVtbl -> get_time(This,pVal) ) 

#define ILisaCOM_pause(This,pause)	\
    ( (This)->lpVtbl -> pause(This,pause) ) 

#define ILisaCOM_isPaused(This,pause)	\
    ( (This)->lpVtbl -> isPaused(This,pause) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILisaCOM_INTERFACE_DEFINED__ */



#ifndef __Lisa50Lib_LIBRARY_DEFINED__
#define __Lisa50Lib_LIBRARY_DEFINED__

/* library Lisa50Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_Lisa50Lib;

#ifndef ___ILisaCOMControllerEvents_DISPINTERFACE_DEFINED__
#define ___ILisaCOMControllerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILisaCOMControllerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILisaCOMControllerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11207FB3-F644-4A03-98F9-90921A709FE7")
    _ILisaCOMControllerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILisaCOMControllerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ILisaCOMControllerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ILisaCOMControllerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ILisaCOMControllerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ILisaCOMControllerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ILisaCOMControllerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ILisaCOMControllerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ILisaCOMControllerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ILisaCOMControllerEventsVtbl;

    interface _ILisaCOMControllerEvents
    {
        CONST_VTBL struct _ILisaCOMControllerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILisaCOMControllerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ILisaCOMControllerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ILisaCOMControllerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ILisaCOMControllerEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ILisaCOMControllerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ILisaCOMControllerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ILisaCOMControllerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILisaCOMControllerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LisaCOMController;

#ifdef __cplusplus

class DECLSPEC_UUID("8557886E-230E-41F8-B1F1-EC61106F9CDF")
LisaCOMController;
#endif

EXTERN_C const CLSID CLSID_LisaCOMTrajectory;

#ifdef __cplusplus

class DECLSPEC_UUID("1AF71AB7-FA43-43D5-BDDF-F244DAFFCF16")
LisaCOMTrajectory;
#endif

#ifndef ___ILisaCOMEvents_DISPINTERFACE_DEFINED__
#define ___ILisaCOMEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ILisaCOMEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ILisaCOMEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EFD56125-1A89-4970-BEEB-62058EA8CCB8")
    _ILisaCOMEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ILisaCOMEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ILisaCOMEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ILisaCOMEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ILisaCOMEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ILisaCOMEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ILisaCOMEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ILisaCOMEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ILisaCOMEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ILisaCOMEventsVtbl;

    interface _ILisaCOMEvents
    {
        CONST_VTBL struct _ILisaCOMEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ILisaCOMEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ILisaCOMEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ILisaCOMEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ILisaCOMEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ILisaCOMEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ILisaCOMEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ILisaCOMEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ILisaCOMEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_LisaCOM;

#ifdef __cplusplus

class DECLSPEC_UUID("AA8F819D-59B4-4D9D-B7BD-64D2402EE265")
LisaCOM;
#endif
#endif /* __Lisa50Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


