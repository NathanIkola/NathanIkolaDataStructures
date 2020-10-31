//**************************************
// vector_iterator.h
//
// The iterator class for nids::vector
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

namespace nids
{
	template<typename Type>
	class vector_iterator final
	{
	public:
		//******************************
		// End getter
		//******************************
		static constexpr inline vector_iterator<Type> end() noexcept
		{
			return vector_iterator<Type> { static_cast<vector<Type>*>(nullptr) };
		}

		//******************************
		// Constructor
		//******************************
		inline vector_iterator(vector<Type>* vector) noexcept : m_vector(vector), m_vectorCapacity(0), m_cursor(0) 
		{ 
			if (m_vector != nullptr) m_vectorCapacity = vector->capacity(); 
		}

		//******************************
		// Copy constructor
		//******************************
		inline vector_iterator(const vector_iterator<Type>& rhs) noexcept : m_vector(rhs.m_vector), m_vectorCapacity(rhs.m_vectorCapacity), m_cursor(0) { }

		//******************************
		// Move constructor
		//******************************
		inline vector_iterator(vector_iterator<Type>&& rhs) noexcept : m_vector(rhs.m_vector), m_vectorCapacity(rhs.m_vectorCapacity), m_cursor(rhs.m_cursor)
		{
			rhs.m_vector = nullptr;
			rhs.m_vectorCapacity = 0;
		}

		//******************************
		// Copy assignment operator
		//******************************
		inline vector_iterator<Type>& operator=(const vector_iterator<Type>& rhs) noexcept
		{
			assert(rhs.m_vector != nullptr);
			if (&rhs != this)
			{
				m_vector = rhs.m_vector;
				m_vectorCapacity = rhs.m_vectorCapacity;
			}
			return *this;
		}

		//******************************
		// Move assignment operator
		//******************************
		inline vector_iterator<Type>& operator=(vector_iterator<Type>&& rhs) noexcept
		{
			assert(rhs.m_vector != nullptr);
			if (&rhs != this)
			{
				m_vector = rhs.m_vector;
				rhs.m_vector = nullptr;
				m_cursor = rhs.m_cursor;
				rhs.m_cursor = 0;
				m_vectorCapacity = rhs.m_vectorCapacity;
				rhs.m_vectorCapacity = 0;
			}
			return *this;
		}

		//******************************
		// Desctructor
		//******************************
		inline ~vector_iterator() noexcept
		{
			m_vector = nullptr;
			m_cursor = 0;
			m_vectorCapacity = 0;
		}

		//*******[ Movement Operations ]
		//******************************
		// Increment operator (prefix)
		//******************************
		inline vector_iterator<Type>& operator++() noexcept 
		{
			assert(is_valid());
			++m_cursor;
			if (m_cursor >= m_vector->size()) m_vector = nullptr;
			return *this;
		}

		//******************************
		// Increment operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator++(int) noexcept 
		{
			assert(is_valid());
			vector_iterator<Type> _r = *this;
			++m_cursor;
			if (m_cursor >= m_vector->size()) m_vector = nullptr;
			return _r;
		}

		//******************************
		// Decrement operator (prefix)
		//******************************
		inline vector_iterator<Type>& operator--() noexcept
		{
			assert(m_cursor != 0);
			assert(is_valid());
			--m_cursor;
			return *this;
		}

		//******************************
		// Decrement operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator--(int) noexcept
		{
			assert(m_cursor != 0);
			assert(is_valid());
			vector_iterator<Type> _r = *this;
			--m_cursor;
			return _r;
		}

		//******************************
		// Next index method
		//******************************
		inline vector_iterator<Type>& next() noexcept { return this->operator++(); }

		//******************************
		// Previous index method
		//******************************
		inline vector_iterator<Type>& previous() noexcept { return this->operator--(); }

		//*****[ Comparison Operations ]
		//******************************
		// Comparison operator
		//******************************
		inline bool operator==(const vector_iterator<Type>& rhs) const noexcept
		{
			if (m_vector == nullptr && rhs.m_vector == nullptr) return true;
			if (m_vector != rhs.m_vector || m_cursor != rhs.m_cursor
				|| m_vectorCapacity != rhs.m_vectorCapacity) return false;
			return true;
		}

		//******************************
		// Comparison operator (NOT)
		//******************************
		inline bool operator!=(const vector_iterator<Type>& rhs) const noexcept { return !(*this == rhs); }

		//*******[ Accessor Operations ]
		//******************************
		// Dereference operator
		// (const correct)
		//******************************
		inline const Type& operator*() const noexcept { return m_vector->at(m_cursor); }

		//******************************
		// Dereference operator
		//******************************
		inline Type& operator*() noexcept { return m_vector->at(m_cursor); }
	private:
		size_t m_cursor;
		size_t m_vectorCapacity;
		vector<Type>* m_vector;

		//******************************
		// Validity checker
		//******************************
		inline bool is_valid() const noexcept 
		{ 
			return m_vector != nullptr 
				&& m_vectorCapacity == m_vector->capacity(); 
		}
	};
}