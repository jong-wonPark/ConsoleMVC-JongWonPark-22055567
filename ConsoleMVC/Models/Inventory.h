#pragma once
#include <string>

struct InventoryItem {
    int productId = 0;
    std::string productName;
    int quantity = 0;         // 실재고
    int minStockLevel = 0;    // 최소 재고 기준
    int reservedQuantity = 0; // 출고 예약 수량

    int availableQuantity() const { return quantity - reservedQuantity; }
    bool isLowStock() const { return quantity <= minStockLevel; }
};
