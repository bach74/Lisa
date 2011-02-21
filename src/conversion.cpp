// =============================================================================
//  Conversion.cpp   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#include "stdafx.h"
#include "conversion.h"


#ifdef _ATL
/**-------------------------------------------------------------------------------
	Convert vector to SAFEARRAY

	\param		vector vect
	\param		SAFEARRAY sa
	\return	nothing
--------------------------------------------------------------------------------*/
void Conversion::vector2SAFEARRAY(const std::vector<double>& vect,SAFEARRAY** sa)
{

	SAFEARRAYBOUND *saBound=new SAFEARRAYBOUND[1];
	saBound[0].lLbound=0;
	saBound[0].cElements=(vect.size()>0)?vect.size():0;

	*sa=SafeArrayCreate(VT_R8,1,saBound);

	// initialize the data
	double HUGEP* pData;
	SafeArrayAccessData(*sa,(void**)&pData);
		for (std::vector<double>::const_iterator it=vect.begin();it!=vect.end();++it) {
			*pData++=(*it);
		}
	SafeArrayUnaccessData(*sa);

}

/**-------------------------------------------------------------------------------
	Convert vector to SAFEARRAY

	\param		SAFEARRAY sa
	\param		vector vect
	\return	nothing
--------------------------------------------------------------------------------*/
void Conversion::SAFEARRAY2vector(SAFEARRAY& sa, std::vector<double>& vect)
{
	double* pData;
	SafeArrayAccessData(&sa,(void**)&pData);
		for (UINT i=0;i<sa.rgsabound[0].cElements;++i)
		{
			vect.push_back(double());
			vect.back()=*pData++;
		}
	SafeArrayUnaccessData(&sa);
}


/**----------------------------------------------------------------------------
	Convert function, vector3 to safearray.
   
	\param vect (Ogre::Vector3 &)
	\return (SAFEARRAY*)
 -----------------------------------------------------------------------------*/
SAFEARRAY* Conversion::Vector3toSAFEARRAY(Ogre::Vector3& vect)
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

#endif