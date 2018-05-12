#pragma once
#ifndef _FP_H_
#define _FP_H_

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
namespace fp
{
	class base_function;
	using base_function_ptr = std::shared_ptr<base_function>;
	base_function_ptr function_parse(std::string func_str);
	class base_function
	{
	public:
		virtual std::string str() = 0;
		virtual double value(double x) = 0;
	};

	class independent_variable :public base_function
	{
	private:
		std::string m_iv;
	public:
		independent_variable(std::string);
		std::string str();
		double value(double x);
	};

	class constant_function :public base_function
	{
	private:
		double c;
	public:
		constant_function(double ac);
		std::string str();
		double value(double x);
	};

	class add_function :public base_function
	{
	private:
		base_function_ptr m_lhs;
		base_function_ptr m_rhs;
	public:
		add_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str();
		double value(double x);
	};

	class minus_function :public base_function
	{
	private:
		base_function_ptr m_lhs;
		base_function_ptr m_rhs;
	public:
		minus_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str();
		double value(double x);
	};

	class multiply_function :public base_function
	{
	private:
		base_function_ptr m_lhs;
		base_function_ptr m_rhs;
	public:
		multiply_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str();
		double value(double x);
	};

	class divide_function :public base_function
	{
	private:
		base_function_ptr m_lhs;
		base_function_ptr m_rhs;
	public:
		divide_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str();
		double value(double x);
	};

	class power_function :public base_function
	{
	private:
		base_function_ptr m_lhs;
		base_function_ptr m_rhs;
	public:
		power_function(base_function_ptr lhs, base_function_ptr rhs);
		std::string str();
		double value(double x);
	};
}

#endif