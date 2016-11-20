#include "./json_array.hpp"

namespace json 
{
    array::array(const array & _arr) noexcept(false)
    {
        this->vlist.reserve(_arr.vlist.size());
        for (const auto& elem : _arr.vlist) {
            this->vlist.emplace_back(elem->clone());
        }
    }

    array & array::operator=(const array & _arr) noexcept(false)
    {
        // Clear and reserve
        this->vlist.clear();
        this->vlist.reserve(_arr.vlist.size());

        // Clone
        for (const auto& elem : _arr.vlist) {
            this->vlist.emplace_back(elem->clone());
        }
        return *this;
    }


    size_t array::size() const noexcept
    {
        return this->vlist.size();
    }

    // - Note
    //      Append the boxed value
    void array::append(ptr<json::value>&& _box)
    {
        // object, Pair is not copy assignable
        vlist.emplace_back(std::move(_box));
    }


    // - Note
    //      현재 보유한 Object 들을 UTF8 JSON 으로 변환한다.
    // - See also
    //      `operator<< (Object&)`
    std::string array::toUtf8() const noexcept(false)
    {
        // StringBuilder
        std::ostringstream sout;

        sout << u8"[ "; // start array

        int i = 1;
        for (const auto& elem : vlist) {
            sout << elem->toUtf8();

            if (i != vlist.size()) {
                sout << u8", ";
            }
            i++;
        }

        sout << u8" ]"; // end array

        return sout.str();
    }

    ptr<value> array::clone() const noexcept(false)
    {
        self_type copy = *this;
        return box_value(std::move(copy));
    }

    const type_info& array::info() const noexcept
    {
        return typeid(self_type);
    }

    // - Note
    //      Acquire inner value's pointer
    void* array::vptr() noexcept
    {
        return this;
    };

    // - Note
    //      Acquire inner value's const pointer
    const void* array::vptr() const noexcept
    {
        return this;
    };


}

