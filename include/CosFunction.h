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
    std::string str() const override;
    double value(double x) const override;
    BaseFunctionPtr derivative() const override;
};
} // namespace cl
