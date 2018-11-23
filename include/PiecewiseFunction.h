#pragma once

#include <BaseFunction.h>
#include <Segment.h>

namespace cl
{

DEC_SHARED_PTR_TYPE(PiecewiseFunction);

using Function = std::pair<Segment, BaseFunctionPtr>;

class PiecewiseFunction : public BaseFunction
{
  private:
    std::vector<Function> _functions;

  public:
    PiecewiseFunction(std::initializer_list<Function> functions = {});
    static std::shared_ptr<PiecewiseFunction> make_piecewise_function();
    void add_function(Function function);
    void remove_function(double value);

    virtual std::string str() override;
    virtual double value(double x) override;
    virtual BaseFunctionPtr derivative() override;
};

} // namespace cl
