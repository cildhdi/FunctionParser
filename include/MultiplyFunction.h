#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(MultiplyFunction);

class MultiplyFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _lhs;
    BaseFunctionPtr _rhs;

  public:
    MultiplyFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
