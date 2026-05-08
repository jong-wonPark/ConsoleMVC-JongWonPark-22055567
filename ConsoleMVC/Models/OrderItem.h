#pragma once
#include <string>

struct OrderItem {
    int productId = 0;
    std::string productName;
    int quantity = 0;
    double unitPrice = 0.0;

    double subtotal() const { return static_cast<double>(quantity) * unitPrice; }
};
