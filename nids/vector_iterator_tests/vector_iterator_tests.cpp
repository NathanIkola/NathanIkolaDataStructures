#include "CppUnitTest.h"

#include "../nids/vector.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace vectoriteratortests
{
	TEST_CLASS(vectoriteratortests)
	{
	public:
		
		TEST_METHOD(TestCreateIteratorForEmptyVector)
		{
			nids::vector<int> v;
			auto begin = v.begin();
			auto end = v.end();
		}

		TEST_METHOD(TestCreateIteratorForPopulatedVector)
		{
			nids::vector<int> v;
			v.push_back(500);
			auto begin = v.begin();
			auto end = v.end();
		}

		TEST_METHOD(TestIncrementEmptyVector)
		{
			nids::vector<int> v;
			auto iter = v.begin();
			++iter;
		}

		TEST_METHOD(TestDecrementEmptyVector)
		{
			nids::vector<int> v;
			auto iter = v.begin();
			--iter;
		}
	};
}