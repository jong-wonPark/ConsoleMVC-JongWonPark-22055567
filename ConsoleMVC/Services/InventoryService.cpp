#include "InventoryService.h"

InventoryService::InventoryService(InventoryRepository& inventoryRepo)
    : inventoryRepo_(inventoryRepo)
{}

std::vector<InventoryItem> InventoryService::getAllInventory() const {
    return inventoryRepo_.findAll();
}

std::optional<InventoryItem> InventoryService::getByProductId(int productId) const {
    return inventoryRepo_.findByProductId(productId);
}

std::vector<InventoryItem> InventoryService::getLowStockItems() const {
    return inventoryRepo_.findLowStock();
}

bool InventoryService::adjustQuantity(int productId, int delta, const std::string& /*reason*/) {
    return inventoryRepo_.updateQuantity(productId, delta);
}

bool InventoryService::receiveFromProduction(int productId, int quantity) {
    return inventoryRepo_.updateQuantity(productId, quantity);
}
