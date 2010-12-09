/** \file    NxOgreLog.h
 *  \brief   Header for the Log class.
 *  \version 1.0-21
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

#ifndef __NXOGRE_LOG_H__
#define __NXOGRE_LOG_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreError.h"			// For: Log inherits ErrorReporter

namespace NxOgre {

	class NxPublicClass Log : public ErrorReporter {
		
		public:

			Log();
			~Log();

			void startReporting();
			void report(const ErrorReport& report) = 0;
			void stopReporting();

			virtual NxString getFileExtension() const = 0;
			virtual void createHeader() = 0;
			virtual void createFooter() = 0;

		protected:

			NxOgre::Resources::Resource* mStream;
	};

	/////////////////////////////////////////////////////////////

	class NxPublicClass HTMLLog : public Log {

		public:

			HTMLLog();
			~HTMLLog();

			NxString getFileExtension() const {return "html";}
			void createHeader();
			void createCSSStyle();
			void report(const ErrorReport& report);
			void createFooter();

			void formatAsHTML(NxString&);

	};


#if 0
	class NxPublicClass Log : public ErrorReporter {

		public:

			enum logType {
				TEXT = 1,
				HTML = 2,
				PHPBB = 3
			};

			Log(logType);
			~Log();
			void report(const ErrorReport&);

		private:

			void openAsHTML(const NxString&);
			void openAsText(const NxString&);
			void openAsPHPBB(const NxString&);

			void reportAsHTML(const ErrorReport&);
			void reportAsText(const ErrorReport&);
			void reportAsPHPBB(const ErrorReport&);

			void closeAsHTML();
			void closeAsText();
			void closeAsPHPBB();

			std::string encodeHTML(std::string);

			logType mType;

			unsigned int nbReports;
	};
#endif
};

#endif
