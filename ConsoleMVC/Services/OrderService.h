#pragma once
#include <vector>
#include <string>
#include <optional>
#include "../Models/Order.h"
#include "../Repositories/OrderRepository.h"
#include "../Repositories/InventoryRepository.h"
#include "../Repositories/CustomerRepository.h"
#include "../Repositories/ProductRepository.h"

class OrderService {
public:
    OrderService(OrderRepository& orderRepo,
                 InventoryRepository& inventoryRepo,
                 CustomerRepository& customerRepo,
                 ProductRepository& productRepo);

    // 주문 등록
    std::optional<Order> createOrder(int customerId,
                                     const std::vector<std::pair<int, int>>& productQuantities);

    // 주문 승인 (재고 예약 포함)
    bool approveOrder(int orderId);

    // 주문 거절
    bool rejectOrder(int orderId, const std::string& reason);

    // 출고 처리 (승인 → 출고중)
    bool processShipment(int orderId);

    // 출고 완료 (출고중 → 완료, 재고 차감)
    bool completeShipment(int orderId);

    std::vector<Order> getAllOrders() const;
    std::vector<Order> getOrdersByStatus(OrderStatus status) const;
    std::optional<Order> getOrderById(int id) const;

private:
    OrderRepository& orderRepo_;
    InventoryRepository& inventoryRepo_;
    CustomerRepository& customerRepo_;
    ProductRepository& productRepo_;

    bool checkInventory(const Order& order) const;
    std::string getCurrentDate() const;
};
