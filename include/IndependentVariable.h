#pragma once

#include <BaseFunction.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(IndependentVariable);

class IndependentVariable : public BaseFunction
{
  private:
    std::string _iv;

  public:
    IndependentVariable(const std::string &iv);
    std::string str() const override;
    double value(double x) const override;
    BaseFunctionPtr derivative() const override;
};
} // namespace cl
