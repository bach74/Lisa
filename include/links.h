// =============================================================================
//  Links.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __LINKS_H__
#define __LINKS_H__

#include "link.h"

/**-------------------------------------------------------------------------------
	Class Links is a collection of links
---------------------------------------------------------------------------------*/
class Links
{

	public:
		Links() {};
		~Links() { mLinks.clear(); };

		friend class LinkIterator;

		size_t size() { return mLinks.size(); }
		void add(boost::shared_ptr<Link> link) { mLinks.push_back(link); }

		typedef LinkIterator iterator;

	private:
		std::vector<boost::shared_ptr<Link> >::iterator begin() { return mLinks.begin(); }
		std::vector<boost::shared_ptr<Link> >::iterator end() { return mLinks.end(); }

		std::vector<boost::shared_ptr<Link> > mLinks;
};

 #endif