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

const int NUM_ELEMENTS = 1500000000;

int main()
{
	vector<int> v(NUM_ELEMENTS);

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
	{
		v.push_back(element);
	}
	v.shrink_to_fit();

	return 0;
}