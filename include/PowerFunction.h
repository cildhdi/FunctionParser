#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(PowerFunction);

class PowerFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _lhs;
    BaseFunctionPtr _rhs;

  public:
    PowerFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};

} // namespace cl
