#pragma once
#include "marker.h"

class MarkerVector : public Marker
{
	public:
		MarkerVector(void);
		~MarkerVector(void);

		void addObjectVector(const Ogre::String& name, Ogre::ColourValue color);

};
