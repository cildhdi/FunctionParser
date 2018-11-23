#include <DivideFunction.h>
#include <MinusFunction.h>
#include <CosFunction.h>
#include <SinFunction.h>
#include <MultiplyFunction.h>

namespace cl
{

DivideFunction::DivideFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_DIVIDE_FUNCTION)
{
}

std::string DivideFunction::str()
{
    return "(" + _lhs->str() + "/" + _rhs->str() + ")";
}

double DivideFunction::value(double x)
{
    return _lhs->value(x) / _rhs->value(x);
}

BaseFunctionPtr DivideFunction::derivative()
{
    return std::make_shared<DivideFunction>(std::make_shared<MinusFunction>(std::make_shared<MultiplyFunction>(_lhs->derivative(), _rhs), std::make_shared<MultiplyFunction>(_lhs, _rhs->derivative())), std::make_shared<MultiplyFunction>(_rhs, _rhs));
}

} // namespace cl
