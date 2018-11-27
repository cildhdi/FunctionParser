#include <FunctionParser.h>

namespace cl
{

namespace detail
{
int get_matching_bracket(std::string_view expr, unsigned int pos)
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

bool include_operators(std::string_view str)
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

bool include_brackets(std::string_view str)
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

bool is_number(std::string_view str)
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

BaseFunctionPtr FunctionParser::parse(std::string_view func_str)
{
    std::string copy;
    //check if this str has spaces
    if (func_str.find(' ') != func_str.npos)
    {
        copy = std::string(func_str.data(), func_str.size());
        copy.erase(std::remove_if(copy.begin(), copy.end(),
                                  [](char c) { return c == ' '; }),
                   copy.end());
        copy.shrink_to_fit();
        func_str = std::string_view(&copy[0], copy.size());
    }

    while ((!func_str.empty()) && func_str.at(0) == '(' && detail::get_matching_bracket(func_str, 0) == (func_str.size() - 1))
    {
        func_str.remove_prefix(1);
        func_str.remove_suffix(1);
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
            char *str_end = const_cast<char *>(func_str.data() + func_str.size());
            return std::make_shared<ConstantFunction>(std::strtod(func_str.data(), &str_end));
        }
        else
        {
            return std::make_shared<IndependentVariable>(std::string(func_str.data(), func_str.size()));
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