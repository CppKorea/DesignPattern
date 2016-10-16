#pragma once

#include "Context.h"

#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class IExpression
{
public:
	virtual T Interpret( const Context<T>& context ) const = 0;
	
	virtual ~IExpression() = default;

	IExpression( const IExpression& ) = default;
	IExpression& operator=( const IExpression& ) = default;
	IExpression( IExpression&& ) = default;
	IExpression& operator=( IExpression&& ) = default;

protected:
	IExpression( ) = default;
};

/*
Terminal Expression
*/
template <typename T>
class CNumberExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& ) const override
	{ 
		return m_operand; 
	}

	explicit CNumberExpr( const T value ) noexcept : m_operand( value ) {}

private:
	T m_operand;
};

template <typename T>
class CVariableExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& context ) const override
	{
		return context.GetVariable( m_name );
	}

	explicit CVariableExpr( const std::string value ) noexcept : m_name( value ) {}

private:
	std::string m_name;
};

/*
Nonterminal Expression
*/
template <typename T>
class CPlusExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& context ) const override
	{ 
		assert( m_lhs != nullptr && m_rhs != nullptr );
		return m_lhs->Interpret( context ) + m_rhs->Interpret( context );
	}
	
	CPlusExpr( IExpression<T>* lhs, IExpression<T>* rhs ) noexcept : m_lhs( lhs ), m_rhs( rhs ) {}

private:
	IExpression<T>* m_lhs;
	IExpression<T>* m_rhs;
};

template <typename T>
class CMinusExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& context ) const override
	{
		assert( m_lhs != nullptr && m_rhs != nullptr );
		return m_lhs->Interpret( context ) - m_rhs->Interpret( context );
	}

	CMinusExpr( IExpression<T>* lhs, IExpression<T>* rhs ) noexcept : m_lhs( lhs ), m_rhs( rhs ) {}

private:
	IExpression<T>* m_lhs;
	IExpression<T>* m_rhs;
};

template <typename T>
class CMultiplyExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& context ) const override
	{
		assert( m_lhs != nullptr && m_rhs != nullptr );
		return m_lhs->Interpret( context ) * m_rhs->Interpret( context );
	}

	CMultiplyExpr( IExpression<T>* lhs, IExpression<T>* rhs ) noexcept : m_lhs( lhs ), m_rhs( rhs ) {}

private:
	IExpression<T>* m_lhs;
	IExpression<T>* m_rhs;
};

template <typename T>
class CDivideExpr : public IExpression<T>
{
public:
	virtual T Interpret( const Context<T>& context ) const override
	{
		assert( m_lhs != nullptr && m_rhs != nullptr );
		return m_lhs->Interpret( context ) / m_rhs->Interpret( context );
	}

	CDivideExpr( IExpression<T>* lhs, IExpression<T>* rhs ) noexcept : m_lhs( lhs ), m_rhs( rhs ) {}

private:
	IExpression<T>* m_lhs;
	IExpression<T>* m_rhs;
};