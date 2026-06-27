#pragma once

#include <unordered_map>

enum Category {
    PHYSICAL,
    SPECIAL,
    STATUS
};

static const std::unordered_map<std::string, Category> STRING_TO_CATEGORY_MAP{
        {"physical", PHYSICAL},
        {"special", SPECIAL},
        {"status", STATUS}
};
