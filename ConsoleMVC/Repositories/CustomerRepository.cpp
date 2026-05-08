#include "CustomerRepository.h"
#include <algorithm>

CustomerRepository::CustomerRepository() {
    seedData();
}

std::vector<Customer> CustomerRepository::findAll() const {
    return data_;
}

std::optional<Customer> CustomerRepository::findById(int id) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Customer& c) { return c.id == id; });
    return (it != data_.end()) ? std::optional<Customer>(*it) : std::nullopt;
}

std::optional<Customer> CustomerRepository::findByCode(const std::string& code) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [&code](const Customer& c) { return c.code == code; });
    return (it != data_.end()) ? std::optional<Customer>(*it) : std::nullopt;
}

Customer CustomerRepository::save(const Customer& customer) {
    if (customer.id == 0) {
        Customer newCustomer = customer;
        newCustomer.id = nextId_++;
        data_.push_back(newCustomer);
        return newCustomer;
    }
    auto it = std::find_if(data_.begin(), data_.end(),
        [&customer](const Customer& c) { return c.id == customer.id; });
    if (it != data_.end()) *it = customer;
    return customer;
}

bool CustomerRepository::remove(int id) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Customer& c) { return c.id == id; });
    if (it == data_.end()) return false;
    data_.erase(it);
    return true;
}

void CustomerRepository::seedData() {
    save({ 0, "CUST-001", "삼성전자",   "김철수", "02-1234-5678", "kim@samsung.com" });
    save({ 0, "CUST-002", "LG전자",     "이영희", "02-2345-6789", "lee@lg.com" });
    save({ 0, "CUST-003", "SK하이닉스", "박민준", "031-3456-7890", "park@skhynix.com" });
    save({ 0, "CUST-004", "현대모비스", "정수진", "031-4567-8901", "jung@mobis.com" });
}
