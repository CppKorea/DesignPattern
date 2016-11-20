#pragma once
#include <memory>
#include <new>

namespace Pattern
{
    // - Note
    //      Minimal allocator interface, use `std::allocator` if possible.
    template <typename T>
    struct allocator
    {
    protected:
        allocator() = default;
        ~allocator() = default;

    public:
        virtual T*      allocate()               noexcept = 0;
        virtual T*      allocate(const std::size_t n)  noexcept = 0;
        virtual void    deallocate(T* _addr, 
                                   const std::size_t _n)  noexcept = 0;
    };

    // - Note
    //      Simple heap(dynamic memory) allocator
    // - Dependency
    //      `std::calloc`
    //      `std::free`
    template <typename T>
    class HeapAllocator : 
            public allocator<T>
    {
    public:
        T* allocate() noexcept 
            override
        {
            void* res = std::calloc(1, sizeof(T));
            return reinterpret_cast<T*>(res);
        }

        T* allocate(std::size_t _n)  noexcept
            override
        {
            void* res = std::calloc(_n, sizeof(T));
            return reinterpret_cast<T*>(res);
        }


        void deallocate(T* _addr, 
                        const std::size_t _n) noexcept
            override
        {
            // Ignore nullptr
            if (_addr == nullptr) { return; }

            // Invoke destructors
            for (int i = 0; i < _n; ++i) {
                _addr[i].~T();
            }
            // Resource release
            std::free(_addr);
        }
    
    };


}// namespace Pattern
