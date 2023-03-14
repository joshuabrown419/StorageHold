#include "GetPath.h"

#include <string>
#include <iostream>

std::string GetPath::getName() {
    return "get_path";
}

void GetPath::run(Database* db) {
    std::cout << "ID of item to get path of: ";
    int id;
    std::cin >> id;
    db->printItemInfo(id);
}