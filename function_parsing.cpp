#include "function_parsing.h"

#define THROW_PARSE_ERROR throw std::invalid_argument("fail to parse")

namespace fp
{

	std::ostream& operator<<(std::ostream& os, BaseFunctionPtr& func)
	{
		os << func->str();
		return os;
	}

	//class defination
	//base function
	BaseFunctionPtr BaseFunction::derivative(unsigned int n)
	{
		if (n == 0)return nullptr;
		BaseFunctionPtr f = this->derivative();
		while (--n)
		{
			f = f->derivative();
		}
		return f;
	}

	//independent_variable
	IndependentVariable::IndependentVariable(std::string iv) :_iv(iv), BaseFunction(T_INDEPENDENT_VARIABLE)
	{
	}

	std::string IndependentVariable::str()
	{
		return _iv;
	}

	double IndependentVariable::value(double x)
	{
		return x;
	}

	BaseFunctionPtr IndependentVariable::derivative()
	{
		return std::make_shared<ConstantFunction>(1);
	}

	//constant function
	ConstantFunction::ConstantFunction(double c) :_c(c), BaseFunction(T_CONSTANT_FUNCTION)
	{
	}

	std::string ConstantFunction::str()
	{
		auto str = std::to_string(_c);
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

	double ConstantFunction::value(double x)
	{
		return _c;
	}

	BaseFunctionPtr ConstantFunction::derivative()
	{
		return std::make_shared<ConstantFunction>(0);
	}

	//add function
	AddFunction::AddFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) :_lhs(lhs), _rhs(rhs), BaseFunction(T_ADD_FUNCTION)
	{
	}

	std::string AddFunction::str()
	{
		return "(" + _lhs->str() + "+" + _rhs->str() + ")";
	}

	double AddFunction::value(double x)
	{
		return _lhs->value(x) + _rhs->value(x);
	}

	BaseFunctionPtr AddFunction::derivative()
	{
		return std::make_shared<AddFunction>(_lhs->derivative(), _rhs->derivative());
	}

	//minus function
	MinusFunction::MinusFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) :_lhs(lhs), _rhs(rhs), BaseFunction(T_MINUS_FUNCTION)
	{
	}

	std::string MinusFunction::str()
	{
		return "(" + _lhs->str() + "-" + _rhs->str() + ")";
	}

	double MinusFunction::value(double x)
	{
		return _lhs->value(x) - _rhs->value(x);
	}

	BaseFunctionPtr MinusFunction::derivative()
	{
		return std::make_shared<MinusFunction>(_lhs->derivative(), _rhs->derivative());
	}

	//multiply function
	MultiplyFunction::MultiplyFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) :_lhs(lhs), _rhs(rhs), BaseFunction(T_MULTIPLY_FUNCTION)
	{
	}

	std::string MultiplyFunction::str()
	{
		return "(" + _lhs->str() + "*" + _rhs->str() + ")";
	}

	double MultiplyFunction::value(double x)
	{
		return _lhs->value(x) * _rhs->value(x);
	}

	BaseFunctionPtr MultiplyFunction::derivative()
	{
		return std::make_shared<AddFunction>(std::make_shared<MultiplyFunction>(_lhs->derivative(), _rhs), std::make_shared<MultiplyFunction>(_lhs, _rhs->derivative()));
	}

	//divide function
	DivideFunction::DivideFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) :_lhs(lhs), _rhs(rhs), BaseFunction(T_DIVIDE_FUNCTION)
	{
	}

	std::string DivideFunction::str()
	{
		return "(" + _lhs->str() + "/" + _rhs->str() + ")";
	}

	double DivideFunction::value(double x)
	{
		return  _lhs->value(x) / _rhs->value(x);
	}

	BaseFunctionPtr DivideFunction::derivative()
	{
		return std::make_shared<DivideFunction>(std::make_shared<MinusFunction>(std::make_shared<MultiplyFunction>(_lhs->derivative(), _rhs), std::make_shared<MultiplyFunction>(_lhs, _rhs->derivative())), std::make_shared<MultiplyFunction>(_rhs, _rhs));
	}

	//power function
	PowerFunction::PowerFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) :_lhs(lhs), _rhs(rhs), BaseFunction(T_POWER_FUNCTION)
	{
	}

	std::string PowerFunction::str()
	{
		return "(" + _lhs->str() + "^" + _rhs->str() + ")";
	}

	double PowerFunction::value(double x)
	{
		return pow(_lhs->value(x), _rhs->value(x));
	}

	BaseFunctionPtr PowerFunction::derivative()
	{
		if (_rhs->_type == T_CONSTANT_FUNCTION)
		{
			return std::make_shared<MultiplyFunction>(std::make_shared<MultiplyFunction>
				(std::make_shared<ConstantFunction>(_rhs->value(0)),
					std::make_shared<PowerFunction>(_lhs,
						std::make_shared<ConstantFunction>(_rhs->value(0) - 1))), _lhs->derivative());
		}
		else
		{
			return std::make_shared<MultiplyFunction>
				(std::make_shared<PowerFunction>(_lhs, _rhs),
					std::make_shared<AddFunction>(std::make_shared<MultiplyFunction>
					(_rhs->derivative(), std::make_shared<LnFunction>(_lhs)),
						std::make_shared<MultiplyFunction>(_rhs,
							std::make_shared<LnFunction>(_lhs)->derivative())));
		}
	}

	//ln function
	LnFunction::LnFunction(BaseFunctionPtr arg) :_arg(arg), BaseFunction(T_LN_FUNCTION)
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


	//sin function
	SinFunction::SinFunction(BaseFunctionPtr arg) :_arg(arg), BaseFunction(T_SIN_FUNCTION)
	{
	}

	std::string SinFunction::str()
	{
		return "(sin" + _arg->str() + ")";
	}

	double SinFunction::value(double x)
	{
		return std::sin(_arg->value(x));
	}

	BaseFunctionPtr SinFunction::derivative()
	{
		return std::make_shared<MultiplyFunction>(std::make_shared<CosFunction>(_arg), _arg->derivative());
	}

	//cos function
	CosFunction::CosFunction(BaseFunctionPtr arg) :_arg(arg), BaseFunction(T_COS_FUNCTION)
	{
	}

	std::string CosFunction::str()
	{
		return "(cos" + _arg->str() + ")";
	}

	double CosFunction::value(double x)
	{
		return std::cos(_arg->value(x));
	}

	BaseFunctionPtr CosFunction::derivative()
	{
		return std::make_shared<MultiplyFunction>(std::make_shared<ConstantFunction>(-1), std::make_shared<MultiplyFunction>(std::make_shared<SinFunction>(_arg), _arg->derivative()));
	}

	//tan function

	TanFunction::TanFunction(BaseFunctionPtr arg) :_arg(arg), BaseFunction(T_TAN_FUNCTION)
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
		return std::make_shared<MultiplyFunction>(std::make_shared<DivideFunction>
			(std::make_shared<ConstantFunction>(1),
				std::make_shared<PowerFunction>(_arg, std::make_shared<ConstantFunction>(2))), _arg->derivative());
	}

	//picewise funciton
	PiecewiseFunction::PiecewiseFunction(std::initializer_list<Function> functions) : BaseFunction(T_PICEWISE_FUNCTION)
	{
		_functions.assign(functions);
		std::sort(_functions.begin(), _functions.end(), [](const Function& lhs, const Function& rhs)
		{
			return lhs.second > rhs.second;
		});
	}

	void PiecewiseFunction::add_function(Function function)
	{
		_functions.push_back(function);
		std::sort(_functions.begin(), _functions.end(), [](const Function& lhs, const Function& rhs)
		{
			return lhs.second > rhs.second;
		});
	}

	void PiecewiseFunction::remove_function(double value)
	{
		_functions.erase(std::remove_if(_functions.begin(), _functions.end(), [value](const Function& function)
		{
			return function.first.contain(value);
		}), _functions.end());
	}

	std::string PiecewiseFunction::str()
	{
		if (_functions.empty()) return "";
		std::string res = "\n";
		for (auto& function : _functions)
		{
			res += (function.first.str() + "  x¡Ê" + function.second->str() + '\n');
		}
		return res;
	}

	double PiecewiseFunction::value(double x)
	{
		for (auto& function : _functions)
		{
			if (function.first.contain(x))
				return function.second->value(x);
		}
		throw std::out_of_range("x not in range");
		return 0;
	}

	BaseFunctionPtr PiecewiseFunction::derivative()
	{
		std::shared_ptr<PiecewiseFunction> res = std::make_shared<PiecewiseFunction>();
		for (auto& function : _functions)
			res->add_function({ function.first, function.second->derivative() });
		return res;
	}
	//class defination end

	int get_matching_bracket(const std::string& expr, unsigned int pos)
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

	bool include_operators(const std::string& str)
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

	bool include_brackets(const std::string& str)
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

	bool is_number(const std::string& str)
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


	BaseFunctionPtr function_parse(std::string func_str)
	{
		func_str.erase(std::remove_if(func_str.begin(), func_str.end(),
			[](char c) { return c == ' '; }), func_str.end());
		while ((!func_str.empty()) && func_str.at(0) == '('&&get_matching_bracket(func_str, 0) == (func_str.size() - 1))
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
			unsigned int fb = get_matching_bracket(func_str, func_str.size() - 1);
			if (fb == -1)
			{
				THROW_PARSE_ERROR;
			}
			auto func_name = func_str.substr(0, fb);
			if (!(include_brackets(func_name) || include_operators(func_name)))
			{
				if (func_name == "ln")
				{
					return std::make_shared<LnFunction>(function_parse(func_str.substr(fb, func_str.size() - fb)));
				}
				else if (func_name == "sin")
				{
					return std::make_shared<SinFunction>(function_parse(func_str.substr(fb, func_str.size() - fb)));
				}
				else if (func_name == "cos")
				{
					return std::make_shared<CosFunction>(function_parse(func_str.substr(fb, func_str.size() - fb)));
				}
				else if (func_name == "tan")
				{
					return std::make_shared<TanFunction>(function_parse(func_str.substr(fb, func_str.size() - fb)));
				}
			}
		}

		if (!include_operators(func_str))
		{
			if (is_number(func_str))
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
				auto next_bracket = get_matching_bracket(func_str, i);
				if (next_bracket == -1)
				{
					THROW_PARSE_ERROR;
				}
				i = next_bracket + 1;
				continue;
			}
			if (is_add_or_minus(func_str.at(i)))
			{
				operators.push_back(i);
			}
			i++;
		}
		if (!operators.empty())
		{
			auto ped = function_parse(func_str.substr(0, operators[0]));
			for (i = 0; i < operators.size(); i++)
			{
				if (ped == nullptr)
				{
					THROW_PARSE_ERROR;
				}
				switch (func_str.at(operators.at(i)))
				{
				case '+':
					if (i != operators.size() - 1)
					{
						ped = std::make_shared<AddFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
					}
					else
					{
						ped = std::make_shared<AddFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
					}
					break;
				case '-':
					if (i != operators.size() - 1)
					{
						ped = std::make_shared<MinusFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
					}
					else
					{
						ped = std::make_shared<MinusFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
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
					auto next_bracket = get_matching_bracket(func_str, i);
					if (next_bracket == -1)
					{
						THROW_PARSE_ERROR;
					}
					i = next_bracket + 1;
					continue;
				}
				if (is_multiply_or_divide(func_str.at(i)))
				{
					operators.push_back(i);
				}
				i++;
			}
			if (!operators.empty())
			{
				auto ped = function_parse(func_str.substr(0, operators[0]));
				for (i = 0; i < operators.size(); i++)
				{
					if (ped == nullptr)
					{
						THROW_PARSE_ERROR;
					}
					switch (func_str.at(operators.at(i)))
					{
					case '*':
						if (i != operators.size() - 1)
						{
							ped = std::make_shared<MultiplyFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
						}
						else
						{
							ped = std::make_shared<MultiplyFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
						}
						break;
					case '/':
						if (i != operators.size() - 1)
						{
							ped = std::make_shared<DivideFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
						}
						else
						{
							ped = std::make_shared<DivideFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
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
						auto next_bracket = get_matching_bracket(func_str, i);
						if (next_bracket == -1)
						{
							THROW_PARSE_ERROR;
						}
						i = next_bracket + 1;
						continue;
					}
					if (is_power(func_str.at(i)))
					{
						operators.push_back(i);
					}
					i++;
				}
				if (!operators.empty())
				{
					auto ped = function_parse(func_str.substr(0, operators[0]));
					for (i = 0; i < operators.size(); i++)
					{
						if (ped == nullptr)
						{
							THROW_PARSE_ERROR;
						}
						if (i != operators.size() - 1)
						{
							ped = std::make_shared<PowerFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, operators.at(i + 1) - operators.at(i) - 1)));
						}
						else
						{
							ped = std::make_shared<PowerFunction>(ped, function_parse(func_str.substr(operators.at(i) + 1, func_str.size() - operators.at(i) - 1)));
						}
					}
					return ped;
				}
			}
		}
		THROW_PARSE_ERROR;
		return nullptr;
	}



}//namespace fp
