#include "OrderController.h"
#include <iostream>
#include <limits>

OrderController::OrderController(OrderService& orderService,
                                 CustomerRepository& customerRepo,
                                 ProductRepository& productRepo)
    : orderService_(orderService)
    , customerRepo_(customerRepo)
    , productRepo_(productRepo)
{}

void OrderController::run() {
    while (true) {
        view_.displayOrderMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;
        switch (choice) {
            case 1: handleCreateOrder();     break;
            case 2: handleListOrders();      break;
            case 3: handleApproveOrder();    break;
            case 4: handleRejectOrder();     break;
            case 5: handleProcessShipment(); break;
            case 6: handleCompleteShipment();break;
            case 7: handleViewDetail();      break;
            default: std::cout << "  잘못된 선택입니다.\n"; break;
        }
        std::cout << "\n  Enter를 눌러 계속...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void OrderController::handleCreateOrder() {
    auto customers = customerRepo_.findAll();
    int customerId = view_.inputCustomerId();
    // 고객 유효성 확인
    if (!customerRepo_.findById(customerId)) {
        std::cout << "  [오류] 존재하지 않는 고객 ID입니다.\n";
        return;
    }
    auto products = productRepo_.findAll();
    auto items = view_.inputOrderItems(products);
    if (items.empty()) {
        std::cout << "  [오류] 주문 항목이 없습니다.\n";
        return;
    }
    auto result = orderService_.createOrder(customerId, items);
    if (result) view_.showOrderCreated(*result);
    else        std::cout << "  [오류] 주문 등록 실패 (제품 정보 오류)\n";
}

void OrderController::handleListOrders() {
    auto orders = orderService_.getAllOrders();
    view_.displayOrderList(orders);
}

void OrderController::handleApproveOrder() {
    auto pending = orderService_.getOrdersByStatus(OrderStatus::Pending);
    if (pending.empty()) { std::cout << "  승인 대기 중인 주문이 없습니다.\n"; return; }
    view_.displayOrderList(pending);
    int id = view_.inputOrderId("승인할 주문 번호: ");
    view_.showApproveResult(orderService_.approveOrder(id), id);
}

void OrderController::handleRejectOrder() {
    auto pending = orderService_.getOrdersByStatus(OrderStatus::Pending);
    if (pending.empty()) { std::cout << "  거절할 대기 주문이 없습니다.\n"; return; }
    view_.displayOrderList(pending);
    int id = view_.inputOrderId("거절할 주문 번호: ");
    std::string reason = view_.inputRejectionReason();
    view_.showRejectResult(orderService_.rejectOrder(id, reason), id);
}

void OrderController::handleProcessShipment() {
    auto approved = orderService_.getOrdersByStatus(OrderStatus::Approved);
    if (approved.empty()) { std::cout << "  출고 가능한 주문이 없습니다.\n"; return; }
    view_.displayOrderList(approved);
    int id = view_.inputOrderId("출고 처리할 주문 번호: ");
    view_.showShipmentResult(orderService_.processShipment(id), id);
}

void OrderController::handleCompleteShipment() {
    auto shipping = orderService_.getOrdersByStatus(OrderStatus::Shipping);
    if (shipping.empty()) { std::cout << "  출고 완료할 주문이 없습니다.\n"; return; }
    view_.displayOrderList(shipping);
    int id = view_.inputOrderId("출고 완료할 주문 번호: ");
    view_.showCompleteResult(orderService_.completeShipment(id), id);
}

void OrderController::handleViewDetail() {
    int id = view_.inputOrderId();
    auto orderOpt = orderService_.getOrderById(id);
    if (orderOpt) view_.displayOrderDetail(*orderOpt);
    else          std::cout << "  [오류] 주문을 찾을 수 없습니다.\n";
}
