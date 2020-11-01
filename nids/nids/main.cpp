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
	/*
	vector<int> v;

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
	{
		v.push_back(element);
	}*/

	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	v.push_back(1000);
	v.push_back(1500);
	v.push_back(2000);
	++iter;

	return 0;
}