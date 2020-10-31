//**************************************
// vector_iterator_tests.cpp
//
// Holds the unit tests for the
// vector_iterator class
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#include "pch.h"

//**************************************
// Creation tests
//**************************************
TEST(IteratorCreate, CreateIteratorForEmptyVector)
{
	nids::vector<int> v;
	auto begin = v.begin();
	auto end = v.end();
}

TEST(IteratorCreate, CreateIteratorForPopulatedVector)
{
	nids::vector<int> v;
	v.push_back(500);
	auto begin = v.begin();
	auto end = v.end();
}

//**************************************
// Dereference tests
//**************************************
TEST(IteratorDereference, IteratorPointsToFirstIndex)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	auto begin = v.begin();
	EXPECT_EQ(500, *begin);
}

TEST(IteratorDereference, ConstIteratorPointsToFirstIndex)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	auto begin = v.begin();
	const auto iter = begin;
	EXPECT_EQ(500, *iter);
}

//**************************************
// Increment tests
//**************************************
TEST(IteratorIncrement, IncrementIteratorForEmptyVector)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(++iter, "");
}

TEST(IteratorIncrement, IncrementIteratorShowsCorrectValue)
{
	nids::vector<int> v;
	for (int index{ 0 }; index < 100; ++index)
		v.push_back(index);
	auto iter = v.begin();
	for (int index{ 0 }; index < 100; ++index, ++iter)
	{
		EXPECT_EQ(index, *iter);
	}
}

//**************************************
// Decrement tests
//**************************************
TEST(IteratorDecrement, DecrementIteratorForEmptyVector)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(--iter, "");
}

TEST(IteratorDecrement, DecrementIteratorShowsCorrectValue)
{
	nids::vector<int> v;
	for (int index{ 0 }; index < 100; ++index)
		v.push_back(index);
	auto iter = v.begin();

	for (int index{ 99 }; index >= 0; --index, ++iter)
	{
		EXPECT_EQ(99 - index, *iter);
	}
}