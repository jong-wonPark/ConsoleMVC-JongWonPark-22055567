#include "OrderView.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <format>

void OrderView::displayOrderMenu() const {
    std::cout << "\n--- 주문 관리 ---\n";
    std::cout << "  1. 신규 주문 등록\n";
    std::cout << "  2. 전체 주문 조회\n";
    std::cout << "  3. 주문 승인\n";
    std::cout << "  4. 주문 거절\n";
    std::cout << "  5. 출고 처리\n";
    std::cout << "  6. 출고 완료 처리\n";
    std::cout << "  7. 주문 상세 조회\n";
    std::cout << "  0. 뒤로가기\n";
    std::cout << "선택: ";
}

void OrderView::displayOrderList(const std::vector<Order>& orders) const {
    if (orders.empty()) {
        std::cout << "  조회된 주문이 없습니다.\n";
        return;
    }
    std::cout << std::left
              << std::setw(6)  << "주문번호"
              << std::setw(16) << "고객명"
              << std::setw(12) << "주문일자"
              << std::setw(10) << "상태"
              << std::setw(14) << "금액(USD)"
              << "\n";
    std::cout << std::string(58, '-') << "\n";
    for (const auto& o : orders) {
        std::cout << std::left
                  << std::setw(6)  << o.id
                  << std::setw(16) << o.customerName
                  << std::setw(12) << o.orderDate
                  << std::setw(10) << toString(o.status)
                  << std::setw(14) << std::fixed << std::setprecision(2) << o.totalAmount()
                  << "\n";
    }
}

void OrderView::displayOrderDetail(const Order& order) const {
    std::cout << "\n[주문 상세 - #" << order.id << "]\n";
    std::cout << "  고객: " << order.customerName << " (ID: " << order.customerId << ")\n";
    std::cout << "  주문일: " << order.orderDate << "\n";
    std::cout << "  상태: " << toString(order.status) << "\n";
    if (!order.rejectionReason.empty())
        std::cout << "  거절 사유: " << order.rejectionReason << "\n";
    std::cout << "  ---- 주문 항목 ----\n";
    for (const auto& item : order.items) {
        std::cout << std::format("  {:20s} {:5d}EA x ${:.2f} = ${:.2f}\n",
            item.productName, item.quantity, item.unitPrice, item.subtotal());
    }
    std::cout << std::format("  총액: ${:.2f}\n", order.totalAmount());
}

int OrderView::inputCustomerId() const {
    int id;
    std::cout << "  고객 ID 입력: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

std::vector<std::pair<int,int>> OrderView::inputOrderItems(const std::vector<Product>& products) const {
    displayProductList(products);
    std::vector<std::pair<int,int>> items;
    std::cout << "  제품 ID와 수량을 입력하세요 (0 입력 시 완료):\n";
    while (true) {
        int productId, qty;
        std::cout << "  제품 ID: ";
        std::cin >> productId;
        if (productId == 0) break;
        std::cout << "  수량: ";
        std::cin >> qty;
        items.emplace_back(productId, qty);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return items;
}

int OrderView::inputOrderId(const std::string& prompt) const {
    int id;
    std::cout << "  " << prompt;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

std::string OrderView::inputRejectionReason() const {
    std::string reason;
    std::cout << "  거절 사유 입력: ";
    std::getline(std::cin, reason);
    return reason;
}

void OrderView::showOrderCreated(const Order& order) const {
    std::cout << "  [완료] 주문 #" << order.id << " 이(가) 등록되었습니다.\n";
}

void OrderView::showApproveResult(bool success, int orderId) const {
    if (success) std::cout << "  [완료] 주문 #" << orderId << " 승인되었습니다.\n";
    else         std::cout << "  [오류] 주문 승인 실패 (재고 부족 또는 상태 불일치)\n";
}

void OrderView::showRejectResult(bool success, int orderId) const {
    if (success) std::cout << "  [완료] 주문 #" << orderId << " 거절되었습니다.\n";
    else         std::cout << "  [오류] 주문 거절 실패\n";
}

void OrderView::showShipmentResult(bool success, int orderId) const {
    if (success) std::cout << "  [완료] 주문 #" << orderId << " 출고 처리되었습니다.\n";
    else         std::cout << "  [오류] 출고 처리 실패 (승인 상태 아님)\n";
}

void OrderView::showCompleteResult(bool success, int orderId) const {
    if (success) std::cout << "  [완료] 주문 #" << orderId << " 출고 완료되었습니다. 재고가 차감됩니다.\n";
    else         std::cout << "  [오류] 출고 완료 실패\n";
}

void OrderView::displayCustomerList(const std::vector<Customer>& customers) const {
    std::cout << "\n  [고객 목록]\n";
    for (const auto& c : customers)
        std::cout << "  [" << c.id << "] " << c.name << " - " << c.contactPerson << "\n";
}

void OrderView::displayProductList(const std::vector<Product>& products) const {
    std::cout << "\n  [제품 목록]\n";
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(20) << "제품명"
              << std::setw(10) << "분류"
              << std::setw(12) << "단가(USD)" << "\n";
    std::cout << std::string(47, '-') << "\n";
    for (const auto& p : products)
        std::cout << std::left << std::setw(5) << p.id
                  << std::setw(20) << p.name
                  << std::setw(10) << toString(p.category)
                  << std::fixed << std::setprecision(2) << p.unitPrice << "\n";
}
