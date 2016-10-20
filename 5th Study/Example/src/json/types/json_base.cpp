#include "./json_base.hpp"

namespace json
{

    jstring::jstring(const std::string& _str) noexcept(false) :
        std::string{_str}
    {}

    jstring::jstring(std::string&& _str) noexcept :
        std::string{ std::move(_str) }
    {}

    jstring & jstring::operator=(const std::string & _rhs) noexcept(false)
    {
        std::string& self = *this;
        self = _rhs;
        return *this;
    }

    jstring & jstring::operator=(std::string && _rhs) noexcept
    {
        std::string& self = *this;
        self = std::move(_rhs);
        return *this;
    }

    jstring::operator std::string() noexcept
    {
        return *this;
    }


    //constexpr json::i64 operator""_js(unsigned long long _i64)
    //{
    //    return json::i64{ _i64 };
    //}

    //constexpr json::f64 operator""_js(long double _f64)
    //{
    //    return json::f64{ _f64 };
    //}

    json::jstring operator""_js(const char * str, std::size_t len)
    {
        std::string temp(str, len);
        return json::jstring{ std::move(temp) };
    }

    std::ostream & operator<<(std::ostream & _out,
                              const json::jstring& _str)
        noexcept(false)
    {
        _out << '\"' << _str.c_str() << '\"';
        return _out;
    }

    std::ostream& operator<< (std::ostream& out, 
                              const json::value& _val)
        noexcept(false)
    {
        // converting via member function 
        // ensures **strong exception guarnatee** 
        // for the stream, `out`.
        out << _val.toUtf8(); 
        return out;
    }


} //namespace json

