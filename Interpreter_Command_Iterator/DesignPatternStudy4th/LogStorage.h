#pragma once

#include "Command.h"

#include <memory>
#include <vector>

class CLogStorage
{
public:
	static CLogStorage& GetInstance( )
	{
		static CLogStorage logStorage;
		return logStorage;
	}

	void AddLog( std::unique_ptr<ILogCommand>&& command )
	{
		if ( command )
		{
			m_commands.emplace_back( std::move( command ) );
		}
	}

	void RemoveAllLog( )
	{
		m_commands.clear( );
	}

	void Print( )
	{
		for ( const auto& command : m_commands )
		{
			if ( command )
			{
				command->Execute( );
			}
		}
	}

private:
	CLogStorage( ) {}

	std::vector<std::unique_ptr<ILogCommand>> m_commands;
};