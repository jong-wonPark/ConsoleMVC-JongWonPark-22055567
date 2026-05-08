#pragma once
#include <vector>
#include <optional>
#include "../Models/Inventory.h"

class InventoryRepository {
public:
    InventoryRepository();

    std::vector<InventoryItem> findAll() const;
    std::optional<InventoryItem> findByProductId(int productId) const;
    std::vector<InventoryItem> findLowStock() const;
    InventoryItem save(const InventoryItem& item);
    bool updateQuantity(int productId, int delta);
    bool updateReserved(int productId, int delta);

private:
    std::vector<InventoryItem> data_;

    void seedData();
};
