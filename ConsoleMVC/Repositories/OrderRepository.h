#pragma once
#include <vector>
#include <optional>
#include "../Models/Order.h"

class OrderRepository {
public:
    std::vector<Order> findAll() const;
    std::vector<Order> findByStatus(OrderStatus status) const;
    std::vector<Order> findByCustomer(int customerId) const;
    std::optional<Order> findById(int id) const;
    Order save(const Order& order);
    bool remove(int id);

private:
    std::vector<Order> data_;
    int nextId_ = 1;
};
