#include "OrderRepository.h"
#include <algorithm>

std::vector<Order> OrderRepository::findAll() const {
    return data_;
}

std::vector<Order> OrderRepository::findByStatus(OrderStatus status) const {
    std::vector<Order> result;
    for (const auto& o : data_)
        if (o.status == status) result.push_back(o);
    return result;
}

std::vector<Order> OrderRepository::findByCustomer(int customerId) const {
    std::vector<Order> result;
    for (const auto& o : data_)
        if (o.customerId == customerId) result.push_back(o);
    return result;
}

std::optional<Order> OrderRepository::findById(int id) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Order& o) { return o.id == id; });
    return (it != data_.end()) ? std::optional<Order>(*it) : std::nullopt;
}

Order OrderRepository::save(const Order& order) {
    if (order.id == 0) {
        Order newOrder = order;
        newOrder.id = nextId_++;
        data_.push_back(newOrder);
        return newOrder;
    }
    auto it = std::find_if(data_.begin(), data_.end(),
        [&order](const Order& o) { return o.id == order.id; });
    if (it != data_.end()) *it = order;
    return order;
}

bool OrderRepository::remove(int id) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Order& o) { return o.id == id; });
    if (it == data_.end()) return false;
    data_.erase(it);
    return true;
}
