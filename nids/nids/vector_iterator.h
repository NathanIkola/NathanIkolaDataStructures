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
		static inline vector_iterator<Type> end() noexcept 
		{
			vector_iterator<Type> v(static_cast<vector<Type>*>(this));
			v.m_vector = nullptr;
			return v;
		}

		//******************************
		// Constructor
		//******************************
		inline vector_iterator(vector<Type>* vector) noexcept : m_vector(vector) { assert(vector != nullptr); }

		//******************************
		// Copy constructor
		//******************************
		inline vector_iterator(const vector_iterator<Type>& rhs) noexcept : m_vector(rhs.m_vector), m_vectorCapacity(rhs.m_vectorCapacity) { assert(m_vector != nullptr); }

		//******************************
		// Move constructor
		//******************************
		inline vector_iterator(vector_iterator<Type>&& rhs) noexcept : m_vector(rhs.m_vector), m_vectorCapacity(rhs.m_vectorCapacity)
		{
			assert(m_vector != nullptr);
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
			assert(m_vector != nullptr);
			++m_cursor;
			if (m_cursor >= m_vectorCapacity) m_vector = nullptr;
			return *this;
		}

		//******************************
		// Increment operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator++(int) noexcept 
		{
			assert(m_vector != nullptr);
			vector_iterator<Type> _r = *this;
			++m_cursor;
			if (m_cursor >= m_vectorCapacity) m_vector = nullptr;
			return _r;
		}

		//******************************
		// Decrement operator (prefix)
		//******************************
		inline vector_iterator<Type>& operator--() noexcept
		{
			assert(m_vector != nullptr);
			assert(m_cursor != 0);
			--m_cursor;
			return *this;
		}

		//******************************
		// Decrement operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator--(int) noexcept
		{
			assert(m_vector != nullptr);
			assert(m_cursor != 0);
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
		inline const Type& operator*() const noexcept { return m_vector[m_cursor]; }

		//******************************
		// Dereference operator
		//******************************
		inline Type& operator*() noexcept { return m_vector[m_cursor]; }
	private:
		size_t m_cursor;
		size_t m_vectorCapacity;
		vector<Type>* m_vector;
	};
}