#include "pch.h"
#include "CppUnitTest.h"
#include "../RBTree/rbtree.h"
#include "../RBTree/iter.h"
#include <random>
#include <vector>
#include <algorithm>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBTreeUnitTest
{
	TEST_CLASS(InsertTest)
	{
	public:

		TEST_METHOD(Test1)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(i);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test2)
		{
			rbt::RBTree<int> tree;
			for (int i = 11; i > 0; i--)
				tree.insert(i);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test3)
		{
			rbt::RBTree<int> tree;
			for (int i = 0; i < 10; i++)
				tree.insert(2);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test4)
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { 5, 8, 13, 45, 9, 2, 3, 2, 10, 30, 22, 0 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test5)
		{
			rbt::RBTree<int> tree;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(1, 100);
			for (int i = 0; i < 100; i++)
				tree.insert(distr(gen));
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test6)
		{
			rbt::RBTree<int> tree;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(1, 1000);
			for (int i = 0; i < 1000; i++)
				tree.insert(distr(gen));
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test7)
		{
			rbt::RBTree<int> tree;
			tree.insert(INT_MIN);
			tree.insert(INT_MAX);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test8)
		{
			rbt::RBTree<int> tree;
			tree.insert(INT_MIN);
			tree.insert(INT_MAX);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(1, 100);
			for (int i = 0; i < 10; i++)
				tree.insert(distr(gen));
			Assert::IsTrue(tree.isRBT());
		}
	};
	TEST_CLASS(EraseTest)
	{
	public:
		TEST_METHOD(Test1)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(i);
			tree.erase(4);				//root
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test2)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(i);
			tree.erase(7);				//black with no children
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test3)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(2);
			tree.erase(9);				//black with one child
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test4)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(2);
			tree.erase(2);				//black with two children
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test5)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(2);
			tree.erase(10);				//red with no children
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test6)
		{
			rbt::RBTree<int> tree;
			for (int i = 1; i < 11; i++)
				tree.insert(2);
			tree.erase(8);				//red with two childs
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test7)		//random deleting
		{
			for (int j = 0; j < 10; j++)
			{
				rbt::RBTree<int> tree;
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distr(1, 100);
				std::vector<int> v;
				for (int i = 0; i < 30; i++)
					v.push_back(distr(gen));
				for (int i = 0; i < v.size(); i++)
					tree.insert(v[i]);
				for (int i = 1; i < 30; i += 3)
					tree.erase(v[i]);
				Assert::IsTrue(tree.isRBT());
			}
		}
		TEST_METHOD(Test8)	//full deleting
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { 5, 8, 13, 45, 9, 2, 3, 2, 10, 30, 22, 0 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (int i = 0; i < v.size(); i++)
			{
				tree.erase(v[i]);
				Assert::IsTrue(tree.isRBT());
			}
		}
		TEST_METHOD(Test9)	//delete not existed node
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { 5, 8, 13, 45, 9, 2, 3, 2, 10, 30, 22, 0 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			tree.erase(1);
			Assert::IsTrue(tree.isRBT());
			tree.erase(55);
			Assert::IsTrue(tree.isRBT());
		}
		TEST_METHOD(Test10)		//more random deleting
		{
			for (int j = 0; j < 50; j++)
			{
				rbt::RBTree<int> tree;
				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distr(1, 100);
				std::vector<int> v;
				for (int i = 0; i < 50; i++)
					v.push_back(distr(gen));
				for (int i = 0; i < v.size(); i++)
					tree.insert(v[i]);
				for (int i = 1; i < 50; i += 3)
					tree.erase(v[i]);
				Assert::IsTrue(tree.isRBT());
			}
		}
	};
	TEST_CLASS(IterTest)
	{
	public:
		TEST_METHOD(Test1)	//++()
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			std::vector<int> check;
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (auto it = tree.begin(), ite = tree.end(); it != ite; ++it)
				check.push_back(*it);
			Assert::IsTrue(v == check);
		}
		TEST_METHOD(Test2)	//++(int)
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			std::vector<int> check;
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (auto it = tree.begin(), ite = tree.end(); it != ite; it++)
				check.push_back(*it);
			Assert::IsTrue(v == check);
		}
		TEST_METHOD(Test3)	//--()
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			std::vector<int> check;
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (auto it = tree.back(), ite = tree.end(); it != ite; --it)
				check.push_back(*it);
			std::reverse(check.begin(), check.end());
			Assert::IsTrue(v == check);
		}
		TEST_METHOD(Test4)	//--(int)
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			std::vector<int> check;
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (auto it = tree.back(), ite = tree.end(); it != ite; it--)
				check.push_back(*it);
			std::reverse(check.begin(), check.end());
			Assert::IsTrue(v == check);
		}
		TEST_METHOD(Test5)	//range-based for
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			std::vector<int> check;
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			for (auto&& value : tree)
				check.push_back(value);
			Assert::IsTrue(v == check);
		}
		TEST_METHOD(Test6)	//std::find
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			auto it = std::find(tree.begin(), tree.end(), 3);
			Assert::IsTrue(it == tree.end());
		}
		TEST_METHOD(Test7)	//std::find
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			auto it = std::find(tree.begin(), tree.end(), 10);
			Assert::IsTrue(*it == 10);
		}
		TEST_METHOD(Test8)	//my find
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			auto it = tree.find(10);
			Assert::IsTrue(*it == 10);
		}
		TEST_METHOD(Test9)	//my find
		{
			rbt::RBTree<int> tree;
			std::vector<int> v = { -7, 0, 2, 4, 6, 7, 9, 10, 44, 45, 46, 100 };
			for (int i = 0; i < v.size(); i++)
				tree.insert(v[i]);
			auto it = tree.find(3);
			Assert::IsTrue(it == tree.end());
		}
	};
}
