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
		vector_iterator(vector<Type>* vector) : m_vector(vector) { }
	private:
		vector<Type>* m_vector;
		size_t m_vectorCapacity;
	};
}