#include "ProductionController.h"
#include <iostream>
#include <limits>

ProductionController::ProductionController(ProductionService& productionService,
                                           ProductRepository& productRepo)
    : productionService_(productionService)
    , productRepo_(productRepo)
{}

void ProductionController::run() {
    while (true) {
        view_.displayProductionMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;
        switch (choice) {
            case 1: handleCreateOrder();      break;
            case 2: handleViewAll();          break;
            case 3: handleStartProduction();  break;
            case 4: handlePauseProduction();  break;
            case 5: handleUpdateProgress();   break;
            case 6: handleCompleteProduction();break;
            default: std::cout << "  잘못된 선택입니다.\n"; break;
        }
        std::cout << "\n  Enter를 눌러 계속...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void ProductionController::handleCreateOrder() {
    auto products = productRepo_.findAll();
    int  productId    = view_.inputProductId(products);
    int  targetQty    = view_.inputTargetQuantity();
    auto targetEndDate = view_.inputTargetEndDate();

    auto result = productionService_.createProductionOrder(productId, targetQty, targetEndDate);
    view_.showCreateResult(result.has_value(), result.value_or(ProductionOrder{}));
}

void ProductionController::handleViewAll() {
    auto orders = productionService_.getAllOrders();
    view_.displayProductionList(orders);
}

void ProductionController::handleStartProduction() {
    auto planned = productionService_.getOrdersByStatus(ProductionStatus::Planned);
    if (planned.empty()) { std::cout << "  시작 가능한 생산 지시가 없습니다.\n"; return; }
    view_.displayProductionList(planned);
    int id = view_.inputProductionOrderId("시작할 생산 지시 번호: ");
    view_.showStatusChangeResult(productionService_.startProduction(id), "생산 시작");
}

void ProductionController::handlePauseProduction() {
    auto inProgress = productionService_.getOrdersByStatus(ProductionStatus::InProgress);
    if (inProgress.empty()) { std::cout << "  진행 중인 생산 지시가 없습니다.\n"; return; }
    view_.displayProductionList(inProgress);
    int id = view_.inputProductionOrderId("일시정지할 생산 지시 번호: ");
    view_.showStatusChangeResult(productionService_.pauseProduction(id), "생산 일시정지");
}

void ProductionController::handleUpdateProgress() {
    int id = view_.inputProductionOrderId("진행 업데이트할 생산 지시 번호: ");
    auto poOpt = productionService_.getOrderById(id);
    if (!poOpt) { std::cout << "  [오류] 생산 지시를 찾을 수 없습니다.\n"; return; }
    view_.displayProductionDetail(*poOpt);
    int completed = view_.inputCompletedQuantity(poOpt->targetQuantity);
    view_.showProgressResult(productionService_.updateProgress(id, completed));
}

void ProductionController::handleCompleteProduction() {
    auto active = productionService_.getOrdersByStatus(ProductionStatus::InProgress);
    auto paused = productionService_.getOrdersByStatus(ProductionStatus::Paused);
    active.insert(active.end(), paused.begin(), paused.end());
    if (active.empty()) { std::cout << "  완료 처리할 생산 지시가 없습니다.\n"; return; }
    view_.displayProductionList(active);
    int id = view_.inputProductionOrderId("완료 처리할 생산 지시 번호: ");
    bool result = productionService_.completeProduction(id);
    view_.showStatusChangeResult(result, "생산 완료");
    if (result) std::cout << "  완료 수량이 자동으로 재고에 반영되었습니다.\n";
}
