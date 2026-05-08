#pragma once
#include <string>
#include "Enums.h"

struct ProductionOrder {
    int id = 0;
    int productId = 0;
    std::string productName;
    int targetQuantity = 0;
    int completedQuantity = 0;
    std::string startDate;
    std::string targetEndDate;
    ProductionStatus status = ProductionStatus::Planned;
    std::string remarks;

    double progressRate() const {
        if (targetQuantity == 0) return 0.0;
        return static_cast<double>(completedQuantity) / targetQuantity * 100.0;
    }
};
