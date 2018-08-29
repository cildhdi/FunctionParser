/*********************************************************
Developer: MilesYang
Mail: 1961464399@qq.com
FileName: test.cpp
*********************************************************/

#include "function_parsing.h"
#include <gtest/gtest.h>
#include <climits>
#include <cmath>
#pragma comment(lib, "gtestd.lib")

//for IntelliSense
#define ValueTest ValueTest
#define DerivativeTest DerivativeTest

const double MINX = -1000;
const double MAXX = 1000;

#define FOR_ALL_X							\
	for (double x = MINX; x <= MAXX; x++)
#define FOR_NEGATIVE_X						\
	for (double x = MINX; x <= 0; x++)
#define FOR_POSITIVE_X						\
	for (double x = 0; x <= MAXX; x++)
#define WITH_MORE_INFO						\
	<< "When x equals " << x
#define FP_TEST_BEGIN()						\
	try										\
	{										
#define FP_TEST_END()						\
	}										\
	catch (...)								\
	{										\
		ADD_FAILURE();						\
	}


TEST(ConstantFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	FOR_ALL_X
	{
		auto f = fp::function_parse(std::to_string(x));
		EXPECT_DOUBLE_EQ(f->value(0), x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(ConstantFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	FOR_ALL_X
	{
		auto f = fp::function_parse(std::to_string(x))->derivative();
		EXPECT_DOUBLE_EQ(f->value(0), 0) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(IndependentVariableTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(IndependentVariableTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(AddFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 + 3");
	EXPECT_DOUBLE_EQ(f->value(0), 4);

	f = fp::function_parse("x + 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x + 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("x + x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x + x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(AddFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 + 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = fp::function_parse("x + 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1) WITH_MORE_INFO;
	}

	f = fp::function_parse("x + x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 2) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MinusFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 - 3");
	EXPECT_DOUBLE_EQ(f->value(0), -2);

	f = fp::function_parse("x - 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x - 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("x - x + 1");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MinusFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 - 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = fp::function_parse("x - 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1) WITH_MORE_INFO;
	}
	f = fp::function_parse("3 - x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), -1) WITH_MORE_INFO;
	}
	f = fp::function_parse("x - x + 1")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 0) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MultiplyFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 * 3");
	EXPECT_DOUBLE_EQ(f->value(0), 3);

	f = fp::function_parse("x * 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x * 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("x * x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x * x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MultiplyFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 * 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = fp::function_parse("x * 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("x * x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 2 * x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(DivideFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 / 3");
	EXPECT_DOUBLE_EQ(f->value(0), static_cast<double>(1) / 3);

	f = fp::function_parse("x / 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(x) / 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("3 / x");
	FOR_ALL_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(3) / x) WITH_MORE_INFO;
	}

	f = fp::function_parse("x / x");
	FOR_ALL_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(x) / x) WITH_MORE_INFO;
	}
	FP_TEST_END();
}


TEST(DivideFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 / 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = fp::function_parse("x / 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(1) / 3) WITH_MORE_INFO;
	}

	f = fp::function_parse("3 / x")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(3%2Fx)%2Fdx
		if (x) EXPECT_DOUBLE_EQ(f->value(x), -static_cast<double>(3) / (x * x)) WITH_MORE_INFO;
	}

	f = fp::function_parse("x / x")->derivative();
	FOR_ALL_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), 0) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(PowerFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 ^ 3");
	EXPECT_DOUBLE_EQ(f->value(0), std::pow(1, 3));

	f = fp::function_parse("x ^ 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::pow(x, 3)) WITH_MORE_INFO;
	}

	f = fp::function_parse("3 ^ x");
	FOR_ALL_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), std::pow(3, x)) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(PowerFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("1 ^ 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = fp::function_parse("x ^ 3")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(x+%5E+3)%2Fdx
		EXPECT_DOUBLE_EQ(f->value(x), 3 * std::pow(x, 2)) WITH_MORE_INFO;
	}

	f = fp::function_parse("3 ^ x")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(3%5Ex)%2Fdx
		if (x) EXPECT_DOUBLE_EQ(f->value(x), std::pow(3, x) * std::log(3)) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(LnFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("ln(x)");
	FOR_POSITIVE_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), std::log(x)) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("ln(ln(x))");
	FOR_POSITIVE_X
	{
		if (x > 1)EXPECT_DOUBLE_EQ(ff->value(x), std::log(std::log(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(LnFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("ln(x)")->derivative();
	FOR_POSITIVE_X
	{
		if (x) EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(1) / x) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("ln(ln(x))")->derivative();
	FOR_POSITIVE_X
	{
		//http://www.wolframalpha.com/input/?i=d(ln(ln(x)))%2Fdx
		if (x > 1)EXPECT_DOUBLE_EQ(ff->value(x), static_cast<double>(1) / (x*std::log(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(SinFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("sin(x)");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::sin(x)) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("sin(sin(x))");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(ff->value(x), std::sin(std::sin(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(SinFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("sin(x)")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::cos(x)) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("sin(sin(x))")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(sin(sin(x)))%2Fdx
		EXPECT_DOUBLE_EQ(ff->value(x), std::cos(x) * std::cos(std::sin(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(CosFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("cos(x)");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::cos(x)) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("cos(cos(x))");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(ff->value(x), std::cos(std::cos(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(CosFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = fp::function_parse("cos(x)")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), -std::sin(x)) WITH_MORE_INFO;
	}
	auto ff = fp::function_parse("cos(cos(x))")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(cos(cos(x)))%2Fdx
		EXPECT_DOUBLE_EQ(ff->value(x), std::sin(x) * std::sin(std::cos(x))) WITH_MORE_INFO;
	}
	FP_TEST_END();
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}
