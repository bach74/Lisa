#ifndef __MARKERVECTOR_H__
#define __MARKERVECTOR_H__
#include "marker.h"

class MarkerVector : public Marker
{
	public:
		MarkerVector(void);
		~MarkerVector(void);

		void addObjectVector(const Ogre::String& name, Ogre::ColourValue color);

};

 #endif