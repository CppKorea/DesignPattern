#include "./json_builder.h"

namespace json
{

    // class object_builder
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    // - Note
    //      Prepare the name argument
    void object_builder::save_name(json::jstring && _name) noexcept
    {
        name_arg = std::move(_name);
    }

    // - Note
    //      Prepare the value argument
    void object_builder::save_value(ptr<json::value>&& _value) noexcept
    {
        value_arg = std::move(_value);
    }

    // - Note
    //      Save the property with the prepared args.
    void object_builder::save_property() noexcept(false)
    {
        // if invalid argument, do nothing
        if (name_arg.length() == 0
            || value_arg == nullptr)
        {
            throw std::invalid_argument{
                "Arguments for property is not valid"};
        }
        // save the property
        result.set(name_arg, std::move(value_arg));
    }

    json::object&& object_builder::build() noexcept
    {
        // building task....

        return std::move(this->result);
    }



    // class array_builder
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    json::array&& array_builder::build() noexcept
    {
        return std::move(this->result);
    }


}