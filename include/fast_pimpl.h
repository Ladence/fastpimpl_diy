#pragma once

#include <type_traits>

namespace fast_pimpl {
template<typename T, std::size_t Size, std::size_t Alignment>
class pimpl
{
    template<std::size_t ActualSize, std::size_t ActualAlignment>
    static void validate()
    {
        static_assert(Size == ActualSize, "Size and sizeof(T) doesn't match!");
        static_assert(Alignment == ActualAlignment, "Alignment and alignof(T) doesn't match");
    }

    T* ptr() { return reinterpret_cast<T*>(&m_implStrg); }

    const T* ptr() const noexcept { return reinterpret_cast<const T*>(&m_implStrg); }

public:
    pimpl(const pimpl& rhs) {
        new (ptr()) T(*rhs);
    }

    pimpl(pimpl&& rhs) noexcept {
        new (ptr()) T(std::move(*rhs));
    }

    pimpl& operator=(const pimpl& rhs) {
        *ptr() = *rhs;
        return *this;
    }

    pimpl& operator=(pimpl&& rhs) noexcept {
        *ptr() = std::move(*rhs);
        return *this;
    }

    template<typename... TArgs>
    explicit pimpl(TArgs&&... args)
    {
        new (ptr()) T(std::forward<TArgs>(args)...);
    }

    ~pimpl()
    {
        validate<sizeof(T), alignof(T)>();
        ptr()->~T();
    }

    T* operator->()
    {
        return ptr();
    }

    const T* operator->() const noexcept
    {
        return ptr();
    }

    T& operator*()
    {
        return *ptr();
    }

    const T& operator*() const noexcept
    {
        return *ptr();
    }
private:
    std::aligned_storage<Size, Alignment> m_implStrg;
};
}