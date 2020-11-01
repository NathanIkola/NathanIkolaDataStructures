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

TEST(IteratorCreate, CreateIteratorFromCopy)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	auto iter2{ iter1 };
}

//**************************************
// Assignment tests
//**************************************
TEST(IteratorAssign, IteratorAssign)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	auto iter2 = v.end();
	iter1 = iter2;
}

TEST(IteratorAssign, IteratorMove)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter1 = v.begin();
	iter1 = v.end();
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

#ifdef _DEBUG
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
#endif

TEST(IteratorDereference, DereferenceClassByPointerOperator)
{
	struct A { inline int works() const noexcept { return 1; } };

	nids::vector<A> v;
	v.push_back(A{});
	auto iter = v.begin();
	EXPECT_TRUE(iter->works() == 1);
}

TEST(IteratorDereference, ConstDereferenceClassByPointerOperator)
{
	struct A { inline int works() const noexcept { return 1; } };

	nids::vector<A> v;
	v.push_back(A{});
	const auto iter = v.begin();
	EXPECT_TRUE(iter->works() == 1);
}

TEST(IteratorDereference, IteratorOffset)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter = v.begin();
	++iter;
	EXPECT_TRUE(iter[1] == 1500);
	EXPECT_TRUE(iter[-1] == 500);
}

TEST(IteratorDereference, ConstIteratorOffset)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	const auto iter = ++v.begin();
	EXPECT_TRUE(iter[1] == 1500);
	EXPECT_TRUE(iter[-1] == 500);
}

//**************************************
// Increment tests
//**************************************
#ifdef _DEBUG
TEST(IteratorIncrement, IncrementIteratorForEmptyVector)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(++iter, "");
}

TEST(IteratorIncrement, IncrementIteratorPastEnd)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	++iter;
	EXPECT_DEATH(++iter, "");
}
#endif

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

TEST(IteratorIncrement, IncrementIteratorPost)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	auto iter2 = iter;
	EXPECT_TRUE(iter2 == iter++);
	EXPECT_TRUE(iter == v.end());
}

TEST(IteratorIncrement, NextIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	auto iter1 = v.begin();
	auto iter2 = iter1++;
	EXPECT_TRUE(iter1 == iter2.next());
}

TEST(IteratorIncrement, PlusIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter = v.begin();
	iter = iter + 1;
	EXPECT_TRUE(*iter == 1000);
	iter = 1 + iter;
	EXPECT_TRUE(*iter = 1500);
}

TEST(IteratorIncrement, PlusEqualsIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter = v.begin();
	iter += 2;
	EXPECT_TRUE(*iter == 1500);
}

//**************************************
// Decrement tests
//**************************************
#ifdef _DEBUG
TEST(IteratorDecrement, DecrementIteratorForEmptyVector)
{
	nids::vector<int> v;
	auto iter = v.begin();
	EXPECT_DEATH(--iter, "");
}

TEST(IteratorDecrement, DecrementIteratorPastBegin)
{
	nids::vector<int> v;
	v.push_back(500);
	auto iter = v.begin();
	EXPECT_DEATH(--iter, "");
}
#endif

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

TEST(IteratorDecrement, DecrementIteratorPost)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	auto iter = v.begin();
	++iter;
	auto iter2 = iter;
	EXPECT_TRUE(iter2 == iter--);
	EXPECT_TRUE(iter == v.begin());
}

TEST(IteratorDecrement, PreviousIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	auto iter = v.begin();
	auto iter2 = iter;
	++iter;
	EXPECT_TRUE(iter2 == iter.previous());
}

TEST(IteratorDecrement, MinusIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter = v.begin();
	++iter;
	iter = iter - 1;
	EXPECT_TRUE(*iter == 500);
}

TEST(IteratorDecrement, MinusEqualsIterator)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter = v.begin();
	iter += 2;
	iter -= 1;
	EXPECT_TRUE(*iter == 1000);
}

TEST(IteratorDecrement, MinusTwoIterators)
{
	nids::vector<int> v;
	v.push_back(500);
	v.push_back(1000);
	v.push_back(1500);
	auto iter1 = v.begin();
	auto iter2 = iter1;
	iter1 += 2;
	EXPECT_TRUE(iter1 - iter2 == 2);
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

TEST(IteratorEquality, BeginLessThanEnd)
{
	nids::vector<int> v;
	v.push_back(500);
	EXPECT_TRUE(v.begin() < v.end());
	EXPECT_FALSE(v.end() < v.begin());
	EXPECT_FALSE(v.begin() < v.begin());
	EXPECT_TRUE(v.end() > v.begin());
	EXPECT_FALSE(v.begin() > v.end());
	EXPECT_FALSE(v.begin() > v.begin());
}

TEST(IteratorEquality, EqualityOfEqualIterators)
{
	nids::vector<int> v;
	v.push_back(500);
	EXPECT_TRUE(v.begin() <= v.begin());
	EXPECT_TRUE(v.begin() <= v.end());
	EXPECT_TRUE(v.end() >= v.end());
	EXPECT_TRUE(v.end() >= v.begin());
}