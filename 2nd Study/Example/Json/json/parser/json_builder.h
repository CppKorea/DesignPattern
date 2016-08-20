// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// 
//  File    : json_builder.h
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//  Updated : 16/08/18
//
//  Note
//      JSON object builder definition
//  Types
//    - `object_builder`   : builder class for `json::object`
//    - `array_builder`    : builder class for `json::array`
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _JSON_BUILDER_H_
#define _JSON_BUILDER_H_

#include <stack>

#include "../types.h"

namespace json
{

    // [ object_builder]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      Builder class for `json::object`
    class object_builder
    {
        json::object            result;

        json::jstring           name_arg;
        json::ptr<json::value>  value_arg = nullptr;

    public:
        // - Note
        //      Prepare the name argument
        void save_name(json::jstring&& _name)
            noexcept;

        // - Note
        //      Prepare the value argument
        void save_value(ptr<json::value>&& _value)
            noexcept;

        // - Note
        //      Save the property with the prepared args.
        void save_property() noexcept(false);

        // - Note
        //      Fetch the JSON object from builder 
        json::object&& build() noexcept;

    };

    // [ array_builder]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      Builder class for `json::array`
    class array_builder
    {
        json::array result;
    public:
        template <typename T>
        void append(T&& _value) noexcept(false);

        json::array&& build() noexcept;

    };

    template<typename T>
    inline
    void array_builder::append(T && _value)
        noexcept(false)
    {
        result.append(std::move(_value));
    }

} //namespace json

#endif
