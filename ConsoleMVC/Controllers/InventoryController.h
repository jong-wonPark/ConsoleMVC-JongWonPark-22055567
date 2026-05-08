#pragma once
#include "../Services/InventoryService.h"
#include "../Repositories/ProductRepository.h"
#include "../Views/InventoryView.h"

class InventoryController {
public:
    InventoryController(InventoryService& inventoryService,
                        ProductRepository& productRepo);

    void run();

private:
    InventoryService& inventoryService_;
    ProductRepository& productRepo_;
    InventoryView view_;

    void handleViewAll();
    void handleViewLowStock();
    void handleAdjustQuantity();
};
