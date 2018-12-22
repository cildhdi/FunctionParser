#pragma once

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

#include <FunctionType.h>

#define DEC_SHARED_PTR_TYPE(type)       \
    class type; /*Forward declaration*/ \
    using type##Ptr = std::shared_ptr<type>;

namespace cl
{

DEC_SHARED_PTR_TYPE(BaseFunction);

class BaseFunction
{
  public:
    virtual std::string str() const = 0;
    virtual double value(double x) const = 0;
    virtual BaseFunctionPtr derivative() const = 0;
    virtual BaseFunctionPtr derivative(unsigned int n) const;
    const FunctionType _type;
    BaseFunction(FunctionType type) : _type(type) {}
};
} // namespace cl
