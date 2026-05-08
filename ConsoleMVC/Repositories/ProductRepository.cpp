#include "ProductRepository.h"
#include <algorithm>

ProductRepository::ProductRepository() {
    seedData();
}

std::vector<Product> ProductRepository::findAll() const {
    return data_;
}

std::optional<Product> ProductRepository::findById(int id) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Product& p) { return p.id == id; });
    return (it != data_.end()) ? std::optional<Product>(*it) : std::nullopt;
}

std::optional<Product> ProductRepository::findByCode(const std::string& code) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [&code](const Product& p) { return p.code == code; });
    return (it != data_.end()) ? std::optional<Product>(*it) : std::nullopt;
}

Product ProductRepository::save(const Product& product) {
    if (product.id == 0) {
        Product newProduct = product;
        newProduct.id = nextId_++;
        data_.push_back(newProduct);
        return newProduct;
    }
    auto it = std::find_if(data_.begin(), data_.end(),
        [&product](const Product& p) { return p.id == product.id; });
    if (it != data_.end()) *it = product;
    return product;
}

bool ProductRepository::remove(int id) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [id](const Product& p) { return p.id == id; });
    if (it == data_.end()) return false;
    data_.erase(it);
    return true;
}

void ProductRepository::seedData() {
    save({ 0, "SSMT-M001", "DDR5-8GB",     ProductCategory::Memory,   45.00, "EA", "DDR5 8GB DRAM" });
    save({ 0, "SSMT-M002", "NAND-256G",    ProductCategory::Memory,   28.00, "EA", "256GB NAND Flash" });
    save({ 0, "SSMT-L001", "AP-A500",      ProductCategory::LogicIC, 120.00, "EA", "모바일 애플리케이션 프로세서" });
    save({ 0, "SSMT-P001", "PMU-200",      ProductCategory::PowerIC,  15.00, "EA", "전력 관리 IC" });
    save({ 0, "SSMT-R001", "RF-TRX-100",   ProductCategory::RFIC,      8.50, "EA", "5G RF 트랜시버" });
    save({ 0, "SSMT-S001", "IMU-300",      ProductCategory::SensorIC, 12.00, "EA", "6축 IMU 센서" });
}
