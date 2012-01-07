

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ILisaCOMController,0x2316E6F0,0xC3AA,0x41DA,0xA9,0xCC,0x71,0xAE,0x78,0x21,0x35,0x6F);


MIDL_DEFINE_GUID(IID, IID_ILisaCOMTrajectory,0xB49CAF7A,0x3149,0x4894,0x97,0xDB,0xB6,0x00,0x9D,0x13,0x6F,0x7D);


MIDL_DEFINE_GUID(IID, IID_ILisaCOM,0x4878F5AA,0x2913,0x4C1F,0xAE,0x81,0x93,0x9A,0xF4,0xF2,0xB3,0xF6);


MIDL_DEFINE_GUID(IID, LIBID_Lisa50Lib,0xA821B86A,0xCD3D,0x4A7D,0xB0,0x6E,0x76,0xD7,0x04,0xFB,0xC8,0xB0);


MIDL_DEFINE_GUID(IID, DIID__ILisaCOMControllerEvents,0x11207FB3,0xF644,0x4A03,0x98,0xF9,0x90,0x92,0x1A,0x70,0x9F,0xE7);


MIDL_DEFINE_GUID(CLSID, CLSID_LisaCOMController,0x8557886E,0x230E,0x41F8,0xB1,0xF1,0xEC,0x61,0x10,0x6F,0x9C,0xDF);


MIDL_DEFINE_GUID(CLSID, CLSID_LisaCOMTrajectory,0x1AF71AB7,0xFA43,0x43D5,0xBD,0xDF,0xF2,0x44,0xDA,0xFF,0xCF,0x16);


MIDL_DEFINE_GUID(IID, DIID__ILisaCOMEvents,0xEFD56125,0x1A89,0x4970,0xBE,0xEB,0x62,0x05,0x8E,0xA8,0xCC,0xB8);


MIDL_DEFINE_GUID(CLSID, CLSID_LisaCOM,0xAA8F819D,0x59B4,0x4D9D,0xB7,0xBD,0x64,0xD2,0x40,0x2E,0xE2,0x65);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



