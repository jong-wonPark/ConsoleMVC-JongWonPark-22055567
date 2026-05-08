#include "InventoryController.h"
#include <iostream>
#include <limits>

InventoryController::InventoryController(InventoryService& inventoryService,
                                         ProductRepository& productRepo)
    : inventoryService_(inventoryService)
    , productRepo_(productRepo)
{}

void InventoryController::run() {
    while (true) {
        view_.displayInventoryMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;
        switch (choice) {
            case 1: handleViewAll();         break;
            case 2: handleViewLowStock();    break;
            case 3: handleAdjustQuantity();  break;
            default: std::cout << "  잘못된 선택입니다.\n"; break;
        }
        std::cout << "\n  Enter를 눌러 계속...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void InventoryController::handleViewAll() {
    auto items    = inventoryService_.getAllInventory();
    auto products = productRepo_.findAll();
    view_.displayInventoryList(items, products);
}

void InventoryController::handleViewLowStock() {
    auto items    = inventoryService_.getLowStockItems();
    auto products = productRepo_.findAll();
    view_.displayLowStockList(items, products);
}

void InventoryController::handleAdjustQuantity() {
    int productId = view_.inputProductId();
    if (!inventoryService_.getByProductId(productId)) {
        std::cout << "  [오류] 해당 제품의 재고 정보가 없습니다.\n";
        return;
    }
    int delta = view_.inputQuantityDelta();
    bool result = inventoryService_.adjustQuantity(productId, delta, "수동조정");
    view_.showAdjustResult(result);
}
