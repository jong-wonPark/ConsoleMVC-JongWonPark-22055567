#pragma once
#include <vector>
#include <optional>
#include "../Models/Inventory.h"
#include "../Repositories/InventoryRepository.h"

class InventoryService {
public:
    explicit InventoryService(InventoryRepository& inventoryRepo);

    std::vector<InventoryItem> getAllInventory() const;
    std::optional<InventoryItem> getByProductId(int productId) const;
    std::vector<InventoryItem> getLowStockItems() const;

    // 재고 수량 직접 조정 (입고/폐기 등)
    bool adjustQuantity(int productId, int delta, const std::string& reason);

    // 생산 완료 시 재고 입고
    bool receiveFromProduction(int productId, int quantity);

private:
    InventoryRepository& inventoryRepo_;
};
