#pragma once
#include "../Repositories/ProductRepository.h"
#include "../Repositories/CustomerRepository.h"
#include "../Repositories/OrderRepository.h"
#include "../Repositories/InventoryRepository.h"
#include "../Repositories/ProductionRepository.h"
#include "../Services/OrderService.h"
#include "../Services/InventoryService.h"
#include "../Services/ProductionService.h"
#include "../Views/MainMenuView.h"
#include "OrderController.h"
#include "InventoryController.h"
#include "ProductionController.h"

class AppController {
public:
    AppController();
    void run();

private:
    // Repositories (소유권 보유, 선언 순서 = 초기화 순서)
    ProductRepository    productRepo_;
    CustomerRepository   customerRepo_;
    OrderRepository      orderRepo_;
    InventoryRepository  inventoryRepo_;
    ProductionRepository productionRepo_;

    // Services
    OrderService      orderService_;
    InventoryService  inventoryService_;
    ProductionService productionService_;

    // View
    MainMenuView mainMenuView_;

    // Sub-controllers
    OrderController      orderController_;
    InventoryController  inventoryController_;
    ProductionController productionController_;

    bool isRunning_ = true;

    void handleMenuChoice(int choice);
};
