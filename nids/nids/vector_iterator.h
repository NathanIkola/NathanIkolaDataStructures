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
		// Constructor
		//******************************
		inline vector_iterator(const vector<Type>* vector) noexcept : m_vector(vector), m_cursor(nullptr) 
		{ 
			assert(m_vector != nullptr);
			if(m_vector->capacity() != 0)
				m_cursor = &(const_cast<nids::vector<Type>*>(vector)->at(0));
		}

		//******************************
		// Copy constructor
		//******************************
		inline vector_iterator(const vector_iterator<Type>& rhs) noexcept : m_vector(rhs.m_vector), m_cursor(rhs.m_cursor) 
		{ 
			assert(m_vector != nullptr);
		}

		//******************************
		// Move constructor
		//******************************
		inline vector_iterator(vector_iterator<Type>&& rhs) noexcept : m_vector(rhs.m_vector), m_cursor(rhs.m_cursor)
		{
			rhs.m_cursor = nullptr;
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
				m_cursor = rhs.m_cursor;
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
				rhs.m_cursor = nullptr;
			}
			return *this;
		}

		//******************************
		// Desctructor
		//******************************
		inline ~vector_iterator() noexcept
		{
			m_vector = nullptr;
			m_cursor = nullptr;
		}

		//*******[ Movement Operations ]
		//******************************
		// Increment operator (prefix)
		//******************************
		inline vector_iterator<Type>& operator++() noexcept 
		{
			assert(m_cursor != m_vector->back() + 1);
			++m_cursor;
			return *this;
		}

		//******************************
		// Increment operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator++(int) noexcept 
		{
			vector_iterator<Type> _r = *this;
			assert(m_cursor != m_vector->back() + 1);
			++m_cursor;
			return _r;
		}

		//******************************
		// Decrement operator (prefix)
		//******************************
		inline vector_iterator<Type>& operator--() noexcept
		{
			assert(m_cursor != m_vector->front());
			--m_cursor;
			return *this;
		}

		//******************************
		// Decrement operator (postfix)
		//******************************
		inline vector_iterator<Type>& operator--(int) noexcept
		{
			assert(m_cursor != m_vector->front());
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

		//******************************
		// Addition operator
		//******************************
		inline vector_iterator<Type> operator+(int amount) noexcept
		{
			vector_iterator<Type> v{ *this };
			v.m_cursor += amount;
		}

		//******************************
		// In-place addition operator
		//******************************
		inline vector_iterator<Type>& operator+=(int amount) noexcept
		{
			m_cursor += amount;
			return *this;
		}

		//******************************
		// Subtraction operator
		//******************************
		inline vector_iterator<Type> operator-(int amount) noexcept
		{
			vector_iterator<Type> v{ *this };
			v.m_cursor -= amount;
		}

		//******************************
		// In-place subtraction operator
		//******************************
		inline vector_iterator<Type>& operator-=(int amount) noexcept
		{
			m_cursor -= amount;
			return *this;
		}

		//*****[ Comparison Operations ]
		//******************************
		// Comparison operator
		//******************************
		inline bool operator==(const vector_iterator<Type>& rhs) const noexcept { return m_cursor == rhs.m_cursor; }

		//******************************
		// Comparison operator (NOT)
		//******************************
		inline bool operator!=(const vector_iterator<Type>& rhs) const noexcept { return !(*this == rhs); }

		//******************************
		// LT operator
		//******************************
		inline bool operator<(const vector_iterator<Type>& rhs) const noexcept { return m_cursor < rhs.m_cursor; }

		//******************************
		// GT operator
		//******************************
		inline bool operator>(const vector_iterator<Type>& rhs) const noexcept { return m_cursor > rhs.m_cursor; }

		//******************************
		// LTE operator
		//******************************
		inline bool operator<=(const vector_iterator<Type>& rhs) const noexcept { return m_cursor <= rhs.m_cursor; }

		//******************************
		// GTE operator
		//******************************
		inline bool operator>=(const vector_iterator<Type>& rhs) const noexcept { return m_cursor >= rhs.m_cursor; }

		//*******[ Accessor Operations ]
		//******************************
		// Dereference operator
		// (const correct)
		//******************************
		inline const Type& operator*() const noexcept 
		{
			assert(m_cursor != m_vector->back() + 1);
			return *m_cursor;
		}

		//******************************
		// Dereference operator
		//******************************
		inline Type& operator*() noexcept 
		{
			assert(m_cursor != m_vector->back() + 1);
			return *m_cursor;
		}

		//******************************
		// Pointer operator 
		// (const correct)
		//******************************
		inline const Type& operator->() const noexcept { return operator*(); }

		//******************************
		// Pointer operator
		//******************************
		inline Type& operator->() noexcept { return operator*(); }

		//******************************
		// Offset subscript operator
		//******************************
		inline Type& operator[](int offset) { return m_cursor[offset]; }

		//************[ Static Methods ]
		//******************************
		// End getter
		//******************************
		static inline vector_iterator<Type> end(const vector<Type>* v) noexcept
		{
			vector_iterator<Type> iter{ v };
			if(v->capacity() != 0)
				iter.m_cursor = v->back() + 1;
			return iter;
		}
	private:
		const vector<Type>* m_vector;
		Type* m_cursor;
	};
}