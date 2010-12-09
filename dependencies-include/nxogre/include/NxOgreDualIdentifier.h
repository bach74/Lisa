/** \file    NxOgreDualIdentifier.h
 *  \brief   Header for the DualIdentifier class.
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

#ifndef __NXOGRE_DUAL_IDENTIFIER_H__
#define __NXOGRE_DUAL_IDENTIFIER_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	/** \brief For a class that has two types of identifiers.
	*/
	template <typename First, typename Second>
	class DualIdentifier {

		public:

			NxTemplateFunction DualIdentifier()
				: firstSet(false), secondSet(false) {}

			NxTemplateFunction DualIdentifier(First _first)
				: first(_first), firstSet(true), secondSet(false) {}

			NxTemplateFunction DualIdentifier(Second _second)
				: second(_second), secondSet(true), firstSet(false) {}

			NxTemplateFunction DualIdentifier(First _first, Second _second)
				: first(_first), second(_second), firstSet(true), secondSet(true) {}

			NxTemplateFunction DualIdentifier(Second second, First first)
				: first(_first), second(_second), firstSet(true), secondSet(true) {}

			NxTemplateFunction First getFirst() const {return first;}
			NxTemplateFunction Second getSecond() const {return second;}

			NxTemplateFunction void set(const First& _first) {first = _first;firstSet = true;}
			NxTemplateFunction void set(const Second& _second) {second = _second;secondSet = true;}

			NxTemplateFunction bool hasFirst() const {return firstSet;}
			NxTemplateFunction bool hasSecond() const {return secondSet;}

		protected:

			First first;
			Second second;

			bool firstSet, secondSet;

	};

	/** \brief Simple class that allows some sort of visual reference passed along as an identifier
	           for a class.
	    \example
	      <code>
	       new ClassName("identifier");
	       new ClassName("identifier; visualIdentifier");
	       new ClassName(VisualIdentifier("identifier","visualIdentifier"));
	      </code>
	*/
	class NxPublicClass VisualIdentifier {

		public:

			VisualIdentifier();
			VisualIdentifier(const char*);
			VisualIdentifier(const NxString&);
			VisualIdentifier(const NxString& _identifier, const NxString& _visualisation);
			
			NxString getIdentifier() const {
				return mIdentifier;
			}

			NxString getVisualIdentifier() const {
				return mVisualIdentifier;
			}
			
		protected:

			NxString mIdentifier;
			NxString mVisualIdentifier;

	};

	
};

#endif


