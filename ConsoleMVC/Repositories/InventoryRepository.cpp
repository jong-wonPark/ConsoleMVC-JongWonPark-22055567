#include "InventoryRepository.h"
#include <algorithm>

InventoryRepository::InventoryRepository() {
    seedData();
}

std::vector<InventoryItem> InventoryRepository::findAll() const {
    return data_;
}

std::optional<InventoryItem> InventoryRepository::findByProductId(int productId) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [productId](const InventoryItem& i) { return i.productId == productId; });
    return (it != data_.end()) ? std::optional<InventoryItem>(*it) : std::nullopt;
}

std::vector<InventoryItem> InventoryRepository::findLowStock() const {
    std::vector<InventoryItem> result;
    for (const auto& i : data_)
        if (i.isLowStock()) result.push_back(i);
    return result;
}

InventoryItem InventoryRepository::save(const InventoryItem& item) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [&item](const InventoryItem& i) { return i.productId == item.productId; });
    if (it != data_.end()) {
        *it = item;
        return item;
    }
    data_.push_back(item);
    return item;
}

bool InventoryRepository::updateQuantity(int productId, int delta) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [productId](const InventoryItem& i) { return i.productId == productId; });
    if (it == data_.end()) return false;
    it->quantity += delta;
    return true;
}

bool InventoryRepository::updateReserved(int productId, int delta) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [productId](const InventoryItem& i) { return i.productId == productId; });
    if (it == data_.end()) return false;
    it->reservedQuantity += delta;
    return true;
}

void InventoryRepository::seedData() {
    save({ 1, "DDR5-8GB",    10000, 2000,  0 });
    save({ 2, "NAND-256G",    5000, 1000,  0 });
    save({ 3, "AP-A500",       800,  200,  0 });
    save({ 4, "PMU-200",      3000,  500,  0 });
    save({ 5, "RF-TRX-100",   1500,  300,  0 });
    save({ 6, "IMU-300",       120,  200,  0 }); // 재고 부족 샘플
}
