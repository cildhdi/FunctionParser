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
    std::string str() const override;
    double value(double x) const override;
    BaseFunctionPtr derivative() const override;
};
} // namespace cl
