/** \file    NxOgreParams.h
 *  \brief   Header for the Params class.
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

#ifndef __NXOGRE_PARAMS_H__
#define __NXOGRE_PARAMS_H__

#include "NxOgrePrerequisites.h"
#include "NxOgreExtendedTypes.h"
#include "BetajaenCC.h"

namespace NxOgre {


	/** \brief Params, a way of giving a method or a constructor of a class. A
	           a number of arguments in any order, or using the default values
	           given.
	           
	    \usage Params can be given in a string format.
	           <code><pre>
	             ClassName* c = new ClassName("parameter: value, parameter2: value2");
	           </pre></code>
	           
	           Or a class based format.
	           
	           <code><pre>
	             ClassNameParams params;
	             params.setToDefault();
	             params.parameter = value;
	             params.parameter2 = value2;
	             ClassName* c = new ClassName(params);
	           </pre></code>
	           
	           Strings are regared as much easier, and quicker to implement. But slighty
	           slower than the class based params. If you are supplying more than 5 params
	           to a class, or converting many intergrals to strings then you should use the
	           class based params.
	   
	*/
	class NxPublicClass Params  {

		public:

			typedef Betajaen::Vector2<NxString> Parameter;
			typedef Betajaen::SharedList<Parameter> Parameters;

			void process(const NxString&);
			Parameters fromString(const NxString&);

			virtual void setToDefault() {}

			struct NxPublicClass Flags {

				virtual void toDefault()             {}
				virtual void fromNxU32(NxU32)        {}
				virtual NxU32 toNxU32() const        {return 0;}
				virtual void parse(const NxString&)  {}

				bool set(const NxString& match_str, const NxString& flag_str, bool& flag) {
					if (match_str == flag_str) {
						flag = true;
						return true;
					}
					return false;
				}


			};

		protected:

			virtual void parse(Parameters) {}

			bool Set(const NxString&, Parameter *, int&) const;
			bool Set(const NxString&, Parameter *, unsigned int&) const;
			bool Set(const NxString&, Parameter *, NxMaterialIndex&) const;
			bool Set(const NxString&, Parameter *, bool&) const;
			bool Set(const NxString&, Parameter *, NxReal&) const;
			bool Set(const NxString&, Parameter *, NxVec3&) const;
			bool Set(const NxString&, Parameter *, NxQuat&) const;
			bool Set(const NxString&, Parameter *, NxMat33&) const;
#if (NX_USE_OGRE == 1)
			bool Set(const NxString&, Parameter *, Ogre::Vector3&) const;
			bool Set(const NxString&, Parameter *, Ogre::Quaternion&) const;
#endif
			bool Set(const NxString&, Parameter *, NxString&) const;
			bool Set(const NxString&, Parameter *, NxHeightFieldAxis&) const;
			bool Set(const NxString&, Parameter *, NxU32&, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr) const;
			bool Set(const NxString&, Parameter *, NxU32&, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr) const;
			bool Set(const NxString&, Parameter *, NxU32&, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr) const;
			bool Set(const NxString&, Parameter *, NxU32&, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr, NxU32 enumE, NxString enumEStr) const;
			bool Set(const NxString&, Parameter *, NxU32&, NxU32 enumA, NxString enumAStr, NxU32 enumB, NxString enumBStr, NxU32 enumC, NxString enumCStr, NxU32 enumD, NxString enumDStr, NxU32 enumE, NxString enumEStr, NxU32 enumF, NxString enumFStr) const;
			bool Set(const NxString&, Parameter *, NxThreadPriority&) const;

			bool isYes(const NxString& yes) const;

			bool is(const NxString&, Parameter*);

	};

    /** \page WantParams
      *  Want Params in your application or engine? This is how it's done:
      *  
      *  <code><pre>
      *  class myParams : Params {
      *  
      *   public:
      *  
      *    myParams() {setToDefault();}
      *    myParams(const char* p) {process(p);}
      *    myParams(NxString p) {process(p);}
      *    
      *    void setToDefault() {
      *      jump = true;
      *      jumpHeight = 2.35f;
      *    }
      *  
      *  
      *    void parse(Parameters P) {
      *      
      *      setToDefault();
      *      
      *      for (Parameter* parameter = params.Begin(); parameter = params.Next();) {
      *        if (Set("jump", parameter, jump)	continue;
      *        if (Set("jump-height", parameter, jumpHeight) continue;
      *      }
      *    }
      *  
      *    bool jump;
      *    float jumpHeight;
      *  
      *  };
      *  
      *  </pre></code>
      *
      *  This is how it is used.
      *
      *  <code><pre>
      *  
      *    myParams my_params("jump: yes, jump-height: 1.53");
      *    
      *    // or:
      *    
      *    myParams my_params;
      *    my_params.setToDefault();
      *    my_params.jumpHeight = 3.21f;
      *  
      *  </pre></code>
      *
      *
      * The set method can process the following types:
      *  
      *   - int
      *   - unsigned int
      *   - bool                 (as Yes, No, True or False)
      *   - float
      *   - double
      *   - Ogre::Vector3        (If NX_USE_OGRE is set)
      *   - Ogre::Quaternion     (If NX_USE_OGRE is set)
      *   - NxVec3
      *   - NxQuat
      *   - NxString
      *   - NxHeightFieldAxis    (as x,y or z)
      *
      *  The string param, i.e. "jump" must be in lowercase for set to work properly. Commas
      *  cannot be used. Spaces are discouraged and it's recommended you use a underscore _
      *  instead.
      *
      *  Anything complicated such as enumerations have to be handled by hand in a 
      *  if statement. parameter->i is the identifier, and parameter->j is the value.
      *
      *  <code><pre>
      *   if (parameter->i == "jump-animation") {
      *     NxStringToLower(parameter->j);
      *     if (parameter->j == "stealthy") {
      *       jumpAnim = JA_Stealth;
      *     }
      *     else if (parameter->j == "comical") { {
      *       jumpAnim = JA_Comical;
      *     }
      *     else {
      *       jumpAnim = JA_Normal;
      *     }
      *   }
      *  </pre></code>
      *
      *  And that's how you use Params in your own application.
      *
      */

};

#endif
