#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(SinFunction);

class SinFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _arg;

  public:
    SinFunction(BaseFunctionPtr arg);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
