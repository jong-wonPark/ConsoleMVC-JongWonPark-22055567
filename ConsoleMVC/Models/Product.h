#pragma once
#include <string>
#include "Enums.h"

struct Product {
    int id = 0;
    std::string code;
    std::string name;
    ProductCategory category = ProductCategory::Other;
    double unitPrice = 0.0;   // USD
    std::string unit;         // 단위 (EA, Lot 등)
    std::string description;
};
