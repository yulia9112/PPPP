#include "pch.h"
#include "CppUnitTest.h"
#include "../PPPP_Laba2/Header.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(metod_test_five)
		{
			string ret;
			Metod(0, 0, 0, 0, 0, 0, &ret);
			Assert::AreEqual(ret.c_str(), "5"); //+
		}

		TEST_METHOD(metod_test_null)
		{
			string ret;
			Metod(2, 0, 1, 0, 1, 1, &ret);
			Assert::AreEqual(ret.c_str(), "0"); //+
		}

		TEST_METHOD(test_no_solution_2)
		{
			string ret;
			Metod(2, 4, 1, 2, 2, 2, &ret);
			Assert::AreEqual(ret.c_str(), "0"); //+
		}

		TEST_METHOD(test_single_solution)
		{
			string ret;
			Metod(1, 0, 0, 1, 1, 1, &ret);
			Assert::AreEqual(ret.c_str(), "2 1 1"); //-
		}

		TEST_METHOD(test_inf_solutions_ykxn)
		{
			string ret;
			Metod(-2, 1, 0, 0, 0, 0, &ret);
			Assert::AreEqual(ret.c_str(), "1 2 0"); //
		}

		TEST_METHOD(test_inf_solutions_ykxn_2)
		{
			string ret;
			Metod(0, 0, 2, 1, 0, 0, &ret);
			Assert::AreEqual(ret.c_str(), "1 -2 0");
		}

		TEST_METHOD(test_inf_solutions_ykxn_3)
		{
			string ret;
			Metod(1, 2, 0, 0, 0, 0, &ret);
			Assert::AreEqual(ret.c_str(), "1 -0.5 0");
		}

		TEST_METHOD(test_inf_solutions_ykxn_4)
		{
			string ret;
			Metod(2, 4, 1, 2, 1, 0.5, &ret);
			Assert::AreEqual(ret.c_str(), "1 -0.5 0.25");
		}

		TEST_METHOD(test_inf_solutions_for_y)
		{
			string ret;
			Metod(1, 0, 0, 0, 1, 0, &ret);
			Assert::AreEqual(ret.c_str(), "3 1");
		}

		TEST_METHOD(test_inf_solutions_for_x)
		{
			string ret;
			Metod(0, 1, 0, 0, 1, 0, &ret);
			Assert::AreEqual(ret.c_str(), "4 1");
		}
	};
}
