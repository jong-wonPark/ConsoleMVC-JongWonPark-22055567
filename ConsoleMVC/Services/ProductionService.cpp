#include "ProductionService.h"
#include <chrono>
#include <format>

ProductionService::ProductionService(ProductionRepository& productionRepo,
                                     InventoryRepository& inventoryRepo,
                                     ProductRepository& productRepo)
    : productionRepo_(productionRepo)
    , inventoryRepo_(inventoryRepo)
    , productRepo_(productRepo)
{}

std::optional<ProductionOrder> ProductionService::createProductionOrder(int productId,
    int targetQuantity, const std::string& targetEndDate) {

    auto product = productRepo_.findById(productId);
    if (!product) return std::nullopt;

    ProductionOrder po;
    po.productId       = productId;
    po.productName     = product->name;
    po.targetQuantity  = targetQuantity;
    po.startDate       = getCurrentDate();
    po.targetEndDate   = targetEndDate;
    po.status          = ProductionStatus::Planned;

    return productionRepo_.save(po);
}

bool ProductionService::startProduction(int orderId) {
    auto poOpt = productionRepo_.findById(orderId);
    if (!poOpt || poOpt->status != ProductionStatus::Planned) return false;

    poOpt->status = ProductionStatus::InProgress;
    productionRepo_.save(*poOpt);
    return true;
}

bool ProductionService::pauseProduction(int orderId) {
    auto poOpt = productionRepo_.findById(orderId);
    if (!poOpt || poOpt->status != ProductionStatus::InProgress) return false;

    poOpt->status = ProductionStatus::Paused;
    productionRepo_.save(*poOpt);
    return true;
}

bool ProductionService::updateProgress(int orderId, int completedQuantity) {
    auto poOpt = productionRepo_.findById(orderId);
    if (!poOpt) return false;
    if (poOpt->status != ProductionStatus::InProgress &&
        poOpt->status != ProductionStatus::Paused) return false;

    poOpt->completedQuantity = completedQuantity;
    productionRepo_.save(*poOpt);
    return true;
}

bool ProductionService::completeProduction(int orderId) {
    auto poOpt = productionRepo_.findById(orderId);
    if (!poOpt || poOpt->status == ProductionStatus::Completed) return false;

    poOpt->status            = ProductionStatus::Completed;
    poOpt->completedQuantity = poOpt->targetQuantity;
    productionRepo_.save(*poOpt);

    // 생산 완료분 재고 자동 입고
    inventoryRepo_.updateQuantity(poOpt->productId, poOpt->completedQuantity);
    return true;
}

std::vector<ProductionOrder> ProductionService::getAllOrders() const {
    return productionRepo_.findAll();
}

std::vector<ProductionOrder> ProductionService::getOrdersByStatus(ProductionStatus status) const {
    return productionRepo_.findByStatus(status);
}

std::optional<ProductionOrder> ProductionService::getOrderById(int id) const {
    return productionRepo_.findById(id);
}

std::string ProductionService::getCurrentDate() const {
    auto now = std::chrono::system_clock::now();
    return std::format("{:%Y-%m-%d}", std::chrono::floor<std::chrono::days>(now));
}
