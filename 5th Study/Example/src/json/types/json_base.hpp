// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// 
//  File    : json_base.hpp
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//  Updated : 16/08/18
//
//  Note
//      Fundamental definitions for `namespace json`
//  Types
//    - `ptr<T>`          : RAII pointer aliasing
//    - `json::i64`       : integer
//    - `json::f64`       : double
//    - `json::jstring`,  : string 
//    - `operator""_js`   : Literal expression
//    - `json::value`     : value interface
//    - `json::typed_value<T>` : value adapter template
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _JSON_BASE_HPP_
#define _JSON_BASE_HPP_

#include <cstdint>
#include <cctype>

#include <iostream>
#include <sstream>

#include <utility>
#include <typeinfo>
#include <type_traits>

#include <string>
#include <memory>

#include <list>
#include <vector>
#include <algorithm>



namespace json
{
    // Type, Template aliasing
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    template <typename T>
    using ptr = std::unique_ptr<T>;

    // - Note
    //      Wrapper function
    // - Dependency
    //      `std::make_unique<T>()`
    template <typename T, typename... Args>
    ptr<T> make_ptr(Args&&... _params) noexcept(false)
    {
        return std::make_unique<T>(std::forward<Args>(_params)...);
    }

    using f64 = std::double_t;
    using i64 = std::int64_t;

    //constexpr json::i64 operator ""_js(unsigned long long _i);
    //constexpr json::f64 operator ""_js(long double _i);


    // [ jstring ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      JSON string
    //      Simple wrapper of `std::string`
    // - Form
    //      "string"
    struct jstring : 
        public std::string 
    {
        jstring() = default;
        jstring(const std::string&) noexcept(false);
        jstring(std::string&&)      noexcept;

        jstring& operator = (const std::string& _rhs) noexcept(false);
        jstring& operator = (std::string&& _rhs) noexcept;

        // - Note
        //      Support implicit casting 
        operator std::string() noexcept;

    }; // struct json::string

    json::jstring operator ""_js(const char *str, std::size_t len);

    std::ostream& operator<<(std::ostream& _out, 
                             const json::jstring& _name)
        noexcept(false);

    // [ value ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      JSON value interface.
    //      Adapter for various JSON value types
    struct value
    {
        virtual ~value() = default;

        // - Note
        //      **Serialize** the object.
        // - Return
        //      Assume the result is utf8 string.
        // - Exception Safety
        //      Strong exception guarantee
        virtual std::string toUtf8() const noexcept(false) = 0;

        // - Note
        //      Copy construct for the object
        // - Return
        //      Copied object's unique pointer
        virtual ptr<value> clone() const noexcept(false) = 0;

        // - Note
        //      Acquire real type's information
        virtual 
        const std::type_info& info() const
            noexcept = 0;

        // - Note
        //      Acquire inner value's address
        // - Return
        //      `nullptr` : invalid case
        virtual void* vptr() noexcept = 0;

        // - Note
        //      Acquire inner value's const address
        // - Return
        //      `nullptr` : invalid case
        virtual const void* vptr() const noexcept = 0;

    };

    // - Note
    //      convert the value into utf8 string 
    //      and then print via `ostream`
    std::ostream& operator<< (std::ostream& out, 
                              const json::value& _val)
        noexcept(false);


    // [ typed_value ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      Value adapter. Support primitive type's wrapper
    //      원래라면 각 타입마다 다 만들었겠지만... 
    //      그건 너무 손이 바쁘니까... 인생은 짧아요 :)
    // - Form
    //      "hell world!"   // jstring : JSON string
    //      -1234           // i64     : JSON integer
    //      567.89          // f64     : JSON double
    template <typename Type>
    class typed_value: 
        public value 
    {
    public:
        using base_type = Type;
        using self_type = typed_value;

    protected:
        // Type이 const로 추론될 경우 정상적인 사용이 불가능.
        // non-const 멤버변수로 강제함.
        using value_type = std::remove_const_t<base_type>;

        value_type iv;        // inner value

    public:
        explicit typed_value() = default;

        explicit typed_value(const base_type& _value) 
            noexcept(false)
        {
            iv = _value;
        };

        explicit typed_value(base_type&& _value)
            noexcept(false)
        {
            iv = std::move(_value);
        };


        // - Note
        //      **Move** : Modifty inner value
        typed_value& operator =(base_type&& _rhs)
            noexcept 
        {
            iv = std::move(_rhs);
            return *this;
        }

    public:
        virtual
        const std::type_info& info() const noexcept
            override
        {
            return typeid(base_type);
        }

        // - Note
        //      Acquire inner value's pointer
        virtual 
        void* vptr() noexcept 
            override 
        { 
            return &iv; 
        };

        // - Note
        //      Acquire inner value's const pointer
        virtual
        const void* vptr() const noexcept 
            override 
        { 
            return &iv; 
        };

        // - Note
        //      Convert inner value to utf8 `std::string`
        virtual 
        std::string toUtf8() const noexcept(false) 
            override;

        virtual 
        ptr<value> clone() const noexcept(false)
            override;

    };// class typed_value<T>





    template<typename T>
    inline
    ptr<value> typed_value<T>::clone() const noexcept(false)
    {
        base_type copy = iv;

        //auto box = box_value<std::remove_reference_t<base_type>>(std::move(copy));
        auto box = box_value<base_type>(std::move(copy));
        return box;
    }


    // - Note
    //      Convert inner value to utf8 `std::string`
    template<typename T>
    inline 
    std::string typed_value<T>::toUtf8() const
        noexcept(false)
    {
        // StringBuilder
        std::ostringstream sout;

        // delegate the conversion to appropriate
        // `operator <<()` override.
        sout << iv;

        // Build !
        return sout.str();
    }

    // - Note
    //      Template specialization
    //      `base_type` == `json::string`
    template<>
    inline 
    std::string typed_value<json::jstring>::toUtf8() const
        noexcept(false)
    {
        // JSON expression : "string"
        return "\"" + this->iv + "\"";
    }


    template <typename T>
    static
    ptr<value> box_value(T& _base) noexcept(false)
    {
        ptr<value> ptr = nullptr;
        // copy
        ptr = make_ptr<typed_value<T>>(_base);
        return ptr;
    }

    // - Note
    //      Box the given type object into `ptr<value>`
    // 
    //      Boxing작업을 하는 별도의 함수를 만든 이유는
    //      향후 최적화 과정에서 Object pool 또는 
    //      특정 타입 전용 Allocator를 사용하게 될 
    //      가능성이 높기 때문
    // 
    //      보다 유연한 Boxing의 가능성을 제공
    template <typename T>
    static 
    ptr<value> box_value(T&& _base) noexcept(false)
    {
        ptr<value> ptr = nullptr;
        // move
        ptr = make_ptr<typed_value<T>>(std::move(_base));
        return ptr;
    }


}// namespace json


#endif 
