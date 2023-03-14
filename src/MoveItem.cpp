#include "MoveItem.h"
#include <string>
#include <iostream>

std::string MoveItem::getName() {
	return "move_item";
}

void MoveItem::run(Database *db) {
    std::cout << "Enter ID of item to move" << std::endl;
    std::string id_str;
    std::cin >> id_str;
    int id = std::atoi(id_str.c_str());

    std::cout << "Enter path to move the item to ";
    std::cout << "(\"/\" for root or \"/<container_id>/<container_id>/\" for specific location)";
    std::cout << std::endl;

    std::string newPath;
    std::cin >> newPath;

    if (newPath.at(newPath.length() - 1) != '/'){
      newPath.append("/");
    }

    db->moveItem(id, newPath);
    db->writeData();

}