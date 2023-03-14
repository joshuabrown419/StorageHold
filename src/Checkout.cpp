#include "Checkout.h"
#include <string>
#include <iostream>

std::string Checkout::getName() {
    return "checkout";
}

void Checkout::run(Database *db) {
    std::cout << "Enter id of item to check out" << std::endl;
    std::string str_id;
    std::cin >> str_id;
    int id = std::atoi(str_id.c_str());

    std::cout << "Enter your name" << std::endl;
    std::string name;
    std::cin >> name;

    db->checkout(id, name);
}