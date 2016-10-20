#pragma once

#include "Expression.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

template <typename T>
using ExpressionStack = std::stack<IExpression<T>*>;

template <typename T>
using OwnerPtr = T*;

template <typename T>
class IHandler
{
public:
	virtual IExpression<T>* CreateExpression( const std::string& pattern, ExpressionStack<T>& exprs ) const = 0;

	bool HandleRequest( const std::string& pattern, ExpressionStack<T>& exprs/*out*/ )
	{
		IExpression<T>* expr = CreateExpression( pattern, exprs );
		if ( expr )
		{
			m_ownExpr.push_back( expr );
			exprs.push( expr );
			return true;
		}

		if ( m_helpHandler )
		{
			return m_helpHandler->HandleRequest( pattern, exprs );
		}

		return false;
	}

	virtual ~IHandler( )
	{
		for ( auto expr : m_ownExpr )
		{
			delete expr;
		}
	}

protected:
	IHandler( std::unique_ptr<IHandler>&& handler = nullptr ) : m_helpHandler( std::move( handler ) )
	{

	}

	IHandler( const IHandler& ) = delete;
	IHandler& operator=( const IHandler& ) = delete;
	IHandler( IHandler&& ) = delete;
	IHandler& operator=( IHandler&& ) = delete;

	LinkedList<OwnerPtr<IExpression<T>>> m_ownExpr;

	std::unique_ptr<IHandler> m_helpHandler;
};

template <typename T>
class CNumberHandler : public IHandler<T>
{
public:
	virtual IExpression<T>* CreateExpression( const std::string& pattern, ExpressionStack<T>& ) const
	{
		T value{};
		if ( CheckAndGetArithmetic( pattern, value ) )
		{	
			return new CNumberExpr<T>( value );
		}

		return nullptr;
	}

	CNumberHandler( std::unique_ptr<IHandler>&& handler = nullptr ) : IHandler<T>( std::move( handler ) )
	{
	}

private:
	bool CheckAndGetArithmetic( const std::string& pattern, T& retValue/*out*/ ) const
	{
		if ( !std::is_arithmetic<T>::value )
		{
			return false;
		}

		std::stringstream stream( pattern );
		stream >> retValue;

		return stream.eof( ) && !stream.fail( );
	}
};

template <typename T>
class CVariableHandler : public IHandler<T>
{
public:
	virtual IExpression<T>* CreateExpression( const std::string& pattern, ExpressionStack<T>& ) const
	{
		if ( IsVariable( pattern ) )
		{
			return new CVariableExpr<T>( pattern );
		}

		return nullptr;
	}

	CVariableHandler( std::unique_ptr<IHandler>&& handler = nullptr ) : IHandler<T>( std::move( handler ) )
	{
	}

private:
	bool IsVariable( const std::string& pattern ) const
	{
		return pattern.size( ) > 0 && pattern.substr( 0, 1 ) == "$";
	}
};

template <typename T>
class COperatorHandler : public IHandler<T>
{
public:
	virtual IExpression<T>* CreateExpression( const std::string& pattern, ExpressionStack<T>& exprs ) const
	{
		if ( exprs.size( ) < 2 )
		{
			return nullptr;
		}

		if ( std::string( "+-*/" ).find( pattern ) == std::string::npos )
		{
			return nullptr;
		}

		IExpression<T>* rhs = exprs.top( );
		exprs.pop( );
		IExpression<T>* lhs = exprs.top( );
		exprs.pop( );

		IExpression<T>* expr = nullptr;
		if ( pattern == "+" )
		{
			expr = new CPlusExpr<T>( lhs, rhs );
		}
		else if ( pattern == "-" )
		{
			expr = new CMinusExpr<T>( lhs, rhs );
		}
		else if ( pattern == "*" )
		{
			expr = new CMultiplyExpr<T>( lhs, rhs );
		}
		else if ( pattern == "/" )
		{
			expr = new CDivideExpr<T>( lhs, rhs );
		}
		else
		{
			assert( false && "Invalid Pattern" );
		}
		
		return expr;
	}

	COperatorHandler( std::unique_ptr<IHandler>&& handler = nullptr ) : IHandler<T>( std::move( handler ) )
	{
	}
};