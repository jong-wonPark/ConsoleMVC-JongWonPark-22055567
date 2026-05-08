#pragma once
#include <string>
#include <vector>
#include "../Models/Order.h"
#include "../Models/Product.h"
#include "../Models/Customer.h"

class OrderView {
public:
    // 메뉴
    void displayOrderMenu() const;

    // 목록 조회
    void displayOrderList(const std::vector<Order>& orders) const;
    void displayOrderDetail(const Order& order) const;

    // 입력 폼
    int  inputCustomerId() const;
    std::vector<std::pair<int,int>> inputOrderItems(const std::vector<Product>& products) const;
    int  inputOrderId(const std::string& prompt = "주문 번호 입력: ") const;
    std::string inputRejectionReason() const;

    // 결과 출력
    void showOrderCreated(const Order& order) const;
    void showApproveResult(bool success, int orderId) const;
    void showRejectResult(bool success, int orderId) const;
    void showShipmentResult(bool success, int orderId) const;
    void showCompleteResult(bool success, int orderId) const;

    // 고객/제품 보조 출력
    void displayCustomerList(const std::vector<Customer>& customers) const;
    void displayProductList(const std::vector<Product>& products) const;
};
