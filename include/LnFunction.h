#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(LnFunction);

class LnFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _arg;

  public:
    LnFunction(BaseFunctionPtr arg);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
