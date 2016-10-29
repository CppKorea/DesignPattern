#pragma once

#include <map>
#include <string>

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Context
{
public:
	void AddVariable( const std::string& variable, const T value )
	{
		m_variables.emplace( variable, value );
	}

	T GetVariable( const std::string& variable ) const
	{
		auto found = m_variables.find( variable );
		
		if ( found == m_variables.end( ) )
		{
			T defaultValue{};
			return defaultValue;
		}

		return found->second;
	}

private:
	using VariableMap = std::map<std::string, T>;

	VariableMap m_variables;
};