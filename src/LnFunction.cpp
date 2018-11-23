#include <LnFunction.h>
#include <MultiplyFunction.h>
#include <DivideFunction.h>
#include <ConstantFunction.h>

namespace cl
{

LnFunction::LnFunction(BaseFunctionPtr arg) : _arg(arg), BaseFunction(T_LN_FUNCTION)
{
}

std::string LnFunction::str()
{
    return "(ln" + _arg->str() + ")";
}

double LnFunction::value(double x)
{
    return std::log(_arg->value(x));
}

BaseFunctionPtr LnFunction::derivative()
{
    return std::make_shared<MultiplyFunction>(std::make_shared<DivideFunction>(std::make_shared<ConstantFunction>(1), _arg), _arg->derivative());
}

} // namespace cl
