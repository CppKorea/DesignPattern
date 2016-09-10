#pragma once

#include <iostream>
#include <string>

class CLogger
{
public:
	static CLogger& GetInstance( )
	{
		static CLogger logger;
		return logger;
	}
	
	void Log( const std::string& msg ) const
	{
		std::cout << ">> " << msg;
	}

private:
	CLogger( ) {}
};