#include "./json_object.hpp"

namespace json
{

    // [ object::property ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    object::property::property(json::jstring && _name, 
                               value_ptr && _ptr) noexcept(false):
        base_type{std::make_pair(std::move(_name), std::move(_ptr))}
    {
        if ((first.length() == 0)
            || (second == nullptr))
        {
            throw std::invalid_argument{ typeid(self_type).name() };
        }
    }

    object::property::property(const property& _rhs) noexcept(false) :
        base_type{ std::make_pair(_rhs.first, 
                                  _rhs.second->clone()) }
    {}

    object::property::property(property && _rhs) noexcept:
        base_type{std::move(_rhs)}
    {}


    object::property& 
        object::property::operator=(const object::property& _rhs) noexcept(false)
    {
        this->first = _rhs.first;
        this->second = std::move(_rhs.second->clone());
        return *this;
    }

    object::property& 
        object::property::operator=(object::property&& _rhs) noexcept
    {
        this->first = _rhs.first;
        this->second = std::move(_rhs.second->clone());
        return *this;
    }


    // - Note
    //      Protect property's name via const reference

    const json::jstring & object::property::name() const noexcept
    {
        return this->first;
    }

    json::value & object::property::value() 
    { 
        return *second; 
    }

    const json::value & object::property::value() const 
    { 
        return *second;
    }


    // - Note
    //      Overlap current pimpl.
    object::property& object::property::operator =(ptr<json::value>&& _rhs)
        noexcept
    {
        // ignore invalid argument
        if (_rhs != nullptr) {
            // smart pointer. 
            // just follow move semantic
            this->second = std::move(_rhs);
        }
        return *this;
    }


    std::ostream & operator<<(std::ostream & out, 
                              const object::property & _prop) 
        noexcept(false)
    {
        // "name" : value
        out << _prop.name() << u8" : "
            << _prop.value().toUtf8();
        return out;
    }




    // [ object ]
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

    object::iter_type
        object::find(const std::string& _pname)
        noexcept
    {
        auto iter = std::find_if(props.begin(), props.end(),
            [&](const elem_type& _pair)
        {
            return (_pair.name() == _pname);
        });

        return iter;
    }

    object::const_iter_type
        object::find(const std::string& _pname) const
        noexcept
    {
        auto iter = std::find_if(props.begin(), props.end(),
            [&](const elem_type& _pair)
        {
            return (_pair.name() == _pname);
        });

        return iter;
    }




    // - Note
    //      현재 object Instance를 UTF8 JSON 으로 변환한다.
    // - See also
    //      `operator<< (object&)`
    std::string object::toUtf8() const 
        noexcept(false)
    {
        // StringBuilder
        std::ostringstream sout;

        sout << u8"{ ";  // begin object

        size_t i = 1;
        for (const auto& elem : props) 
        {
            sout << elem;

            if (i < props.size()) {
                sout << u8", ";
            }
            i++;
        }
        sout << u8" }";  // end object

        return sout.str();
    }

    ptr<json::value> object::clone() const noexcept(false)
    {
        return box_value(*this);
    }

    const std::type_info& object::info() const
        noexcept
    {
        return typeid(self_type);
    }

    // - Note
    //      Acquire inner value's pointer
    void* object::vptr() noexcept
    {
        return this;
    };

    // - Note
    //      Acquire inner value's const pointer
    const void* object::vptr() const noexcept
    {
        return this;
    };

    void object::set(const std::string& _name,
                     ptr<value>&&       _value)
        noexcept(false)
    {
        iter_type iter = this->find(_name);

        // case : Found
        if (iter != this->props.end()) {
            iter->second = std::move(_value);
        }
        // case : Not found
        else {
            // elem_type == json::property
            elem_type pair { _name, std::move(_value) };

            props.emplace_back(std::move(pair));
        }
    }

    size_t object::count() const noexcept
    {
        return this->props.size();
    }

    void object::prototype(json::object & _proto) noexcept
    {
        this->proto = &_proto;
    }

    object *        object::prototype() noexcept
    {
        return this->proto;
    }

    const object *  object::prototype() const noexcept
    {
        return this->proto;
    }







    // - Note
    //      `object`는 `Value`의 확장타입이므로, 자체 구현된 멤버함수
    //      `toUtf8()`을 사용하여 문자열로 **변환한 후** 출력한다.
    // 
    //      변환하는 과정에서 문제가 발생할 경우 `std::ostream&`에 대한 
    //      **Strong Exception Guarantee**를 지원할 수 있게 된다.
    //
    // -  See also
    //      `object::toUtf8()`
    std::ostream& operator<< (std::ostream& out, 
                              const json::object& _object)
        noexcept(false)
    {
        out << _object.toUtf8();
        return out;
    }



}// namespace json


