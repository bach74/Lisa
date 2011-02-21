// =============================================================================
//  LinkIterator.h   version:  1.5
//
//  Copyright (C) 2007-2010 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
//
// =============================================================================
#ifndef __LINKITERATOR_H__
#define __LINKITERATOR_H__

#include "link.h"
#include "links.h"

/**-------------------------------------------------------------------------------
	LinkIterator facilitates iteration through Link objects
---------------------------------------------------------------------------------*/
class LinkIterator : public boost::iterator_facade<LinkIterator, Link, boost::forward_traversal_tag>
{
	public:
		LinkIterator(Links* links):mLinks(links) { begin();};
		~LinkIterator() {};

		LinkIterator& begin();
		bool end();

	private:
		LinkIterator():mLinks(NULL) {};

		friend class boost::iterator_core_access;

		void increment();
		bool equal(LinkIterator const& other) const;
		Link& dereference() const { return *(*mNode); }

		std::vector<boost::shared_ptr<Link> >::iterator mNode;
		Links* mLinks;
};

 #endif