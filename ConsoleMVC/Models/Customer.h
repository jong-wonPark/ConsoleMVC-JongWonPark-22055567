#pragma once
#include <string>

struct Customer {
    int id = 0;
    std::string code;
    std::string name;
    std::string contactPerson;  // 담당자
    std::string phone;
    std::string email;
};
