//**************************************
// main.cpp
//
// Driver program for testing purposes
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#define MYVEC

#ifdef MYVEC
#include "vector.h"
using nids::vector;
#else
#include <vector>
using std::vector;
#endif
#include "vector.h"

const int NUM_ELEMENTS = 1000000000;

int main()
{
	vector<int> v;

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
	{
		v.push_back(element);
	}

	return 0;
}