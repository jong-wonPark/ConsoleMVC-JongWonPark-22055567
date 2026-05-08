#pragma once
#include <vector>
#include "../Models/Inventory.h"
#include "../Models/Product.h"

class InventoryView {
public:
    void displayInventoryMenu() const;
    void displayInventoryList(const std::vector<InventoryItem>& items,
                              const std::vector<Product>& products) const;
    void displayLowStockList(const std::vector<InventoryItem>& items,
                             const std::vector<Product>& products) const;

    int  inputProductId() const;
    int  inputQuantityDelta() const;
    void showAdjustResult(bool success) const;
};
