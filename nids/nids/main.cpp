//**************************************
// main.cpp
//
// Driver program for testing purposes
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#include <iostream>
#include <chrono>
#include <functional>

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration;
using std::chrono::steady_clock;
using std::chrono::duration_cast;

//#define MYVEC

#ifdef MYVEC
#include "vector.h"
using nids::vector;
#else
#include <vector>
using std::vector;
#endif
#include "vector.h"

constexpr int NUM_ELEMENTS = 10;
constexpr int NUM_ITERATIONS = 500;
nanoseconds durations[NUM_ITERATIONS];

// test structure
typedef struct
{
	const char* testName;
	void(*func)();
	nanoseconds duration;
} test_t;

template<int size = 1024>
struct sizeType
{
	char buffer[size];
};

//**************************************
// Test inserting 1 million ints at
// default size
//**************************************
void InsertOneMillionInts() noexcept;

//**************************************
// Test inserting 10 million ints at
// default size
//**************************************
void InsertTenMillionInts() noexcept;

//**************************************
// Insert 1 million 1KB sized items
//**************************************
void InsertOneMillionKBs() noexcept;

//**************************************
// Insert 10 million 1KB sized items
//**************************************
void InsertTenMillionKBs() noexcept;

//**************************************
int main()
{
	// array of functions to test
	test_t tests[] = { 
		{"One million ints", InsertOneMillionInts}, 
		{"Ten million ints", InsertTenMillionInts},
		{"One million 1K objects", InsertOneMillionKBs},
		//{"Ten million 1K objects", InsertTenMillionKBs},
	};

	vector<int> v;
	steady_clock::time_point begin, end;

	for (test_t& test : tests)
	{
		std::cout << "Performing test '" << test.testName << "'" << std::endl;
		for (int run{ 0 }; run < NUM_ITERATIONS; ++run)
		{
			begin = high_resolution_clock::now();
			test.func();
			end = high_resolution_clock::now();
			durations[run] = duration_cast<nanoseconds>(end - begin);
		}

		for (nanoseconds duration : durations)
			test.duration += duration;
		test.duration /= NUM_ITERATIONS;
	}

	for (test_t& test : tests)
		std::cout << "Test: '" << test.testName << "' took " << 
			test.duration.count() << " nanoseconds on average" << std::endl;

	return 0;
}

//**************************************
void InsertOneMillionInts() noexcept
{
	vector<int> vals;
	for (int i{ 0 }; i < 1000000; ++i)
		vals.push_back(rand());
}

//**************************************
void InsertTenMillionInts() noexcept
{
	vector<int> vals;
	for (int i{ 0 }; i < 10000000; ++i)
		vals.push_back(rand());
}

//**************************************
void InsertOneMillionKBs() noexcept
{
	vector<sizeType<1024>> vals;
	for (int i{ 0 }; i < 1000000; ++i)
		vals.push_back({});
}

//**************************************
void InsertTenMillionKBs() noexcept
{
	vector<sizeType<1024>> vals;
	for (int i{ 0 }; i < 10000000; ++i)
		vals.push_back({});
}