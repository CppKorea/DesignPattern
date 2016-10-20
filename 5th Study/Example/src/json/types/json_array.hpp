// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// 
//  File    : json_array.hpp
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//  Updated : 16/08/18
//
//  Note
//      Definitions for JSON value array.
//      Later optimization is required
//  Types
//    - `json::array`    : JSON array class
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _JSON_ARRAY_HPP_
#define _JSON_ARRAY_HPP_

#include "./json_object.hpp"

namespace json
{
    // [ array ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      JSON value array
    // - Form
    //      [ { }, "str", 1234, -56.78 ]
    class array : 
        public json::value
    {
    public:
        using self_type = array;
        using elem_type = ptr<json::value>;
        using container = std::vector<elem_type>;
        using iter_type = container::iterator;
        using const_iter_type = container::const_iterator;

    protected:
        container vlist;


    public:

        explicit array() = default;
        // copy
        array(const array& _arr) noexcept(false);
        array& operator = (const array& _arr) noexcept(false);

        // move
        array(array&& _arr) noexcept = default;
        array& operator=(array&& _arr) noexcept = default;


        // - Note
        //      Current size of the array
        size_t size() const noexcept;
        
        // - Note
        //      Access to the element and then
        //      reinterpret it to specified type's pointer
        // - Return
        //      nullptr : type mismatch
        template <typename Out>
        Out* at(int _idx) noexcept(false);

        template <typename Out>
        const Out* at(int _idx) const noexcept(false);

        // - Note
        //      Append the **boxed** value
        void append(ptr<json::value>&& _box);

        template <typename T>
        void append(T& _value) noexcept(false);

        // - Note
        //      **Box and Append** the given argument 
        template <typename T>
        void append(T&& _value) noexcept(false);


        // - Note
        //      현재 보유한 object 들을 UTF8 JSON 으로 변환한다.
        // - See also
        //      `operator<< (object&)`
        virtual 
        std::string toUtf8() const noexcept(false)
            override;

        virtual
        const type_info& info() const noexcept
            override;

        // - Note
        //      Acquire inner value's pointer
        virtual void*       vptr() noexcept override;

        // - Note
        //      Acquire inner value's const pointer
        virtual const void* vptr() const noexcept override;


        virtual
        ptr<value> clone() const noexcept(false) 
            override;

    };// class array


    // - Note
    //      Access to the element and then
    //      reinterpret it to specified type's pointer
    // - Return
    //      nullptr : type mismatch
    template<typename Out>
    inline Out * array::at(int _idx) noexcept(false)
    {
        elem_type& elem = this->vlist.at(_idx);
        json::value& val = *elem;

        if (val.info() == typeid(Out)) {
            Out* ptr = reinterpret_cast<Out *>(val.vptr());
            return ptr;
        }
        else {
            return nullptr;
        }
    }

    // - Note
    //      Access to the element and then
    //      reinterpret it to specified type's pointer
    // - Return
    //      nullptr : type mismatch
    template<typename Out>
    inline const Out * array::at(int _idx) const noexcept(false)
    {
        const elem_type& elem = this->vlist.at(_idx);
        const json::value& val = *elem;

        if (val.info() == typeid(Out)) {
            const Out* ptr = reinterpret_cast<const Out *>(val.vptr());
            return ptr;
        }
        else {
            return nullptr;
        }
    }

    // - Note
    //      **Box and Append** the given argument 
    template<typename T>
    inline void array::append(T& _value)
        noexcept(false)
    {
        elem_type box = json::box_value(_value);

        this->append(std::move(box));
    }

    // - Note
    //      **Box and Append** the given argument 
    template<typename T>
    inline void array::append(T&& _value)
        noexcept(false)
    {
        elem_type box =
            json::box_value(std::move(_value));

        this->append(std::move(box));
    }



}// namespace json

#endif
