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
	const auto iter = v.begin();
	EXPECT_EQ(500, *iter);
}

TEST(IteratorDereference, DereferenceInvalidIterator)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(*iter, "");
}

TEST(IteratorDereference, DereferenceInvalidConstIterator)
{
	nids::vector<int> v;
	const auto iter = v.begin();
	EXPECT_DEATH(*iter, "");
}

TEST(IteratorDereference, DereferenceEndIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.end();
	EXPECT_DEATH(*iter, "");
}

TEST(IteratorDereference, DereferenceEndIteratorEmpty)
{
	nids::vector<int> v;
	auto iter = v.end();
	EXPECT_DEATH(*iter, "");
}

TEST(IteratorDereference, DereferenceBeginIteratorEmpty)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(*iter, "");
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

TEST(IteratorIncrement, IncrementIteratorPastEnd)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	++iter;
	EXPECT_DEATH(++iter, "");
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

TEST(IteratorDecrement, DecrementIteratorPastBegin)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	EXPECT_DEATH(--iter, "");
}

//**************************************
// Equality checks
//**************************************
TEST(IteratorEquality, BeginIteratorsAreEqual)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	v.push_back(1000);
	auto iter2 = v.begin();
	EXPECT_TRUE(iter1 == iter2);
}

TEST(IteratorEquality, IteratorsAreNotEqual)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	v.push_back(1000);
	auto iter2 = v.begin();
	++iter2;
	EXPECT_FALSE(iter1 == iter2);
}

TEST(IteratorEquality, IteratorsAreNotEqualDueToCursor)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	v.push_back(1000);
	auto iter2 = v.begin();
	++iter2;
	EXPECT_FALSE(iter1 == iter2);
}

TEST(IteratorEquality, IteratorsAreNotEqualOperatorNot)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	v.push_back(1000);
	auto iter2 = v.begin();
	++iter2;
	EXPECT_TRUE(iter1 != iter2);
}

TEST(IteratorEquality, EmptyBeginEqualsEnd)
{
	nids::vector<int> v;
	EXPECT_TRUE(v.begin() == v.end());
}

TEST(IteratorEquality, IteratorsHaveDifferentVectors)
{
	nids::vector<int> v;
	v.push_back(500);
	nids::vector<int> w;
	v.push_back(1000);
	EXPECT_FALSE(v.begin() == w.begin());
}