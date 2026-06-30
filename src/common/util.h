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