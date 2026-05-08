#include "InventoryView.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

void InventoryView::displayInventoryMenu() const {
    std::cout << "\n--- 재고 관리 ---\n";
    std::cout << "  1. 전체 재고 현황 조회\n";
    std::cout << "  2. 재고 부족 품목 조회\n";
    std::cout << "  3. 재고 수량 직접 조정\n";
    std::cout << "  0. 뒤로가기\n";
    std::cout << "선택: ";
}

static const Product* findProduct(const std::vector<Product>& products, int productId) {
    for (const auto& p : products)
        if (p.id == productId) return &p;
    return nullptr;
}

void InventoryView::displayInventoryList(const std::vector<InventoryItem>& items,
                                         const std::vector<Product>& products) const {
    if (items.empty()) {
        std::cout << "  재고 데이터가 없습니다.\n";
        return;
    }
    std::cout << "\n  [전체 재고 현황]\n";
    std::cout << std::left
              << std::setw(5)  << "제품ID"
              << std::setw(20) << "제품명"
              << std::setw(10) << "실재고"
              << std::setw(10) << "예약수량"
              << std::setw(10) << "가용수량"
              << std::setw(10) << "최소기준"
              << "상태\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& item : items) {
        auto* p = findProduct(products, item.productId);
        std::string name = p ? p->name : "알수없음";
        std::string status = item.isLowStock() ? "[부족!]" : "정상";
        std::cout << std::left
                  << std::setw(5)  << item.productId
                  << std::setw(20) << name
                  << std::setw(10) << item.quantity
                  << std::setw(10) << item.reservedQuantity
                  << std::setw(10) << item.availableQuantity()
                  << std::setw(10) << item.minStockLevel
                  << status << "\n";
    }
}

void InventoryView::displayLowStockList(const std::vector<InventoryItem>& items,
                                        const std::vector<Product>& products) const {
    if (items.empty()) {
        std::cout << "  재고 부족 품목이 없습니다.\n";
        return;
    }
    std::cout << "\n  [재고 부족 품목]\n";
    for (const auto& item : items) {
        auto* p = findProduct(products, item.productId);
        std::string name = p ? p->name : "알수없음";
        std::cout << "  제품ID: " << item.productId
                  << " | " << name
                  << " | 현재: " << item.quantity
                  << " | 최소기준: " << item.minStockLevel << "\n";
    }
}

int InventoryView::inputProductId() const {
    int id;
    std::cout << "  제품 ID 입력: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

int InventoryView::inputQuantityDelta() const {
    int delta;
    std::cout << "  조정 수량 입력 (입고 +, 폐기 -): ";
    std::cin >> delta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return delta;
}

void InventoryView::showAdjustResult(bool success) const {
    if (success) std::cout << "  [완료] 재고가 조정되었습니다.\n";
    else         std::cout << "  [오류] 재고 조정 실패\n";
}
