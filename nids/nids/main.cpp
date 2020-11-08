//**************************************
// main.cpp
//
// Driver program for testing purposes
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#include <iostream>

#define MYVEC

#ifdef MYVEC
#include "vector.h"
using nids::vector;
#else
#include <vector>
using std::vector;
#endif
#include "vector.h"

const int NUM_ELEMENTS = 10;

int main()
{
	vector<int> v;

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
	{
		v.push_back(element);
	}
	v.shrink_to_fit();

	auto iter = v.begin() + 2;

	v.insert(v.end(), 21);

	for (int& i : v)
	{
		std::cout << i << std::endl;
	}

	return 0;
}