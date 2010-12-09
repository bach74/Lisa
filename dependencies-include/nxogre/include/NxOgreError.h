/** \file    NxOgreError.h
 *  \brief   Header for the ErrorReport struct, the Error and ErrorReporter classes.
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

#ifndef __NXOGRE_ERROR_H__
#define __NXOGRE_ERROR_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreContainer.h"

namespace NxOgre {

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass ErrorReport {

		public:
		
			enum ErrorType {
				ET_Debug   = 0,
				ET_Warning = 1,
				ET_Error   = 2
			};

			struct TimeFrame {
				unsigned int seconds_passed;
				unsigned int simulations_passed;
			};

			const char*  mSource;
			unsigned int mSourceLine;
			const char*  mMessage;
			ErrorType    mType;
			TimeFrame    mTimeFrame;

	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass Error : public NxUserOutputStream {

		public:

			Error(PhysXDriver*, bool shutdownOnErrors = false);
			~Error();

			unsigned int addReporter(ErrorReporter*,bool own);
			void removeReporter(unsigned int id);

			void report(const ErrorReport&);
			void setShutdownOnErrors(bool);

			ErrorReport	getNewReport();

			static Error* getInstance()							{
																	return mError;
																}

			// NxUserOutputStream bits.

			/// reportError
			void reportError (NxErrorCode code, const char *message, const char* file, int line);
			
			/// reportAssertViolation
			NxAssertResponse reportAssertViolation (const char *message, const char *file,int line);
			
			/// print
			void print (const char *message);
			
			/// getErrorCode
			NxString getErrorCode(NxErrorCode);

		protected:

			NxU32 nbWarnings;
			NxU32 nbErrors;
			bool ShutdownOnErrors;

			ErrorReporterList mReporters;

		private:

			PhysXDriver *mDriver;
			static Error* mError;
	};

	///////////////////////////////////////////////////////////////////////

	class NxPublicClass ErrorReporter {

		public:

			ErrorReporter()										{}
			virtual ~ErrorReporter()							{}
			virtual void startReporting()						{}
			virtual void report(const ErrorReport&)				{}
			virtual void stopReporting()						{}
	};

/*

	// Example
	class myNxOgreErrorSystem : public ErrorReporter {

		public:

			myNxOgreErrorSystem() {
				MyErrorSystem::getSingleton()->createErrorSubSection("Physics");
			}

			~myNxOgreErrorSystem () {
				MyErrorSystem::getSingleton()->destroyErrorSubSection("Physics");
			}

			void report(const ErrorReport&) {
				MyErrorSystem::getSingleton()->reportError("Physics", r.Caller, r.Message, r.Frame);
			}

	};

*/

};

#endif
