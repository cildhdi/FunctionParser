#include <PiecewiseFunction.h>

namespace cl
{

PiecewiseFunction::PiecewiseFunction(std::initializer_list<Function> functions) : BaseFunction(T_PICEWISE_FUNCTION)
{
    _functions.assign(functions);
    std::sort(_functions.begin(), _functions.end(), [](const Function &lhs, const Function &rhs) {
        return lhs.second > rhs.second;
    });
}

PiecewiseFunctionPtr PiecewiseFunction::make_piecewise_function()
{
    return std::make_shared<PiecewiseFunction>();
}

void PiecewiseFunction::add_function(Function function)
{
    _functions.push_back(function);
    std::sort(_functions.begin(), _functions.end(), [](const Function &lhs, const Function &rhs) {
        return lhs.second < rhs.second;
    });
}

void PiecewiseFunction::remove_function(double value)
{
    _functions.erase(std::remove_if(_functions.begin(), _functions.end(), [value](const Function &function) {
                         return function.first.contain(value);
                     }),
                     _functions.end());
}

std::string PiecewiseFunction::str() const
{
    if (_functions.empty())
        return "";
    std::string res = "\n";
    for (auto &function : _functions)
    {
        res += (function.second->str() + " ,for x in " + function.first.str() + '\n');
    }
    return res;
}

double PiecewiseFunction::value(double x) const
{
    for (auto &function : _functions)
    {
        if (function.first.contain(x))
            return function.second->value(x);
    }
    throw std::out_of_range("x not in range");
    return 0;
}

BaseFunctionPtr PiecewiseFunction::derivative() const
{
    std::shared_ptr<PiecewiseFunction> res = std::make_shared<PiecewiseFunction>();
    for (auto &function : _functions)
        res->add_function({function.first, function.second->derivative()});
    return res;
}

} // namespace cl
