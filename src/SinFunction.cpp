#include <SinFunction.h>
#include <MultiplyFunction.h>
#include <CosFunction.h>

namespace cl
{

SinFunction::SinFunction(BaseFunctionPtr arg) : _arg(arg), BaseFunction(T_SIN_FUNCTION)
{
}

std::string SinFunction::str() const
{
    return "(sin" + _arg->str() + ")";
}

double SinFunction::value(double x) const
{
    return std::sin(_arg->value(x));
}

BaseFunctionPtr SinFunction::derivative() const
{
    return std::make_shared<MultiplyFunction>(std::make_shared<CosFunction>(_arg), _arg->derivative());
}

} // namespace cl
