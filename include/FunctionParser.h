#pragma once

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
    BaseFunctionPtr parse(std::string func_str);
};

} // namespace cl
