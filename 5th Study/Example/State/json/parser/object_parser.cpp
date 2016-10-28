#include "./object_parser.h"
#include "./array_parser.h"

namespace json
{

    // class object_parser : parser
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    object_parser::object_parser(std::istream & _in) :
        parser{ _in }
    {}

    json::object object_parser::parse()
        noexcept(false)
    {
        json::object_builder builder{};

        ignore_epsilon(in);

        char c = in.get();
        if (c != '{') {
            in.unget();
            throw std::invalid_argument{ typeid(*this).name() };
        }

        // OK, building object !

        while (in)
        {
            ignore_epsilon(in);

            // "name"
            {
                stream_parser sp{ in };
                json::jstring name = sp.read_string();

                // save name
                builder.save_name(std::move(name));
            }
            ignore_epsilon(in);

            // :
            if (in.get() != ':') {
                throw std::invalid_argument{ typeid(*this).name() };
            }

            ptr<value> pval = nullptr;

            ignore_epsilon(in);
            // caution! must be `peek()`
            char ch = in.peek(); 

            // `json::object`
            if (ch == '{') {
                object_parser op{ this->stream() };

                auto obj = op.parse();
                pval = box_value(std::move(obj));
            }
            // `json::array`
            else if (ch == '[') {
                array_parser ap{ this->stream() };

                auto arr = ap.parse();
                pval = box_value(std::move(arr));
            }
            // `json::string`
            else if (ch == '"') {
                stream_parser sp{ this->stream() };

                auto str = sp.read_string();
                pval = box_value(std::move(str));
            }
            // `json::f64`
            // possibly numeric
            // `switch` statement can't do this! :(
            else if ((ch == '-')
                || (is_digit(ch) == true))
            {
                stream_parser sp{ this->stream() };

                auto num = sp.read_double();
                pval = box_value(std::move(num));
            }
            // No case
            else {
                // unexpected token
                throw std::invalid_argument{ typeid(*this).name() };
            }

            // Store the boxed value
            if (pval != nullptr) {
                builder.save_value(std::move(pval));
            }

            builder.save_property();

            ignore_epsilon(in);

            ch = in.get();
            if (ch == ',') {
                continue;
            }
            else if (ch == '}') {
                break;
            }
            else {
                // unexpected token
                throw std::invalid_argument{ typeid(*this).name() };
            }
        }// while(in)

        return builder.build();
    }





}
