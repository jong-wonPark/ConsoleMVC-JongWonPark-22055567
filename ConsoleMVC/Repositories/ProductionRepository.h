#pragma once
#include <vector>
#include <optional>
#include "../Models/ProductionOrder.h"

class ProductionRepository {
public:
    std::vector<ProductionOrder> findAll() const;
    std::vector<ProductionOrder> findByStatus(ProductionStatus status) const;
    std::optional<ProductionOrder> findById(int id) const;
    ProductionOrder save(const ProductionOrder& order);
    bool remove(int id);

private:
    std::vector<ProductionOrder> data_;
    int nextId_ = 1;
};
