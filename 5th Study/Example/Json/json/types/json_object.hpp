// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ====
// 
//  File    : json_object.hpp
//  Author  : Park  Dong Ha ( luncliff@gmail.com )
//  Updated : 16/08/18
//
//  Note
//      Definitions for JSON object.
//      Later optimization is required
//  Types
//    - `json::object`    : JSON object class
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
#ifndef _JSON_OBJECT_HPP_
#define _JSON_OBJECT_HPP_

#include <tuple>
#include "./json_base.hpp"

namespace json
{
    // [ json::object ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      JSON object 
    //      This implementation uses `std::vector<T>` for
    //      simplicity. 
    class object :
        public json::value
    {
    public:
        // [ object::property ]
        class property;

        using elem_type = property;
        using container = std::vector<elem_type>;
        using self_type = json::object;
        using iter_type       = container::iterator;
        using const_iter_type = container::const_iterator;

    private:
        container props; // property list

        // pointer to prototype
        self_type* proto = nullptr;

    protected:
        // - Note
        //      json에서 property를 탐색하는 이유는 
        //      값의 변경(non-const)일 가능성이 높으므로
        //      향후 최적화에서 이 부분을 고려하여야 함
        iter_type find(const std::string& _prop_name)
            noexcept;

        // - Note
        //      const 함수 내에서 find를 사용하기 위해서는
        //      상수성을 지원하는 find또한 존재해야 한다.
        const_iter_type find(const std::string& _prop_name) const
            noexcept;

    public:
        explicit object() = default;

        // - Note
        //      현재 object Instance를 UTF8 JSON 으로 변환한다.
        // - See also
        //      `operator<< (object&)`
        virtual
        std::string toUtf8() const noexcept(false)
            override;

        virtual
        const std::type_info& info() const noexcept
            override;
        
        virtual void*       vptr() noexcept override;
        virtual const void* vptr() const noexcept override;


        // - Note
        //      Copy construct for the object
        // - Return
        //      Copied object's unique pointer
        virtual 
        ptr<value> clone() const noexcept(false)
            override;

        // - Note
        //      코드 작성 시점에 value의 타입이 명확하지 않을 수 있다.
        //      Tvalue 템플릿을 이용해 pair를 만들고, 이를 property list에 
        //      추가하는 Generic 접근법을 취한다.
        template <typename T>
        void set(const std::string& _name, T&& _value)
            noexcept(false);

        // - Note
        //      이미 Boxing된 값을 전달하는 경우
        void set(const std::string& _name, ptr<value>&& _value)
            noexcept(false);

        // - Note
        //      특정 속성에 대해 임의의 타입으로 캐스팅을 시도한다.
        //      속성이 존재하지 않거나, 타입이 맞지 않을 경우
        //      nullptr를 반환한다.
        // - Return
        //      nullptr : type mismatch, missing property
        //      Out&    : type matched
        // - Note
        //      Q. 포인터인 이유?
        //      A. value가 virtual한 타입일 가능성이 있으므로
        //         reference를 반환하면 nullptr exception을 막기 위해
        //         예외처리를 강제해야 함.
        template <typename Out>
        Out*       get(const std::string& _pname)
            noexcept(false);

        // - Note
        //      get operation for constant instance
        template <typename Out>
        const Out* get(const std::string& _pname) const
            noexcept(false);

        // - Note
        //      the number of properties in current list
        size_t count() const noexcept;


        void          prototype(json::object& _proto) noexcept;

        object*       prototype() noexcept;
        const object* prototype() const noexcept;

    };


    // [ object::property ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
    // - Note
    //      Object's property( name-value pair)
    //      Bridge pattern(pointer to implementation)
    // - Form
    //      "name" : value(utf8)
    class object::property :
        public std::pair<jstring, ptr<json::value>>
    {
    public:
        using value_ptr = ptr<json::value>;
        // first  : name
        // second : pimpl to value
        using base_type = std::pair<jstring, ptr<json::value>>;
        using self_type = property;

    public:
        // - Note
        //      `속성 이름`만큼은 JSON 표기에서 빈 문자열을 
        //      허용할 수 없으므로, 이에 대한 검사를 수행한다.
        explicit property(json::jstring&& _name,
                          value_ptr&& _ptr)
            noexcept(false);

        // - Note
        //      Copy constructor with `clone()`
        property(const property& _rhs)  noexcept(false);

        // - Note
        //      Move constructor with `clone()`
        property(property&& _rhs)       noexcept;


        property& operator=(const property& _rhs) noexcept(false);
        property& operator=(property&& _rhs) noexcept;


        // - Note
        //      Overlap current pimpl.
        property& operator =(value_ptr&& _rhs) noexcept;


        // - Note
        //      Protect property's name via const reference
        const json::jstring& name() const
            noexcept;

        json::value&       value();
        const json::value& value() const;

    };

    // - Note
    //      Print `property` class via `std::ostream`
    std::ostream& operator<< (std::ostream& out,
                              const object::property& _prop)
        noexcept(false);


    template <typename Out>
    inline
    Out*        object::get(const std::string& _pname)
        noexcept(false) 
    {
        auto iter = this->find(_pname);
        // not fount
        if (iter == this->props.end()) {
            return nullptr;
        }

        auto& val = iter->value();

        if (val.info() == typeid(Out)) {
            Out* ptr = reinterpret_cast<Out*>(val.vptr());
            // return pointer
            return ptr;
        }
        else {
            return nullptr;
        }
    }

    template <typename Out>
    inline
    const Out*  object::get(const std::string& _pname) const
        noexcept(false)
    {
        auto iter = this->find(_pname);
        // not found
        if (iter == this->props.end()) {
            return nullptr;
        }

        const auto& val = iter->value();

        // Compare type_info
        if (val.info() == typeid(Out)) {
            const Out* ptr = reinterpret_cast<const Out*>(val.vptr());
            return ptr;
        }
        else {
            return nullptr;
        }
    }

    // - Note
    //      코드 작성 시점에 value의 타입이 명확하지 않을 수 있다.
    //      Tvalue 템플릿을 이용해 pair를 만들고, 이를 property list에 
    //      추가하는 Generic 접근법을 취한다.
    template<typename T>
    inline 
    void object::set(const std::string& _name, T&& _value)
        noexcept(false)
    {
        auto iter = this->find(_name);
        // Boxing
        ptr<value> pval = nullptr;

        // l-value reference. copy the object
        if (std::is_lvalue_reference<T>::value) {
            pval = box_value(_value);
        }
        // r-value reference
        else {
            pval = box_value(std::move(_value));
        }

        // case : Found
        if (iter != this->props.end()) {
            *iter = std::move(pval);
        }
        else {
            object::property pair { _name, std::move(pval) };
            this->props.emplace_back(std::move(pair));
        }
    }

    // - Note
    //      `object`는 `value`의 확장타입이므로, 자체 구현된 멤버함수
    //      `toUtf8()`을 사용하여 문자열로 **변환한 후** 출력한다.
    // 
    //      변환하는 과정에서 문제가 발생할 경우 `std::ostream&`에 대한 
    //      **Strong Exception Guarantee**를 지원할 수 있게 된다.
    //
    // -  See also
    //      `object::toUtf8()`
    std::ostream& operator<< (std::ostream& out, 
                              const json::object& _object)
        noexcept(false);

}// namespace json

#endif
