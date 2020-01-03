#define CATCH_CONFIG_MAIN

#include "Aggregate.h"
#include "Command.h"
#include "Expression.h"
#include "Evaluator.h"
#include "Handler.h"
#include "Lib\catch.hpp"
#include "LogStorage.h"

#include <crtdbg.h>
#include <iostream>
#include <list>
#include <type_traits>

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__ )
#endif

TEST_CASE( "Expression" )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Context<int> dummyContext;

	SECTION( "Operand Expression" )
	{
		float floatingInput = 3.14f;
		CNumberExpr<float> floatingType( floatingInput );
		Context<float> floatContext;

		REQUIRE( floatingType.Interpret( floatContext ) == floatingInput );

		int integerInput = 20160911;
		CNumberExpr<int> integerType( integerInput );

		REQUIRE( integerType.Interpret( dummyContext ) == integerInput );
	}

	SECTION( "Value Expression" )
	{
		Context<float> floatCtx;
		REQUIRE( floatCtx.GetVariable( "" ) == 0.f );

		floatCtx.AddVariable( "$critical", 201.60911f );
		REQUIRE( floatCtx.GetVariable( "$critical" ) == 201.60911f );

		Context<int> integerCtx;
		REQUIRE( integerCtx.GetVariable( "" ) == 0 );

		integerCtx.AddVariable( "$attack", 2016 );
		REQUIRE( integerCtx.GetVariable( "$attack" ) == 2016 );

		CVariableExpr<float> criticalExp( "$critical" );
		REQUIRE( criticalExp.Interpret( floatCtx ) == 201.60911f );

		CVariableExpr<int> attackExp( "$attack" );
		REQUIRE( attackExp.Interpret( integerCtx ) == 2016 );
	}

	int lhsInput = 20160911;
	int rhsInput = 11906102;
	CNumberExpr<int> lhs( 20160911 );
	CNumberExpr<int> rhs( 11906102 );

	SECTION( "Plus Expression" )
	{
		CPlusExpr<int> plus( &lhs, &rhs );
		REQUIRE( plus.Interpret( dummyContext ) == lhsInput + rhsInput );

		CPlusExpr<int> rPlus( &rhs, &lhs );
		REQUIRE( rPlus.Interpret( dummyContext ) == rhsInput + lhsInput );
	}

	SECTION( "Minus Expression" )
	{
		CMinusExpr<int> minus( &lhs, &rhs );
		REQUIRE( minus.Interpret( dummyContext ) == lhsInput - rhsInput );

		CMinusExpr<int> rMinus( &rhs, &lhs );
		REQUIRE( rMinus.Interpret( dummyContext ) == rhsInput - lhsInput );
	}

	SECTION( "Multiply Expression" )
	{
		CMultiplyExpr<int> mul( &lhs, &rhs );
		REQUIRE( mul.Interpret( dummyContext ) == lhsInput * rhsInput );

		CMultiplyExpr<int> rMul( &rhs, &lhs );
		REQUIRE( mul.Interpret( dummyContext ) == rhsInput * lhsInput );
	}

	SECTION( "Divide Expression" )
	{
		CDivideExpr<int> div( &lhs, &rhs );
		REQUIRE( div.Interpret( dummyContext ) == lhsInput / rhsInput );

		CDivideExpr<int> rDiv( &rhs, &lhs );
		REQUIRE( rDiv.Interpret( dummyContext ) == rhsInput / lhsInput );
	}
}

TEST_CASE( "Handler" )
{
	CNumberHandler<float> numberHandler;
	CVariableHandler<float> variableHandler;
	COperatorHandler<float> operatorHandler;

	SECTION( "Number Handler" )
	{
		ExpressionStack<float> exprStack;

		REQUIRE( numberHandler.HandleRequest( "201.60911", exprStack ) );
		REQUIRE( exprStack.size( ) == 1 );

		REQUIRE_FALSE( numberHandler.HandleRequest( "something", exprStack ) );
		REQUIRE( exprStack.size( ) == 1 );

		REQUIRE( numberHandler.HandleRequest( "119.06102", exprStack ) );
		REQUIRE( exprStack.size( ) == 2 );
	}

	SECTION( "Variable Handler" )
	{
		ExpressionStack<float> exprStack;

		REQUIRE( variableHandler.HandleRequest( "$attack", exprStack ) );
		REQUIRE( exprStack.size( ) == 1 );

		REQUIRE_FALSE( variableHandler.HandleRequest( "something", exprStack ) );
		REQUIRE( exprStack.size( ) == 1 );

		REQUIRE( variableHandler.HandleRequest( "$critical", exprStack ) );
		REQUIRE( exprStack.size( ) == 2 );
	}

	SECTION( "Operator Handler" )
	{
		ExpressionStack<float> exprStack;

		REQUIRE( numberHandler.HandleRequest( "201.60911", exprStack ) );
		REQUIRE( numberHandler.HandleRequest( "119.06102", exprStack ) );
		REQUIRE( operatorHandler.HandleRequest( "+", exprStack ) );
		REQUIRE( exprStack.size( ) == 1 );
	}
}

TEST_CASE( "Evaluator" )
{
	CEvaluator<float> evaluator;
	
	REQUIRE( evaluator.Evaluate( "( 150 + 60 / 2 ) * 2 + ( 78 - 20 + 60 ) + 1", Context<float>( ) ) == (150.f + 60.f / 2.f) * 2.f + (78.f - 20.f + 60.f) + 1.f );

	Context<float> floatCtx;
	floatCtx.AddVariable( "$critical", 201.60911f );
	floatCtx.AddVariable( "$baseDamage", 50.f );
	
	REQUIRE( evaluator.Evaluate( "( $critical + 60 / 2 ) * 2 + ( 78 - 20 + 60 ) + 1", floatCtx ) == (201.60911f + 60.f / 2.f) * 2.f + (78.f - 20.f + 60.f) + 1.f );
	REQUIRE( evaluator.Evaluate( "$critical * $baseDamage", floatCtx ) == 50.f * 201.60911f );
}

TEST_CASE( "Command" )
{
	LogDamageResult<float> log( "$critical * $baseDamage", 2000 );
	log.Execute( );
}

TEST_CASE( "LogStorage" )
{
	CLogStorage& invoker = CLogStorage::GetInstance( );

	invoker.AddLog( std::make_unique<LogDamageResult<float>>( "$critical * $baseDamage", 100.f ) );
	invoker.AddLog( std::make_unique<LogDamageResult<float>>( "$critical * $baseDamage", 200.f ) );

	invoker.RemoveAllLog( );
	invoker.Print( );

	invoker.AddLog( std::make_unique<LogDamageResult<float>>( "$critical * $baseDamage", 300.f ) );
	invoker.AddLog( std::make_unique<LogDamageResult<float>>( "$critical * $baseDamage", 400.f ) );

	invoker.Print( );
}

TEST_CASE( "Custom Linked List" )
{
	LinkedList<float> list;
	list.push_back( 1 );

	REQUIRE( list.size( ) == 1 );
	REQUIRE( *list.begin( ) == 1 );

	list.push_back( 2 );
	list.push_back( 3 );

	REQUIRE( list.size( ) == 3 );

	float i = 1;
	for ( auto value : list )
	{
		REQUIRE( value == i );
		++i;
	}
}