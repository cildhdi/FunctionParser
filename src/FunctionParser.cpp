#include <FunctionParser.h>

namespace cl
{

namespace detail
{
int get_matching_bracket(const std::string &expr, unsigned int pos)
{
    unsigned int tag = 0;
    if (expr.at(pos) == '(')
    {
        for (unsigned int i = pos; i < expr.size(); i++)
        {
            if (expr.at(i) == '(')
                tag++;
            else if (expr.at(i) == ')')
                tag--;
            if (tag == 0)
                return i;
        }
    }
    else if (expr.at(pos) == ')')
    {
        for (int i = pos; i >= 0; i--)
        {
            if (expr.at(i) == ')')
                tag++;
            else if (expr.at(i) == '(')
                tag--;
            if (tag == 0)
                return i;
        }
    }
    return -1;
}

bool is_add_or_minus(char c)
{
    return c == '+' || c == '-';
}

bool include_operators(const std::string &str)
{
    for (auto c : str)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            return true;
        }
    }
    return false;
}

bool include_brackets(const std::string &str)
{
    for (auto c : str)
    {
        if (c == '(' || c == ')')
        {
            return true;
        }
    }
    return false;
}

bool is_number(const std::string &str)
{
    for (auto c : str)
    {
        if (!((c <= '9' && c >= '0') || c == '.'))
        {
            return false;
        }
    }
    return true;
}

bool is_multiply_or_divide(char c)
{
    return c == '*' || c == '/';
}

bool is_power(char c)
{
    return c == '^';
}

} // namespace detail

BaseFunctionPtr FunctionParser::parse(std::string func_str)
{
    func_str.erase(std::remove_if(func_str.begin(), func_str.end(),
                                  [](char c) { return c == ' '; }),
                   func_str.end());
    while ((!func_str.empty()) && func_str.at(0) == '(' && detail::get_matching_bracket(func_str, 0) == (func_str.size() - 1))
    {
        func_str.erase(func_str.begin());
        func_str.pop_back();
    }
    if (func_str.empty())
    {
        return std::make_shared<ConstantFunction>(0);
    }

    if (func_str.at(func_str.size() - 1) == ')')
    {
        unsigned int fb = detail::get_matching_bracket(func_str, func_str.size() - 1);
        if (fb == -1)
        {
            throw std::invalid_argument("fail to parse");
        }
        auto func_name = func_str.substr(0, fb);
        if (!(detail::include_brackets(func_name) || detail::include_operators(func_name)))
        {
            if (func_name == "ln")
            {
                return std::make_shared<LnFunction>(parse(func_str.substr(fb, func_str.size() - fb)));
            }
            else if (func_name == "sin")
            {
                return std::make_shared<SinFunction>(parse(func_str.substr(fb, func_str.size() - fb)));
            }
            else if (func_name == "cos")
            {
                return std::make_shared<CosFunction>(parse(func_str.substr(fb, func_str.size() - fb)));
            }
            else if (func_name == "tan")
            {
                return std::make_shared<TanFunction>(parse(func_str.substr(fb, func_str.size() - fb)));
            }
        }
    }

    if (!detail::include_operators(func_str))
    {
        if (detail::is_number(func_str))
        {
            return std::make_shared<ConstantFunction>(std::atof(func_str.c_str()));
        }
        else
        {
            return std::make_shared<IndependentVariable>(func_str);
        }
    }

    unsigned int i = 0;
    std::vector<unsigned int> operators;
    while (i < func_str.size())
    {
        if (func_str.at(i) == '(')
        {
            auto next_bracket = detail::get_matching_bracket(func_str, i);
            if (next_bracket == -1)
            {
                throw std::invalid_argument("fail to parse");
            }
            i = next_bracket + 1;
            continue;
        }
        if (detail::is_add_or_minus(func_str.at(i)))
        {
            operators.push_back(i);
        }
        i++;
    }
    if (!operators.empty())
    {
        auto ped = parse(func_str.substr(0, operators[0]));
        for (i = 0; i < operators.size(); i++)
        {
            if (ped == nullptr)
            {
                throw std::invalid_argument("fail to parse");
            }
            switch (func_str.at(operators.at(i)))
            {
            case '+':
                if (i != operators.size() - 1)
                {
                    ped = std::make_shared<AddFunction>(ped, parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
                }
                else
                {
                    ped = std::make_shared<AddFunction>(ped, parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
                }
                break;
            case '-':
                if (i != operators.size() - 1)
                {
                    ped = std::make_shared<MinusFunction>(ped, parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
                }
                else
                {
                    ped = std::make_shared<MinusFunction>(ped, parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
                }
                break;
            }
        }
        return ped;
    }
    else
    {
        operators.clear();
        i = 0;
        while (i < func_str.size())
        {
            if (func_str.at(i) == '(')
            {
                auto next_bracket = detail::get_matching_bracket(func_str, i);
                if (next_bracket == -1)
                {
                    throw std::invalid_argument("fail to parse");
                }
                i = next_bracket + 1;
                continue;
            }
            if (detail::is_multiply_or_divide(func_str.at(i)))
            {
                operators.push_back(i);
            }
            i++;
        }
        if (!operators.empty())
        {
            auto ped = parse(func_str.substr(0, operators[0]));
            for (i = 0; i < operators.size(); i++)
            {
                if (ped == nullptr)
                {
                    throw std::invalid_argument("fail to parse");
                }
                switch (func_str.at(operators.at(i)))
                {
                case '*':
                    if (i != operators.size() - 1)
                    {
                        ped = std::make_shared<MultiplyFunction>(ped, parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
                    }
                    else
                    {
                        ped = std::make_shared<MultiplyFunction>(ped, parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
                    }
                    break;
                case '/':
                    if (i != operators.size() - 1)
                    {
                        ped = std::make_shared<DivideFunction>(ped, parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
                    }
                    else
                    {
                        ped = std::make_shared<DivideFunction>(ped, parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
                    }
                    break;
                }
            }
            return ped;
        }
        else
        {
            operators.clear();
            i = 0;
            while (i < func_str.size())
            {
                if (func_str.at(i) == '(')
                {
                    auto next_bracket = detail::get_matching_bracket(func_str, i);
                    if (next_bracket == -1)
                    {
                        throw std::invalid_argument("fail to parse");
                    }
                    i = next_bracket + 1;
                    continue;
                }
                if (detail::is_power(func_str.at(i)))
                {
                    operators.push_back(i);
                }
                i++;
            }
            if (!operators.empty())
            {
                auto ped = parse(func_str.substr(0, operators[0]));
                for (i = 0; i < operators.size(); i++)
                {
                    if (ped == nullptr)
                    {
                        throw std::invalid_argument("fail to parse");
                    }
                    if (i != operators.size() - 1)
                    {
                        ped = std::make_shared<PowerFunction>(ped, parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
                    }
                    else
                    {
                        ped = std::make_shared<PowerFunction>(ped, parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
                    }
                }
                return ped;
            }
        }
    }
    throw std::invalid_argument("fail to parse");
    return nullptr;
}

} // namespace cl