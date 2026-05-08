#pragma once
#include <vector>
#include <optional>
#include "../Models/Customer.h"

class CustomerRepository {
public:
    CustomerRepository();

    std::vector<Customer> findAll() const;
    std::optional<Customer> findById(int id) const;
    std::optional<Customer> findByCode(const std::string& code) const;
    Customer save(const Customer& customer);
    bool remove(int id);

private:
    std::vector<Customer> data_;
    int nextId_ = 1;

    void seedData();
};
