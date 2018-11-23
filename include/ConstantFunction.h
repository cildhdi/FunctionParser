#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(ConstantFunction);

class ConstantFunction : public BaseFunction
{
  private:
    double _c;

  public:
    ConstantFunction(double c);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
