//**************************************
// main.cpp
//
// Driver program for testing purposes
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/

#define MYVEC

#ifdef MYVEC
#include "vector.h"
#define VEC nids::Vector
#else
#include <vector>
#define VEC std::vector
#endif
#include "vector.h"

const int NUM_ELEMENTS = 1000000000;

int main()
{
	VEC<int> v;

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
	{
		v.push_back(element);
	}

	return 0;
}