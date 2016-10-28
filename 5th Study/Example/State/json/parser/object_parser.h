// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

#ifndef _JSON_OBJECT_PARSER_HPP_
#define _JSON_OBJECT_PARSER_HPP_

#include "./stream_parser.hpp"

namespace json
{

    // [ object_parser ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      //
    class object_parser :
        public parser
    {
        struct state_type
        {
            virtual ~state_type() = default;
            virtual
            state_type* handle_input(parser& _parser,
                                     const char   _ch)
                noexcept(false) = 0;
        };

        struct init;
        struct get_object;
        struct get_name;
        struct name_to_value;
        struct get_value;
        struct accquired;
        struct complete;

        state_type* state;

    public:
        explicit object_parser(std::istream& _in);

        // - Note
        //      Read JSON Object from the stream
        // - Format
        //      { ... } 
        json::object parse() noexcept(false);

    };

}// namespace json

#endif
