#pragma once
#include <vector>
#include <optional>
#include "../Models/Product.h"

class ProductRepository {
public:
    ProductRepository();

    std::vector<Product> findAll() const;
    std::optional<Product> findById(int id) const;
    std::optional<Product> findByCode(const std::string& code) const;
    Product save(const Product& product);
    bool remove(int id);

private:
    std::vector<Product> data_;
    int nextId_ = 1;

    void seedData();
};
