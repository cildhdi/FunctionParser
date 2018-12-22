#include <LnFunction.h>
#include <MultiplyFunction.h>
#include <DivideFunction.h>
#include <ConstantFunction.h>

namespace cl
{

LnFunction::LnFunction(BaseFunctionPtr arg) : _arg(arg), BaseFunction(T_LN_FUNCTION)
{
}

std::string LnFunction::str() const
{
    return "(ln" + _arg->str() + ")";
}

double LnFunction::value(double x) const
{
    return std::log(_arg->value(x));
}

BaseFunctionPtr LnFunction::derivative() const
{
    return std::make_shared<MultiplyFunction>(std::make_shared<DivideFunction>(std::make_shared<ConstantFunction>(1), _arg), _arg->derivative());
}

} // namespace cl
