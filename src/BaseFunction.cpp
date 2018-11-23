#include <BaseFunction.h>

namespace cl
{

BaseFunctionPtr BaseFunction::derivative(unsigned int n)
{
    if (n == 0)
        return nullptr;
    BaseFunctionPtr f = this->derivative();
    while (--n)
    {
        f = f->derivative();
    }
    return f;
}

} // namespace cl
