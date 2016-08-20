
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _JSON_STREAM_PARSER_HPP_
#define _JSON_STREAM_PARSER_HPP_

#include "./json_builder.h"

namespace json
{
    // Helper functions
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    static 
    bool is_digit(const char _ch) noexcept 
    {
        return isdigit(_ch) != 0;
    }

    static 
    bool is_epsilon(const char _ch) noexcept
    {
        return (_ch == ' ')
            || (_ch == '\n')
            || (_ch == '\r')
            || (_ch == '\t');
    };

    static 
    void ignore_epsilon(std::istream& _in) noexcept(false)
    {
        _in >> std::ws;
    }


    // [ parser ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      General parser interface
    class parser 
    {
    protected:
        std::istream& in;
    public:
        explicit parser(std::istream& _in) : 
            in{ _in } 
        {};

        virtual ~parser() = default;

        // - Note 
        //      stream's reference
        std::istream& stream() noexcept 
        {
            return this->in;
        }
    };

    // [ stream_parser ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      Parse string/double json types from `istream`
    //      Modify the stream in parsing process
    // - Data Race
    //      the class is only for single thread
    class stream_parser : 
        public parser
    {
    public:
        explicit stream_parser(std::istream& _in);

        // - Note
        //      Read JSON Integer/Double from the stream
        // - Format
        //      -56.234
        json::f64    read_double() noexcept(false);

        // - Note
        //      Read JSON String from the stream
        // - Format
        //      "string"
        json::jstring read_string() noexcept(false);

    };




}// namespace json

#endif
