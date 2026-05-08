#include "OrderService.h"
#include <chrono>
#include <format>

OrderService::OrderService(OrderRepository& orderRepo,
                           InventoryRepository& inventoryRepo,
                           CustomerRepository& customerRepo,
                           ProductRepository& productRepo)
    : orderRepo_(orderRepo)
    , inventoryRepo_(inventoryRepo)
    , customerRepo_(customerRepo)
    , productRepo_(productRepo)
{}

std::optional<Order> OrderService::createOrder(int customerId,
    const std::vector<std::pair<int, int>>& productQuantities) {

    auto customer = customerRepo_.findById(customerId);
    if (!customer) return std::nullopt;

    Order order;
    order.customerId   = customerId;
    order.customerName = customer->name;
    order.orderDate    = getCurrentDate();
    order.status       = OrderStatus::Pending;

    for (const auto& [productId, qty] : productQuantities) {
        auto product = productRepo_.findById(productId);
        if (!product) return std::nullopt;

        OrderItem item;
        item.productId   = productId;
        item.productName = product->name;
        item.quantity    = qty;
        item.unitPrice   = product->unitPrice;
        order.items.push_back(item);
    }

    return orderRepo_.save(order);
}

bool OrderService::approveOrder(int orderId) {
    auto orderOpt = orderRepo_.findById(orderId);
    if (!orderOpt || orderOpt->status != OrderStatus::Pending) return false;

    if (!checkInventory(*orderOpt)) return false;

    // 재고 예약
    for (const auto& item : orderOpt->items)
        inventoryRepo_.updateReserved(item.productId, item.quantity);

    orderOpt->status = OrderStatus::Approved;
    orderRepo_.save(*orderOpt);
    return true;
}

bool OrderService::rejectOrder(int orderId, const std::string& reason) {
    auto orderOpt = orderRepo_.findById(orderId);
    if (!orderOpt || orderOpt->status != OrderStatus::Pending) return false;

    orderOpt->status          = OrderStatus::Rejected;
    orderOpt->rejectionReason = reason;
    orderRepo_.save(*orderOpt);
    return true;
}

bool OrderService::processShipment(int orderId) {
    auto orderOpt = orderRepo_.findById(orderId);
    if (!orderOpt || orderOpt->status != OrderStatus::Approved) return false;

    orderOpt->status = OrderStatus::Shipping;
    orderRepo_.save(*orderOpt);
    return true;
}

bool OrderService::completeShipment(int orderId) {
    auto orderOpt = orderRepo_.findById(orderId);
    if (!orderOpt || orderOpt->status != OrderStatus::Shipping) return false;

    // 실재고 차감 및 예약 해제
    for (const auto& item : orderOpt->items) {
        inventoryRepo_.updateQuantity(item.productId, -item.quantity);
        inventoryRepo_.updateReserved(item.productId, -item.quantity);
    }

    orderOpt->status = OrderStatus::Completed;
    orderRepo_.save(*orderOpt);
    return true;
}

std::vector<Order> OrderService::getAllOrders() const {
    return orderRepo_.findAll();
}

std::vector<Order> OrderService::getOrdersByStatus(OrderStatus status) const {
    return orderRepo_.findByStatus(status);
}

std::optional<Order> OrderService::getOrderById(int id) const {
    return orderRepo_.findById(id);
}

bool OrderService::checkInventory(const Order& order) const {
    for (const auto& item : order.items) {
        auto inv = inventoryRepo_.findByProductId(item.productId);
        if (!inv || inv->availableQuantity() < item.quantity) return false;
    }
    return true;
}

std::string OrderService::getCurrentDate() const {
    auto now = std::chrono::system_clock::now();
    return std::format("{:%Y-%m-%d}", std::chrono::floor<std::chrono::days>(now));
}
