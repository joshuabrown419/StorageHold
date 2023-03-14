#include "DisplayAll.h"

#include <string>
#include <iostream>
#include <stdlib.h>

std::string DisplayAll::getName() {
    return "display_all";
}

void DisplayAll::run(Database* db) {
    std::cout << std::endl << "Displaying all nodes and their path: " << std::endl;
    for(DBNode* node : db->getAllNodes()) {
        db->printItemInfo(node->id);
    }
}