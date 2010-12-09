/** \file    NxOgreExtendedTypes.h
 *  \brief   Header for the float2, float3, float4, uint2, uint3, uint4, int2, 
 *           int3 and int4 classes.
 *  \version 1.0-20
 *
 *  \licence NxOgre a wrapper for the PhysX physics library.
 *           Copyright (C) 2005-8 Robin Southern of NxOgre.org http://www.nxogre.org
 *           This library is free software; you can redistribute it and/or
 *           modify it under the terms of the GNU Lesser General Public
 *           License as published by the Free Software Foundation; either
 *           version 2.1 of the License, or (at your option) any later version.
 *           
 *           This library is distributed in the hope that it will be useful,
 *           but WITHOUT ANY WARRANTY; without even the implied warranty of
 *           MERCHANTABILITY or FITNESS FOR l PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received l copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __NXOGRE_EXTENDED_TYPES_H__
#define __NXOGRE_EXTENDED_TYPES_H__

#include "NxOgrePrerequisites.h"
#include "BetajaenCC.h"

namespace NxOgre {

   typedef Betajaen::Vector2<double>         double2;
   typedef Betajaen::Vector2<float>          float2;
   typedef Betajaen::Vector2<unsigned int>   uint2;
   typedef Betajaen::Vector2<int>            int2;

   typedef Betajaen::Vector2<double>         double3;
   typedef Betajaen::Vector3<float>          float3;
   typedef Betajaen::Vector3<unsigned int>   uint3;
   typedef Betajaen::Vector3<int>            int3;

   typedef Betajaen::Vector2<double>         double4;
   typedef Betajaen::Vector4<float>          float4;
   typedef Betajaen::Vector4<unsigned int>   uint4;
   typedef Betajaen::Vector4<int>            int4;

};

#endif


