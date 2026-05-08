#include "ProductionRepository.h"
#include <algorithm>

std::vector<ProductionOrder> ProductionRepository::findAll() const {
    return data_;
}

std::vector<ProductionOrder> ProductionRepository::findByStatus(ProductionStatus status) const {
    std::vector<ProductionOrder> result;
    for (const auto& p : data_)
        if (p.status == status) result.push_back(p);
    return result;
}

std::optional<ProductionOrder> ProductionRepository::findById(int id) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const ProductionOrder& p) { return p.id == id; });
    return (it != data_.end()) ? std::optional<ProductionOrder>(*it) : std::nullopt;
}

ProductionOrder ProductionRepository::save(const ProductionOrder& order) {
    if (order.id == 0) {
        ProductionOrder newOrder = order;
        newOrder.id = nextId_++;
        data_.push_back(newOrder);
        return newOrder;
    }
    auto it = std::find_if(data_.begin(), data_.end(),
        [&order](const ProductionOrder& p) { return p.id == order.id; });
    if (it != data_.end()) *it = order;
    return order;
}

bool ProductionRepository::remove(int id) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const ProductionOrder& p) { return p.id == id; });
    if (it == data_.end()) return false;
    data_.erase(it);
    return true;
}
