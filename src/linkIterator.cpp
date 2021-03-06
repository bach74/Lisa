// =============================================================================
//  linkIterator.cpp   
//  
//  Copyright (C) 2007-2012 by Bach 
//  This file is part of the LiSA project.
//  The LiSA project is licensed under MIT license.
// 
// =============================================================================

#include "stdafx.h"
#include "linkIterator.h"
#include "links.h"

/**-------------------------------------------------------------------------------
	begin

	@brief
	@return LinkIterator&
---------------------------------------------------------------------------------*/
LinkIterator& LinkIterator::begin()
{
	if (mLinks!=NULL)
	{
		mNode=mLinks->begin();
	}
	return *this;
}

/**-------------------------------------------------------------------------------
	end

	@brief
	@return bool
---------------------------------------------------------------------------------*/
bool LinkIterator::end()
{
	if (mLinks)
	{
		return mNode==mLinks->end();
	}
	else
	{
		return true;
	}
}

/**-------------------------------------------------------------------------------
	increment

	@brief
	@return void
---------------------------------------------------------------------------------*/
void LinkIterator::increment()
{
	++mNode;
}

/**-------------------------------------------------------------------------------
	equal

	@brief
	@param other
	@return bool
---------------------------------------------------------------------------------*/
bool LinkIterator::equal(LinkIterator const& other) const
{
	return mNode==other.mNode && mLinks==other.mLinks;
}
