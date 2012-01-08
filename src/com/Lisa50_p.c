

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Jan 08 00:48:16 2012
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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "Lisa50.h"

#define TYPE_FORMAT_STRING_SIZE   1063                              
#define PROC_FORMAT_STRING_SIZE   751                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _Lisa50_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } Lisa50_MIDL_TYPE_FORMAT_STRING;

typedef struct _Lisa50_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } Lisa50_MIDL_PROC_FORMAT_STRING;

typedef struct _Lisa50_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } Lisa50_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const Lisa50_MIDL_TYPE_FORMAT_STRING Lisa50__MIDL_TypeFormatString;
extern const Lisa50_MIDL_PROC_FORMAT_STRING Lisa50__MIDL_ProcFormatString;
extern const Lisa50_MIDL_EXPR_FORMAT_STRING Lisa50__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILisaCOMController_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILisaCOMController_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILisaCOMTrajectory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILisaCOMTrajectory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILisaCOM_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILisaCOM_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const Lisa50_MIDL_PROC_FORMAT_STRING Lisa50__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure getVersion */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter version */

/* 16 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_number */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x22 ),	/* 34 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 44 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getJointCoordinates */


	/* Procedure getParameters */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x9 ),	/* 9 */
/* 64 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 66 */	NdrFcShort( 0x6 ),	/* 6 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter i */


	/* Parameter i */

/* 72 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter val */


	/* Parameter params */

/* 78 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 80 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 82 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */


	/* Return value */

/* 84 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 86 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getPosition */

/* 90 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 92 */	NdrFcLong( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0xa ),	/* 10 */
/* 98 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 100 */	NdrFcShort( 0x6 ),	/* 6 */
/* 102 */	NdrFcShort( 0x2c ),	/* 44 */
/* 104 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 108 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 110 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 112 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 116 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 118 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setSetpoint */

/* 124 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 126 */	NdrFcLong( 0x0 ),	/* 0 */
/* 130 */	NdrFcShort( 0xb ),	/* 11 */
/* 132 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 134 */	NdrFcShort( 0x1c ),	/* 28 */
/* 136 */	NdrFcShort( 0x8 ),	/* 8 */
/* 138 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter i */

/* 140 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 142 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 144 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter numRef */

/* 146 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 148 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 150 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter Val */

/* 152 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 154 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 156 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 160 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getVelocity */

/* 164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 170 */	NdrFcShort( 0xc ),	/* 12 */
/* 172 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 174 */	NdrFcShort( 0x6 ),	/* 6 */
/* 176 */	NdrFcShort( 0x2c ),	/* 44 */
/* 178 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 182 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 184 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 186 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 188 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 190 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 192 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 194 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setParameter */

/* 198 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 200 */	NdrFcLong( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0xd ),	/* 13 */
/* 206 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 208 */	NdrFcShort( 0x1c ),	/* 28 */
/* 210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 212 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter i */

/* 214 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 216 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 218 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter numParam */

/* 220 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 222 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 224 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter Val */

/* 226 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 228 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 230 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 232 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 234 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 236 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setParameters */

/* 238 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 240 */	NdrFcLong( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0xe ),	/* 14 */
/* 246 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 248 */	NdrFcShort( 0x6 ),	/* 6 */
/* 250 */	NdrFcShort( 0x8 ),	/* 8 */
/* 252 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 254 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 258 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter params */

/* 260 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 262 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 264 */	NdrFcShort( 0x40e ),	/* Type Offset=1038 */

	/* Return value */

/* 266 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getTorque */

/* 272 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0xf ),	/* 15 */
/* 280 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 282 */	NdrFcShort( 0x6 ),	/* 6 */
/* 284 */	NdrFcShort( 0x2c ),	/* 44 */
/* 286 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 290 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 292 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 294 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 296 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 298 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 302 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getSetpoint */

/* 306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0x10 ),	/* 16 */
/* 314 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 316 */	NdrFcShort( 0xc ),	/* 12 */
/* 318 */	NdrFcShort( 0x2c ),	/* 44 */
/* 320 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter i */

/* 322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 324 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 326 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter numRef */

/* 328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 330 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 332 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter retVal */

/* 334 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 336 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 338 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 342 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getPositions */

/* 346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x11 ),	/* 17 */
/* 354 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 360 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter positions */

/* 362 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 364 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 366 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 370 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setSetpoints */

/* 374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x12 ),	/* 18 */
/* 382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 388 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter values */

/* 390 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 392 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 394 */	NdrFcShort( 0x40e ),	/* Type Offset=1038 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadTrajectory */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x7 ),	/* 7 */
/* 410 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter filename */

/* 418 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 420 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 422 */	NdrFcShort( 0x41c ),	/* Type Offset=1052 */

	/* Return value */

/* 424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 426 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLinkMass */

/* 430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x7 ),	/* 7 */
/* 438 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 440 */	NdrFcShort( 0x6 ),	/* 6 */
/* 442 */	NdrFcShort( 0x2c ),	/* 44 */
/* 444 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 448 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 450 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter value */

/* 452 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 454 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 456 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 460 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLinkPosition */

/* 464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x8 ),	/* 8 */
/* 472 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 474 */	NdrFcShort( 0x6 ),	/* 6 */
/* 476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 478 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter i */

/* 480 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 484 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter val */

/* 486 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 488 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 490 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 494 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getCOPPosition */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0xa ),	/* 10 */
/* 506 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x8 ),	/* 8 */
/* 512 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter point */

/* 514 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 516 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 518 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 520 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 522 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure close */

/* 526 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 528 */	NdrFcLong( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0xb ),	/* 11 */
/* 534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 540 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 542 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 544 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 546 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getCOPForce */

/* 548 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 550 */	NdrFcLong( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0xc ),	/* 12 */
/* 556 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	NdrFcShort( 0x8 ),	/* 8 */
/* 562 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter force */

/* 564 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 566 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 568 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 572 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_numLinks */

/* 576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0xd ),	/* 13 */
/* 584 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x22 ),	/* 34 */
/* 590 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 592 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 594 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 596 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 598 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 600 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure enumerateLinks */

/* 604 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 606 */	NdrFcLong( 0x0 ),	/* 0 */
/* 610 */	NdrFcShort( 0xe ),	/* 14 */
/* 612 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 618 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter val */

/* 620 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 624 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 628 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLinkPositionByName */

/* 632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0xf ),	/* 15 */
/* 640 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 646 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter name */

/* 648 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 650 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 652 */	NdrFcShort( 0x41c ),	/* Type Offset=1052 */

	/* Parameter val */

/* 654 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 656 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 658 */	NdrFcShort( 0x3f8 ),	/* Type Offset=1016 */

	/* Return value */

/* 660 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 662 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_time */

/* 666 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0x10 ),	/* 16 */
/* 674 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x2c ),	/* 44 */
/* 680 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 682 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 684 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 686 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 690 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure pause */

/* 694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x11 ),	/* 17 */
/* 702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 704 */	NdrFcShort( 0x6 ),	/* 6 */
/* 706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 708 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pause */

/* 710 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 712 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 714 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 716 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 718 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure isPaused */

/* 722 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 724 */	NdrFcLong( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x12 ),	/* 18 */
/* 730 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x22 ),	/* 34 */
/* 736 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pause */

/* 738 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 740 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 742 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 746 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const Lisa50_MIDL_TYPE_FORMAT_STRING Lisa50__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1a ),	/* Offset= 26 (30) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 42 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 44 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 46 */	NdrFcShort( 0x3ca ),	/* Offset= 970 (1016) */
/* 48 */	
			0x13, 0x0,	/* FC_OP */
/* 50 */	NdrFcShort( 0x3b2 ),	/* Offset= 946 (996) */
/* 52 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 54 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 56 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 58 */	NdrFcShort( 0x2 ),	/* Offset= 2 (60) */
/* 60 */	NdrFcShort( 0x10 ),	/* 16 */
/* 62 */	NdrFcShort( 0x2f ),	/* 47 */
/* 64 */	NdrFcLong( 0x14 ),	/* 20 */
/* 68 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 70 */	NdrFcLong( 0x3 ),	/* 3 */
/* 74 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 76 */	NdrFcLong( 0x11 ),	/* 17 */
/* 80 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 82 */	NdrFcLong( 0x2 ),	/* 2 */
/* 86 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 88 */	NdrFcLong( 0x4 ),	/* 4 */
/* 92 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 94 */	NdrFcLong( 0x5 ),	/* 5 */
/* 98 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 100 */	NdrFcLong( 0xb ),	/* 11 */
/* 104 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 106 */	NdrFcLong( 0xa ),	/* 10 */
/* 110 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 112 */	NdrFcLong( 0x6 ),	/* 6 */
/* 116 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (348) */
/* 118 */	NdrFcLong( 0x7 ),	/* 7 */
/* 122 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 124 */	NdrFcLong( 0x8 ),	/* 8 */
/* 128 */	NdrFcShort( 0xff86 ),	/* Offset= -122 (6) */
/* 130 */	NdrFcLong( 0xd ),	/* 13 */
/* 134 */	NdrFcShort( 0xdc ),	/* Offset= 220 (354) */
/* 136 */	NdrFcLong( 0x9 ),	/* 9 */
/* 140 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (372) */
/* 142 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 146 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (390) */
/* 148 */	NdrFcLong( 0x24 ),	/* 36 */
/* 152 */	NdrFcShort( 0x302 ),	/* Offset= 770 (922) */
/* 154 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 158 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (922) */
/* 160 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 164 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (926) */
/* 166 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 170 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (930) */
/* 172 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 176 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (934) */
/* 178 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 182 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (938) */
/* 184 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 188 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (942) */
/* 190 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 194 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (946) */
/* 196 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 200 */	NdrFcShort( 0x2da ),	/* Offset= 730 (930) */
/* 202 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 206 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (934) */
/* 208 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 212 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (950) */
/* 214 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 218 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (946) */
/* 220 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 224 */	NdrFcShort( 0x2da ),	/* Offset= 730 (954) */
/* 226 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 230 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (958) */
/* 232 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 236 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (962) */
/* 238 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 242 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (966) */
/* 244 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 248 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (970) */
/* 250 */	NdrFcLong( 0x10 ),	/* 16 */
/* 254 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 256 */	NdrFcLong( 0x12 ),	/* 18 */
/* 260 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 262 */	NdrFcLong( 0x13 ),	/* 19 */
/* 266 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 268 */	NdrFcLong( 0x15 ),	/* 21 */
/* 272 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 274 */	NdrFcLong( 0x16 ),	/* 22 */
/* 278 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 280 */	NdrFcLong( 0x17 ),	/* 23 */
/* 284 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 286 */	NdrFcLong( 0xe ),	/* 14 */
/* 290 */	NdrFcShort( 0x2b0 ),	/* Offset= 688 (978) */
/* 292 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 296 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (988) */
/* 298 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 302 */	NdrFcShort( 0x2b2 ),	/* Offset= 690 (992) */
/* 304 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 308 */	NdrFcShort( 0x26e ),	/* Offset= 622 (930) */
/* 310 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 314 */	NdrFcShort( 0x26c ),	/* Offset= 620 (934) */
/* 316 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 320 */	NdrFcShort( 0x26a ),	/* Offset= 618 (938) */
/* 322 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 326 */	NdrFcShort( 0x260 ),	/* Offset= 608 (934) */
/* 328 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 332 */	NdrFcShort( 0x25a ),	/* Offset= 602 (934) */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* Offset= 0 (338) */
/* 340 */	NdrFcLong( 0x1 ),	/* 1 */
/* 344 */	NdrFcShort( 0x0 ),	/* Offset= 0 (344) */
/* 346 */	NdrFcShort( 0xffff ),	/* Offset= -1 (345) */
/* 348 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 352 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 354 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 370 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 372 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 374 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 382 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 384 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 386 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 388 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 390 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 392 */	NdrFcShort( 0x2 ),	/* Offset= 2 (394) */
/* 394 */	
			0x13, 0x0,	/* FC_OP */
/* 396 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (904) */
/* 398 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 400 */	NdrFcShort( 0x18 ),	/* 24 */
/* 402 */	NdrFcShort( 0xa ),	/* 10 */
/* 404 */	NdrFcLong( 0x8 ),	/* 8 */
/* 408 */	NdrFcShort( 0x58 ),	/* Offset= 88 (496) */
/* 410 */	NdrFcLong( 0xd ),	/* 13 */
/* 414 */	NdrFcShort( 0x78 ),	/* Offset= 120 (534) */
/* 416 */	NdrFcLong( 0x9 ),	/* 9 */
/* 420 */	NdrFcShort( 0x94 ),	/* Offset= 148 (568) */
/* 422 */	NdrFcLong( 0xc ),	/* 12 */
/* 426 */	NdrFcShort( 0xbc ),	/* Offset= 188 (614) */
/* 428 */	NdrFcLong( 0x24 ),	/* 36 */
/* 432 */	NdrFcShort( 0x114 ),	/* Offset= 276 (708) */
/* 434 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 438 */	NdrFcShort( 0x130 ),	/* Offset= 304 (742) */
/* 440 */	NdrFcLong( 0x10 ),	/* 16 */
/* 444 */	NdrFcShort( 0x148 ),	/* Offset= 328 (772) */
/* 446 */	NdrFcLong( 0x2 ),	/* 2 */
/* 450 */	NdrFcShort( 0x160 ),	/* Offset= 352 (802) */
/* 452 */	NdrFcLong( 0x3 ),	/* 3 */
/* 456 */	NdrFcShort( 0x178 ),	/* Offset= 376 (832) */
/* 458 */	NdrFcLong( 0x14 ),	/* 20 */
/* 462 */	NdrFcShort( 0x190 ),	/* Offset= 400 (862) */
/* 464 */	NdrFcShort( 0xffff ),	/* Offset= -1 (463) */
/* 466 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 468 */	NdrFcShort( 0x4 ),	/* 4 */
/* 470 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 476 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 478 */	NdrFcShort( 0x4 ),	/* 4 */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x1 ),	/* 1 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	0x13, 0x0,	/* FC_OP */
/* 490 */	NdrFcShort( 0xfe2a ),	/* Offset= -470 (20) */
/* 492 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 494 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 496 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 500 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 502 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 504 */	NdrFcShort( 0x4 ),	/* 4 */
/* 506 */	NdrFcShort( 0x4 ),	/* 4 */
/* 508 */	0x11, 0x0,	/* FC_RP */
/* 510 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (466) */
/* 512 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 514 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 516 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 524 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 528 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 530 */	NdrFcShort( 0xff50 ),	/* Offset= -176 (354) */
/* 532 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 534 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x6 ),	/* Offset= 6 (546) */
/* 542 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x11, 0x0,	/* FC_RP */
/* 548 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (516) */
/* 550 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 558 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 562 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 564 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (372) */
/* 566 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 568 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 570 */	NdrFcShort( 0x8 ),	/* 8 */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x6 ),	/* Offset= 6 (580) */
/* 576 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 578 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 580 */	
			0x11, 0x0,	/* FC_RP */
/* 582 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (550) */
/* 584 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 586 */	NdrFcShort( 0x4 ),	/* 4 */
/* 588 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 594 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 596 */	NdrFcShort( 0x4 ),	/* 4 */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	NdrFcShort( 0x1 ),	/* 1 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	0x13, 0x0,	/* FC_OP */
/* 608 */	NdrFcShort( 0x184 ),	/* Offset= 388 (996) */
/* 610 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 612 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 614 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 616 */	NdrFcShort( 0x8 ),	/* 8 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x6 ),	/* Offset= 6 (626) */
/* 622 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 624 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 626 */	
			0x11, 0x0,	/* FC_RP */
/* 628 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (584) */
/* 630 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 632 */	NdrFcLong( 0x2f ),	/* 47 */
/* 636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 642 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 644 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 646 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 648 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 650 */	NdrFcShort( 0x1 ),	/* 1 */
/* 652 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 654 */	NdrFcShort( 0x4 ),	/* 4 */
/* 656 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 658 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 660 */	NdrFcShort( 0x10 ),	/* 16 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0xa ),	/* Offset= 10 (674) */
/* 666 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 668 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 670 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (630) */
/* 672 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 674 */	
			0x13, 0x0,	/* FC_OP */
/* 676 */	NdrFcShort( 0xffe4 ),	/* Offset= -28 (648) */
/* 678 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 680 */	NdrFcShort( 0x4 ),	/* 4 */
/* 682 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 688 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 690 */	NdrFcShort( 0x4 ),	/* 4 */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x1 ),	/* 1 */
/* 696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	0x13, 0x0,	/* FC_OP */
/* 702 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (658) */
/* 704 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 706 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 708 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 710 */	NdrFcShort( 0x8 ),	/* 8 */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 714 */	NdrFcShort( 0x6 ),	/* Offset= 6 (720) */
/* 716 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 718 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 720 */	
			0x11, 0x0,	/* FC_RP */
/* 722 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (678) */
/* 724 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 726 */	NdrFcShort( 0x8 ),	/* 8 */
/* 728 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 730 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 732 */	NdrFcShort( 0x10 ),	/* 16 */
/* 734 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 736 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 738 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (724) */
			0x5b,		/* FC_END */
/* 742 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x18 ),	/* 24 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0xa ),	/* Offset= 10 (758) */
/* 750 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 752 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 754 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (730) */
/* 756 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 758 */	
			0x11, 0x0,	/* FC_RP */
/* 760 */	NdrFcShort( 0xff0c ),	/* Offset= -244 (516) */
/* 762 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 764 */	NdrFcShort( 0x1 ),	/* 1 */
/* 766 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 772 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 776 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 778 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 780 */	NdrFcShort( 0x4 ),	/* 4 */
/* 782 */	NdrFcShort( 0x4 ),	/* 4 */
/* 784 */	0x13, 0x0,	/* FC_OP */
/* 786 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (762) */
/* 788 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 790 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 792 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 794 */	NdrFcShort( 0x2 ),	/* 2 */
/* 796 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 800 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 802 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 806 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 808 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 810 */	NdrFcShort( 0x4 ),	/* 4 */
/* 812 */	NdrFcShort( 0x4 ),	/* 4 */
/* 814 */	0x13, 0x0,	/* FC_OP */
/* 816 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (792) */
/* 818 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 820 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 822 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 824 */	NdrFcShort( 0x4 ),	/* 4 */
/* 826 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 830 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 832 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 834 */	NdrFcShort( 0x8 ),	/* 8 */
/* 836 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 838 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 840 */	NdrFcShort( 0x4 ),	/* 4 */
/* 842 */	NdrFcShort( 0x4 ),	/* 4 */
/* 844 */	0x13, 0x0,	/* FC_OP */
/* 846 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (822) */
/* 848 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 850 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 852 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 854 */	NdrFcShort( 0x8 ),	/* 8 */
/* 856 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 862 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 864 */	NdrFcShort( 0x8 ),	/* 8 */
/* 866 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 868 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 870 */	NdrFcShort( 0x4 ),	/* 4 */
/* 872 */	NdrFcShort( 0x4 ),	/* 4 */
/* 874 */	0x13, 0x0,	/* FC_OP */
/* 876 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (852) */
/* 878 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 880 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 882 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 886 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 888 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 890 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 894 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 896 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 898 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 900 */	NdrFcShort( 0xffee ),	/* Offset= -18 (882) */
/* 902 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 904 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 906 */	NdrFcShort( 0x28 ),	/* 40 */
/* 908 */	NdrFcShort( 0xffee ),	/* Offset= -18 (890) */
/* 910 */	NdrFcShort( 0x0 ),	/* Offset= 0 (910) */
/* 912 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 914 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 916 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 918 */	NdrFcShort( 0xfdf8 ),	/* Offset= -520 (398) */
/* 920 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 922 */	
			0x13, 0x0,	/* FC_OP */
/* 924 */	NdrFcShort( 0xfef6 ),	/* Offset= -266 (658) */
/* 926 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 928 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 930 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 932 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 934 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 936 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 938 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 940 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 944 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 946 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 948 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 950 */	
			0x13, 0x0,	/* FC_OP */
/* 952 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (348) */
/* 954 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 956 */	NdrFcShort( 0xfc4a ),	/* Offset= -950 (6) */
/* 958 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 960 */	NdrFcShort( 0xfda2 ),	/* Offset= -606 (354) */
/* 962 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 964 */	NdrFcShort( 0xfdb0 ),	/* Offset= -592 (372) */
/* 966 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 968 */	NdrFcShort( 0xfdbe ),	/* Offset= -578 (390) */
/* 970 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 972 */	NdrFcShort( 0x2 ),	/* Offset= 2 (974) */
/* 974 */	
			0x13, 0x0,	/* FC_OP */
/* 976 */	NdrFcShort( 0x14 ),	/* Offset= 20 (996) */
/* 978 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 980 */	NdrFcShort( 0x10 ),	/* 16 */
/* 982 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 984 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 986 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 988 */	
			0x13, 0x0,	/* FC_OP */
/* 990 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (978) */
/* 992 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 994 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 996 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 998 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1002 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1002) */
/* 1004 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1006 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1008 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1010 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1012 */	NdrFcShort( 0xfc40 ),	/* Offset= -960 (52) */
/* 1014 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1016 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1018 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1020 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1024 */	NdrFcShort( 0xfc30 ),	/* Offset= -976 (48) */
/* 1026 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1028 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1030 */	
			0x11, 0x0,	/* FC_RP */
/* 1032 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1038) */
/* 1034 */	
			0x12, 0x0,	/* FC_UP */
/* 1036 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (996) */
/* 1038 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1040 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1042 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1034) */
/* 1048 */	
			0x12, 0x0,	/* FC_UP */
/* 1050 */	NdrFcShort( 0xfbfa ),	/* Offset= -1030 (20) */
/* 1052 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1056 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1048) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ILisaCOMController, ver. 0.0,
   GUID={0x2316E6F0,0xC3AA,0x41DA,{0xA9,0xCC,0x71,0xAE,0x78,0x21,0x35,0x6F}} */

#pragma code_seg(".orpc")
static const unsigned short ILisaCOMController_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    90,
    124,
    164,
    198,
    238,
    272,
    306,
    346,
    374
    };

static const MIDL_STUBLESS_PROXY_INFO ILisaCOMController_ProxyInfo =
    {
    &Object_StubDesc,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOMController_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILisaCOMController_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOMController_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _ILisaCOMControllerProxyVtbl = 
{
    &ILisaCOMController_ProxyInfo,
    &IID_ILisaCOMController,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getVersion */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::get_number */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getParameters */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getPosition */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::setSetpoint */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getVelocity */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::setParameter */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::setParameters */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getTorque */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getSetpoint */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::getPositions */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMController::setSetpoints */
};


static const PRPC_STUB_FUNCTION ILisaCOMController_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ILisaCOMControllerStubVtbl =
{
    &IID_ILisaCOMController,
    &ILisaCOMController_ServerInfo,
    19,
    &ILisaCOMController_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ILisaCOMTrajectory, ver. 0.0,
   GUID={0xB49CAF7A,0x3149,0x4894,{0x97,0xDB,0xB6,0x00,0x9D,0x13,0x6F,0x7D}} */

#pragma code_seg(".orpc")
static const unsigned short ILisaCOMTrajectory_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    402
    };

static const MIDL_STUBLESS_PROXY_INFO ILisaCOMTrajectory_ProxyInfo =
    {
    &Object_StubDesc,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOMTrajectory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILisaCOMTrajectory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOMTrajectory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _ILisaCOMTrajectoryProxyVtbl = 
{
    &ILisaCOMTrajectory_ProxyInfo,
    &IID_ILisaCOMTrajectory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ILisaCOMTrajectory::LoadTrajectory */
};


static const PRPC_STUB_FUNCTION ILisaCOMTrajectory_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _ILisaCOMTrajectoryStubVtbl =
{
    &IID_ILisaCOMTrajectory,
    &ILisaCOMTrajectory_ServerInfo,
    8,
    &ILisaCOMTrajectory_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ILisaCOM, ver. 0.0,
   GUID={0x4878F5AA,0x2913,0x4C1F,{0xAE,0x81,0x93,0x9A,0xF4,0xF2,0xB3,0xF6}} */

#pragma code_seg(".orpc")
static const unsigned short ILisaCOM_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    430,
    464,
    56,
    498,
    526,
    548,
    576,
    604,
    632,
    666,
    694,
    722
    };

static const MIDL_STUBLESS_PROXY_INFO ILisaCOM_ProxyInfo =
    {
    &Object_StubDesc,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOM_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILisaCOM_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    Lisa50__MIDL_ProcFormatString.Format,
    &ILisaCOM_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _ILisaCOMProxyVtbl = 
{
    &ILisaCOM_ProxyInfo,
    &IID_ILisaCOM,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getLinkMass */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getLinkPosition */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getJointCoordinates */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getCOPPosition */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::close */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getCOPForce */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::get_numLinks */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::enumerateLinks */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::getLinkPositionByName */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::get_time */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::pause */ ,
    (void *) (INT_PTR) -1 /* ILisaCOM::isPaused */
};


static const PRPC_STUB_FUNCTION ILisaCOM_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ILisaCOMStubVtbl =
{
    &IID_ILisaCOM,
    &ILisaCOM_ServerInfo,
    19,
    &ILisaCOM_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    Lisa50__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _Lisa50_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ILisaCOMTrajectoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILisaCOMProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILisaCOMControllerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _Lisa50_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ILisaCOMTrajectoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ILisaCOMStubVtbl,
    ( CInterfaceStubVtbl *) &_ILisaCOMControllerStubVtbl,
    0
};

PCInterfaceName const _Lisa50_InterfaceNamesList[] = 
{
    "ILisaCOMTrajectory",
    "ILisaCOM",
    "ILisaCOMController",
    0
};

const IID *  const _Lisa50_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _Lisa50_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _Lisa50, pIID, n)

int __stdcall _Lisa50_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _Lisa50, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _Lisa50, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _Lisa50, 3, *pIndex )
    
}

const ExtendedProxyFileInfo Lisa50_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _Lisa50_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _Lisa50_StubVtblList,
    (const PCInterfaceName * ) & _Lisa50_InterfaceNamesList,
    (const IID ** ) & _Lisa50_BaseIIDList,
    & _Lisa50_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

