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

	int arr[] = {501, 502, 503};

	auto iter = v.begin() + 7;

	v.insert(iter, arr, arr+3);

	for (int& i : v)
	{
		std::cout << i << std::endl;
	}

	return 0;
}