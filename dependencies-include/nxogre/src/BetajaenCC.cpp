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

#include "NxOgreStable.h"
#include "BetajaenCC.h"

#if 0

BETAJAEN_CC_NAMESPACE_START

/*
							Flat

	\note      Iterator is known as Type* in this file only.
*/

template< class Type, class AllocatorType >
Flat<Type, AllocatorType>::Flat(AllocatorPtr allocator, bool deleteAllocator)
	: First(NULL), Last(NULL), End(NULL), Allocator(allocator), AutoDeleteAllocator(deleteAllocator)
{
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
Flat<Type, AllocatorType>::~Flat()
{
	_deallocate(First);
	if (AutoDeleteAllocator)
		delete Allocator;
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
unsigned int Flat<Type, AllocatorType>::_size() const
{
	return (unsigned int) (Last - First);
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
unsigned int Flat<Type, AllocatorType>::_capacity() const
{
	return (unsigned int) (First == 0 ? 0 : End - First);
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
Type* Flat<Type, AllocatorType>::_allocate(unsigned int size)
{
	return (Type*) Allocator->Allocate(size * sizeof(Type));
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
void Flat<Type, AllocatorType>::_deallocate(Type* p)
{
	if (p)
		Allocator->Deallocate(p);
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
Type* Flat<Type, AllocatorType>::_reallocate(Type* p, unsigned int size)
{
	return (Iterator) Allocator->Reallocate(p, size  * sizeof(Type));
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
void Flat<Type, AllocatorType>::_clip(unsigned int size)
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

template< class Type, class AllocatorType >
void Flat<Type, AllocatorType>::_reserve(unsigned int new_size)
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

template< class Type, class AllocatorType >
Type* Flat<Type, AllocatorType>::_copy(Type* begin, Type* end, Type* dest)
{
	for (;begin != end; ++dest, ++begin)
		*dest = *begin;
	return dest;
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
void Flat<Type, AllocatorType>::_delete_range(Type* begin, Type* end)
{
	for (; begin != end; ++begin) {
		BETAJAEN_CC_DELETE(*begin);
	}
}

/////////////////////////////////////////////////////////////

template< class Type, class AllocatorType >
void Flat<Type, AllocatorType>::_destroy(Type* begin, Type* end)
{
	for (; begin != end; ++begin) {
		BETAJAEN_CC_DESTRUCTOR(begin)
		begin->~Type();
	}
}

BETAJAEN_CC_NAMESPACE_END


/**
					SharedList
*/

BETAJAEN_CC_NAMESPACE_START

/////////////////////////////////////////////////////////////

#define SharedListType SharedList<Type, AllocatorType>
#define TypePtr        Type*

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
SharedList<Type, AllocatorType>::SharedList(AllocatorType* _allocator, bool _auto_delete_allocator)
{
	if (_allocator == NULL)
		_allocator = new AllocatorType();

	_Flat = new FlatType(_allocator, _auto_delete_allocator);
	_Usage = new unsigned int(1);

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
SharedList<Type, AllocatorType>::SharedList(const SharedListType& other)
{

	_Flat = other._Flat;
	_Usage = other._Usage;
	++(*_Usage);

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
SharedListType& SharedList<Type, AllocatorType>::operator=(const SharedListType& other)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Get(size_t pos)
{
	if (pos > Size())
		return NULL;

	return *(_Flat->First + pos);
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::operator[](size_t pos)
{
	if (pos > Size())
		return NULL;

	return *(_Flat->First + pos);
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
unsigned int SharedList<Type, AllocatorType>::WhereIs(TypePtr ptr)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
bool SharedList<Type, AllocatorType>::Has(TypePtr ptr)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
unsigned SharedList<Type, AllocatorType>::Size() const
{
	return _Flat->_size();
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Insert(Type* const & val)
{

	if (_Flat->End <= _Flat->Last)
		_Flat->_reserve( (1 + Size()) * 2);

	*_Flat->Last = val;
	_Flat->Last++;

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Clean(unsigned int n)
{
	_Flat->_clip(_Flat->_size() + n);
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Destroy(unsigned int n)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::DestroyAll()
{
	if (Size() == 0)
		return;

	_Flat->_delete_range(_Flat->First, _Flat->Last);
	// Could be iffy.
	_Flat->Last = _Flat->First;

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Destroy(TypePtr val) {
	unsigned int i = WhereIs(val);
	Destroy(i);
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Destroy(AbsolutePosition position)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Remove(unsigned int n)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Remove(AbsolutePosition position)
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

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Begin()
{

	if (_Flat->_size() == 0)
		return NULL;

	_Iterator = _Flat->First;
	return *_Iterator;

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Next()
{

	if (_Flat->_size() == 0)
		return NULL;
	else if (_Iterator == _Flat->Last)
		return NULL;
	else
		return (*_Iterator++);

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::End()
{

	if (_Flat->_size() == 0)
		return NULL;

	_Iterator = _Flat->Last - 1;
	return *_Iterator;

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
TypePtr SharedList<Type, AllocatorType>::Previous()
{

	if (_Flat->_size() == 0)
		return NULL;
	else if (_Iterator == _Flat->First - 1)
		return NULL;
	else
		return (*_Iterator--);

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)()) {
	
	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin) {
		(*begin->*MethodPtr)();
	}

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template < typename _A >
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A), _A _1) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin) {
		(*begin->*MethodPtr)(_1);
	}

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template < typename _A, typename _B>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B), _A _1, _B _2) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C), _A _1, _B _2, _C _3)
{

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C, typename _D>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4)
{

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C, typename _D, typename _E>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5) {

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6)
{

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6, _G _7)
{

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6, _7);

}

/////////////////////////////////////////////////////////////

template < typename Type, typename AllocatorType>
template <typename _A, typename _B, typename _C, typename _D, typename _E, typename _F, typename _G, typename _H>
void SharedList<Type, AllocatorType>::Each(void (Type::*MethodPtr)(_A, _B, _C, _D), _A _1, _B _2, _C _3, _D _4, _E _5, _F _6, _G _7, _H _8)
{

	if (_Flat->_size() == 0)
		return;

	for(Iterator begin = _Flat->First; begin != _Flat->Last; ++begin)
		(*begin->*MethodPtr)(_1, _2, _3, _4, _5, _6, _7, _8);

}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
unsigned int SharedList<Type, AllocatorType>::getUsageCount() const
{
	return *_Usage;
}

/////////////////////////////////////////////////////////////

template < class Type, class AllocatorType >
Flat<Type*, AllocatorType>* SharedList<Type, AllocatorType>::getFlat() const {
	return _Flat;
}

/////////////////////////////////////////////////////////////

#undef SharedListType
#undef TypePtr

/////////////////////////////////////////////////////////////

BETAJAEN_CC_NAMESPACE_END


#endif