#include "function_parsing.h"

namespace fp
{
	//class defination
	//independent_variable
	independent_variable::independent_variable(std::string iv) :m_iv(iv)
	{
	}

	std::string independent_variable::str()
	{
		return m_iv;
	}

	double independent_variable::value(double x)
	{
		return x;
	}

	base_function_ptr independent_variable::derivative()
	{
		return std::make_shared<constant_function>(1);
	}
	//constant_function
	constant_function::constant_function(double ac) :c(ac)
	{
	}

	std::string constant_function::str()
	{
		auto str = std::to_string(c);
		while ((!str.empty()) && str.at(str.size() - 1) == '0')
		{
			str.pop_back();
		}
		if (!str.empty() && str.at(str.size() - 1) == '.')
		{
			str.pop_back();
		}
		return str;
	}

	double constant_function::value(double x)
	{
		return c;
	}

	base_function_ptr constant_function::derivative()
	{
		return std::make_shared<constant_function>(0);
	}

	//add_function
	add_function::add_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string add_function::str()
	{
		return "(" + m_lhs->str() + "+" + m_rhs->str() + ")";
	}

	double add_function::value(double x)
	{
		try
		{
			return m_lhs->value(x) + m_rhs->value(x);
		}
		catch (...)
		{
			throw;
		}
	}

	base_function_ptr add_function::derivative()
	{
		return std::make_shared<add_function>(m_lhs->derivative(), m_rhs->derivative());
	}

	//minus_function
	minus_function::minus_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string minus_function::str()
	{
		return "(" + m_lhs->str() + "-" + m_rhs->str() + ")";
	}

	double minus_function::value(double x)
	{
		try
		{
			return m_lhs->value(x) - m_rhs->value(x);
		}
		catch (...)
		{
			throw;
		}
	}

	base_function_ptr minus_function::derivative()
	{
		return std::make_shared<minus_function>(m_lhs->derivative(), m_rhs->derivative());
	}

	//multiply_function
	multiply_function::multiply_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string multiply_function::str()
	{
		return "(" + m_lhs->str() + "*" + m_rhs->str() + ")";
	}

	double multiply_function::value(double x)
	{
		try
		{
			return m_lhs->value(x) * m_rhs->value(x);
		}
		catch (...)
		{
			throw;
		}
	}

	base_function_ptr multiply_function::derivative()
	{
		return std::make_shared<add_function>(std::make_shared<multiply_function>(m_lhs->derivative(), m_rhs), std::make_shared<multiply_function>(m_lhs, m_rhs->derivative()));
	}

	//divide_function
	divide_function::divide_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string divide_function::str()
	{
		return "(" + m_lhs->str() + "/" + m_rhs->str() + ")";
	}

	double divide_function::value(double x)
	{
		try
		{
			return  m_lhs->value(x) / m_rhs->value(x);
		}
		catch (...)
		{
			throw;
		}
	}

	base_function_ptr divide_function::derivative()
	{

		return std::make_shared<divide_function>(std::make_shared<minus_function>(std::make_shared<multiply_function>(m_lhs->derivative(), m_rhs), std::make_shared<multiply_function>(m_lhs, m_rhs->derivative())), std::make_shared<multiply_function>(m_rhs, m_rhs));
	}

	//power_function
	power_function::power_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string power_function::str()
	{
		return "(" + m_lhs->str() + "^" + m_rhs->str() + ")";
	}

	double power_function::value(double x)
	{
		try
		{
			return pow(m_lhs->value(x), m_rhs->value(x));
		}
		catch (...)
		{
			throw;
		}

	}

	base_function_ptr power_function::derivative()
	{
		return std::make_shared<multiply_function>(std::make_shared<power_function>(m_lhs, m_rhs), std::make_shared<add_function>(std::make_shared<multiply_function>(m_rhs->derivative(), std::make_shared<ln_function>(m_lhs)), std::make_shared<multiply_function>(m_rhs, std::make_shared<ln_function>(m_lhs)->derivative())));
	}

	//ln_function
	ln_function::ln_function(base_function_ptr arg) :m_arg(arg)
	{
	}

	std::string ln_function::str()
	{
		return "(ln" + m_arg->str() + ")";
	}

	double ln_function::value(double x)
	{
		try
		{
			return std::log(m_arg->value(x));
		}
		catch (...)
		{
			throw;
		}
	}

	base_function_ptr ln_function::derivative()
	{
		return std::make_shared<multiply_function>(std::make_shared<divide_function>(std::make_shared<constant_function>(1), m_arg), m_arg->derivative());
	}

	//class defination end

	int get_matching_bracket(std::string expr, unsigned int pos)
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
			for (unsigned int i = pos; pos >= 0; i--)
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

	bool include_operators(std::string str)
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

	bool is_number(std::string str)
	{
		for (auto c : str)
		{
			if (!((c <= '9'&&c >= '0') || c == '.'))
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


	base_function_ptr function_parse(std::string func_str)
	{
		try
		{
			func_str.erase(std::remove_if(func_str.begin(), func_str.end(),
				[](char c) {return c == ' '; }), func_str.end());
			while ((!func_str.empty()) && func_str.at(0) == '('&&get_matching_bracket(func_str, 0) == (func_str.size() - 1))
			{
				func_str.erase(func_str.begin());
				func_str.pop_back();
			}
			if (func_str.empty())
			{
				throw std::invalid_argument("fail to parse");
			}



			if (!include_operators(func_str))
			{
				if (is_number(func_str))
				{
					return std::make_shared<constant_function>(std::atof(func_str.c_str()));
				}
				else
				{
					return std::make_shared<independent_variable>(func_str);
				}
			}


			unsigned int i = 0;
			std::vector<unsigned int> add_minus;
			while (i < func_str.size())
			{
				if (func_str.at(i) == '(')
				{
					auto next_br = get_matching_bracket(func_str, i);
					if (next_br == -1)
					{
						throw std::invalid_argument("no matching bracket");
					}
					i = next_br + 1;
					continue;
				}
				if (is_add_or_minus(func_str.at(i)))
				{
					add_minus.push_back(i);
				}
				i++;
			}
			if (!add_minus.empty())
			{
				auto pPre = function_parse(func_str.substr(0, add_minus[0]));
				for (i = 0; i < add_minus.size(); i++)
				{
					if (pPre == nullptr)
					{
						throw std::invalid_argument("fail to parse");
					}
					switch (func_str.at(add_minus.at(i)))
					{
					case '+':
						if (i != add_minus.size() - 1)
						{
							pPre = std::make_shared<add_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, add_minus.at(i + 1) - add_minus.at(i) - 1)));
						}
						else
						{
							pPre = std::make_shared<add_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, func_str.size() - add_minus.at(i) - 1)));
						}
						break;
					case '-':
						if (i != add_minus.size() - 1)
						{
							pPre = std::make_shared<minus_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, add_minus.at(i + 1) - add_minus.at(i) - 1)));
						}
						else
						{
							pPre = std::make_shared<minus_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, func_str.size() - add_minus.at(i) - 1)));
						}
						break;
					}
				}
				return pPre;
			}
			else
			{
				std::vector<unsigned int> multiply_divide;
				i = 0;
				while (i < func_str.size())
				{
					if (func_str.at(i) == '(')
					{
						auto next_br = get_matching_bracket(func_str, i);
						if (next_br == -1)
						{
							throw std::invalid_argument("no matching bracket");
						}
						i = next_br + 1;
						continue;
					}
					if (is_multiply_or_divide(func_str.at(i)))
					{
						multiply_divide.push_back(i);
					}
					i++;
				}
				if (!multiply_divide.empty())
				{
					auto pPre = function_parse(func_str.substr(0, multiply_divide[0]));
					for (i = 0; i < multiply_divide.size(); i++)
					{
						if (pPre == nullptr)
						{
							throw std::invalid_argument("fail to parse");
						}
						switch (func_str.at(multiply_divide.at(i)))
						{
						case '*':
							if (i != multiply_divide.size() - 1)
							{
								pPre = std::make_shared<multiply_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, multiply_divide.at(i + 1) - multiply_divide.at(i) - 1)));
							}
							else
							{
								pPre = std::make_shared<multiply_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, func_str.size() - multiply_divide.at(i) - 1)));
							}
							break;
						case '/':
							if (i != multiply_divide.size() - 1)
							{
								pPre = std::make_shared<divide_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, multiply_divide.at(i + 1) - multiply_divide.at(i) - 1)));
							}
							else
							{
								pPre = std::make_shared<divide_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, func_str.size() - multiply_divide.at(i) - 1)));
							}
							break;
						}
					}
					return pPre;
				}
				else
				{
					std::vector<unsigned int> power_operator;
					i = 0;
					while (i < func_str.size())
					{
						if (func_str.at(i) == '(')
						{
							auto next_br = get_matching_bracket(func_str, i);
							if (next_br == -1)
							{
								throw std::invalid_argument("no matching bracket");
							}
							i = next_br + 1;
							continue;
						}
						if (is_power(func_str.at(i)))
						{
							power_operator.push_back(i);
						}
						i++;
					}
					if (!power_operator.empty())
					{
						auto pPre = function_parse(func_str.substr(0, power_operator[0]));
						for (i = 0; i < power_operator.size(); i++)
						{
							if (pPre == nullptr)
							{
								throw std::invalid_argument("fail to parse");
							}
							if (i != power_operator.size() - 1)
							{
								pPre = std::make_shared<power_function>(pPre, function_parse(func_str.substr(power_operator.at(i) + 1, power_operator.at(i + 1) - power_operator.at(i) - 1)));
							}
							else
							{
								pPre = std::make_shared<power_function>(pPre, function_parse(func_str.substr(power_operator.at(i) + 1, func_str.size() - power_operator.at(i) - 1)));
							}
						}
						return pPre;
					}
				}
			}
		}
		catch (...)
		{
			throw;
		}
		throw std::invalid_argument("fail to parse");
		return nullptr;
	}


}//namespace fp
