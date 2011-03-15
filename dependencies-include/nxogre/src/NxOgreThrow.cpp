/** \file    NxOgreGlobalFunctions.cpp
 *  \brief   Source for the NxThrow function.
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

#include "NxOgreStable.h"
#include "NxOgrePrerequisites.h"
#include "NxOgreError.h"
#include "NxOgreHelpers.h"
namespace NxOgre {

	void NxPrint(const char* message, const char* header) {
		
		NxString str(message);
		NxStringTrim(str);

		unsigned int header_length = strlen(header) + 3;
		unsigned int c = header_length;
		unsigned int size = 75;
		printf("[%s] ", header);

		bool wrap = false;
		
		for (unsigned int i=0; i < str.size();i++) {

			c++;

			if (str[i] == '\n') {
				c = header_length;
				printf("\n[%s] ", header);
				continue;
			}

			if (c == size - 1) {
				if (i < strlen(message)) {
					if (str[i + 1] != ' ') {
						wrap = true;
						continue;
					}
				}
			}
			if (c == size) {
				if (message[i] != '\n') {
					c = header_length;
					printf("-\n[%s] ", header);
					if (wrap == true) {
						printf("%c", str[i - 1]);
						wrap = false;
					}
				}
			}

			printf("%c", str[i]);

		}
		printf("\n");

	}
	
	void NxThrow_impl(const char* message, unsigned int type, const char* source, unsigned int line)
	{ 

		if (Error::getInstance() == NULL) {
			NxPrint(message);
			return;
		}

		ErrorReport rp = Error::getInstance()->getNewReport();
		rp.mMessage = message;
		rp.mSource = source;
		rp.mType = (ErrorReport::ErrorType) type;

		Error::getInstance()->report(rp);

	}

	void NxToConsole(const NxString& string) {
		NxPrint(string.c_str());
	}

}; //End of NxOgre namespace.
