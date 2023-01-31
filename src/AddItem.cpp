#include "AddItem.h"

#include <string>
#include <iostream>
#include <stdlib.h>

std::string AddItem::getName() {
    return "add_item";
}

void AddItem::run(Database* db) {
    std::cout << "Enter item id" << std::endl;
    std::string id_str;
    std::cin >> id_str;
    int id = std::atoi(id_str.c_str());

    std::cout << "Enter item name" << std::endl;
    std::string name;
    std::cin >> name;

    std::cout << "Enter path to item (\"/\" for root or \"/<container_id>/<container_id>\" for specific location)" << std::endl;
    std::string path;

    db->addItem(name, id, path);
}