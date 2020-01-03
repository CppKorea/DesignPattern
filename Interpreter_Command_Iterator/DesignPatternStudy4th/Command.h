#pragma once

#include "Receiver.h"

#include <chrono>
#include <string>

class ILogCommand
{
public:
	virtual void Execute( ) const = 0;
	
	virtual ~ILogCommand( ) = default;

	ILogCommand( const ILogCommand& ) = default;
	ILogCommand& operator=( const ILogCommand& ) = default;
	ILogCommand( ILogCommand&& ) = default;
	ILogCommand& operator=( ILogCommand&& ) = default;

protected:
	ILogCommand( ) = default;
};

template <typename T>
class LogDamageResult : public ILogCommand
{
public:
	virtual void Execute( ) const override
	{
		std::stringstream stream;
		stream << ">> " << m_expression << " = " << m_totalDamage << std::endl;
		CLogger::GetInstance().Log( stream.str() );
	}

	LogDamageResult( const std::string& expression, T totalDamage ) : 
		m_expression( expression ),
		m_totalDamage( totalDamage )
	{
	}

private:
	std::string m_expression;
	T m_totalDamage;
};