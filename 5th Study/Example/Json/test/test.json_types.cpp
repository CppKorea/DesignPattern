// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
//
//  File    : test.json_types.cpp
//  Updated : 16/08/18
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//
//  Note
//      Testcase for simple types in `namespace json` 
//      - `json::i64`, `json::f64`
//      - `json::string`
//      - `json::object`
//      - `json::array`
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#include <catch.hpp>

#include "../json.hpp"

TEST_CASE("json::i64")
{
    using namespace json;

    SECTION("literal") 
    {
        volatile i64 var = 15;
        var = 17 * var;

        REQUIRE_FALSE(var == 15);
        REQUIRE(var == 15 * 17);

        var = 23 * var;
        REQUIRE(var == 15 * 17 * 23);
    }

}// `json::i64`

TEST_CASE("json::f64")
{
    using namespace json;

    SECTION("literal")
    {
        volatile f64 var = 15.124;
        var = 17.182 * var;

        REQUIRE_FALSE(var == 15.124);
        REQUIRE(var == 17.182 * 15.124);

        var = 23 * var;
        REQUIRE(var == 17.182 * 15.124 * 23);
    }

}// `json::f64` 

TEST_CASE("json::jstring")
{
    using namespace std::literals;
    using namespace json;

    SECTION("literal/ctor") 
    {
        std::string std = "StringLiteral"s;
        // literal 
        jstring jstr = "StringLiteral"_js;

        // NO additional length
        REQUIRE(std.length() == jstr.length());

        // random access, last character
        // no difference with `std::string`
        REQUIRE_FALSE(jstr[0] == '"');
        REQUIRE_FALSE(jstr.back() == '"');

        const auto jlit = "jsonString"_js;

        // copy construction
        jstring copy = jlit;
        // move construction
        jstring move = std::move(jlit);

        REQUIRE(copy == move);
    }

    SECTION("stream/utf8")
    {
        jstring jstr{};
        jstr = "Some strange string";

        std::ostringstream sout;

        // just simple stream output!
        REQUIRE_NOTHROW({
            sout << jstr;
        });

        std::string output = sout.str();

        REQUIRE(output.length() > jstr.length());
        // json string starts and ends with " character
        REQUIRE(output[0] == '"');
        REQUIRE(output.back() == '"');
    }

}// `json::jstring` 

TEST_CASE("json::object")
{
    using namespace json;

    // 몸에 좋고? 맛도 좋은? 크로아상~
    jstring name     = "croissant"_js;
    i64     price    = 3000;
    f64     discount = 0.15;

    object bread{};
    object coffee{};
    object menu{};

    SECTION("ctor/operator=") 
    {
        bread.set("name", "croissant"_js);  // json::jstring
        bread.set("price", i64{ 3000 });    // json::i64
        bread.set("discount", f64{ 0.15 }); // json::f64

        coffee.set("name", json::jstring{ "espresso" });
        coffee.set("price", i64{ 2000 });

        // copy construction
        auto copy_bread{ bread };
        REQUIRE(copy_bread.count() == bread.count());

        // copy assignment
        REQUIRE_NOTHROW({
            menu = bread;
        });

        // move construction
        auto move_coffee{ std::move(coffee) };
        REQUIRE(move_coffee.count() > coffee.count());
        REQUIRE(move_coffee.count() == 2);

        // move assignment
        REQUIRE_NOTHROW({
            // coffee to... bread?
            bread = std::move(move_coffee);
        });

        REQUIRE_FALSE(bread.count() == move_coffee.count());
    }

    // set/get
    SECTION("property set/get")
    {
        bread.set("name", "croissant"_js);  // json::jstring
        bread.set("price", i64{ 3000 });    // json::i64
        bread.set("discount", f64{ 0.15 }); // json::f64
        REQUIRE(bread.count() == 3);

        coffee.set("name", json::jstring{ "espresso" });
        coffee.set("price", i64{ 2000 });
        REQUIRE(coffee.count() == 2);

        // get
        // ---- ---- ---- ---- ----
        jstring* pstr = bread.get<jstring>("name");
        REQUIRE(pstr != nullptr);
        REQUIRE(*pstr == name);

        // type mismatch.
        // should return nullptr;
        i64* pi64 = bread.get<i64>("name");
        REQUIRE(pi64 == nullptr);

        // property not found
        // should return nullptr;
        f64* pf64 = bread.get<f64>("size");
        REQUIRE(pf64 == nullptr);


        i64* pi = bread.get<i64>("price");
        REQUIRE(pi != nullptr);
        if (pi != nullptr) {
            REQUIRE(*pi == price);
        }

        f64* pf = bread.get<f64>("discount");
        REQUIRE(pf != nullptr);
        if (pf != nullptr) {
            REQUIRE(*pf == discount);
        }

        // move
        menu.set("bread", std::move(bread));
        REQUIRE(bread.count() == 0);

        // copy
        menu.set("coffee", coffee);
        REQUIRE(coffee.count() == 2);

        object* pobj = menu.get<json::object>("coffee");
        REQUIRE(pobj != nullptr);

        if (pobj != nullptr) {
            // Referencing the object
            const auto& cof = *pobj;
            REQUIRE(cof.count() == 2);

            // try to serialize
            REQUIRE(cof.toUtf8().length() > 2);
        }

    }

    SECTION("prototype")
    {
        object espresso{};
        espresso.set("name",    "Espresso"_js);
        espresso.set("price",   2000);
        espresso.set("shot",    2);
        espresso.set("taste",   "Awesome"_js);


        object latte{};

        REQUIRE_NOTHROW({
            latte.prototype(espresso);
        });
        
        latte.set("name",   "Latte"_js);
        latte.set("price",  3000);


        object* proto = nullptr;
        REQUIRE_NOTHROW({
            proto = latte.prototype();
        });

        REQUIRE(proto != nullptr);
        REQUIRE(proto == &espresso);

        const object& cref_latte = latte;

        REQUIRE_NOTHROW({
            const auto* ptr = cref_latte.prototype();
            REQUIRE(ptr != nullptr);
        });

    }
}// `json::object` 


TEST_CASE("json::array")
{
    using namespace json;

    const i64 Width = 210;
    const i64 Height = 297;

    object paper{};
    paper.set("format", json::jstring{ "A4" });
    paper.set("width", Width);
    paper.set("height", Height);

    jstring str = "C++";

    i64 ival = 1234;
    f64 fval = -56.78;

    SECTION("append") 
    {
        array arr{};

        object trash = paper;
        arr.append(std::move(trash));
        arr.append(str);
        REQUIRE(arr.size() == 2);

        arr.append(ival);
        arr.append(fval);
        REQUIRE(arr.size() == 4);
    }

    SECTION("random access") 
    {
        array arr{};

        arr.append(paper);
        arr.append(str);
        arr.append(ival);
        arr.append(fval);

        object* pobj = arr.at<object>(0);
        REQUIRE_FALSE(pobj == nullptr);

        i64* pwidth = pobj->get<i64>("width");
        REQUIRE(pwidth != nullptr);
        if (pwidth != nullptr) {
            REQUIRE(*pwidth == 210);
        }

        jstring* pstr = arr.at<jstring>(1);
        REQUIRE_FALSE(pstr == nullptr);
        if (pstr != nullptr) {
            REQUIRE(*pstr == str);
        }

        i64* pi = arr.at<i64>(2);
        REQUIRE(pi != nullptr);
        if (pi != nullptr) {
            REQUIRE(*pi == ival);
        }

        f64* pf = arr.at<f64>(3);
        REQUIRE(pf != nullptr);
        if (pf != nullptr) {
            REQUIRE(*pf == fval);
        }
    }

    SECTION("serialization")
    {
        array arr{};

        std::string std = arr.toUtf8();
        REQUIRE(std.length() > 2);

        arr.append(paper);
        arr.append(str);
        arr.append(ival);
        arr.append(fval);

        REQUIRE_NOTHROW({
            std = arr.toUtf8();
        }); 

    }

    SECTION("clone")
    {
        array arr{};

        arr.append(str);
        arr.append(ival);
        arr.append(fval);

        ptr<value> ptr = arr.clone();
        REQUIRE(ptr != nullptr);

        // `ptr` is clone! it must be equal to `arr`
        REQUIRE(ptr->toUtf8() == arr.toUtf8());
    }

}// `json::array` 

