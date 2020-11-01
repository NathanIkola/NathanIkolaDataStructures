//**************************************
// vector.h
//
// Holds the definition of my
// vector class.
//
// The resize strategy is to up the
// size by 3 each time an allocation
// is required
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <assert.h>
#include <limits>
#include <stdlib.h>
#include <string.h>
#include <utility>

/*
TODO:
	front
	back
	begin, cbegin
	end, cend
	rbegin, crbegin
	reserve
	shrink_to_fit
	clear
	insert
	emplace
	erase
	emplace_back
	pop_back
	swap
*/

namespace nids
{
	// static expansion size on push_back expansion
	const float EXPANSION_SIZE = 3;

	template<typename Type>
	class vector_iterator;

	template<typename Type>
	class vector final
	{
	public:
		using iterator = vector_iterator<Type>;

		//************************************
		// End getter method
		//************************************
		inline typename iterator end() const noexcept;

		//*****************[ Manager Methods ]
		//************************************
		// Default constructor
		//************************************
		inline vector() noexcept : m_array(nullptr), m_size(0), m_capacity(0)
		{
			static_assert(sizeof(Type) != 0);
			m_array = nullptr;
		}

		//************************************
		// Parameterized constructor
		//
		// Allows for defining the size
		// without explicitly using the
		// template parameters
		//************************************
		inline vector(size_t size) noexcept : m_array(nullptr), m_size(0), m_capacity(size)
		{
			static_assert(sizeof(Type) != 0);
			if (m_capacity > 0)
			{
				m_array = static_cast<Type*>(malloc(sizeof(Type) * m_capacity));
				assert(m_array != nullptr);
			}
			else
				m_array = nullptr;
		}

		//************************************
		// Copy constructor
		//************************************
		vector(const vector& rhs) noexcept;

		//************************************
		// Move constructor
		//************************************
		vector(vector&& rhs) noexcept;

		//************************************
		// Copy assignment operator
		//************************************
		vector& operator=(const vector& rhs) noexcept;

		//************************************
		// Move assignment operator
		//************************************
		vector& operator=(vector&& rhs) noexcept;

		//************************************
		// Destructor
		//************************************
		inline ~vector() noexcept 
		{
			m_size = 0;
			m_capacity = 0;
			free(m_array);
			m_array = nullptr;
		}

		//****************[ Accessor Methods ]
		//************************************
		// Size accessor
		//************************************
		inline size_t size() const noexcept { return m_size; }

		//************************************
		// Capacity accessor
		//************************************
		inline size_t capacity() const noexcept { return m_capacity; }

		//************************************
		// Const correct subscript operator
		//************************************
		inline const Type& operator[](size_t index) const noexcept
		{
			assert(index < m_size);
			return m_array[index];
		}

		//************************************
		// Subscript operator
		//************************************
		inline Type& operator[](size_t index) noexcept
		{
			assert(index < m_size);
			return m_array[index];
		}

		//************************************
		// Const correct at object accessor
		//************************************
		inline const Type& at(size_t index) const noexcept { return operator[](index); }

		//************************************
		// At object accessor
		//************************************
		inline Type& at(size_t index) noexcept { return operator[](index); }

		//************************************
		// Max index getter
		//************************************
		inline size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); }

		//************************************
		// Empty status getter
		//************************************
		inline bool empty() const noexcept { return m_size == 0; }

		//************************************
		// Array getter
		//************************************
		const Type* data() const noexcept { return m_array; }

		//************************************
		// Front item getter
		//************************************
		inline Type* front() const noexcept { return m_array; }

		//************************************
		// Back item getter
		//************************************
		inline Type* back() const noexcept { return &m_array[m_size - 1]; }

		//************************************
		// Begin iterator getter
		//************************************
		inline typename iterator begin() noexcept;

		//*****************[ Mutator Methods ]
		//************************************
		// Resize method
		//
		// Resizes the vector and does not
		// initialize the new data members
		//
		// Returns new capacity, or old
		// capacity if unchanged
		//************************************
		size_t resize(size_t size) noexcept;

		//************************************
		// Resize method
		//
		// Resizes the vector and initializes
		// the data to the value of val
		// 
		// Returns new capacity, or old
		// capacity if unchanged
		//************************************
		size_t resize(size_t size, const Type& val) noexcept;

		//************************************
		// Push back method
		//
		// Adds the specified data to the end
		// of the vector and reallocates it
		// if necessary
		//
		// WARNING: passing in references
		// to current vector index can
		// result in undefined behavior if
		// the vector resizes on push_back
		//************************************
		inline void push_back(const Type& data) noexcept;

		//************************************
		// Push back method (rvalue)
		//
		// Adds the specified data to the end
		// of the vector and reallocates it
		// if necessary
		//
		// WARNING: passing in references
		// to current vector index can
		// result in undefined behavior if
		// the vector resizes on push_back
		//************************************
		inline void push_back(Type&& data) noexcept;

		//************************************
		// Push back method (internal safe)
		//
		// Adds the specified data to the end
		// of the vector and reallocates it
		// if necessary
		//************************************
		inline void push_back_i(const Type& data) noexcept;

		//************************************
		// Push back method 
		// (rvalue, internal safe)
		//
		// Adds the specified data to the end
		// of the vector and reallocates it
		// if necessary
		//************************************
		inline void push_back_i(Type&& data) noexcept;
	private:
		Type* m_array;
		size_t m_size;
		size_t m_capacity;
	};

	//*************************************
	// Copy constructor
	//*************************************
	template<typename Type>
	inline vector<Type>::vector(const vector& rhs) noexcept
		: m_array(nullptr), m_size(rhs.m_size), m_capacity(rhs.m_capacity)
	{
		assert(rhs.m_capacity > 0);
		m_array = static_cast<Type*>(malloc(sizeof(Type) * m_capacity));
		assert(m_array != nullptr);
		memcpy(m_array, rhs.m_array, sizeof(Type) * m_size);
	}

	//**********************************
	// Move constructor
	//**********************************
	template<typename Type>
	inline vector<Type>::vector(vector&& rhs) noexcept
		: m_array(rhs.m_array), m_size(rhs.m_size), m_capacity(rhs.m_capacity)
	{
		assert(rhs.m_capacity > 0);
		rhs.m_array = nullptr;
		rhs.m_capacity = 0;
		rhs.m_size = 0;
	}

	//**********************************
	// Copy assignment operator
	//**********************************
	template<typename Type>
	inline vector<Type>& vector<Type>::operator=(const vector& rhs) noexcept
	{
		assert(rhs.m_capacity > 0);
		if (this != &rhs)
		{
			// avoid allocating space if we can help it
			if (m_capacity < rhs.m_capacity)
			{
				m_capacity = rhs.m_capacity;
				Type* newRegion = static_cast<Type*>(realloc(m_array, sizeof(Type) * m_capacity));
				if (newRegion == nullptr)
				{
					free(m_array);
					newRegion = static_cast<Type*>(malloc(sizeof(Type) * m_capacity));
					assert(newRegion != nullptr);
				}
				m_array = newRegion;
			}

			// deep copy rhs
			m_size = rhs.m_size;
			memcpy(m_array, rhs.m_array, sizeof(Type) * m_size);
		}
		return *this;
	}

	//**********************************
	// Move assignment operator
	//**********************************
	template<typename Type>
	inline vector<Type>& vector<Type>::operator=(vector&& rhs) noexcept
	{
		assert(rhs.m_capacity > 0);
		if (this != &rhs)
		{
			// purge the left hand side
			free(m_array);
			// move the right hand side
			m_array = rhs.m_array;
			m_size = rhs.m_size;
			m_capacity = rhs.m_capacity;
			rhs.m_array = nullptr;
			rhs.m_capacity = 0;
			rhs.m_size = 0;
		}
		return *this;
	}

	//**********************************
	// Resize method (no initialization)
	//**********************************
	template<typename Type>
	size_t vector<Type>::resize(size_t size) noexcept
	{
		// see if size is equal to zero
		if (size == 0)
		{
			m_capacity = 0;
			free(m_array);
			m_array = nullptr;
			return 0;
		}

		void* newRegion = realloc(m_array, sizeof(Type) * size);

		// if realloc failed
		if (newRegion == nullptr)
		{
			newRegion = malloc(sizeof(Type) * size);
			if (newRegion == nullptr)
				return m_capacity;
			
			// copy the old data
			memcpy(newRegion, m_array, sizeof(Type) * m_size);
			free(m_array);
		}

		m_array = static_cast<Type*>(newRegion);

		m_capacity = size;
		if (m_capacity < m_size)
			m_size = m_capacity;
		return m_capacity;
	}

	//**********************************
	// Resize method (initialization)
	//**********************************
	template<typename Type>
	size_t vector<Type>::resize(size_t size, const Type& val) noexcept
	{
		// see if size is equal to zero
		if (size == 0)
		{
			m_capacity = 0;
			free(m_array);
			m_array = nullptr;
			return 0;
		}

		Type* newRegion = static_cast<Type*>(realloc(m_array, sizeof(Type) * size));

		// if realloc failed
		if (newRegion == nullptr)
		{
			newRegion = static_cast<Type*>(malloc(sizeof(Type) * size));
			if (newRegion == nullptr)
				return m_capacity;

			// copy the old data
			memcpy(newRegion, m_array, sizeof(Type) * m_size);
			free(m_array);
		}

		m_array = newRegion;

		// initialize the new data
		for (; m_capacity < size; ++m_capacity)
			m_array[m_capacity] = val;

		// this is still required in case size < m_capacity
		m_capacity = size;
		if (m_capacity < m_size)
			m_size = m_capacity;
		return m_capacity;
	}

	//**********************************
	// Push back method
	//**********************************
	template<typename Type>
	inline void vector<Type>::push_back(const Type& data) noexcept
	{
		// if reallocation is necessary
		if (m_size < m_capacity)
		{
			m_array[m_size++] = data;
			return;
		}

		if (m_capacity == 0) ++m_capacity;
		resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
		m_array[m_size++] = data;
	}

	//**********************************
	// Push back method (rvalue)
	//**********************************
	template<typename Type>
	inline void vector<Type>::push_back(Type&& data) noexcept
	{
		// if reallocation is not necessary
		if (m_size < m_capacity)
		{
			m_array[m_size++] = data;
			return;
		}

		if (m_capacity == 0) ++m_capacity;
		resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
		m_array[m_size++] = data;
	}

	//**********************************
	// Push back method (internal safe)
	//**********************************
	template<typename Type>
	inline void vector<Type>::push_back_i(const Type& data) noexcept
	{
		// if reallocation is not necessary
		if (m_size < m_capacity)
		{
			m_array[m_size++] = data;
			return;
		}

		if (m_capacity == 0) ++m_capacity;
		else if (&data >= m_array && &data <= m_array + m_capacity)
		{
			size_t _cached_index = static_cast<size_t>(&data - &m_array[0]);
			resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
			m_array[m_size++] = m_array[_cached_index];
			return;
		}
		resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
		m_array[m_size++] = data;
	}

	//**********************************
	// Push back method 
	// (rvalue, internal safe)
	//**********************************
	template<typename Type>
	inline void vector<Type>::push_back_i(Type&& data) noexcept
	{
		// if reallocation is necessary
		if (m_size < m_capacity)
		{
			m_array[m_size++] = data;
			return;
		}

		if (m_capacity == 0) ++m_capacity;
		else if (&data >= m_array && &data <= m_array + m_capacity)
		{
			size_t _cached_index = static_cast<size_t>(&data - &m_array[0]);
			resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
			m_array[m_size++] = std::move(m_array[_cached_index]);
			return;
		}
		resize(static_cast<size_t>(m_capacity * EXPANSION_SIZE));
		m_array[m_size++] = data;
	}
}

#include "vector_iterator.h"

// split out the methods that need the vector_iterator class
namespace nids
{
	//************************************
	// Begin iterator getter
	//************************************
	template<typename Type>
	inline typename vector<Type>::iterator vector<Type>::begin() noexcept
	{
		if (m_capacity) return vector_iterator(this);
		return end();
	}

	//************************************
	// End getter method
	//************************************
	template<typename Type>
	inline typename vector<Type>::iterator vector<Type>::end() const noexcept
	{
		return vector_iterator<Type>::end(this);
	}
}