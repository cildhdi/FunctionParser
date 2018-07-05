#ifndef _FP_H_
#define _FP_H_

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>

namespace fp
{
	class base_function;
	using base_function_ptr = std::shared_ptr<base_function>;
	base_function_ptr function_parse(std::string func_str);
	std::ostream& operator<<(std::ostream& os, base_function_ptr& func);


	enum FunctionType
	{
		T_BASE_FUNCTION,
		T_INDEPENDENT_VARIABLE,
		T_CONSTANT_FUNCTION,
		T_ADD_FUNCTION,
		T_MINUS_FUNCTION,
		T_MULTIPLY_FUNCTION,
		T_DIVIDE_FUNCTION,
		T_POWER_FUNCTION,
		T_LN_FUNCTION,
		T_SIN_FUNCTION,
		T_COS_FUNCTION,
		T_TAN_FUNCTION
	};

	class base_function
	{
	public:
		virtual std::string str() = 0;
		virtual double value(double x) = 0;
		virtual base_function_ptr derivative() = 0;
		virtual base_function_ptr derivative(unsigned int n);
		const FunctionType _type;
		base_function(FunctionType type) :_type(type) {}
	};

	class independent_variable :public base_function
	{
	private:
		std::string _iv;
	public:
		independent_variable(std::string iv);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class constant_function :public base_function
	{
	private:
		double _c;
	public:
		constant_function(double c);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class add_function :public base_function
	{
	private:
		base_function_ptr _lhs;
		base_function_ptr _rhs;
	public:
		add_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class minus_function :public base_function
	{
	private:
		base_function_ptr _lhs;
		base_function_ptr _rhs;
	public:
		minus_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class multiply_function :public base_function
	{
	private:
		base_function_ptr _lhs;
		base_function_ptr _rhs;
	public:
		multiply_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class divide_function :public base_function
	{
	private:
		base_function_ptr _lhs;
		base_function_ptr _rhs;
	public:
		divide_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class power_function :public base_function
	{
	private:
		base_function_ptr _lhs;
		base_function_ptr _rhs;
	public:
		power_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class ln_function :public base_function
	{
	private:
		base_function_ptr _arg;
	public:
		ln_function(base_function_ptr arg);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class sin_function :public base_function
	{
	private:
		base_function_ptr _arg;
	public:
		sin_function(base_function_ptr arg);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class cos_function :public base_function
	{
	private:
		base_function_ptr _arg;
	public:
		cos_function(base_function_ptr arg);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

	class tan_function :public base_function
	{
	private:
		base_function_ptr _arg;
	public:
		tan_function(base_function_ptr arg);
		std::string str() override;
		double value(double x) override;
		base_function_ptr derivative() override;
	};

}//namespace fp

#endif