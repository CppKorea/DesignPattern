#ifndef _JSON_ARRAY_PARSER_H_
#define _JSON_ARRAY_PARSER_H_

#include "./stream_parser.hpp"

namespace json
{

    // [ array_parser ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      //
    class array_parser :
        public parser
    {
    public:
        explicit array_parser(std::istream& _in);

        // - Note
        //      Read JSON Array from the stream
        // - Format
        //      [ "", {}, -12, 4.294 ]
        json::array  parse()  noexcept(false);

    };

}// namespace json
#endif