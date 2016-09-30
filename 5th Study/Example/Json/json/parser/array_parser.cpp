#include "./array_parser.h"
#include "./object_parser.h"

namespace json
{
    // class array_parser : parser
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    array_parser::array_parser(std::istream & _in) :
        parser{ _in }
    {}

    json::array array_parser::parse()
        noexcept(false)
    {
        // ignore ws(white spaces)
        ignore_epsilon(in);

        if (in.get() != '[') {
            throw std::invalid_argument{ typeid(*this).name() };
        }

        json::array_builder builder{};

        // assume stream is good
        while (in)
        {
            // skip white spaces before parsing
            ignore_epsilon(in);

            // caution! must be `peek()`
            char ch = in.peek();
            // json::object
            if (ch == '{') {
                object_parser op{ this->stream() };

                auto obj = op.parse();
                builder.append(std::move(obj));
            }
            // json::array
            else if (ch == '[') {
                array_parser ap{ this->stream() };

                auto arr = ap.parse();
                builder.append(std::move(arr));
            }
            // json::string
            else if (ch == '"') {
                stream_parser sp{ this->stream() };

                auto str = sp.read_string();
                builder.append(std::move(str));
            }
            // json::f64 
            //      possibly numeric
            //      `switch` statement can't do this! :(
            else if ((ch == '-')
                || (is_digit(ch) == true))
            {
                stream_parser sp{ this->stream() };

                auto num = sp.read_double();
                builder.append(std::move(num));
            }
            // No case
            else {
                // unexpected token
                throw std::invalid_argument{ typeid(*this).name() };
            }

            // skip white spaces after parsing
            ignore_epsilon(in);

            ch = in.get();
            // end of array
            if (ch == ']') { break; }
            // more value...
            else if (ch == ',') { continue; }
            else {
                throw std::invalid_argument{ typeid(*this).name() };
            }
        }

        return builder.build();
    }

}