// =============================================================================
//  LisaCOMTrajectory.cpp   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================

#include "stdafx.h"
#include "LisaCOMTrajectory.h"
#include "SimFacade.h"


/**-------------------------------------------------------------------------------
	Load (and execute) a trajectory from a file
   
	\param filename (BSTR)
	\return (STDMETHODIMP)
 -----------------------------------------------------------------------------*/
STDMETHODIMP CLisaCOMTrajectory::LoadTrajectory(BSTR filename)
{
	USES_CONVERSION;
	SimFacade::Instance().loadTrajectory(COLE2T(filename));

	return S_OK;
}


