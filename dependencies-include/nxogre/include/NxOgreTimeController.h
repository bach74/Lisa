/** \file    NxOgreTimeController.h
 *  \brief   Header for the TimeController class
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

#ifndef __NXOGRE_TIME_CONTROLLER_H__
#define __NXOGRE_TIME_CONTROLLER_H__

#include "NxOgrePrerequisites.h"

namespace NxOgre {

	/** \brief Injects time events into NxOgre which causes a simulation and a update of graphics.
		
		This class is totally abstract. It's upto YOU on how to implement it.
		
		But here are a few tips.
		
		1. Simulate and Render once every time step.
		2. Use the following methods to inject time into NxOgre.
		    - PhysXDriver::simulate
		    - PhysXDriver::render
		3. Use the simulate method first then render afterwards.
		4. Have a copy of the PhysXDriver handy. You can get a copy once
		   world was created.
		5. TimeController is deleted on the destruction of PhysXDriver
		6. Pass on the time as a variable time step rather than a fixed 
		   number, leave it to the Scene's controller for things like that.

		If your uncomfortable with this style of class or you have your own
		system of rendering then you can directly use PhysXDriver::simulate
		and PhysXDriver::render when ever needed. Just make sure the
		PhysXDriver::mCustomTimeControllerPtr pointer is zero and mTimeController
		is TC_NONE when passed into the PhysXDriver.
	*/
	class NxPublicClass TimeController {
		public:
			virtual ~TimeController() {}
	};

};

#endif
