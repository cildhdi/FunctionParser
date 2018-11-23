#include <TanFunction.h>
#include <MultiplyFunction.h>
#include <ConstantFunction.h>
#include <DivideFunction.h>
#include <PowerFunction.h>

namespace cl
{
    
TanFunction::TanFunction(BaseFunctionPtr arg) : _arg(arg), BaseFunction(T_TAN_FUNCTION)
{
}

std::string TanFunction::str()
{
    return "(tan" + _arg->str() + ")";
}

double TanFunction::value(double x)
{
    return tan(_arg->value(x));
}

BaseFunctionPtr TanFunction::derivative()
{
    return std::make_shared<MultiplyFunction>(std::make_shared<DivideFunction>(std::make_shared<ConstantFunction>(1),
                                                                               std::make_shared<PowerFunction>(_arg, std::make_shared<ConstantFunction>(2))),
                                              _arg->derivative());
}

} // namespace cl
