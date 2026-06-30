#pragma once

#include <unordered_map>

enum class Category {
    PHYSICAL,
    SPECIAL,
    STATUS
};

inline const std::unordered_map<std::string, Category> STRING_TO_CATEGORY_MAP{
        {"physical", Category::PHYSICAL},
        {"special", Category::SPECIAL},
        {"status", Category::STATUS}
};
