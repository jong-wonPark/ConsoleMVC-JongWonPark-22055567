#pragma once
#include <vector>
#include <optional>
#include <string>
#include "../Models/ProductionOrder.h"
#include "../Repositories/ProductionRepository.h"
#include "../Repositories/InventoryRepository.h"
#include "../Repositories/ProductRepository.h"

class ProductionService {
public:
    ProductionService(ProductionRepository& productionRepo,
                      InventoryRepository& inventoryRepo,
                      ProductRepository& productRepo);

    // 생산 지시 등록
    std::optional<ProductionOrder> createProductionOrder(int productId,
                                                         int targetQuantity,
                                                         const std::string& targetEndDate);

    // 생산 시작
    bool startProduction(int orderId);

    // 생산 일시정지
    bool pauseProduction(int orderId);

    // 생산 진행 수량 업데이트
    bool updateProgress(int orderId, int completedQuantity);

    // 생산 완료 처리 (재고 자동 입고)
    bool completeProduction(int orderId);

    std::vector<ProductionOrder> getAllOrders() const;
    std::vector<ProductionOrder> getOrdersByStatus(ProductionStatus status) const;
    std::optional<ProductionOrder> getOrderById(int id) const;

private:
    ProductionRepository& productionRepo_;
    InventoryRepository& inventoryRepo_;
    ProductRepository& productRepo_;

    std::string getCurrentDate() const;
};
