#pragma once

#if __has_include(<string_view>)
#include <string_view>
#define use_string_view 1
#define experimental_string_view 0
namespace cl
{
using expression_string = std::string_view;
}

#elif __has_include(<experimental/string_view>)
#include <experimental/string_view>
#define use_string_view 1
#define experimental_string_view 1
namespace cl
{
using expression_string = std::experimental::string_view;
}
#else
#define use_string_view 0
namespace cl
{
using expression_string = std::string;
}
#endif

#include <IndependentVariable.h>
#include <ConstantFunction.h>
#include <AddFunction.h>
#include <MinusFunction.h>
#include <MultiplyFunction.h>
#include <DivideFunction.h>
#include <PowerFunction.h>
#include <LnFunction.h>
#include <SinFunction.h>
#include <CosFunction.h>
#include <TanFunction.h>
#include <PiecewiseFunction.h>
#include <Segment.h>

namespace cl
{

class FunctionParser
{
public:
  BaseFunctionPtr parse(expression_string func_str);
};

} // namespace cl
