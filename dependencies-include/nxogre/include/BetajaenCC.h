/*

Betajaen's Container Classes

Copyright (c) 2007 Robin Southern, http://www.nxogre.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef BETAJAENS_CC_H
#define BETAJAENS_CC_H

#include "NxOgrePlatform.h"
#include "NxOgreAllocator.h"

// Configuration

/** \brief Namespace to place the Containers in. Comment out if you want it in the global namespace.
*/
#define BETAJAEN_CC_NAMESPACE Betajaen


/** \brief Enable debug comments. Set to zero to disable, 1 to enable
*/
#define BETAJAEN_CC_DEBUG_COMMENTS 1


/** \brief Export Class Macro, replace value with your export macro
*/
#define BETAJAEN_CC_CLASS_EXPORT __declspec(dllexport)
#define BETAJAEN_CC_TEMPLATE_CLASS_EXPORT __forceinline
// #define BETAJAEN_CC_FUNCTION_EXPORT NxPublicFunction


/** \brief Delete macro. Used if you have your own leak checker, etc.
*/
#define BETAJAEN_CC_DELETE(ptr) \
	{::NxOgre::Allocator::getPtr()->watch_delete(static_cast<void*>(ptr));}; \
	delete ptr;

/** \brief Called just before when a class is destroyed using it's destructor.
*/
#define BETAJAEN_CC_DESTRUCTOR(ptr) \
	::NxOgre::Allocator::getPtr()->watch_delete(begin);

//////////////////////////////////////////////////////////////////////////

#if (BETAJAEN_CC_DEBUG_COMMENTS == 1)
#	include <stdio.h>
#endif 

#ifdef BETAJAEN_CC_NAMESPACE
#   define BETAJAEN_CC_NAMESPACE_START namespace BETAJAEN_CC_NAMESPACE {
#   define BETAJAEN_CC_NAMESPACE_END }
#else
#   define BETAJAEN_CC_NAMESPACE_START /**/
#   define BETAJAEN_CC_NAMESPACE_END /**/
#endif

BETAJAEN_CC_NAMESPACE_START

#if (BETAJAEN_CC_DEBUG_COMMENTS == 1)
#   define BETAJAEN_CC_PRINT(x) printf(x "\n");
#   define BETAJAEN_CC_PRINTF(x, y) printf(x "\n",y);
#else
#   define BETAJAEN_CC_PRINT(x) /* x */
#   define BETAJAEN_CC_PRINTF(x,y) /* x, y*/
#endif

#if (_MSC_VER>=1000)
#   define BETAJAEN_CC_INLINE __forceinline
#else
#   define BETAJAEN_CC_INLINE inline
#endif

#ifndef BETAJAEN_CC_CLASS_EXPORT
#   define BETAJAEN_CC_CLASS_EXPORT
#endif

#ifndef BETAJAEN_CC_TEMPLATE_CLASS_EXPORT
#   define BETAJAEN_CC_TEMPLATE_CLASS_EXPORT
#endif

#ifndef BETAJAEN_CC_FUNCTION_EXPORT
#   define BETAJAEN_CC_FUNCTION_EXPORT
#endif

#ifndef BETAJAEN_CC_DELETE
#   define BETAJAEN_CC_DELETE(ptr) delete ptr;
#endif

#ifndef BETAJAEN_CC_DESTRUCTOR
#   define BETAJAEN_CC_DESTRUCTOR(ptr)
#endif

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <class TypePtr, class AllocatorType = SharedAllocator> class Flat;
class SharedAllocator;
template <class BaseType, class AllocatorType = SharedAllocator> class Array;
template <class BaseType, class AllocatorType = SharedAllocator> class SharedList;
template <typename IdentifierType, class BaseType, class AllocatorType = SharedAllocator> class SharedMap;
template <typename IdentifierType, class TypePtr> class Tree;
template <typename> class Vector2;
template <typename> class Vector3;
template <typename> class Vector4;

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

class BETAJAEN_CC_CLASS_EXPORT SharedAllocator {

public:

/////////////////////////////////////////////////////////////

void* Allocate(size_t size)
{
	return malloc(size);
}

/////////////////////////////////////////////////////////////

void Deallocate(void* mem)
{
	if (mem)
		free(mem);
}

/////////////////////////////////////////////////////////////

void* Reallocate(void* mem, size_t size)
{
	return realloc(mem, size);
}

/////////////////////////////////////////////////////////////

}; // End of the SharedAllocator class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template
		<
			class Type,
			class AllocatorType
		>
class BETAJAEN_CC_CLASS_EXPORT Flat
{
		
public:

typedef Type * Iterator;
typedef AllocatorType* AllocatorPtr;

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE Flat(AllocatorPtr allocator, bool deleteAllocator)
	: First(NULL), Last(NULL), End(NULL), Allocator(allocator), AutoDeleteAllocator(deleteAllocator)
{
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE ~Flat()
{
	_deallocate(First);
	if (AutoDeleteAllocator)
		delete Allocator;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE unsigned int _size() const
{
	return (unsigned int) (Last - First);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE unsigned int _capacity() const
{
	return (unsigned int) (First == 0 ? 0 : End - First);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE Type* _allocate(unsigned int size)
{
	return (Type*) Allocator->Allocate(size * sizeof(Type));
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void _deallocate(Type* p)
{
	if (p)
		Allocator->Deallocate(p);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE Iterator _reallocate(Iterator p, unsigned int size)
{
	return (Iterator) Allocator->Reallocate(p, size  * sizeof(Type));
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void _clip(unsigned int size)
{
	
	if (size < _size())
		return;

	Iterator new_first = _allocate(size);
	_copy(First, Last, new_first);
	_destroy(First, Last);
	_deallocate(First);
	End = new_first + size;
	Last = new_first + _size();
	First = new_first;

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void _reserve(unsigned int new_size)
{
	if (_capacity() >= new_size)
		return;

	Iterator new_first = _allocate(new_size);
	_copy(First, Last, new_first);
	_destroy(First, Last);
	_deallocate(First);
	End = new_first + new_size;
	Last = new_first + _size();
	First = new_first;

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE Iterator _copy(Iterator begin, Iterator end, Iterator dest)
{
	for (;begin != end; ++dest, ++begin)
		*dest = *begin;
	return dest;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void _delete_range(Iterator begin, Iterator end)
{
	for (; begin != end; ++begin) {
		BETAJAEN_CC_DELETE(*begin);
	}
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void _destroy(Iterator begin, Iterator end)
{
	for (; begin != end; ++begin) {
		BETAJAEN_CC_DESTRUCTOR(begin)
		begin->~Type();
	}
}

/////////////////////////////////////////////////////////////

protected: AllocatorPtr Allocator;
protected: bool AutoDeleteAllocator;
public:  Iterator First, Last, End;

}; // End of Flat<Type,AllocatorType> class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template
		<
			class Type,					/* Class to Store; A, myClassName, etc. */
			class AllocatorType			/* Allocator to use, or leave blank for SharedAllocator */
		>
class BETAJAEN_CC_CLASS_EXPORT Array {

public:

typedef Type* TypePtr;
typedef Array<Type, AllocatorType> ArrayType;
typedef Flat<Type, AllocatorType> FlatType;
typedef FlatType* FlatPtr;

BETAJAEN_CC_INLINE Array(AllocatorType* _allocator = NULL, bool _auto_delete_allocator = true)
{
	if (_allocator == NULL)
		_allocator = new AllocatorType();

	_Flat = new FlatType(_allocator, _auto_delete_allocator);

}

BETAJAEN_CC_INLINE ~Array()
{
	delete _Flat;
}

BETAJAEN_CC_INLINE TypePtr getPtr()
{
	return _Flat->First;
}

BETAJAEN_CC_INLINE unsigned int Size()
{
	return _Flat->_size();
}

BETAJAEN_CC_INLINE void Append(Type v) {

	if (_Flat->End <= _Flat->Last)
		_Flat->_reserve( (1 + _Flat->_size()) * 2);

	*_Flat->Last = v;
	_Flat->Last++;

}

BETAJAEN_CC_INLINE void Clip() {
	_Flat->_clip(0);
}

private: FlatPtr _Flat;

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief A list of pointers with garbage collections and the ability to
	share the same list with similar lists. Like STL's Vector.

	\example
		<code>
			class A;

			SharedList<A> aList;
			a.Insert(new A());
			a.Remove(a.Last);
		</code>

*/
template
		<
			class Type,					/* Class to Store; A, myClassName, etc. */
			class AllocatorType			/* Allocator to use, or leave blank for SharedAllocator */
		>
class BETAJAEN_CC_CLASS_EXPORT SharedList {

public:
	
typedef Type* TypePtr;
typedef TypePtr* Iterator;
typedef SharedList<Type, AllocatorType> SharedListType;
typedef Flat<TypePtr, AllocatorType> FlatType;
typedef FlatType* FlatPtr;

/////////////////////////////////////////////////////////////

enum AbsolutePosition
{
	First,
	Last
};

/**
	Constructor with optional custom allocator
*/
BETAJAEN_CC_INLINE SharedList(AllocatorType* _allocator = NULL, bool _auto_delete_allocator = true)
{
	if (_allocator == NULL)
		_allocator = new AllocatorType();

	_Flat = new FlatType(_allocator, _auto_delete_allocator);
	_Usage = new unsigned int(1);

}

/** \brief Copy Constructor between SharedList's. The Flat will not be copied but referenced.
	Any action on this list will effect all lists using the same Flat. Clean up will only
	happen on the destruction of the last surviving list.

	\example
			<code>
				typedef SharedList<A> AList;
				AList a;
				AList b(a);
			</code>
*/
BETAJAEN_CC_INLINE SharedList(const SharedListType& other)
{

	_Flat = other._Flat;
	_Usage = other._Usage;
	++(*_Usage);

}


/** \brief	Copy Operator. Functions the same as Copy Constructor but deletes the set that this
			may already have.

	\example
			<code>
				typedef SharedList<A> AList;
				AList a;
				AList b;
				b = a;
			</code>
*/
BETAJAEN_CC_INLINE SharedListType& operator=(const SharedListType& other)
{

	if (_Flat)
	{
		_Flat->_delete_range(_Flat->First, _Flat->Last);
		delete _Flat;
	}

	if (_Usage)
		delete _Usage;

	_Flat = other._Flat;
	_Usage = other._Usage;
	++(*_Usage);

	return *this;

}


/** \brief Destructor. If this is the last of all SharedLists sharing the same set,
	the set will be destroyed otherwise the Flat will be ignored and this SharedList
	dies gracefully.
*/
BETAJAEN_CC_INLINE ~SharedList()
{
	
	if (--(*_Usage) == 0)
	{
		_Flat->_delete_range(_Flat->First, _Flat->Last);
		delete _Flat;
		delete _Usage;
	}
	
}


/** \brief Gets the pointer to the nth Type in the list. Alternate interface to operator[]. 
*/
BETAJAEN_CC_INLINE TypePtr Get(size_t pos)
{
	if (pos > Size())
		return NULL;

	return *(_Flat->First + pos);
}


/** \brief Gets the pointer to the nth TypePtr in the list.
*/
BETAJAEN_CC_INLINE TypePtr operator[](size_t pos)
{
	if (pos > Size())
		return NULL;

	return *(_Flat->First + pos);
}


/** \brief Where is something in the list.
*/
BETAJAEN_CC_INLINE unsigned int WhereIs(TypePtr ptr)
{

	if (_Flat->_size() == 0)
		return 0;

	unsigned int i=0;
	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin, ++i)
	{
		if (ptr == (*begin))
			return i;
	}
	
	return 0;
}

BETAJAEN_CC_INLINE bool Has(TypePtr ptr)
{
	
	if (_Flat->_size() == 0)
		return false;

		for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		{
			if (ptr == (*begin))
				return true;
		}

	return false;

}

/** \brief The size of the SharedList.
*/
BETAJAEN_CC_INLINE unsigned Size() const
{
	return _Flat->_size();
}


/** \brief Insert something into the list
*/
BETAJAEN_CC_INLINE void Insert(const TypePtr& val)
{

	if (_Flat->End <= _Flat->Last)
		_Flat->_reserve( (1 + Size()) * 2);

	*_Flat->Last = val;
	_Flat->Last++;

}


/** \brief Resize the capacity of the list to size + n.
*/
BETAJAEN_CC_INLINE void Clean(unsigned int n = 4)
{
	_Flat->_clip(_Flat->_size() + n);
}


/** \brief Destroy something nth position into the list.
*/
BETAJAEN_CC_INLINE void Destroy(unsigned int n)
{
	if (n == 0)
		return Destroy(First);
	
	if (n == Size())
		return Destroy(Last);

	delete *(_Flat->First + n);

	_Flat->_destroy(_Flat->First + n, _Flat->First + n + 1);
	_Flat->_copy(_Flat->First + n + 1, _Flat->Last, _Flat->First + n);
	_Flat->Last--;

}

// \brief Destroys everything
//
BETAJAEN_CC_INLINE void DestroyAll()
{
	if (Size() == 0)
		return;

	_Flat->_delete_range(_Flat->First, _Flat->Last);
	// Could be iffy.
	_Flat->Last = _Flat->First;

}

/** \brief Destroys something in the list based on the pointer in the list.
*/
BETAJAEN_CC_INLINE void Destroy(TypePtr val) {
	unsigned int i = WhereIs(val);
	Destroy(i);
}

/** \brief Deletes something from the list based on AbsolutePosition
*/
BETAJAEN_CC_INLINE void Destroy(AbsolutePosition position)
{

	switch(position) {

		case First:
			{
				delete *_Flat->First;
				_Flat->_copy(_Flat->First + 1, _Flat->Last + 1, _Flat->First);
				_Flat->Last--;
			}
		break;

		case Last:
			{
				_Flat->Last--;
				delete *_Flat->Last;
			}
		break;

	}

}


/** \brief Removes something from the list based on numerical position.
*/
BETAJAEN_CC_INLINE TypePtr Remove(unsigned int n)
{

	if (n == 0)
		return Remove(First);
	
	if (n == Size())
		return Remove(Last);

	TypePtr ptr = Get(n);
	_Flat->_destroy(_Flat->First + n, _Flat->First + n + 1);
	_Flat->_copy(_Flat->First + n + 1, _Flat->Last, _Flat->First + n);
	_Flat->Last--;

	return ptr;
}


/** \brief Removes something from the list based on AbsolutePosition
*/
BETAJAEN_CC_INLINE TypePtr Remove(AbsolutePosition position)
{

	if (_Flat->_size() == 0)
		return NULL;

	switch(position) {

		case First:
			{
				TypePtr t = *(_Flat->First);
				_Flat->_copy(_Flat->First + 1, _Flat->Last + 1, _Flat->First);
				_Flat->Last--;
				return t;
			}

		break;

		case Last:
			{
				_Flat->Last--;
				return *(_Flat->Last);
			}
		break;
	}

	return NULL;

}

// \brief Destroys everything
//
BETAJAEN_CC_INLINE void RemoveAll()
{
	if (Size() == 0)
		return;

	_Flat->_deallocate(_Flat->First);

	// Could be iffy.
	_Flat->Last = _Flat->First;

}


/** \brief Places the Iterator at the beginning of the List
*/
BETAJAEN_CC_INLINE TypePtr Begin()
{

	if (_Flat->_size() == 0)
		return NULL;

	_Iterator = _Flat->First;
	return *_Iterator;

}


/** \brief Advances the Iterator forward by one, and returns the value of the list or NULL
	\returns The next item in the list, or NULL if it has reached the end of it.
*/
BETAJAEN_CC_INLINE TypePtr Next()
{

	if (_Flat->_size() == 0)
		return NULL;
	else if (_Iterator == _Flat->Last)
		return NULL;
	else
		return (*_Iterator++);

}


/** \brief Places the iterator at the end of the List
*/
BETAJAEN_CC_INLINE TypePtr End()
{

	if (_Flat->_size() == 0)
		return NULL;

	_Iterator = _Flat->Last - 1;
	return *_Iterator;

}


/** \brief Advances the Iterator backwards by one, and returns the value of the list or NULL
	\returns The previous item in the list, or NULL if it has reached the beginning of it.
*/
BETAJAEN_CC_INLINE TypePtr Previous()
{

	if (_Flat->_size() == 0)
		return NULL;
	else if (_Iterator == _Flat->First - 1)
		return NULL;
	else
		return (*_Iterator--);

}

/** \brief For each item in the list call it's own method.
*/
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)()) {
	
	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin) {
		(*begin->*MethodPtr)();
	}

}


/** \brief For each item in the list call it's own method, with one argument.
*/
template <typename _A>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A), _A _1) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin) {
		(*begin->*MethodPtr)(_1);
	}

}


/** \brief For each item in the list call it's own method, with two arguments.
*/
template <typename _A, typename _B>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B), _A _1, _B _2) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2);

}


/** \brief For each item in the list call it's own method, with three arguments.
*/
template <typename _A, typename _B, typename _C>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C), _A _1, _B _2, _C _3) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3);

}


/** \brief For each item in the list call it's own method, with four arguments.
*/
template <typename _A, typename _B, typename _C, typename _D>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4);

}


/** \brief For each item in the list call it's own method, with five arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5);

}


/** \brief For each item in the list call it's own method, with six arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6);

}


/** \brief For each item in the list call it's own method, with seven arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6, _G _7) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6, _7);

}


/** \brief For each item in the list call it's own method, with eight arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G, typename _H>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6, _G _7, _H _8) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6, _7, _8);

}

/** \brief Returns the pointer to the working set.
*/
BETAJAEN_CC_INLINE FlatPtr getFlat() const {
	return _Flat;
}


/** \brief Returns the number of SharedLists using this set.
*/
BETAJAEN_CC_INLINE unsigned int getUsageCount() const {
	return *_Usage;
}


private: unsigned int* _Usage;
private: FlatPtr _Flat;
private: Iterator _Iterator;

};	// End of SharedList<Type, AllocatorType> Class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START


/** \brief Binary Tree with variable identifer and storage type.

*/
template <typename NodeIdentifier, class Type>
class BETAJAEN_CC_CLASS_EXPORT Tree
{
	// Much of this Tree was from the excellent tutorial by Julienne Walker
	// http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_bst1.aspx

public:

class Node;
typedef Node*			NodePtr;
typedef Type*			TypePtr;

/** \brief A tree is made up of nodes.
*/
class BETAJAEN_CC_CLASS_EXPORT Node
{

public:

Node(NodeIdentifier id, TypePtr val) : _ID(id), _Val(val)
{
	_Children[0] = NULL;
	_Children[1] = NULL;
}

void Replace(Node* n)
{
	_ID = n->_ID;
	_Val = n->_Val;
}

NodeIdentifier	_ID;
TypePtr			_Val;
NodePtr			_Children[2];

};

class BETAJAEN_CC_CLASS_EXPORT NodeIterator
{
public:
	NodePtr  _Up[50];
	NodePtr  _It;
	int      _Top;
};

/** \brief Tree constructor
*/
public: BETAJAEN_CC_INLINE Tree() : _Root(NULL)
{
}


/** \brief Tree destructor.
	\note Does not remove or destroy the contents of the tree.
*/
public: BETAJAEN_CC_INLINE ~Tree()
{
}

public: BETAJAEN_CC_INLINE bool isEmpty() const {
	return (_Root == 0);
}

/** \brief Destroys all the nodes in the tree and deletes all of the values referenced in it.
*/
public: BETAJAEN_CC_INLINE void DestroyAll()
{
	if (_Root == NULL)
		return;

	NodePtr iterator = _Root;
	NodePtr save = 0;

	while (iterator != NULL)
	{
		if (iterator->_Children[0] != NULL)
		{
			save = iterator->_Children[0];
			iterator->_Children[0] = save->_Children[1];
			save->_Children[1] = iterator;
		}
		else
		{
			save = iterator->_Children[1];
			delete iterator->_Val;
			delete iterator;
		}

		iterator = save;
	}

	_Root = NULL;
}


/** \brief Destroys all the nodes in the tree, but not all of the values referenced in it.
*/
public: BETAJAEN_CC_INLINE void RemoveAll()
{
	
	if (_Root == NULL)
		return;

	NodePtr iterator = _Root;
	NodePtr save = 0;

	while (iterator != NULL)
	{
		if (iterator->_Children[0] != NULL)
		{
			save = iterator->_Children[0];
			iterator->_Children[0] = save->_Children[1];
			save->_Children[1] = iterator;
		}
		else
		{
			save = iterator->_Children[1];
			delete iterator;
			iterator = NULL;
		}

		iterator = save;
	}

	_Root = NULL;

}


/** \brief Remove a Node based of an identifier
*/
public: BETAJAEN_CC_INLINE void Remove(NodeIdentifier id)
{

	if (_Root == NULL)
		return;

	Node head = {0};
	NodePtr iterator = &head;
	NodePtr *f = 0, *p = 0;
	int direction = 1;

	iterator->_Children[1] = _Root;

	//while (iterator = 

}



/** \brief Removes a ranges of nodes based on max. and min. identifiers.
	\note This operates based on the "operator <" of the TypeIdentifier the class,
	which defines if the type is in the range or not. Types such as ints, or reals
	aren't a problem but things like strings or complicated classes may produce
	strange results.
*/
public: BETAJAEN_CC_INLINE void RemoveRange(NodeIdentifier id_min, NodeIdentifier id_max)
{


}


/**
*/
public: BETAJAEN_CC_INLINE void Destroy(NodeIdentifier id)
{

}


/**
*/
public: BETAJAEN_CC_INLINE void DestroyRange(NodeIdentifier id_min, NodeIdentifier id_max)
{

}


/**
*/
public: BETAJAEN_CC_INLINE TypePtr Find(NodeIdentifier target)
{
	NodePtr iterator = _Root;
	while (iterator != NULL)
	{
		if (iterator->_ID == target)
		{
			return iterator->_Val;
		}
		else
		{
			iterator = iterator->_Children[int(iterator->_ID < target)];
		}
	}

	return 0;
}

/**
*/
public: BETAJAEN_CC_INLINE TypePtr First(NodeIterator* it)
{

	it->_It = _Root;
	it->_Top = 0;

	if (it->_It != 0) {
		while (it->_It->_Children[0] != 0) {
			it->_Up[it->_Top++] = it->_It;
			it->_It = it->_It->_Children[0];
		}
	}

	if (it->_It != 0)
		return it->_It->_Val;
	else
		return 0;

}

/**
*/
public: BETAJAEN_CC_INLINE TypePtr Next(NodeIterator* it)
{
	if (it->_It->_Children[1] != 0) {
		it->_Up[it->_Top++] = it->_It;
		it->_It = it->_It->_Children[1];

		while (it->_It->_Children[0] != 0) {
			it->_Up[it->_Top++] = it->_It;
			it->_It = it->_It->_Children[0];
		}

	}
	else {
		NodePtr last;

		do {

			if (it->_Top == 0) {
				it->_It = 0;
				break;
			}
			
			last = it->_It;
			it->_It = it->_Up[--it->_Top];

		} while (last == it->_It->_Children[1]);

	}

	if (it->_It != 0)
		return it->_It->_Val;
	else
		return 0;

}

/**
*/
public: BETAJAEN_CC_INLINE bool Insert(NodeIdentifier target, TypePtr val)
{
	Node* node = new Node(target, val);
	
	
	if (_Root == NULL)
	{
		_Root = node;
		return true;
	}
	else
	{
		Node* iterator = _Root;
		unsigned int direction;

		for ( ; ; )
		{
			direction = iterator->_ID < target;

			if (iterator->_ID == target)
			{
				delete node;
				return false;
			}
			else if (iterator->_Children[direction] == NULL)
				break;


			iterator = iterator->_Children[direction];
		}

		iterator->_Children[direction] = node;
	}

	return true;
}


private: NodePtr _Root;

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <
			typename IdentifierType,
			class Type,
			class AllocatorType
		 >
class BETAJAEN_CC_CLASS_EXPORT SharedMap
{

public:

typedef Type*						TypePtr;
typedef Tree<IdentifierType, Type>	TreeType;
typedef TreeType*					TreePtr;


/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE SharedMap()
{
	_Tree = new TreeType();
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE ~SharedMap()
{
	_Tree->DestroyAll();
	delete _Tree;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Get(IdentifierType identifier)
{
	return _Tree->Find(identifier);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr operator[](IdentifierType identifier)
{
	return _Tree->Find(identifier);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Insert(IdentifierType identifier, TypePtr ptr)
{
	_Tree->Insert(identifier, ptr);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void DestroyAll()
{
	_Tree->DestroyAll();
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void RemoveAll() {
	_Tree->RemoveAll();
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Destroy(IdentifierType);

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Remove(IdentifierType);

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Begin();

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Next();

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr End();

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Previous();

/////////////////////////////////////////////////////////////

/** \brief For each item in the list call it's own method.
*/
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)()) {

	if (_Tree->isEmpty())
		return;

	TreeType::NodeIterator iterator;
	TypePtr ptr = _Tree->First(&iterator);

	while (ptr != 0) {
		(ptr->*MethodPtr)();
		ptr = _Tree->Next(&iterator);
	}
}


/** \brief For each item in the list call it's own method, with one argument.
*/
template <typename _A>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A), _A _1) {

	if (_Tree->isEmpty())
		return;

	TreeType::NodeIterator iterator;
	TypePtr ptr = _Tree->First(&iterator);

	while (ptr != 0) {
		(ptr->*MethodPtr)(_1);
		ptr = _Tree->Next(&iterator);
	}
}
/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TreePtr getTree() const
{
	return _Tree;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE unsigned int getUsage() const 
{
	return *_Usage;
}

/////////////////////////////////////////////////////////////

private: TreePtr _Tree;
private: unsigned int* _Usage;

/////////////////////////////////////////////////////////////

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with two rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector2
{

public:

typedef Vector2<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

BETAJAEN_CC_INLINE Vector2()
{
}

BETAJAEN_CC_INLINE Vector2(Type _i, Type _j) 
: i(_i), j(_j)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other)
{
	i = other.i; j = other.j;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator = (const Type& other)
{
	i = other; j = other;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const
{
	return (i == other.i && j == other.j);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const
{
	return (i != other.i || j != other.j);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with three rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector3
{

public:

typedef Vector3<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

/* \brief Third */
Type k;


BETAJAEN_CC_INLINE Vector3()
{
}

BETAJAEN_CC_INLINE Vector3(Type _i, Type _j, Type _k) 
: i(_i), j(_j), k(_k)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j, Third = k;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
	k = other.k; other.k = Third;
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other)
{
	i = other.i; j = other.j; k = other.k;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator = (const Type& other)
{
	i = other; j = other; k = other;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other; k *= other;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j; k *= other.k;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const
{
	return (i == other.i && j == other.j && k == other.k);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const
{
	return (i != other.i || j != other.j || k != other.k);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with four rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector4 {

public:

typedef Vector4<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

/* \brief Third */
Type k;

/* \brief Fourth */
Type l;

BETAJAEN_CC_INLINE Vector4()
{
}

BETAJAEN_CC_INLINE Vector4(Type _i, Type _j, Type _k, Type _l) 
: i(_i), j(_j), k(_k), l(_l)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j, Third = k, Fourth = l;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
	k = other.k; other.k = Third;
	l = other.l; other.l = Fourth;
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other) {
	i = other.i; j = other.j; k = other.k; l = other.l;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other; k *= other; l *= other
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j; k *= other.k; l *= other.l;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const {
	return (i == other.i && j == other.j && k == other.k && l == other.l);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const {
	return (i != other.i || j != other.j || k != other.k || l != other.l);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <typename Type>
class BETAJAEN_CC_CLASS_EXPORT Vector {

	public:
		typedef Type* TypePtr;

		TypePtr j;
		unsigned int jSize;

		Vector(unsigned int j_size)
		{

		}

		~Vector()
		{

		}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

#if 0
BETAJAEN_CC_NAMESPACE_START

template <typename Type>
class BETAJAEN_CC_TEMPLATE_CLASS_EXPORT Matrix {

public:
	typedef Type* TypePtr;

	TypePtr        ij;
	unsigned int   iSize,
		           jSize;

	class MatrixIterator {
		public:
			
			enum IteratorRole {
				IR_COLUMN,
				IR_ROW
			};

			MatrixIterator(Matrix* _matrix, IteratorRole _role, unsigned int _iterator = 0)
				mMatrix(_matrix), mRole(_role), mIterator(_iterator)
			{
			}
			
			Matrix*      mMatrix;
			IteratorRole mRole;
			unsigned int mIterator;
			
	};

	class RowIterator {
		public:
			RowIterator(TypePtr ijPtr, unsigned int row, unsigned int i_size, unsigned j_size)
				: ij(ijPtr), r(row), iSize(i_size), jSize(j_size)
			{
			}

			Type& operator[] (unsigned int column)
			{
				return ij[(column * iSize) + r];
			}


			RowIterator& operator=(Type _f) {

				// Doesn't work.
				for (unsigned int i=r * iSize;i < (r * iSize) + iSize;i++) {
					printf("i=%i\n", i);
					ij[i] = _f;
				}
				printf("Done.\n");
				return *this;
			}

			TypePtr      ij;
			unsigned int r, iSize, jSize;

	};

	class ColumnIterator {
	
		public:

			ColumnIterator(TypePtr ijPtr, unsigned int col, unsigned int i_size, unsigned j_size)
				: ij(ijPtr), c(col), iSize(i_size), jSize(j_size)
			{
			}

			Type& operator[] (unsigned int row)
			{
				if (row > i_size)
					row = i_size;

				return ij[(c * iSize) + row];
			}


			ColumnIterator& operator=(Type _f) {
				for (unsigned int i=c;i < c + jSize;i++) {
					printf("i=%i\n", i);
					ij[i] = _f;
				}
				printf("Done.\n");
				return *this;
			}

			TypePtr      ij;
			unsigned int c, iSize, jSize;
	};

	class All {
		public:

			All()
			{
			}

			All(TypePtr ijPtr, unsigned int i_size, unsigned int j_size)
				: ij(ijPtr), iSize(i_size), jSize(j_size)
			{
			}

			All& operator=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] = _f;
				return *this;
			}

			All& operator*=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] *= _f;
				return *this;
			}

			All& operator/=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] /= _f;
				return *this;
			}

			All& operator+=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] += _f;
				return *this;
			}

			All& operator-=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] -= _f;
				return *this;
			}

			All& operator++(int) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i]++;
				return *this;
			}
			

			TypePtr      ij;
			unsigned iSize, jSize;
	};

	All all;

Matrix(unsigned int nbRows, unsigned int nbColumns)
: iSize(nbRows), jSize(nbColumns)
{
	ij = new Type[iSize * jSize];
	for (unsigned int i = 0;i < (iSize * jSize);i++)
		ij[i] = 0;

	all = All(ij, iSize, jSize);

	BETAJAEN_CC_PRINTF("Matrix created with %i", nbColumns);
}

~Matrix()
{
	if (iSize || jSize)
		delete [] ij;
}

RowIterator operator[] (unsigned int row)
{
	return RowIterator(ij, row, iSize, jSize);
}

ColumnIterator operator() (unsigned col)
{
	return ColumnIterator(ij, col, iSize, jSize);
}

void dump()
{
	for (unsigned int i=0;i < iSize;i++) {
		for (unsigned int j=0;j < jSize;j++) {
			printf("%f\t", ij[(j * jSize) + i]);
		}
		printf("\n");
	}

}

};
BETAJAEN_CC_NAMESPACE_END
#endif

//////////////////////////////////////////////////////////////////////////

#endif


#if 0
/*

Betajaen's Container Classes

Copyright (c) 2007 Robin Southern, http://www.nxogre.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef BETAJAENS_CC_H
#define BETAJAENS_CC_H

#include "NxOgrePlatform.h"
#include "NxOgreAllocator.h"

// Configuration

/** \brief Namespace to place the Containers in. Comment out if you want it in the global namespace.
*/
#define BETAJAEN_CC_NAMESPACE Betajaen


/** \brief Enable debug comments. Set to zero to disable, 1 to enable
*/
#define BETAJAEN_CC_DEBUG_COMMENTS 1


/** \brief Export Class Macro, replace value with your export macro
*/
#define BETAJAEN_CC_CLASS_EXPORT __declspec(dllexport)
#define BETAJAEN_CC_TEMPLATE_CLASS_EXPORT __forceinline
// #define BETAJAEN_CC_FUNCTION_EXPORT NxPublicFunction


/** \brief Delete macro. Used if you have your own leak checker, etc.
*/
#define BETAJAEN_CC_DELETE(ptr) \
	{::NxOgre::Allocator::getPtr()->watch_delete(static_cast<void*>(ptr));}; \
	delete ptr;

/** \brief Called just before when a class is destroyed using it's destructor.
*/
#define BETAJAEN_CC_DESTRUCTOR(ptr) \
	::NxOgre::Allocator::getPtr()->watch_delete(begin);

//////////////////////////////////////////////////////////////////////////

#if (BETAJAEN_CC_DEBUG_COMMENTS == 1)
#	include <stdio.h>
#endif 

#ifdef BETAJAEN_CC_NAMESPACE
#   define BETAJAEN_CC_NAMESPACE_START namespace BETAJAEN_CC_NAMESPACE {
#   define BETAJAEN_CC_NAMESPACE_END }
#else
#   define BETAJAEN_CC_NAMESPACE_START /**/
#   define BETAJAEN_CC_NAMESPACE_END /**/
#endif

BETAJAEN_CC_NAMESPACE_START

#if (BETAJAEN_CC_DEBUG_COMMENTS == 1)
#   define BETAJAEN_CC_PRINT(x) printf(x "\n");
#   define BETAJAEN_CC_PRINTF(x, y) printf(x "\n",y);
#else
#   define BETAJAEN_CC_PRINT(x) /* x */
#   define BETAJAEN_CC_PRINTF(x,y) /* x, y*/
#endif

#if (_MSC_VER>=1000)
#   define BETAJAEN_CC_INLINE __forceinline
#else
#   define BETAJAEN_CC_INLINE inline
#endif

#ifndef BETAJAEN_CC_CLASS_EXPORT
#   define BETAJAEN_CC_CLASS_EXPORT
#endif

#ifndef BETAJAEN_CC_TEMPLATE_CLASS_EXPORT
#   define BETAJAEN_CC_TEMPLATE_CLASS_EXPORT
#endif

#ifndef BETAJAEN_CC_FUNCTION_EXPORT
#   define BETAJAEN_CC_FUNCTION_EXPORT
#endif

#ifndef BETAJAEN_CC_DELETE
#   define BETAJAEN_CC_DELETE(ptr) delete ptr;
#endif

#ifndef BETAJAEN_CC_DESTRUCTOR
#   define BETAJAEN_CC_DESTRUCTOR(ptr)
#endif

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <class TypePtr, class AllocatorType = SharedAllocator> class Flat;
class SharedAllocator;
template <class BaseType, class AllocatorType = SharedAllocator> class SharedList;
template <typename IdentifierType, class BaseType, class AllocatorType = SharedAllocator> class SharedMap;
template <typename IdentifierType, class TypePtr> class Tree;
template <typename> class Vector2;
template <typename> class Vector3;
template <typename> class Vector4;

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

class BETAJAEN_CC_CLASS_EXPORT SharedAllocator {

public:

/////////////////////////////////////////////////////////////

void* Allocate(size_t size)
{
	return malloc(size);
}

/////////////////////////////////////////////////////////////

void Deallocate(void* mem)
{
	if (mem)
		free(mem);
}

/////////////////////////////////////////////////////////////

void* Reallocate(void* mem, size_t size)
{
	return realloc(mem, size);
}

/////////////////////////////////////////////////////////////

}; // End of the SharedAllocator class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template
		<
			class Type,
			class AllocatorType
		>
class BETAJAEN_CC_CLASS_EXPORT Flat
{
		
public:

typedef Type * Iterator;
typedef AllocatorType* AllocatorPtr;

BETAJAEN_CC_INLINE Flat(AllocatorPtr allocator, bool deleteAllocator);
BETAJAEN_CC_INLINE ~Flat();
BETAJAEN_CC_INLINE unsigned int _size() const;
BETAJAEN_CC_INLINE unsigned int _capacity() const;
BETAJAEN_CC_INLINE Type* _allocate(unsigned int size);
BETAJAEN_CC_INLINE void _deallocate(Type* p);
BETAJAEN_CC_INLINE Iterator _reallocate(Iterator p, unsigned int size);
BETAJAEN_CC_INLINE void _clip(unsigned int size);
BETAJAEN_CC_INLINE void _reserve(unsigned int new_size);
BETAJAEN_CC_INLINE Iterator _copy(Iterator begin, Iterator end, Iterator dest);
BETAJAEN_CC_INLINE void _delete_range(Iterator begin, Iterator end);
BETAJAEN_CC_INLINE void _destroy(Iterator begin, Iterator end);

private: AllocatorPtr Allocator;
private: bool AutoDeleteAllocator;
public:  Iterator First, Last, End;

}; // End of Flat<Type,AllocatorType> class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief A list of pointers with garbage collections and the ability to
	share the same list with similar lists. Like STL's Vector.

	\example
		<code>
			class A;

			SharedList<A> aList;
			a.Insert(new A());
			a.Remove(a.Last);
		</code>

*/
template
		<
			class Type,					/* Class to Store; A, myClassName, etc. */
			class AllocatorType			/* Allocator to use, or leave blank for SharedAllocator */
		>
class BETAJAEN_CC_CLASS_EXPORT SharedList {

public:
	
typedef Type* TypePtr;
typedef TypePtr* Iterator;
typedef SharedList<Type, AllocatorType> SharedListType;
typedef Flat<TypePtr, AllocatorType> FlatType;
typedef FlatType* FlatPtr;

/////////////////////////////////////////////////////////////

enum AbsolutePosition
{
	First,
	Last
};

/**
	Constructor with optional custom allocator
*/
BETAJAEN_CC_INLINE SharedList(AllocatorType* _allocator = NULL, bool _auto_delete_allocator = true);

/** \brief Copy Constructor between SharedList's. The Flat will not be copied but referenced.
	Any action on this list will effect all lists using the same Flat. Clean up will only
	happen on the destruction of the last surviving list.

	\example
			<code>
				typedef SharedList<A> AList;
				AList a;
				AList b(a);
			</code>
*/
BETAJAEN_CC_INLINE SharedList(const SharedListType& other);

/** \brief	Copy Operator. Functions the same as Copy Constructor but deletes the set that this
			may already have.

	\example
			<code>
				typedef SharedList<A> AList;
				AList a;
				AList b;
				b = a;
			</code>
*/
BETAJAEN_CC_INLINE SharedListType& operator=(const SharedListType& other);


/** \brief Destructor. If this is the last of all SharedLists sharing the same set,
	the set will be destroyed otherwise the Flat will be ignored and this SharedList
	dies gracefully.
*/
BETAJAEN_CC_INLINE ~SharedList() {

	if (--(*_Usage) == 0)
	{
		_Flat->_delete_range(_Flat->First, _Flat->Last);
		delete _Flat;
		delete _Usage;
	}

}

/** \brief Gets the pointer to the nth Type in the list. Alternate interface to operator[]. 
*/
BETAJAEN_CC_INLINE TypePtr Get(size_t pos);

/** \brief Gets the pointer to the nth TypePtr in the list.
*/
BETAJAEN_CC_INLINE TypePtr operator[](size_t pos);

/** \brief Where is something in the list.
*/
BETAJAEN_CC_INLINE unsigned int WhereIs(TypePtr ptr);

/** \brief Is this pointer in the list?
*/
BETAJAEN_CC_INLINE bool Has(TypePtr ptr);

/** \brief The size of the SharedList.
*/
BETAJAEN_CC_INLINE unsigned Size() const;

/** \brief Insert something into the list
*/
BETAJAEN_CC_INLINE void Insert(const TypePtr& val);

/** \brief Resize the capacity of the list to size + n.
*/
BETAJAEN_CC_INLINE void Clean(unsigned int n = 4);

/** \brief Destroy something nth position into the list.
*/
BETAJAEN_CC_INLINE void Destroy(unsigned int n);

// \brief Destroys everything
//
BETAJAEN_CC_INLINE void DestroyAll();

/** \brief Destroys something in the list based on the pointer in the list.
*/
BETAJAEN_CC_INLINE void Destroy(TypePtr val);

/** \brief Deletes something from the list based on AbsolutePosition
*/
BETAJAEN_CC_INLINE void Destroy(AbsolutePosition position);

/** \brief Removes something from the list based on numerical position.
*/
BETAJAEN_CC_INLINE TypePtr Remove(unsigned int n);

/** \brief Removes something from the list based on AbsolutePosition
*/
BETAJAEN_CC_INLINE TypePtr Remove(AbsolutePosition position);

/** \brief Places the Iterator at the beginning of the List
*/
BETAJAEN_CC_INLINE TypePtr Begin();

/** \brief Advances the Iterator forward by one, and returns the value of the list or NULL
	\returns The next item in the list, or NULL if it has reached the end of it.
*/
BETAJAEN_CC_INLINE TypePtr Next();

/** \brief Places the iterator at the end of the List
*/
BETAJAEN_CC_INLINE TypePtr End();

/** \brief Advances the Iterator backwards by one, and returns the value of the list or NULL
	\returns The previous item in the list, or NULL if it has reached the beginning of it.
*/
BETAJAEN_CC_INLINE TypePtr Previous();

/** \brief For each item in the list call it's own method.
*/
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)());

/** \brief For each item in the list call it's own method, with one argument.
*/
template <typename _A>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A), _A);

/** \brief For each item in the list call it's own method, with two arguments.
*/
template <typename _A, typename _B>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B), _A, _B);

/** \brief For each item in the list call it's own method, with three arguments.
*/
template <typename _A, typename _B, typename _C>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C), _A, _B, _C);

/** \brief For each item in the list call it's own method, with four arguments.
*/
template <typename _A, typename _B, typename _C, typename _D>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A, _B, _C, _D);

/** \brief For each item in the list call it's own method, with five arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A, _B, _C, _D, _E);

/** \brief For each item in the list call it's own method, with six arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A, _B, _C, _D, _E, _F);

/** \brief For each item in the list call it's own method, with seven arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A, _B, _C, _D, _E, _F, _G);

/** \brief For each item in the list call it's own method, with eight arguments.
*/
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G, typename _H>
BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A, _B, _C, _D, _E, _F, _G, _H);

/** \brief Returns the pointer to the working set.
*/
BETAJAEN_CC_INLINE FlatPtr getFlat() const;

/** \brief Returns the number of SharedLists using this set.
*/
BETAJAEN_CC_INLINE unsigned int getUsageCount() const;

private: unsigned int* _Usage;
private: FlatPtr _Flat;
private: Iterator _Iterator;

};	// End of SharedList<Type, AllocatorType> Class.

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START


/** \brief Binary Tree with variable identifer and storage type.

*/
template <typename NodeIdentifier, class Type>
class BETAJAEN_CC_CLASS_EXPORT Tree
{
	// Much of this Tree was from the excellent tutorial by Julienne Walker
	// http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_bst1.aspx

public:

class Node;
typedef Node*			NodePtr;
typedef Type*			TypePtr;

/** \brief A tree is made up of nodes.
*/
class BETAJAEN_CC_CLASS_EXPORT Node
{

public:

Node(NodeIdentifier id, TypePtr val) : _ID(id), _Val(val)
{
	_Children[0] = NULL;
	_Children[1] = NULL;
}

void Replace(Node* n)
{
	_ID = n->_ID;
	_Val = n->_Val;
}

NodeIdentifier	_ID;
TypePtr			_Val;
NodePtr			_Children[2];

};


/** \brief Tree constructor
*/
public: BETAJAEN_CC_INLINE Tree() : _Root(NULL)
{
}


/** \brief Tree destructor.
	\note Does not remove or destroy the contents of the tree.
*/
public: BETAJAEN_CC_INLINE ~Tree()
{
}


/** \brief Destroys all the nodes in the tree and deletes all of the values referenced in it.
*/
public: BETAJAEN_CC_INLINE void DestroyAll()
{

	NodePtr iterator = _Root;
	NodePtr save = 0;

	while (iterator != NULL)
	{
		if (iterator->_Children[0] != NULL)
		{
			save = iterator->_Children[0];
			iterator->_Children[0] = save->_Children[1];
			save->_Children[1] = iterator;
		}
		else
		{
			save = iterator->_Children[1];
			delete iterator->_Val;
			delete iterator;
		}

		iterator = save;
	}

}


/** \brief Destroys all the nodes in the tree, but not all of the values referenced in it.
*/
public: BETAJAEN_CC_INLINE void RemoveAll()
{
	NodePtr iterator = _Root;
	NodePtr save = 0;

	while (iterator != NULL)
	{
		if (iterator->_Children[0] != NULL)
		{
			save = iterator->_Children[0];
			iterator->_Children[0] = save->_Children[1];
			save->_Children[1] = iterator;
		}
		else
		{
			save = iterator->_Children[1];
			delete iterator;
		}

		iterator = save;
	}

}


/** \brief Remove a Node based of an identifier
*/
public: BETAJAEN_CC_INLINE void Remove(NodeIdentifier id)
{

	if (_Root == NULL)
		return;

	Node head = {0};
	NodePtr iterator = &head;
	NodePtr *f = 0, *p = 0;
	int direction = 1;

	iterator->_Children[1] = _Root;

	//while (iterator = 

}



/** \brief Removes a ranges of nodes based on max. and min. identifiers.
	\note This operates based on the "operator <" of the TypeIdentifier the class,
	which defines if the type is in the range or not. Types such as ints, or reals
	aren't a problem but things like strings or complicated classes may produce
	strange results.
*/
public: BETAJAEN_CC_INLINE void RemoveRange(NodeIdentifier id_min, NodeIdentifier id_max)
{


}


/**
*/
public: BETAJAEN_CC_INLINE void Destroy(NodeIdentifier id)
{

}


/**
*/
public: BETAJAEN_CC_INLINE void DestroyRange(NodeIdentifier id_min, NodeIdentifier id_max)
{

}


/**
*/
public: BETAJAEN_CC_INLINE TypePtr Find(NodeIdentifier target)
{
	NodePtr iterator = _Root;
	while (iterator != NULL)
	{
		if (iterator->_ID == target)
		{
			return iterator->_Val;
		}
		else
		{
			iterator = iterator->_Children[int(iterator->_ID < target)];
		}
	}

	return 0;
}


/**
*/
public: BETAJAEN_CC_INLINE bool Insert(NodeIdentifier target, TypePtr val)
{
	Node* node = new Node(target, val);
	
	
	if (_Root == NULL)
	{
		_Root = node;
		return true;
	}
	else
	{
		Node* iterator = _Root;
		unsigned int direction;

		for ( ; ; )
		{
			direction = iterator->_ID < target;

			if (iterator->_ID == target)
			{
				delete node;
				return false;
			}
			else if (iterator->_Children[direction] == NULL)
				break;


			iterator = iterator->_Children[direction];
		}

		iterator->_Children[direction] = node;
	}

	return true;
}

private: NodePtr _Root;

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <
			typename IdentifierType,
			class Type,
			class AllocatorType
		 >
class BETAJAEN_CC_CLASS_EXPORT SharedMap
{

public:

typedef Type*						TypePtr;
typedef Tree<IdentifierType, Type>	TreeType;
typedef TreeType*					TreePtr;


/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE SharedMap()
{
	_Tree = new TreeType();
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE ~SharedMap()
{
	_Tree->DestroyAll();
	delete _Tree;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Get(IdentifierType identifier)
{
	return _Tree->Find(identifier);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr operator[](IdentifierType identifier)
{
	return _Tree->Find(identifier);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Insert(IdentifierType identifier, TypePtr ptr)
{
	_Tree->Insert(identifier, ptr);
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void DestroyAll()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void RemoveAll()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Destroy(IdentifierType)
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Remove(IdentifierType)
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Begin()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Next()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr End()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TypePtr Previous()
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE void Each(void (Type::*MethodPtr)())
{

}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE TreePtr getTree() const
{
	return _Tree;
}

/////////////////////////////////////////////////////////////

BETAJAEN_CC_INLINE unsigned int getUsage() const 
{
	return *_Usage;
}

/////////////////////////////////////////////////////////////

private: TreePtr _Tree;
private: unsigned int* _Usage;

/////////////////////////////////////////////////////////////

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with two rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector2
{

public:

typedef Vector2<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

BETAJAEN_CC_INLINE Vector2()
{
}

BETAJAEN_CC_INLINE Vector2(Type _i, Type _j) 
: i(_i), j(_j)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other)
{
	i = other.i; j = other.j;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator = (const Type& other)
{
	i = other; j = other;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const
{
	return (i == other.i && j == other.j);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const
{
	return (i != other.i || j != other.j);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with three rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector3
{

public:

typedef Vector3<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

/* \brief Third */
Type k;


BETAJAEN_CC_INLINE Vector3()
{
}

BETAJAEN_CC_INLINE Vector3(Type _i, Type _j, Type _k) 
: i(_i), j(_j), k(_k)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j, Third = k;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
	k = other.k; other.k = Third;
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other)
{
	i = other.i; j = other.j; k = other.k;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator = (const Type& other)
{
	i = other; j = other; k = other;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other; k *= other;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j; k *= other.k;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const
{
	return (i == other.i && j == other.j && k == other.k);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const
{
	return (i != other.i || j != other.j || k != other.k);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

/** \brief Vector with four rows.
*/
template <
			typename Type
		 >
class BETAJAEN_CC_CLASS_EXPORT Vector4 {

public:

typedef Vector4<Type> ThisType;

/* \brief First */
Type i;

/* \brief Second */
Type j;

/* \brief Third */
Type k;

/* \brief Fourth */
Type l;

BETAJAEN_CC_INLINE Vector4()
{
}

BETAJAEN_CC_INLINE Vector4(Type _i, Type _j, Type _k, Type _l) 
: i(_i), j(_j), k(_k), l(_l)
{
}

BETAJAEN_CC_INLINE void swap(ThisType& other)
{
	Type First = i, Second = j, Third = k, Fourth = l;
	i = other.i; other.i = First;
	j = other.j; other.j = Second; 
	k = other.k; other.k = Third;
	l = other.l; other.l = Fourth;
}

BETAJAEN_CC_INLINE ThisType& operator = (const ThisType& other) {
	i = other.i; j = other.j; k = other.k; l = other.l;
	return *this;
}

BETAJAEN_CC_INLINE ThisType& operator *= (const Type& other)
{
	i *= other; j *= other; k *= other; l *= other
}

BETAJAEN_CC_INLINE ThisType& operator *= (const ThisType& other)
{
	i *= other.i; j *= other.j; k *= other.k; l *= other.l;
}

BETAJAEN_CC_INLINE bool operator == (const ThisType& other) const {
	return (i == other.i && j == other.j && k == other.k && l == other.l);
}

BETAJAEN_CC_INLINE bool operator != (const ThisType& other) const {
	return (i != other.i || j != other.j || k != other.k || l != other.l);
}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_START

template <typename Type>
class BETAJAEN_CC_CLASS_EXPORT Vector {

	public:
		typedef Type* TypePtr;

		TypePtr j;
		unsigned int jSize;

		Vector(unsigned int j_size)
		{

		}

		~Vector()
		{

		}

};

BETAJAEN_CC_NAMESPACE_END

//////////////////////////////////////////////////////////////////////////
#if 0
BETAJAEN_CC_NAMESPACE_START

template <typename Type>
class BETAJAEN_CC_TEMPLATE_CLASS_EXPORT Matrix {

public:
	typedef Type* TypePtr;

	TypePtr        ij;
	unsigned int   iSize,
		           jSize;

	class MatrixIterator {
		public:
			
			enum IteratorRole {
				IR_COLUMN,
				IR_ROW
			};

			MatrixIterator(Matrix* _matrix, IteratorRole _role, unsigned int _iterator = 0)
				mMatrix(_matrix), mRole(_role), mIterator(_iterator)
			{
			}
			
			Matrix*      mMatrix;
			IteratorRole mRole;
			unsigned int mIterator;
			
	};

	class RowIterator {
		public:
			RowIterator(TypePtr ijPtr, unsigned int row, unsigned int i_size, unsigned j_size)
				: ij(ijPtr), r(row), iSize(i_size), jSize(j_size)
			{
			}

			Type& operator[] (unsigned int column)
			{
				return ij[(column * iSize) + r];
			}


			RowIterator& operator=(Type _f) {

				// Doesn't work.
				for (unsigned int i=r * iSize;i < (r * iSize) + iSize;i++) {
					printf("i=%i\n", i);
					ij[i] = _f;
				}
				printf("Done.\n");
				return *this;
			}

			TypePtr      ij;
			unsigned int r, iSize, jSize;

	};

	class ColumnIterator {
	
		public:

			ColumnIterator(TypePtr ijPtr, unsigned int col, unsigned int i_size, unsigned j_size)
				: ij(ijPtr), c(col), iSize(i_size), jSize(j_size)
			{
			}

			Type& operator[] (unsigned int row)
			{
				if (row > i_size)
					row = i_size;

				return ij[(c * iSize) + row];
			}


			ColumnIterator& operator=(Type _f) {
				for (unsigned int i=c;i < c + jSize;i++) {
					printf("i=%i\n", i);
					ij[i] = _f;
				}
				printf("Done.\n");
				return *this;
			}

			TypePtr      ij;
			unsigned int c, iSize, jSize;
	};

	class All {
		public:

			All()
			{
			}

			All(TypePtr ijPtr, unsigned int i_size, unsigned int j_size)
				: ij(ijPtr), iSize(i_size), jSize(j_size)
			{
			}

			All& operator=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] = _f;
				return *this;
			}

			All& operator*=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] *= _f;
				return *this;
			}

			All& operator/=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] /= _f;
				return *this;
			}

			All& operator+=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] += _f;
				return *this;
			}

			All& operator-=(Type _f) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i] -= _f;
				return *this;
			}

			All& operator++(int) {
				for (unsigned int i=0;i < iSize;i++)
					for (unsigned int j=0;j < jSize;j++)
						ij[(j * jSize) + i]++;
				return *this;
			}
			

			TypePtr      ij;
			unsigned iSize, jSize;
	};

	All all;

Matrix(unsigned int nbRows, unsigned int nbColumns)
: iSize(nbRows), jSize(nbColumns)
{
	ij = new Type[iSize * jSize];
	for (unsigned int i = 0;i < (iSize * jSize);i++)
		ij[i] = 0;

	all = All(ij, iSize, jSize);

	BETAJAEN_CC_PRINTF("Matrix created with %i", nbColumns);
}

~Matrix()
{
	if (iSize || jSize)
		delete [] ij;
}

RowIterator operator[] (unsigned int row)
{
	return RowIterator(ij, row, iSize, jSize);
}

ColumnIterator operator() (unsigned col)
{
	return ColumnIterator(ij, col, iSize, jSize);
}

void dump()
{
	for (unsigned int i=0;i < iSize;i++) {
		for (unsigned int j=0;j < jSize;j++) {
			printf("%f\t", ij[(j * jSize) + i]);
		}
		printf("\n");
	}

}

};
BETAJAEN_CC_NAMESPACE_END
#endif

//////////////////////////////////////////////////////////////////////////

#endif

#endif