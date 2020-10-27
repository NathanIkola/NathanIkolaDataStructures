//**************************************
// vector.h
//
// Holds the definition of my
// vector class.
//
// The resize strategy is to up the
// size by 1.5 each time an allocation
// is required
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <assert.h>
#include <stdlib.h>
#include <string.h>

namespace nids
{
	template<typename Type, size_t Size = 8>
	class Vector
	{
	public:
		//*****************[ Manager Methods ]
		//************************************
		// Default constructor
		//************************************
		inline Vector() noexcept : m_array(nullptr), m_size(0), m_capacity(Size)
		{
			static_assert(sizeof(Type) != 0);
			m_array = malloc(sizeof(Type) * m_capacity);
			assert(m_array != nullptr);
		}

		//************************************
		// Parameterized constructor
		//
		// Allows for defining the size
		// without explicitly using the
		// template parameters
		//************************************
		inline Vector(size_t size) noexcept : m_array(nullptr), m_size(0), m_capacity(size)
		{
			static_assert(sizeof(Type) != 0);
			assert(size != 0);
			m_array = malloc(sizeof(Type) * m_capacity);
			assert(m_array != nullptr);
		}

		//************************************
		// Copy constructor
		//************************************
		Vector(const Vector& rhs) noexcept;

		//************************************
		// Move constructor
		//************************************
		Vector(Vector&& rhs) noexcept;

		//************************************
		// Copy assignment operator
		//************************************
		const Vector& operator=(const Vector& rhs) noexcept;

		//************************************
		// Move assignment operator
		//************************************
		Vector& operator=(Vector&& rhs) noexcept;

		//************************************
		// Destructor
		//************************************
		inline ~Vector() noexcept 
		{ 
			m_size = 0;
			m_capacity = 0;
			free(m_array);
		}

		//****************[ Accessor Methods ]
		//************************************
		// Size accessor
		//************************************
		inline size_t Size() const noexcept { return m_size; }

		//************************************
		// Capacity accessor
		//************************************
		inline size_t Capacity() const noexcept { return m_capacity; }

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
		size_t Resize(size_t size);

		//************************************
		// Resize method
		//
		// Resizes the vector and initializes
		// the data to the value of val
		// 
		// Returns new capacity, or old
		// capacity if unchanged
		//************************************
		size_t Resize(size_t size, const Type& val);

		//************************************
		// Push back method
		//
		// Adds the specified data to the end
		// of the vector and reallocates it
		// if necessary
		//************************************
		void PushBack(const Type& data);
	private:
		Type* m_array;
		size_t m_size;
		size_t m_capacity;
	};

	//*************************************
	// Copy constructor
	//*************************************
	template<typename Type, size_t Size>
	inline Vector<Type, Size>::Vector(const Vector& rhs) noexcept
		: m_array(nullptr), m_size(rhs.m_size), m_capacity(rhs.m_capacity)
	{
		assert(rhs.m_capacity > 0);
		m_array = malloc(sizeof(Type) * m_capacity);
		assert(m_array != nullptr);
		memcpy(m_array, rhs.m_array, sizeof(Type) * m_size);
	}

	//**********************************
	// Move constructor
	//**********************************
	template<typename Type, size_t Size>
	inline Vector<Type, Size>::Vector(Vector&& rhs) noexcept
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
	template<typename Type, size_t Size>
	inline const Vector<Type, Size>& Vector<Type, Size>::operator=(const Vector& rhs) noexcept
	{
		assert(rhs.m_capacity > 0);
		if (this != &rhs)
		{
			// avoid allocating space if we can help it
			if (m_capacity < rhs.m_capacity)
			{
				m_capacity = rhs.m_capacity;
				Type* newRegion = realloc(m_array, sizeof(Type) * m_capacity);
				if (newRegion == nullptr)
				{
					free(m_array);
					newRegion = malloc(sizeof(Type) * m_capacity);
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
	template<typename Type, size_t Size>
	inline Vector<Type, Size>& Vector<Type, Size>::operator=(Vector&& rhs) noexcept
	{
		assert(rhs.m_capacity > 0);
		if (this != &rhs)
		{
			// purge the left hand side
			free(m_arrray);
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
	template<typename Type, size_t Size>
	size_t Vector<Type, Size>::Resize(size_t size)
	{
		assert(size > 0);
		Type* newRegion = realloc(m_array, sizeof(Type) * size);

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

		m_array = newRegion;

		m_capacity = size;
		if (m_capacity < m_size)
			m_size = m_capacity;
		return m_capacity;
	}

	//**********************************
	// Resize method (initialization)
	//**********************************
	template<typename Type, size_t Size>
	inline size_t Vector<Type, Size>::Resize(size_t size, const Type& val)
	{
		assert(size > 0);
		Type* newRegion = realloc(m_array, sizeof(Type) * size);

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
	template<typename Type, size_t Size>
	inline void Vector<Type, Size>::PushBack(const Type& data)
	{
		assert(m_capacity != 0);
		// if reallocation is necessary
		if (m_size >= m_capacity)
		{
			// attempt to realloc to fit our new size
			size_t newCapacity = m_capacity * 1.5;
			Type* newRegion = realloc(m_array, sizeof(Type) * newCapacity);
			// check if realloc failed
			if (newRegion == nullptr)
			{
				newRegion = malloc(sizeof(Type) * newCapacity);
				assert(newRegion != nullptr);
				memcpy(newRegion, m_array, sizeof(Type) * m_size);
				free(m_array);
				m_array = newRegion;
			}
		}
		m_array[m_size++] = data;
	}
}