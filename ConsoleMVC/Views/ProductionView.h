#pragma once
#include <vector>
#include <string>
#include "../Models/ProductionOrder.h"
#include "../Models/Product.h"

class ProductionView {
public:
    void displayProductionMenu() const;
    void displayProductionList(const std::vector<ProductionOrder>& orders) const;
    void displayProductionDetail(const ProductionOrder& order) const;

    int  inputProductId(const std::vector<Product>& products) const;
    int  inputTargetQuantity() const;
    std::string inputTargetEndDate() const;
    int  inputProductionOrderId(const std::string& prompt = "생산지시 번호 입력: ") const;
    int  inputCompletedQuantity(int max) const;

    void showCreateResult(bool success, const ProductionOrder& po) const;
    void showStatusChangeResult(bool success, const std::string& action) const;
    void showProgressResult(bool success) const;
};
