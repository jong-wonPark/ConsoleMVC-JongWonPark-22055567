#include "ProductionView.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <format>

void ProductionView::displayProductionMenu() const {
    std::cout << "\n--- 생산 관리 ---\n";
    std::cout << "  1. 생산 지시 등록\n";
    std::cout << "  2. 전체 생산 현황 조회\n";
    std::cout << "  3. 생산 시작\n";
    std::cout << "  4. 생산 일시정지\n";
    std::cout << "  5. 생산 진행 수량 업데이트\n";
    std::cout << "  6. 생산 완료 처리\n";
    std::cout << "  0. 뒤로가기\n";
    std::cout << "선택: ";
}

void ProductionView::displayProductionList(const std::vector<ProductionOrder>& orders) const {
    if (orders.empty()) {
        std::cout << "  조회된 생산 지시가 없습니다.\n";
        return;
    }
    std::cout << "\n  [생산 현황]\n";
    std::cout << std::left
              << std::setw(6)  << "지시번호"
              << std::setw(20) << "제품명"
              << std::setw(10) << "목표수량"
              << std::setw(10) << "완료수량"
              << std::setw(10) << "진행률"
              << std::setw(12) << "목표완료일"
              << "상태\n";
    std::cout << std::string(75, '-') << "\n";
    for (const auto& po : orders) {
        std::cout << std::left
                  << std::setw(6)  << po.id
                  << std::setw(20) << po.productName
                  << std::setw(10) << po.targetQuantity
                  << std::setw(10) << po.completedQuantity
                  << std::setw(10) << std::format("{:.1f}%", po.progressRate())
                  << std::setw(12) << po.targetEndDate
                  << toString(po.status) << "\n";
    }
}

void ProductionView::displayProductionDetail(const ProductionOrder& po) const {
    std::cout << "\n[생산 지시 상세 - #" << po.id << "]\n";
    std::cout << "  제품: " << po.productName << " (ID: " << po.productId << ")\n";
    std::cout << "  목표수량: " << po.targetQuantity << "\n";
    std::cout << "  완료수량: " << po.completedQuantity << "\n";
    std::cout << std::format("  진행률: {:.1f}%\n", po.progressRate());
    std::cout << "  시작일: " << po.startDate << "\n";
    std::cout << "  목표완료일: " << po.targetEndDate << "\n";
    std::cout << "  상태: " << toString(po.status) << "\n";
    if (!po.remarks.empty())
        std::cout << "  비고: " << po.remarks << "\n";
}

int ProductionView::inputProductId(const std::vector<Product>& products) const {
    std::cout << "\n  [제품 목록]\n";
    for (const auto& p : products)
        std::cout << "  [" << p.id << "] " << p.name << "\n";
    int id;
    std::cout << "  제품 ID 입력: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

int ProductionView::inputTargetQuantity() const {
    int qty;
    std::cout << "  목표 수량 입력: ";
    std::cin >> qty;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return qty;
}

std::string ProductionView::inputTargetEndDate() const {
    std::string date;
    std::cout << "  목표 완료일 입력 (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    return date;
}

int ProductionView::inputProductionOrderId(const std::string& prompt) const {
    int id;
    std::cout << "  " << prompt;
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

int ProductionView::inputCompletedQuantity(int max) const {
    int qty;
    std::cout << "  현재까지 완료된 수량 입력 (최대 " << max << "): ";
    std::cin >> qty;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return qty;
}

void ProductionView::showCreateResult(bool success, const ProductionOrder& po) const {
    if (success) std::cout << "  [완료] 생산 지시 #" << po.id << " (" << po.productName << ") 등록되었습니다.\n";
    else         std::cout << "  [오류] 생산 지시 등록 실패\n";
}

void ProductionView::showStatusChangeResult(bool success, const std::string& action) const {
    if (success) std::cout << "  [완료] " << action << " 처리되었습니다.\n";
    else         std::cout << "  [오류] " << action << " 처리 실패 (상태 불일치)\n";
}

void ProductionView::showProgressResult(bool success) const {
    if (success) std::cout << "  [완료] 생산 진행 수량이 업데이트되었습니다.\n";
    else         std::cout << "  [오류] 진행 수량 업데이트 실패\n";
}
