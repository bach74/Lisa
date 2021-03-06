// =============================================================================
//  LisaCOMTrajectory.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOMTrajectory.h"
#include "lisaAPI.h"


/**-------------------------------------------------------------------------------
	Load (and execute) a trajectory from a file
   
	\param filename (BSTR)
	\return (STDMETHODIMP)
 -----------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMTrajectory::LoadTrajectory(BSTR filename)
{
	USES_CONVERSION;
	LisaAPI::Instance().loadTrajectory(COLE2T(filename));

	return S_OK;
}


