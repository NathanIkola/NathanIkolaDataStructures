//**************************************
// vector_tests.cpp
//
// Holds unit tests for the vector
// class that ensure it is compliant
// with std::vector
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#include <vector>

#include "gtest/gtest.h"
#include "../nids/vector.h"

// define a set of data
const std::initializer_list<int> _valList = { 10, 45, 4, 16, 8, 0, 99, 22, 20, 21 };

TEST(VectorConstructor, DefaultConstructor) 
{
	// create the vectors
	nids::vector<int> nv;
	std::vector<int> sv;
	ASSERT_TRUE(nv.size() == sv.size());
	ASSERT_TRUE(nv.capacity() == sv.capacity());
}

TEST(VectorConstructor, SizedConstructor)
{
	// create the vectors
	nids::vector<int> nv(10);
	std::vector<int> sv(10);
	ASSERT_TRUE(nv.size() == sv.size());
	ASSERT_TRUE(nv.capacity() == sv.capacity());
}

TEST(VectorConstructor, InitializerListConstructor)
{
	// create the vectors
	nids::vector<int> nv = { 1, 3, 5, 7 };
	std::vector<int> sv = { 1, 3, 5, 7 };
	ASSERT_TRUE(nv.size() == sv.size());
	ASSERT_TRUE(nv.capacity() == sv.capacity());
	for (int value{ 0 }; value < nv.size(); ++value)
		ASSERT_TRUE(nv[value] == sv[value]);
}

TEST(VectorAccess, TestOutOfRangeAccessSubscript)
{
	// create our vector
	nids::vector<int> nv;
	EXPECT_DEATH(nv[0], "");
}

TEST(VectorAccess, TestOutOfRangeAccess)
{
	// create our vector
	nids::vector<int> nv;
	EXPECT_DEATH(nv.at(0), "");
}

#ifdef _DEBUG
TEST(VectorAccess, TestOutOfRangeStdSubscript)
{
	std::vector<int> sv;
	EXPECT_ANY_THROW(EXPECT_DEATH(sv[0], ""));
}
#endif

TEST(VectorAccess, TestOutOfRangeStd)
{
	std::vector<int> sv;
	EXPECT_ANY_THROW(sv.at(0));
}

TEST(VectorAccess, TestInRange)
{
	nids::vector<int> nv = _valList;
	int value{ 0 };
	const int* cursor = _valList.begin();
	while (cursor != _valList.end())
	{
		ASSERT_EQ(*cursor, nv[value++]);
		++cursor;
	}
}

TEST(VectorResize, TestResize)
{
	nids::vector<int> nv = _valList;
	std::vector<int> sv = _valList;
	nv.resize(100);
	sv.resize(100);
	ASSERT_EQ(nv.size(), sv.size());

	nv.resize(3);
	sv.resize(3);
	ASSERT_EQ(nv.size(), sv.size());

	nv.resize(0);
	sv.resize(0);
	ASSERT_EQ(nv.size(), sv.size());
}

TEST(VectorReserve, TestReserve)
{
	nids::vector<int> nv = _valList;
	std::vector<int> sv = _valList;

	nv.reserve(100);
	sv.reserve(100);
	ASSERT_EQ(nv.size(), sv.size());
	ASSERT_EQ(nv.capacity(), sv.capacity());

	nv.reserve(10);
	sv.reserve(10);
	ASSERT_EQ(nv.size(), sv.size());
	ASSERT_EQ(nv.capacity(), sv.capacity());

	nv.reserve(0);
	sv.reserve(0);
	ASSERT_EQ(nv.size(), sv.size());
	ASSERT_EQ(nv.capacity(), sv.capacity());
}

TEST(VectorFront, TestFront)
{
	nids::vector<int> nv = _valList;
	std::vector<int> sv = _valList;

	ASSERT_EQ(nv.front(), sv.front());
}

TEST(VectorBack, TestBack)
{
	nids::vector<int> nv = _valList;
	std::vector<int> sv = _valList;

	ASSERT_EQ(nv.back(), sv.back());
}

TEST(VectorSize, TestEmpty)
{
	nids::vector<int> nv;
	ASSERT_TRUE(nv.empty());
}

TEST(VectorSize, TestSizeEmpty)
{
	nids::vector<int> nv;
	ASSERT_EQ(nv.size(), 0);
}

TEST(VectorSize, TestEmptyOnPopulatedVector)
{
	nids::vector<int> nv = _valList;
	ASSERT_FALSE(nv.empty());
}

TEST(VectorSize, TestSizeOnPopulatedVector)
{
	nids::vector<int> nv = _valList;
	ASSERT_EQ(nv.size(), _valList.size());
}