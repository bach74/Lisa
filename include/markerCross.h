#pragma once
#include "marker.h"

class MarkerCross : public Marker
{
	public:
		MarkerCross(void);
		~MarkerCross(void);

		void addObjectCross(const Ogre::String& name, Ogre::ColourValue color, float scale);
};
