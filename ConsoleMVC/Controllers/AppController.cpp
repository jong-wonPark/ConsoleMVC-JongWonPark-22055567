#include "AppController.h"
#include <iostream>

AppController::AppController()
    : orderService_     (orderRepo_, inventoryRepo_, customerRepo_, productRepo_)
    , inventoryService_ (inventoryRepo_)
    , productionService_(productionRepo_, inventoryRepo_, productRepo_)
    , orderController_     (orderService_,      customerRepo_, productRepo_)
    , inventoryController_ (inventoryService_,  productRepo_)
    , productionController_(productionService_,  productRepo_)
{}

void AppController::run() {
    while (isRunning_) {
        mainMenuView_.displayBanner();
        mainMenuView_.displayMainMenu();
        int choice = mainMenuView_.getMenuChoice(0, 3);
        handleMenuChoice(choice);
    }
    std::cout << "\ns-semi 시스템을 종료합니다. 안녕히 가세요!\n";
}

void AppController::handleMenuChoice(int choice) {
    switch (choice) {
        case 1: orderController_.run();      break;
        case 2: inventoryController_.run();  break;
        case 3: productionController_.run(); break;
        case 0: isRunning_ = false;          break;
    }
}
