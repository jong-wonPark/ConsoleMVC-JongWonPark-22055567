#pragma once
#include <string>

enum class OrderStatus {
    Pending,    // 대기중
    Approved,   // 승인됨
    Rejected,   // 거절됨
    Shipping,   // 출고중
    Completed   // 완료
};

enum class ProductionStatus {
    Planned,    // 계획됨
    InProgress, // 생산중
    Paused,     // 일시정지
    Completed   // 완료
};

enum class ProductCategory {
    LogicIC,    // 로직 IC
    Memory,     // 메모리
    PowerIC,    // 전력 IC
    RFIC,       // RF IC
    SensorIC,   // 센서 IC
    Other       // 기타
};

inline std::string toString(OrderStatus s) {
    switch (s) {
        case OrderStatus::Pending:   return "대기중";
        case OrderStatus::Approved:  return "승인됨";
        case OrderStatus::Rejected:  return "거절됨";
        case OrderStatus::Shipping:  return "출고중";
        case OrderStatus::Completed: return "완료";
        default:                     return "알수없음";
    }
}

inline std::string toString(ProductionStatus s) {
    switch (s) {
        case ProductionStatus::Planned:    return "계획됨";
        case ProductionStatus::InProgress: return "생산중";
        case ProductionStatus::Paused:     return "일시정지";
        case ProductionStatus::Completed:  return "완료";
        default:                           return "알수없음";
    }
}

inline std::string toString(ProductCategory c) {
    switch (c) {
        case ProductCategory::LogicIC:  return "로직IC";
        case ProductCategory::Memory:   return "메모리";
        case ProductCategory::PowerIC:  return "전력IC";
        case ProductCategory::RFIC:     return "RF IC";
        case ProductCategory::SensorIC: return "센서IC";
        case ProductCategory::Other:    return "기타";
        default:                        return "알수없음";
    }
}
