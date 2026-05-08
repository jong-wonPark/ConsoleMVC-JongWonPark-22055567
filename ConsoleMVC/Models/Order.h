#pragma once
#include <string>
#include <vector>
#include "Enums.h"
#include "OrderItem.h"

struct Order {
    int id = 0;
    int customerId = 0;
    std::string customerName;
    std::string orderDate;
    OrderStatus status = OrderStatus::Pending;
    std::vector<OrderItem> items;
    std::string rejectionReason;
    std::string notes;

    double totalAmount() const {
        double total = 0.0;
        for (const auto& item : items)
            total += item.subtotal();
        return total;
    }
};
