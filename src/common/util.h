#pragma once
#include <stdexcept>

template<typename T>
void ensure_not_null(T* t) {
    if (t == nullptr) {
        throw std::runtime_error{"t was null"};
    }
}

template<typename T>
constexpr int to_int(T t) {
    return static_cast<int>(t);
}

template <typename... H>
std::size_t hash_combine(std::size_t seed, const H... h) {
    return (
        (seed = seed ^ (h + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2))),
        ...
    );
}