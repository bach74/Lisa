/** \file    NxOgreError.cpp
 *  \see     NxOgreError.h
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
 *           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *           Lesser General Public License for more details.
 *           
 *           You should have received a copy of the GNU Lesser General Public
 *           License along with this library; if not, write to the Free Software
 *           Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "NxOgreStable.h"
#include "NxOgreError.h"
#include "NxOgrePhysXDriver.h"			// For: World Access
#include "NxOgreWorld.h"				// For: World->Shutodwn

#include "OgreRoot.h"
#include "OgreSingleton.h"

namespace NxOgre {

////////////////////////////////////////////////////////////////////////////////////////////////

Error* Error::mError = 0;

////////////////////////////////////////////////////////////////////////////////////////////////

Error::Error(PhysXDriver *d, bool b) {
	
	if (mError) {
		ErrorReport rp = getNewReport();
		rp.mMessage = "Error Instance has been created more than once!";
		rp.mSource = typeid(this).name();
		rp.mSourceLine = 0;
		report(rp);
		return;
	}

	nbErrors = 0;
	nbWarnings = 0;
	mDriver = d;
	ShutdownOnErrors = b;
	mError = this;
}

////////////////////////////////////////////////////////////////////////////////////////////////

Error::~Error() {

	for(ErrorReporter* reporter = mReporters.begin();reporter = mReporters.next();) {
		if (reporter)
			reporter->stopReporting();
	}

	mReporters.destroyAllOwned();
	mError = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Error::addReporter(ErrorReporter* e,bool o) {
	mReporters.insert(mReporters.count(), e);
	mReporters.lock(mReporters.count() - 1, o);
	e->startReporting();
	return mReporters.count() - 1; 
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Error::removeReporter(unsigned int id) {

	mReporters.get(id)->stopReporting();
	
	if (mReporters.isLocked(id))
		delete mReporters.get(id);
	mReporters.remove(id);

}

////////////////////////////////////////////////////////////////////////////////////////////////

void Error::reportError(NxErrorCode code, const char *message, const char* file, int line) {

	NxString str_code = getErrorCode(code);
	printf("PhysX Error! %s (%s:%i)\n%s\n", str_code.c_str(), file, line, message);
	/// \todo Report as a message.
}

////////////////////////////////////////////////////////////////////////////////////////////////

NxAssertResponse Error::reportAssertViolation(const char *message, const char *file,int line) {
	printf("PhysX Assertion! (%s:%i)\n%s\n", file, line, message);
	/// \todo Report as a message.
	return NX_AR_CONTINUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Error::print (const char *message) {
	printf("PhysX message\n%s\n", message);
	NxDebug(message);
}

////////////////////////////////////////////////////////////////////////////////////////////////

NxString Error::getErrorCode(NxErrorCode c) {

	NxString e;

	switch(c) {
		case NXE_ASSERTION:				e = "NXE_ASSERTION:";			break;
		case NXE_DB_INFO:				e = "NXE_DB_INFO";				break;
		case NXE_DB_PRINT:				e = "NXE_DB_PRINT";				break;
		case NXE_DB_WARNING:			e = "NXE_DB_WARNING";			break;
		case NXE_INTERNAL_ERROR:		e = "NXE_INTERNAL_ERROR";		break;
		case NXE_INVALID_OPERATION:		e = "NXE_INVALID_OPERATION";	break;
		case NXE_INVALID_PARAMETER:		e = "NXE_INVALID_PARAMETER";	break;
		case NXE_NO_ERROR:				e = "NXE_NO_ERROR";				break;
		case NXE_OUT_OF_MEMORY:			e = "NXE_OUT_OF_MEMORY";		break;
		default:						e = "Unknown";					break;
	}

	return e;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Error::report(const ErrorReport& er) {

	if (er.mType == ErrorReport::ET_Error)
		nbErrors++;
	else if (er.mType == ErrorReport::ET_Warning)
		nbWarnings++;

	if (mReporters.count()) {
		for(ErrorReporter* reporter = mReporters.begin();reporter = mReporters.next();) {
			if (reporter)
				reporter->report(er);
		}
	}

	if (ShutdownOnErrors)
		mDriver->getWorld()->shutdown();

}

////////////////////////////////////////////////////////////////////////////////////////////////

void Error::setShutdownOnErrors(bool b) {
	ShutdownOnErrors = b;
}

////////////////////////////////////////////////////////////////////////////////////////////////

ErrorReport	Error::getNewReport() {
	ErrorReport r;
	r.mSourceLine = 0;
	r.mTimeFrame.seconds_passed = mDriver->getTime();
	r.mTimeFrame.simulations_passed = mDriver->getNbSimulations();
	return r;
}

////////////////////////////////////////////////////////////////////////////////////////////////

}; //End of NxOgre namespace.
