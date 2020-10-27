//**************************************
// main.cpp
//
// Driver program for testing purposes
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <vector>
//#include "vector.h"

//using namespace nids;

const int NUM_ELEMENTS = 1000000000;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::vector<int> v;

	for (int element{ 0 }; element < NUM_ELEMENTS; ++element)
		v.push_back(element);

	return 0;
}