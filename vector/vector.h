#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>

//? use default capacity
//const int def_capacity = 1024;//some multiple of 2

//Iterator class
template<class T>
class m_iterator
{
public:
	m_iterator()
		:_iterator_ptr(NULL)
	{}
	m_iterator(T* ptr)
		:_iterator_ptr(ptr)
	{}
	m_iterator(const m_iterator& itObj)
		:_iterator_ptr(itObj._iterator_ptr)
	{}
	m_iterator& operator=(const m_iterator& itObj)
	{
		_iterator_ptr = itObj._iterator_ptr;
	}
	T operator*()
	{
		return *_iterator_ptr;
	}
	T* operator->()
	{
		return _iterator_ptr;
	}
	bool operator==(m_iterator itObj)
	{
		return itObj._iterator_ptr == _iterator_ptr;
	}
	bool operator!=(m_iterator itObj)
	{
		return !(itObj == *this);
	}
	m_iterator& operator++()
	{
		++(this->_iterator_ptr);
		return *this;
	}
	m_iterator operator++(int)
	{
		m_iterator tmp = *this;
		++(this->_iterator_ptr);
		return tmp;
	}
	m_iterator& operator--()
	{
		--(this->_iterator_ptr);
		return *this;
	}
	m_iterator operator--(int)
	{
		m_iterator tmp = *this;
		--(this->_iterator_ptr);
		return tmp;
	}
	int operator+(const m_iterator& itObj)
	{
		return (this->_iterator_ptr + itObj._iterator_ptr);
	}
	m_iterator operator+(int diff)
	{
		return m_iterator(this->_iterator_ptr + diff);
	}
	int operator-(const m_iterator& itObj)
	{
		return (this->_iterator_ptr - itObj._iterator_ptr);
	}
	m_iterator operator-(int diff)
	{
		return m_iterator(this->_iterator_ptr - diff);
	}
private:
	T* _iterator_ptr;
};
//TODO::const m_iterator
//TODO::reverse m_iterator
//TODO::const_reverse m_iterator

template<class T>
class m_vector
{
public:
	using iterator = m_iterator<T>;
	m_vector()
		: _size(0)
		, _capacity(0)
		, _ptr(NULL)
	{}
//TODO::m_vector() noexcept(noexcept(Allocator()));since C++17․ Change

//TODO::explicit m_vector(const Allocator& alloc) noexcept;since C++17․ Add

	m_vector(size_t count, const T& val)
	{
		_ptr = new T[count];
		_size = _capacity = count;
		for (size_t i = 0; i < count; ++i)
		{
			_ptr[i] = val;
		}
	}
	//TODO::m_vector(size_type count,
		//const T& value,
		//const Allocator& alloc = Allocator());since C++11․ Add

	explicit m_vector(size_t count)
	{
		_ptr = new T[count];
		_size = _capacity = count;
		for (size_t i = 0; i < count; ++i)
		{
			_ptr[i] = T();
		}
	}
	//TODO::explicit m_vector( size_type count, const Allocator& alloc = Allocator() );since C++14. Change

	//TODO::template< class InputIt >
	//m_vector(InputIt first, InputIt last,
		//const Allocator& alloc = Allocator());
	m_vector(iterator first, iterator last)
	{
		_capacity = _size = last - first;
		_ptr = new T[_size];
		for (size_t i = 0; i < _size; ++i)
		{
			_ptr[i] = *(first++);
		}
	}
	
	m_vector(const m_vector& obj)//copy constructor
	{
		_size = obj._size;
		_capacity = obj._capacity;
		_ptr = new T[obj._size];
		for (size_t i = 0; i < obj._size; ++i)
		{
			_ptr[i] = obj._ptr[i];
		}
	}
	//TODO:: m_vector( const m_vector& other, const Allocator& alloc );since C++11․ Change

	m_vector(m_vector&& obj) noexcept//move constructor
	{
		_size = obj._size;
		_capacity = obj._capacity;
		_ptr = obj._ptr;
		obj._ptr = NULL;
		obj._capacity = 0;
		obj._size = 0;
	}
	//TODO:: m_vector(vector&& other, const Allocator& alloc);

	//TODO::m_vector(std::initializer_list<T> init,
		//const Allocator& alloc = Allocator());

	~m_vector()//contexpr appears only on c++20
	{
		_size = 0;
		_capacity = 0;
		delete _ptr;
		_ptr = NULL;
	}

	m_vector& operator=(const m_vector& obj)//copy assign operator
	{
		T* tmp = NULL;
		try
		{
			if (obj._ptr == this->_ptr)//to avoid self-assignement.
				return *this;
			tmp = new T[obj._size];//Also think about optimization when _size>obj._size
			delete[] _ptr;
			for (size_t i = 0; i < obj._size; ++i)
			{
				tmp[i] = obj._ptr[i];
			}
			_ptr = tmp;
			_size = obj._size;
			_capacity = obj._capacity;
		}
		catch (...)
		{
			if (tmp)
			{
				delete[] tmp;
				tmp = NULL;
			}
			throw;
		}
		return *this;
	}
	m_vector& operator=(m_vector&& obj) noexcept//move assign operator
	{
		_size = obj._size;
		_capacity = obj._capacity;
		_ptr = obj._ptr;
		obj._ptr = NULL;
		obj._capacity = 0;
		obj._size = 0;
		return *this;
	}
	//TODO::m_vector& operator=( std::initializer_list<T> ilist );

	//TODO::assign, get_allocator

	

	//Element access
	T& operator[](size_t index) noexcept
	{
		//TODO:use assert for debug version: assert(index < _size && "vector subscript out of range");
		return _ptr[index];
	}
	T& at(size_t index) //noexcept for release version in std
	{
		if (index >= _size)
			throw std::exception("vector subscript out of range");
		return _ptr[index];
	}
	//TODO::front, back, data

	//Iterators
	iterator begin()
	{
		return iterator(_ptr);
	}
	iterator end()
	{
		return iterator(_ptr + _size);
	}
	//TODO::cbegin, rbegin, cend, rend, crbegin, crend

	//Capacity
	//TODO::empty,size,max_size,reserve,capacity,shrink_to_fit

	//Modifiers
	void push_back(const T& val)
	{
		if (_size == _capacity)
		{//enhance vector
			_capacity *= 2;
			T* newPtr = new T[_capacity];
			for (size_t i = 0; i < _capacity/2; ++i)
			{
				newPtr[i] = _ptr[i];
			}
			delete _ptr;
			_ptr = newPtr;
		}
		_ptr[_size++] = val;
	}
	void emplace_back(T&& val)
	{
		if (_size == _capacity)
		{//enhance vector
			_capacity *= 2;
			T* newPtr = new T[_capacity];
			for (size_t i = 0; i < _capacity/2; ++i)
			{
				newPtr[i] = _ptr[i];
			}
			delete _ptr;
			_ptr = newPtr;
		}
		_ptr[_size++] = std::move(val);
	}
	//TODO:: clear, insert, emplace, erase, pop_back, resize, swap
	
	//Non-member functions
	//TODO::operator==,!=,<,<=,>,>=
	//TODO::std::swap(std::vector)
	//TODO::c++20:: <=>, erase(std::vector), erase_if(std::vector)

	//TODO::allocator
private:
	T* _ptr;//TODO:consider unique_ptr
	size_t _size;
	size_t _capacity;
};

//TODO::vector<bool> specialization(which may be optimized for space efficiency.)

#endif

