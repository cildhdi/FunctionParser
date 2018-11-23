#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(DivideFunction);

class DivideFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _lhs;
    BaseFunctionPtr _rhs;

  public:
    DivideFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
