#include "./stream_parser.hpp"

namespace json
{

    // class stream_parser : parser
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    stream_parser::stream_parser(std::istream & _in):
        parser{ _in }
    {}

    json::f64    stream_parser::read_double() 
        noexcept(false)
    {
        // json::f64 == double
        double value;
        // ignore white space and read double
        in >> std::ws >> value;
        return value;
    }

    json::jstring stream_parser::read_string() 
        noexcept(false)
    {
        std::string buffer{};
        if (in.get() == '"') {
            // read until token(")
            std::getline(this->in, buffer, '"');
        }
        return json::jstring{ std::move(buffer) };
    }


}
