// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File    : test.json_parser.cpp
//  Updated : 16/08/18
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//
//  Note
//      Testcase for parser types in `namespace json` 
//      - `json::stream_parser`
//      - `json::object_builder`
//      - `json::object_parser`
//      - `json::array_parsesr`
//
//  Task
//      - Estimate the test input's structure 
//      - Compose test cases
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#include <catch.hpp>
#include <istream>
#include "../json.hpp"

namespace test
{
    using namespace std;
    using namespace std::literals;
    using namespace json;

    namespace in
    {
        const char dbl[] = u8"-15.928372";
        const char jstr[] = u8"\"Hell World!\"";
        const char arr[] = u8"";
        const char obj[] =
            u8"{ \"glossary\":{  \r "
            " \"title\": \"example glossary\","
            "\"number\" :-982.12  , "
            "\"GlossDiv\" : {  \t   "
            "  \"title\": \"S\", \t\n\r "
            "\"GlossList\" : {          "
            "  \"GlossEntry\": {         "
            "       \"ID\": \"SGML\", "
            "                   \"SortAs\" : \"SGML\",  "
            "  \"GlossTerm\" : \"Standard Generalized Markup Language\","
            "\"Acronym\" : \"SGML\", "
            "\"Abbrev\" : \"ISO 8879:1986\","
            "\"GlossDef\" : { "
            "\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\","
            "\"GlossSeeAlso\" : [\"GML\", \"XML\"]   "
            "},"
            "\"GlossSee\" : \"markup\" "
            "}        }    }}}";
    }

    namespace out
    {
        json::f64     dbl  = -15.928372;
        json::jstring jstr = "Hell World!";
    }

}

/*
// !!! On work !!!
TEST_CASE("json::object_builder") 
{
    using namespace json;
}

TEST_CASE("json::parser")
{
    using namespace json;

    REQUIRE_NOTHROW({
        parser p{ std::cin };
        p.stream();
    });
    
}

TEST_CASE("json::stream_parser") 
{
    using namespace test;
    using namespace json;

    SECTION("read_string") 
    {
        std::stringstream sin;

        stream_parser sp{ sin };
        sin << test::jstr_input << std::endl;
        
        json::jstring jstr;

        REQUIRE_NOTHROW({
            jstr = sp.read_string();
        });

        REQUIRE(jstr == jstr_res);

        //REQUIRE_THROWS();

    }

    SECTION("read_double")
    {
        std::stringstream sin;

        stream_parser sp{ sin };
        json::f64 fvalue;
        sin << test::f64_input << std::endl;
        REQUIRE_NOTHROW({
            fvalue = sp.read_double();
        });

        REQUIRE(fvalue == test::f64_res);

        //REQUIRE_THROWS();

    }

}

// !!! On work !!!
TEST_CASE("json::object_parser")
{
    SECTION("parse")
    {
        //std::stringstream sin;
        //sin << test::object_input << std::endl;

        //json::object_parser op{ sin };

        //json::object obj = op.parse();

    }

}

// !!! On work !!!
TEST_CASE("json::array_parser") 
{
    SECTION("parse")
    {
        //std::stringstream sin;
        //sin << test::array_input << std::endl;

        //json::array_parser ap{ sin };

        //json::array arr = ap.parse();

    }
}
*/