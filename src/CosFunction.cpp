#include <CosFunction.h>
#include <MultiplyFunction.h>
#include <ConstantFunction.h>
#include <SinFunction.h>

namespace cl
{

CosFunction::CosFunction(BaseFunctionPtr arg) : _arg(arg), BaseFunction(T_COS_FUNCTION)
{
}

std::string CosFunction::str() const
{
    return "(cos" + _arg->str() + ")";
}

double CosFunction::value(double x) const
{
    return std::cos(_arg->value(x));
}

BaseFunctionPtr CosFunction::derivative() const
{
    return std::make_shared<MultiplyFunction>(std::make_shared<ConstantFunction>(-1), std::make_shared<MultiplyFunction>(std::make_shared<SinFunction>(_arg), _arg->derivative()));
}

} // namespace cl
