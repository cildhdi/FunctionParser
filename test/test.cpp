/*********************************************************
Developer: MilesYang
Mail: 1961464399@qq.com
FileName: test.cpp
*********************************************************/

#include <FunctionParser.h>
#include <gtest/gtest.h>
#include <climits>
#include <cmath>

//for IntelliSense
#define ValueTest ValueTest
#define DerivativeTest DerivativeTest

const double MINX = -1000;
const double MAXX = 1000;

#define FOR_ALL_X \
	for (double x = MINX; x <= MAXX; x++)
#define FOR_NEGATIVE_X \
	for (double x = MINX; x <= 0; x++)
#define FOR_POSITIVE_X \
	for (double x = 0; x <= MAXX; x++)
#define WITH_MORE_INFO \
	<< "When x equals " << x
#define FP_TEST_BEGIN() \
	try                 \
	{
#define FP_TEST_END()  \
	}                  \
	catch (...)        \
	{                  \
		ADD_FAILURE(); \
	}

cl::FunctionParser parser;

TEST(ConstantFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	FOR_ALL_X
	{
		auto f = parser.parse(std::to_string(x));
		EXPECT_DOUBLE_EQ(f->value(0), x)
		WITH_MORE_INFO;
	}
	for (double x = -1.0; x < 1.0; x += 0.01)
	{
		auto f = parser.parse(std::to_string(x));
		EXPECT_TRUE(std::fabs(f->value(0) - x) < 1e-13)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(ConstantFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	FOR_ALL_X
	{
		auto f = parser.parse(std::to_string(x))->derivative();
		EXPECT_DOUBLE_EQ(f->value(0), 0)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(IndependentVariableTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(IndependentVariableTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(AddFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 + 3");
	EXPECT_DOUBLE_EQ(f->value(0), 4);

	f = parser.parse("x + 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x + 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("x + x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x + x)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(AddFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 + 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = parser.parse("x + 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1)
		WITH_MORE_INFO;
	}

	f = parser.parse("x + x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 2)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MinusFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 - 3");
	EXPECT_DOUBLE_EQ(f->value(0), -2);

	f = parser.parse("x - 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x - 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("x - x + 1");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MinusFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 - 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = parser.parse("x - 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 1)
		WITH_MORE_INFO;
	}
	f = parser.parse("3 - x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), -1)
		WITH_MORE_INFO;
	}
	f = parser.parse("x - x + 1")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 0)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MultiplyFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 * 3");
	EXPECT_DOUBLE_EQ(f->value(0), 3);

	f = parser.parse("x * 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x * 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("x * x");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), x * x)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(MultiplyFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 * 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = parser.parse("x * 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("x * x")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), 2 * x)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(DivideFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 / 3");
	EXPECT_DOUBLE_EQ(f->value(0), static_cast<double>(1) / 3);

	f = parser.parse("x / 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(x) / 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("3 / x");
	FOR_ALL_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(3) / x)
		WITH_MORE_INFO;
	}

	f = parser.parse("x / x");
	FOR_ALL_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(x) / x)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(DivideFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 / 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = parser.parse("x / 3")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(1) / 3)
		WITH_MORE_INFO;
	}

	f = parser.parse("3 / x")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(3%2Fx)%2Fdx
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), -static_cast<double>(3) / (x * x))
		WITH_MORE_INFO;
	}

	f = parser.parse("x / x")->derivative();
	FOR_ALL_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), 0)
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(PowerFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 ^ 3");
	EXPECT_DOUBLE_EQ(f->value(0), std::pow(1, 3));

	f = parser.parse("x ^ 3");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::pow(x, 3))
		WITH_MORE_INFO;
	}

	f = parser.parse("3 ^ x");
	FOR_ALL_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), std::pow(3, x))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(PowerFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("1 ^ 3")->derivative();
	EXPECT_DOUBLE_EQ(f->value(0), 0);

	f = parser.parse("x ^ 3")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(x+%5E+3)%2Fdx
		EXPECT_DOUBLE_EQ(f->value(x), 3 * std::pow(x, 2))
		WITH_MORE_INFO;
	}

	f = parser.parse("3 ^ x")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(3%5Ex)%2Fdx
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), std::pow(3, x) * std::log(3))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(LnFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("ln(x)");
	FOR_POSITIVE_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), std::log(x))
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("ln(ln(x))");
	FOR_POSITIVE_X
	{
		if (x > 1)
			EXPECT_DOUBLE_EQ(ff->value(x), std::log(std::log(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(LnFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("ln(x)")->derivative();
	FOR_POSITIVE_X
	{
		if (x)
			EXPECT_DOUBLE_EQ(f->value(x), static_cast<double>(1) / x)
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("ln(ln(x))")->derivative();
	FOR_POSITIVE_X
	{
		//http://www.wolframalpha.com/input/?i=d(ln(ln(x)))%2Fdx
		if (x > 1)
			EXPECT_DOUBLE_EQ(ff->value(x), static_cast<double>(1) / (x * std::log(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(SinFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("sin(x)");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::sin(x))
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("sin(sin(x))");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(ff->value(x), std::sin(std::sin(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(SinFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("sin(x)")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::cos(x))
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("sin(sin(x))")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(sin(sin(x)))%2Fdx
		EXPECT_DOUBLE_EQ(ff->value(x), std::cos(x) * std::cos(std::sin(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(CosFunctionTest, ValueTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("cos(x)");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), std::cos(x))
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("cos(cos(x))");
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(ff->value(x), std::cos(std::cos(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(CosFunctionTest, DerivativeTest)
{
	FP_TEST_BEGIN();
	auto f = parser.parse("cos(x)")->derivative();
	FOR_ALL_X
	{
		EXPECT_DOUBLE_EQ(f->value(x), -std::sin(x))
		WITH_MORE_INFO;
	}
	auto ff = parser.parse("cos(cos(x))")->derivative();
	FOR_ALL_X
	{
		//http://www.wolframalpha.com/input/?i=d(cos(cos(x)))%2Fdx
		EXPECT_DOUBLE_EQ(ff->value(x), std::sin(x) * std::sin(std::cos(x)))
		WITH_MORE_INFO;
	}
	FP_TEST_END();
}

TEST(PiecewiseFunction, ValueTest)
{
	FP_TEST_BEGIN();
	auto first = parser.parse("-x");
	auto second = parser.parse("x");
	cl::PiecewiseFunctionPtr f = cl::PiecewiseFunction::make_piecewise_function();
	f->add_function({cl::Segment(-10, 0), first});
	f->add_function({cl::Segment(0, 10), second});
	std::cout << f->str();
	std::cout << f->derivative()->str();
	FP_TEST_END();
}

int main(int argc, char **argv)
{
	std::cout << "use " << (use_string_view ? (experimental_string_view ? "std::experimental::string_view" : "std::string_view") : "std::string") << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
