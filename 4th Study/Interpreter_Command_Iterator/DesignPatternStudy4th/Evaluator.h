#pragma once

#include "Aggregate.h"
#include "Context.h"
#include "Handler.h"

#include <map>
#include <memory>
#include <vector>

int GetPrecedence( char symbol )
{
	switch ( symbol )
	{
	case '(':
		return 0;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	default:
		assert( false && "Invaild Symbol" );
		break;
	}

	return -1;
}

bool IsGreaterEqualPrecedence( char lhs, char rhs )
{
	return GetPrecedence( lhs ) <= GetPrecedence( rhs );
}

std::string RemoveSpace( const std::string& source )
{
	std::string result;
	result.reserve( source.size( ) );

	for ( auto c : source )
	{
		if ( c != ' ' )
		{
			result += c;
		}
	}

	return result;
}

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class CEvaluator
{
public:
	CEvaluator( ) : m_exprHandler( nullptr )
	{
		RegisterDefaultHandler( );
	}

	void RegisterDefaultHandler( )
	{
		std::unique_ptr<IHandler<T>> operatorHandler = std::make_unique<COperatorHandler<T>>( );
		std::unique_ptr<IHandler<T>> variableHandler = std::make_unique<CVariableHandler<T>>( std::move( operatorHandler ) );
		m_exprHandler = std::make_unique<CNumberHandler<T>>( std::move( variableHandler ) );
	}

	T Evaluate( const std::string& infix, const Context<T>& ctx )
	{
		return PostfixEvaluate( ConvertInfixToPostfix( RemoveSpace( infix ) ), ctx );
	}

private:
	std::vector<std::string> ConvertInfixToPostfix( const std::string& infix )
	{
		std::vector<std::string> result;
		std::stack<char> operatorStack;
		std::string value;
		value.reserve( 256 );

		for ( auto c : infix )
		{
			switch ( c )
			{
			case ')':
				HandleCloseBracket( operatorStack, value, result );
				break;
			case '(':
				HandleOpenBracket( c, operatorStack, value, result );
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				HandleOperator( c, operatorStack, value, result );
				break;
			default:
				value += c;
				break;
			}
		}

		if ( value.size( ) > 0 )
		{
			result.emplace_back( value );
		}

		while ( operatorStack.size( ) > 0 )
		{
			result.emplace_back( std::string( 1, operatorStack.top( ) ) );
			operatorStack.pop( );
		}

		return result;
	}

	void HandleCloseBracket( std::stack<char>& operatorStack, std::string& value, std::vector<std::string>& result/*out*/ )
	{
		if ( value.size( ) > 0 )
		{
			result.emplace_back( value );
			value.clear( );
		}

		while ( operatorStack.size( ) > 0 )
		{
			char symbol = operatorStack.top( );
			operatorStack.pop( );

			if ( symbol == '(' )
			{
				break;
			}

			result.emplace_back( std::string( 1, symbol ) );
		}
	}

	void HandleOpenBracket( char c, std::stack<char>& operatorStack, std::string& value, std::vector<std::string>& result/*out*/ )
	{
		if ( value.size( ) > 0 )
		{
			result.emplace_back( value );
			value.clear( );
		}

		operatorStack.push( c );
	}

	void HandleOperator( char c, std::stack<char>& operatorStack, std::string& value, std::vector<std::string>& result/*out*/ )
	{
		if ( value.size( ) > 0 )
		{
			result.emplace_back( value );
			value.clear( );
		}

		while ( operatorStack.size( ) > 0 )
		{
			char symbol = operatorStack.top( );

			if ( IsGreaterEqualPrecedence( c, symbol ) )
			{
				result.emplace_back( std::string( 1, symbol ) );
				operatorStack.pop( );
			}
			else
			{
				break;
			}
		}

		operatorStack.push( c );
	}

	T PostfixEvaluate( const std::vector<std::string>& postfix, const Context<T>& ctx )
	{
		assert( m_exprHandler && "m_exprHandler is nullptr" );

		bool handled = false;
		ExpressionStack<T> exprs;

		for ( const auto& pattern : postfix )
		{
			handled = m_exprHandler->HandleRequest( pattern, exprs );
			assert( handled && "pattern doesn't handled" );
		}

		assert( exprs.size( ) == 1 && "result expression stack size is not 1" );
		return exprs.top( )->Interpret( ctx );
	}

	std::unique_ptr<IHandler<T>> m_exprHandler;
};
