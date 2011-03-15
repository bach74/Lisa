/** \file    NxOgreAllocator.cpp
 *  \see     NxOgreAllocator.h
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
#include "NxOgreAllocator.h"
#include "NxOgreResourceSystem.h"
#include "NxOgreResource.h"

namespace NxOgre {

/////////////////////////////////////////////////////////////

Allocator* Allocator::mAllocatorPtr = 0;

/////////////////////////////////////////////////////////////

Allocator::Allocator() {
	mAllocatorPtr = this;
	NbNew = 0;
	NbDelete = 0;
	mLeakFile = 0;
}

/////////////////////////////////////////////////////////////

Allocator::~Allocator() {

	if (mLeakFile)
		dump();

#if 0
	mLeakFile->writeString("NxOgre leaks report at ");
	char* timeStr = new char[32];
	time_t t = time(NULL);
	struct tm *tme = localtime(&t);
	unsigned int timeStrLen = sprintf(timeStr, " %02d/%02d/%04d %02d:%02d:%02d", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
	mLeakFile->write(timeStr, timeStrLen);
	delete [] timeStr;
	mLeakFile->writeString(" .\n\n");

	if (mAllocations.Size()) {
		
		{
			char* str = new char[25];
			unsigned int strLen = sprintf(str, "%i leaks found!\n\n", mAllocations.Size());
			mLeakFile->write(str, strLen);
			delete [] str;
		}

		for (WatchedPointer* item = mAllocations.Begin(); item = mAllocations.Next();) {
			mLeakFile->write(item->getDescription(), item->getDescriptionLength());
			mLeakFile->writeUChar('\n');
		}

	}
	else {
		mLeakFile->writeString("No leaks found.\n\n");
	}

	char* str = new char[64];
	unsigned int strl = sprintf(str, "\n\nNb of NxNew: %i, Nb of NxDelete: %i\n", NbNew, NbDelete);
	mLeakFile->write(str, strl);
	delete [] str;
	mLeakFile->writeString("Leaks marked with a (0) indicate the pointer is zero and may be deleted, otherwise at the time this log has been written the data is still there.");
#endif

}

/////////////////////////////////////////////////////////////

Allocator* Allocator::getPtr() {
	return mAllocatorPtr;
}

/////////////////////////////////////////////////////////////

void Allocator::createLeakFile() {
	if (mLeakFile == 0)
		mLeakFile = Resources::ResourceSystem::getSingleton()->get("file://NxOgre.leaks.html", Resources::RA_ReadWrite);
}

/////////////////////////////////////////////////////////////

void Allocator::watch_new(void* ptr, const char* type_id, const char* fileName, const char* function, unsigned int line, unsigned int sz, const char* description) {

	// No duplicates.
	if (mAllocations.Size() != 0) {
		for (WatchedPointer* item = mAllocations.Begin(); item = mAllocations.Next();) {
			if (item->getPtr() == ptr)
				return;
		}
	}

	NbNew++;

	WatchedPointer* wptr = new WatchedPointer();
	wptr->mPtr = ptr;
	wptr->mFile.set(fileName);
	wptr->mMethod.set(function);
	wptr->mPtrType.set(type_id);
	wptr->mDescription.set(description);
	wptr->mLine = line;
	wptr->mSize = sz;
	mAllocations.Insert(wptr);

}

/////////////////////////////////////////////////////////////

void Allocator::watch_delete(void* ptr) {

	if (mAllocatorPtr == 0)
		return;

	if (ptr == 0)
		return;

	if (mAllocations.Size() == 0)
		return;


	for (WatchedPointer* item = mAllocations.Begin(); item = mAllocations.Next();) {
		if (item->getPtr() == ptr) {
			unsigned int i = mAllocations.WhereIs(item);
			mAllocations.Destroy(i);
			NbDelete++;
			return;
		}
	}

	// printf("Warning; Trying to NxDelete a non-watched pointer (%p), pointer is however deleted. \n", ptr);

}

/////////////////////////////////////////////////////////////

void Allocator::dump() {

	// This should be done...But probably the resource system is dead right now.
	
	//FileResourceStream* mLeakFile = new FileResourceStream("file://NxOgre.leaks.html +write");

#ifndef NX_SMALL
	char header[3294] = {60, 33, 68, 79, 67, 84, 89, 80, 69, 32, 104, 116, 109, 108, 32, 80, 85, 66, 76, 73, 67, 
	32, 34, 45, 47, 47, 87, 51, 67, 47, 47, 68, 84, 68, 32, 88, 72, 84, 77, 76, 32, 49, 
	46, 48, 32, 83, 116, 114, 105, 99, 116, 47, 47, 69, 78, 34, 13, 10, 9, 34, 104, 116, 116, 
	112, 58, 47, 47, 119, 119, 119, 46, 119, 51, 46, 111, 114, 103, 47, 84, 82, 47, 120, 104, 116, 
	109, 108, 49, 47, 68, 84, 68, 47, 120, 104, 116, 109, 108, 49, 45, 115, 116, 114, 105, 99, 116, 
	46, 100, 116, 100, 34, 62, 13, 10, 60, 104, 116, 109, 108, 32, 120, 109, 108, 110, 115, 61, 34, 
	104, 116, 116, 112, 58, 47, 47, 119, 119, 119, 46, 119, 51, 46, 111, 114, 103, 47, 49, 57, 57, 
	57, 47, 120, 104, 116, 109, 108, 34, 62, 13, 10, 60, 104, 101, 97, 100, 62, 13, 10, 9, 60, 
	116, 105, 116, 108, 101, 62, 78, 120, 79, 103, 114, 101, 32, 76, 101, 97, 107, 115, 60, 47, 116, 
	105, 116, 108, 101, 62, 13, 10, 9, 9, 9, 60, 115, 116, 121, 108, 101, 62, 13, 10, 9, 9, 
	9, 9, 98, 111, 100, 121, 32, 123, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 58, 35, 49, 
	50, 49, 50, 49, 50, 59, 99, 111, 108, 111, 114, 58, 119, 104, 105, 116, 101, 59, 102, 111, 110, 
	116, 45, 102, 97, 109, 105, 108, 121, 58, 72, 101, 108, 118, 101, 116, 105, 99, 97, 44, 115, 97, 
	110, 115, 45, 115, 101, 114, 105, 102, 59, 102, 111, 110, 116, 45, 115, 105, 122, 101, 58, 56, 48, 
	37, 59, 112, 97, 100, 100, 105, 110, 103, 45, 116, 111, 112, 58, 49, 101, 109, 59, 125, 13, 10, 
	9, 9, 9, 9, 104, 49, 32, 123, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 58, 32, 117, 
	114, 108, 40, 34, 100, 97, 116, 97, 58, 105, 109, 97, 103, 101, 47, 112, 110, 103, 59, 98, 97, 
	115, 101, 54, 52, 44, 105, 86, 66, 79, 82, 119, 48, 75, 71, 103, 111, 65, 65, 65, 65, 78, 
	83, 85, 104, 69, 85, 103, 65, 65, 65, 80, 111, 65, 65, 65, 66, 80, 67, 65, 77, 65, 65, 
	65, 68, 49, 78, 83, 106, 74, 65, 65, 65, 65, 71, 70, 66, 77, 86, 69, 85, 75, 67, 103, 
	114, 43, 47, 118, 52, 116, 76, 83, 49, 86, 86, 86, 87, 69, 104, 73, 84, 89, 50, 78, 105, 
	116, 114, 97, 51, 47, 47, 47, 43, 89, 53, 83, 85, 122, 65, 65, 65, 65, 67, 72, 82, 83, 
	84, 108, 80, 47, 47, 47, 47, 47, 47, 47, 47, 47, 65, 78, 54, 68, 118, 86, 107, 65, 65, 
	65, 65, 90, 100, 69, 86, 89, 100, 70, 78, 118, 90, 110, 82, 51, 89, 88, 74, 108, 65, 69, 
	70, 107, 98, 50, 74, 108, 73, 69, 108, 116, 89, 87, 100, 108, 85, 109, 86, 104, 90, 72, 108, 
	120, 121, 87, 85, 56, 65, 65, 65, 70, 43, 48, 108, 69, 81, 86, 82, 52, 50, 117, 50, 99, 
	50, 89, 75, 107, 73, 65, 120, 70, 89, 122, 98, 43, 47, 52, 47, 110, 81, 85, 71, 87, 104, 
	77, 87, 121, 50, 54, 114, 113, 52, 87, 50, 113, 111, 51, 104, 89, 65, 114, 109, 66, 103, 102, 
	66, 110, 67, 47, 120, 116, 100, 69, 120, 108, 49, 66, 67, 55, 49, 90, 86, 113, 69, 73, 110, 
	52, 76, 69, 83, 69, 56, 68, 119, 54, 98, 75, 110, 119, 119, 72, 105, 51, 87, 118, 120, 109, 
	73, 70, 98, 90, 106, 67, 76, 75, 66, 79, 43, 67, 118, 117, 72, 100, 54, 69, 67, 54, 100, 
	81, 118, 106, 109, 54, 68, 76, 122, 101, 103, 111, 50, 55, 65, 111, 118, 65, 88, 54, 82, 114, 
	101, 105, 56, 122, 90, 84, 66, 78, 56, 67, 88, 101, 66, 71, 57, 73, 120, 99, 109, 79, 104, 
	48, 112, 49, 104, 79, 102, 52, 70, 110, 48, 87, 88, 115, 54, 82, 98, 82, 77, 88, 111, 122, 
	81, 103, 68, 68, 54, 82, 80, 76, 122, 70, 106, 55, 101, 88, 83, 83, 111, 97, 100, 98, 81, 
	119, 99, 90, 43, 106, 71, 73, 108, 99, 75, 106, 54, 66, 65, 72, 80, 116, 121, 69, 84, 106, 
	115, 53, 122, 76, 81, 80, 80, 89, 115, 101, 112, 121, 98, 102, 104, 75, 53, 84, 48, 51, 104, 
	102, 65, 47, 82, 104, 100, 66, 103, 78, 43, 83, 88, 48, 102, 97, 98, 114, 84, 83, 51, 48, 
	119, 43, 106, 74, 76, 57, 50, 67, 122, 112, 77, 106, 109, 83, 98, 50, 85, 106, 43, 80, 72, 
	114, 84, 118, 99, 74, 102, 81, 90, 82, 74, 112, 72, 50, 118, 48, 78, 80, 114, 65, 48, 54, 
	50, 103, 72, 55, 77, 72, 74, 116, 117, 73, 110, 48, 89, 102, 101, 76, 111, 108, 57, 71, 108, 
	98, 102, 99, 106, 80, 86, 101, 106, 81, 88, 87, 100, 88, 48, 72, 72, 97, 108, 115, 102, 66, 
	119, 50, 43, 103, 72, 48, 55, 72, 54, 89, 82, 49, 57, 66, 110, 80, 84, 84, 101, 52, 101, 
	65, 65, 65, 101, 66, 71, 57, 54, 43, 108, 121, 83, 48, 47, 98, 103, 79, 77, 80, 115, 50, 
	116, 98, 98, 71, 50, 111, 78, 55, 109, 115, 113, 113, 113, 99, 74, 73, 50, 121, 80, 106, 106, 
	47, 105, 85, 99, 56, 73, 78, 112, 117, 72, 65, 69, 112, 118, 89, 109, 53, 108, 69, 99, 97, 
	100, 79, 104, 69, 70, 73, 90, 88, 81, 72, 116, 78, 107, 54, 80, 88, 101, 82, 111, 57, 101, 
	120, 71, 121, 116, 67, 69, 57, 108, 68, 50, 83, 50, 103, 118, 86, 68, 89, 67, 66, 117, 73, 
	109, 90, 53, 87, 121, 101, 66, 106, 48, 79, 101, 82, 52, 78, 101, 68, 87, 55, 108, 87, 75, 
	76, 48, 67, 74, 54, 103, 103, 75, 49, 81, 51, 112, 112, 48, 99, 85, 73, 105, 51, 71, 111, 
	70, 83, 104, 54, 54, 72, 72, 73, 52, 119, 68, 100, 51, 72, 50, 102, 80, 57, 76, 48, 51, 
	114, 121, 48, 116, 68, 57, 89, 119, 69, 74, 88, 81, 120, 67, 81, 113, 103, 117, 116, 81, 104, 
	54, 54, 80, 43, 82, 76, 83, 122, 76, 77, 79, 72, 88, 83, 82, 88, 84, 73, 121, 70, 86, 
	86, 78, 82, 71, 112, 103, 85, 53, 82, 67, 48, 66, 77, 81, 112, 104, 97, 53, 78, 109, 98, 
	85, 114, 99, 97, 54, 76, 69, 112, 97, 89, 65, 101, 103, 57, 74, 50, 82, 99, 78, 119, 71, 
	90, 50, 84, 115, 111, 69, 65, 65, 81, 76, 69, 115, 70, 54, 78, 88, 116, 57, 78, 111, 55, 
	82, 53, 122, 72, 111, 112, 86, 109, 108, 108, 119, 116, 51, 55, 65, 121, 67, 120, 90, 115, 49, 
	106, 111, 98, 116, 104, 84, 71, 87, 74, 106, 90, 109, 101, 106, 84, 71, 47, 78, 99, 47, 82, 
	106, 49, 100, 87, 107, 83, 54, 48, 109, 103, 90, 90, 106, 107, 49, 80, 71, 121, 113, 98, 112, 
	82, 89, 73, 48, 69, 70, 51, 70, 47, 102, 97, 107, 105, 117, 122, 102, 65, 112, 99, 81, 49, 
	99, 110, 120, 109, 99, 80, 118, 88, 84, 112, 53, 53, 53, 89, 80, 78, 71, 80, 107, 111, 50, 
	74, 55, 105, 51, 117, 106, 86, 99, 111, 80, 82, 51, 107, 57, 86, 49, 67, 66, 57, 102, 76, 
	113, 73, 49, 101, 109, 86, 76, 115, 105, 115, 55, 83, 113, 110, 72, 122, 97, 75, 79, 106, 55, 
	101, 107, 97, 121, 51, 76, 76, 86, 111, 83, 112, 56, 43, 104, 52, 80, 117, 90, 47, 77, 100, 
	110, 111, 90, 76, 120, 75, 85, 116, 43, 104, 88, 120, 49, 52, 54, 69, 52, 89, 52, 48, 48, 
	78, 122, 98, 85, 74, 101, 65, 71, 100, 51, 89, 102, 113, 112, 90, 84, 77, 118, 111, 110, 111, 
	118, 98, 65, 120, 55, 89, 48, 99, 100, 78, 118, 84, 71, 90, 98, 110, 120, 120, 55, 68, 72, 
	90, 89, 86, 105, 71, 122, 65, 100, 55, 53, 89, 76, 88, 81, 78, 68, 110, 111, 110, 116, 122, 
	70, 67, 116, 122, 50, 100, 89, 81, 108, 74, 49, 54, 108, 89, 114, 54, 68, 51, 79, 111, 115, 
	116, 100, 79, 54, 105, 99, 48, 100, 73, 89, 66, 47, 100, 57, 72, 83, 87, 90, 102, 120, 119, 
	113, 66, 83, 72, 83, 43, 105, 100, 97, 73, 56, 115, 57, 78, 111, 80, 111, 54, 111, 113, 70, 
	51, 80, 73, 71, 84, 56, 57, 100, 77, 118, 84, 109, 90, 97, 72, 114, 77, 105, 86, 57, 88, 
	86, 48, 68, 90, 102, 82, 68, 102, 102, 104, 83, 121, 77, 117, 117, 117, 88, 112, 84, 77, 116, 
	56, 54, 52, 110, 104, 74, 102, 82, 101, 116, 73, 99, 87, 79, 108, 54, 82, 79, 115, 102, 111, 
	104, 113, 102, 114, 106, 111, 47, 113, 111, 54, 43, 106, 48, 43, 80, 111, 104, 113, 102, 114, 106, 
	52, 57, 121, 99, 106, 121, 75, 102, 109, 119, 122, 50, 83, 119, 121, 82, 109, 47, 68, 109, 80, 
	110, 120, 77, 90, 104, 117, 118, 52, 80, 101, 84, 101, 114, 51, 48, 81, 56, 107, 103, 90, 69, 
	50, 82, 56, 98, 118, 110, 52, 51, 101, 90, 71, 77, 71, 118, 85, 52, 102, 104, 67, 55, 81, 
	82, 54, 56, 70, 71, 56, 99, 121, 66, 90, 66, 116, 71, 68, 65, 106, 85, 74, 48, 98, 119, 
	116, 43, 90, 54, 47, 115, 82, 114, 107, 71, 118, 49, 52, 76, 78, 121, 77, 78, 114, 56, 43, 
	105, 106, 54, 76, 103, 111, 82, 118, 99, 87, 57, 43, 71, 54, 84, 106, 87, 54, 84, 113, 80, 
	68, 117, 54, 71, 88, 50, 82, 106, 84, 99, 113, 43, 71, 54, 43, 48, 51, 84, 74, 122, 73, 
	75, 114, 97, 68, 65, 51, 83, 54, 98, 86, 50, 102, 82, 73, 43, 106, 87, 86, 51, 48, 109, 
	71, 113, 111, 81, 54, 107, 113, 107, 66, 117, 105, 106, 47, 122, 68, 66, 88, 82, 54, 68, 98, 
	48, 73, 89, 54, 122, 73, 76, 83, 107, 122, 86, 86, 81, 90, 90, 106, 79, 116, 99, 66, 54, 
	114, 119, 78, 85, 57, 80, 70, 55, 90, 119, 48, 43, 106, 53, 53, 55, 79, 106, 100, 101, 122, 
	105, 66, 80, 98, 75, 84, 121, 84, 107, 117, 85, 119, 105, 78, 120, 52, 72, 90, 49, 102, 82, 
	77, 56, 57, 110, 97, 102, 83, 53, 69, 76, 107, 115, 108, 97, 66, 51, 86, 72, 86, 108, 121, 
	113, 119, 50, 53, 121, 79, 111, 121, 69, 105, 73, 112, 112, 66, 122, 122, 121, 100, 74, 49, 116, 
	106, 76, 104, 49, 121, 85, 102, 48, 89, 80, 86, 99, 108, 47, 85, 108, 105, 67, 49, 81, 68, 
	100, 66, 115, 112, 78, 115, 115, 89, 80, 102, 78, 48, 106, 87, 85, 74, 87, 43, 110, 121, 107, 
	48, 101, 106, 117, 77, 110, 106, 111, 102, 56, 82, 115, 43, 103, 57, 82, 122, 77, 84, 118, 106, 
	82, 55, 117, 116, 113, 121, 49, 103, 97, 53, 70, 87, 105, 72, 76, 114, 53, 89, 67, 102, 119, 
	99, 74, 83, 43, 104, 57, 120, 82, 90, 87, 69, 70, 80, 89, 89, 121, 100, 102, 97, 72, 97, 
	107, 66, 100, 87, 109, 74, 76, 87, 49, 43, 70, 108, 68, 98, 50, 122, 86, 105, 83, 51, 79, 
	111, 79, 101, 73, 110, 100, 97, 121, 76, 109, 108, 47, 117, 121, 101, 57, 115, 56, 84, 81, 102, 
	89, 114, 121, 56, 84, 122, 76, 72, 114, 110, 47, 66, 97, 78, 70, 70, 108, 122, 121, 71, 116, 
	104, 121, 87, 54, 109, 57, 102, 106, 116, 84, 66, 48, 54, 82, 51, 78, 83, 54, 108, 43, 114, 
	110, 69, 97, 100, 99, 57, 78, 116, 70, 84, 49, 79, 69, 67, 47, 65, 120, 108, 108, 48, 75, 
	74, 76, 101, 89, 65, 47, 51, 122, 70, 67, 114, 112, 48, 83, 90, 105, 100, 75, 120, 99, 67, 
	73, 105, 86, 112, 71, 116, 68, 102, 107, 48, 72, 88, 54, 73, 89, 43, 116, 111, 73, 70, 108, 
	68, 106, 51, 85, 76, 110, 54, 101, 121, 65, 86, 73, 113, 87, 109, 69, 87, 118, 81, 121, 65, 
	73, 101, 117, 74, 87, 117, 97, 110, 102, 77, 106, 84, 78, 108, 102, 73, 67, 103, 78, 70, 108, 
	102, 107, 56, 78, 115, 57, 114, 54, 77, 86, 90, 102, 70, 86, 86, 122, 90, 118, 97, 122, 55, 
	81, 79, 117, 106, 48, 55, 83, 121, 80, 101, 87, 82, 114, 73, 48, 112, 111, 106, 49, 89, 68, 
	77, 52, 76, 57, 113, 72, 86, 104, 69, 55, 56, 111, 86, 70, 79, 98, 82, 105, 121, 56, 67, 
	77, 55, 100, 117, 101, 110, 110, 103, 69, 88, 119, 57, 114, 56, 48, 84, 74, 85, 74, 104, 71, 
	100, 49, 118, 100, 54, 71, 119, 103, 104, 54, 48, 81, 80, 100, 99, 99, 101, 115, 68, 65, 74, 
	50, 114, 88, 115, 101, 90, 66, 50, 77, 104, 113, 121, 57, 74, 67, 85, 79, 52, 103, 66, 54, 
	65, 106, 74, 112, 70, 89, 53, 88, 55, 70, 84, 56, 105, 71, 116, 48, 52, 65, 54, 82, 89, 
	73, 65, 81, 103, 82, 79, 43, 90, 51, 82, 67, 114, 90, 53, 108, 86, 86, 89, 54, 105, 121, 
	107, 122, 109, 116, 90, 68, 52, 67, 109, 89, 86, 69, 100, 70, 48, 50, 75, 49, 67, 104, 53, 
	108, 118, 84, 103, 102, 119, 122, 107, 113, 122, 107, 51, 79, 47, 101, 103, 52, 100, 85, 112, 107, 
	50, 98, 104, 79, 107, 49, 43, 116, 116, 73, 55, 102, 80, 75, 75, 43, 103, 117, 48, 72, 114, 
	102, 47, 84, 47, 54, 77, 47, 121, 77, 84, 80, 98, 116, 56, 79, 43, 72, 116, 51, 110, 119, 
	50, 57, 72, 57, 43, 47, 66, 51, 72, 56, 55, 54, 77, 51, 109, 117, 113, 47, 115, 122, 75, 
	113, 99, 72, 52, 118, 117, 88, 110, 113, 98, 108, 47, 85, 47, 70, 100, 49, 86, 100, 110, 103, 
	54, 104, 102, 101, 112, 54, 71, 67, 102, 98, 81, 88, 101, 98, 112, 47, 113, 98, 55, 101, 117, 
	120, 50, 82, 80, 118, 111, 87, 70, 71, 77, 122, 100, 43, 47, 56, 98, 118, 66, 116, 54, 107, 
	105, 112, 69, 57, 118, 82, 52, 114, 106, 68, 99, 101, 47, 118, 122, 55, 88, 90, 122, 78, 67, 
	88, 109, 102, 79, 100, 71, 49, 109, 80, 88, 117, 50, 47, 56, 118, 117, 69, 101, 72, 103, 49, 
	108, 53, 53, 81, 112, 118, 122, 120, 56, 65, 83, 82, 79, 49, 51, 84, 121, 97, 51, 55, 102, 
	106, 49, 55, 113, 71, 106, 57, 87, 81, 102, 105, 122, 53, 82, 47, 83, 70, 97, 108, 101, 56, 
	77, 79, 48, 43, 81, 65, 65, 65, 65, 66, 74, 82, 85, 53, 69, 114, 107, 74, 103, 103, 103, 
	61, 61, 34, 41, 32, 116, 111, 112, 32, 99, 101, 110, 116, 101, 114, 32, 110, 111, 45, 114, 101, 
	112, 101, 97, 116, 59, 112, 97, 100, 100, 105, 110, 103, 45, 116, 111, 112, 58, 56, 53, 112, 120, 
	59, 102, 111, 110, 116, 45, 115, 105, 122, 101, 58, 48, 59, 116, 101, 120, 116, 45, 105, 110, 100, 
	101, 110, 116, 58, 45, 57, 57, 57, 101, 109, 59, 125, 13, 10, 9, 9, 9, 9, 104, 50, 32, 
	123, 116, 101, 120, 116, 45, 97, 108, 105, 103, 110, 58, 32, 99, 101, 110, 116, 101, 114, 59, 102, 
	111, 110, 116, 58, 32, 49, 49, 112, 116, 32, 115, 97, 110, 115, 45, 115, 101, 114, 105, 102, 59, 
	99, 111, 108, 111, 114, 58, 32, 35, 56, 56, 56, 59, 109, 97, 114, 103, 105, 110, 58, 48, 59, 
	112, 97, 100, 100, 105, 110, 103, 58, 48, 32, 48, 32, 49, 101, 109, 32, 48, 59, 125, 13, 10, 
	9, 9, 9, 9, 100, 105, 118, 32, 123, 109, 97, 114, 103, 105, 110, 58, 48, 32, 97, 117, 116, 
	111, 32, 50, 101, 109, 32, 97, 117, 116, 111, 59, 119, 105, 100, 116, 104, 58, 55, 48, 37, 59, 
	112, 97, 100, 100, 105, 110, 103, 58, 32, 48, 46, 53, 101, 109, 59, 125, 13, 10, 9, 9, 9, 
	9, 100, 105, 118, 46, 108, 101, 97, 107, 32, 123, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 
	45, 99, 111, 108, 111, 114, 58, 32, 35, 55, 57, 51, 55, 51, 55, 59, 102, 111, 110, 116, 45, 
	115, 105, 122, 101, 58, 56, 112, 116, 59, 99, 111, 108, 111, 114, 58, 32, 35, 67, 68, 65, 68, 
	65, 68, 125, 13, 10, 9, 9, 9, 9, 100, 105, 118, 46, 108, 101, 97, 107, 32, 104, 53, 32, 
	123, 109, 97, 114, 103, 105, 110, 58, 48, 59, 112, 97, 100, 100, 105, 110, 103, 58, 48, 59, 102, 
	111, 110, 116, 45, 115, 105, 122, 101, 58, 57, 112, 116, 59, 99, 111, 108, 111, 114, 58, 119, 104, 
	105, 116, 101, 125, 13, 10, 9, 9, 9, 9, 101, 109, 32, 123, 99, 111, 108, 111, 114, 58, 32, 
	119, 104, 105, 116, 101, 59, 125, 13, 10, 9, 9, 9, 9, 100, 105, 118, 35, 110, 111, 110, 101, 
	32, 123, 109, 97, 114, 103, 105, 110, 45, 116, 111, 112, 58, 53, 101, 109, 59, 98, 97, 99, 107, 
	103, 114, 111, 117, 110, 100, 45, 99, 111, 108, 111, 114, 58, 32, 35, 57, 70, 68, 57, 51, 53, 
	59, 99, 111, 108, 111, 114, 58, 32, 100, 97, 114, 107, 103, 114, 101, 101, 110, 59, 102, 111, 110, 
	116, 45, 115, 105, 122, 101, 58, 32, 49, 56, 112, 116, 59, 116, 101, 120, 116, 45, 97, 108, 105, 
	103, 110, 58, 32, 99, 101, 110, 116, 101, 114, 59, 125, 13, 10, 9, 9, 9, 9, 100, 105, 118, 
	35, 115, 116, 97, 116, 115, 32, 123, 98, 97, 99, 107, 103, 114, 111, 117, 110, 100, 45, 99, 111, 
	108, 111, 114, 58, 32, 35, 67, 48, 69, 50, 70, 69, 59, 99, 111, 108, 111, 114, 58, 35, 51, 
	51, 51, 59, 116, 101, 120, 116, 45, 97, 108, 105, 103, 110, 58, 32, 99, 101, 110, 116, 101, 114, 
	59, 102, 111, 110, 116, 45, 115, 105, 122, 101, 58, 57, 112, 116, 125, 13, 10, 9, 9, 9, 60, 
	47, 115, 116, 121, 108, 101, 62, 13, 10, 60, 47, 104, 101, 97, 100, 62, 13, 10, 60, 98, 111, 
	100, 121, 62, 13, 10, 9, 60, 104, 49, 62, 78, 120, 79, 103, 114, 101, 60, 47, 104, 49, 62, 
	13, 10, 9, 60, 104, 50, 62, 87, 97, 116, 99, 104, 101, 100, 32, 112, 111, 105, 110, 116, 101, 
	114, 32, 97, 110, 100, 32, 80, 104, 121, 115, 88, 32, 97, 108, 108, 111, 99, 97, 116, 101, 100, 
	32, 109, 101, 109, 111, 114, 121, 32, 108, 101, 97, 107, 115, 60, 47, 104, 50, 62
	};

	mLeakFile->write(header, 3294);
#else
	mLeakFile->writeString("<pre>");
#endif

	if (mAllocations.Size() == 0) {
#ifndef NX_SMALL
		char none[36] = {60, 100, 105, 118, 32, 105, 100, 61, 34, 110, 111, 110, 101, 34, 62, 78, 111, 32, 108, 101, 97, 
		107, 115, 32, 102, 111, 117, 110, 100, 46, 60, 47, 100, 105, 118, 62};
		mLeakFile->write(none, 36);
#else
		mLeakFile->writeString("No leaks.");
#endif

	}
	else {

#ifndef NX_SMALL
		char leak_hdr[18] = {60, 100, 105, 118, 32, 99, 108, 97, 115, 115, 61, 34, 108, 101, 97, 107, 34, 62 };
		char leak_footer[6] = {60, 47, 100, 105, 118, 62};

		for (WatchedPointer* item = mAllocations.Begin(); item = mAllocations.Next();) {
			// div header.
			mLeakFile->write(leak_hdr, 18);

			// header start.
			mLeakFile->writeString("<h5>");

			// class name
			mLeakFile->write(item->mPtrType.str, item->mPtrType.len);
			
			// size
			char* size_str = new char[24];
			unsigned size_str_length = sprintf(size_str, " (%i bytes)", item->mSize);
			mLeakFile->write(size_str, size_str_length);
			delete [] size_str;

			// Optional description
			if (item->mDescription.len != 0) {
				mLeakFile->writeString(" '");
				mLeakFile->write(item->mDescription.str, item->mDescription.len);
				mLeakFile->writeString("'");
			}
			// header end.
			mLeakFile->writeString("</h5>\n");

			char* mfl_str = new char[item->mFile.len + item->mMethod.len + item->mPtrType.len + 64];
			unsigned int mfl_str_length = sprintf(mfl_str, "Function <em>%s</em> in file <em>%s</em> line <em>%i</em>\n", item->mMethod.str, item->mFile.str, item->mLine);
			mLeakFile->write(mfl_str, mfl_str_length);
			delete [] mfl_str;

			// div footer.
			mLeakFile->write(leak_footer, 6);
		}
#else

		for (WatchedPointer* item = mAllocations.Begin(); item = mAllocations.Next();) {

			mLeakFile->write(item->mPtrType.str, item->mPtrType.len);
			
			// size
			char* size_str = new char[24];
			unsigned size_str_length = sprintf(size_str, " (%i bytes)", item->mSize);
			mLeakFile->write(size_str, size_str_length);
			delete [] size_str;

			// Optional description
			if (item->mDescription.len != 0) {
				mLeakFile->writeString(" '");
				mLeakFile->write(item->mDescription.str, item->mDescription.len);
				mLeakFile->writeString("'");
			}

			mLeakFile->writeString("\n");

			char* mfl_str = new char[item->mFile.len + item->mMethod.len + item->mPtrType.len + 64];
			unsigned int mfl_str_length = sprintf(mfl_str, "Function %s in file %s line %i\n", item->mMethod.str, item->mFile.str, item->mLine);
			mLeakFile->write(mfl_str, mfl_str_length);
			delete [] mfl_str;

			mLeakFile->writeString("\n----\n");
		}
#endif
	}

#ifndef NX_SMALL
	char stats_hdr[16] = {60, 100, 105, 118, 32, 105, 100, 61, 34, 115, 116, 97, 116, 115, 34, 62};
	mLeakFile->write(stats_hdr, 16);
	{
		char* str = new char[72];
		unsigned int strLength = sprintf(str, "NxNew <strong>%i</strong>, NxDelete <strong>%i</strong>", NbNew, NbDelete);
		mLeakFile->write(str, strLength);
		delete [] str;
	}

	char footer[25] = {46, 60, 47, 100, 105, 118, 62, 13, 10, 60, 47, 98, 111, 100, 121, 62, 13, 10, 60, 47, 104, 
	116, 109, 108, 62};
	mLeakFile->write(footer, 25);

	if (mLeakFile)
		mLeakFile->close();
#else
	mLeakFile->writeString("</pre>");

#endif
	delete mLeakFile;
}

/////////////////////////////////////////////////////////////

Allocator::WatchedPointer::WatchedPointer() {
	mPtr = 0;
}

/////////////////////////////////////////////////////////////

Allocator::WatchedPointer::~WatchedPointer() {
	mFile.destroy();
	mMethod.destroy();
	mPtrType.destroy();
	mDescription.destroy();
}
/////////////////////////////////////////////////////////////

void* Allocator::WatchedPointer::getPtr() {
	return mPtr;
}

/////////////////////////////////////////////////////////////

void Allocator::WatchedPointer::ReallySimpleString::set(const char* c) {
	
	if (c == 0) {
		len = 0;
		str = 0;
		return;
	}
	
	// length the string + 1 (null terminator)
	len = strlen(c) + 1;

	// allocate memory and copy over
	str = (unsigned char*) malloc(len);
	memcpy(str, c, len - 1);
	
	// add null character
	str[len - 1] = 0;
}

/////////////////////////////////////////////////////////////

void Allocator::WatchedPointer::ReallySimpleString::destroy() {
	if (len)
		free(str);
}

/////////////////////////////////////////////////////////////

}; // End of NxOgre namespace.
