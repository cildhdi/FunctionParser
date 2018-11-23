#pragma once

#include <BaseFunction.h>

namespace cl
{
    
DEC_SHARED_PTR_TYPE(CosFunction);

class CosFunction : public BaseFunction
{
  private:
    BaseFunctionPtr _arg;

  public:
    CosFunction(BaseFunctionPtr arg);
    std::string str() override;
    double value(double x) override;
    BaseFunctionPtr derivative() override;
};
} // namespace cl
