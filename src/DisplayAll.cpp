#include "DisplayAll.h"

#include <string>
#include <iostream>
#include <stdlib.h>

std::string DisplayAll::getName() {
    return "display_all";
}

void DisplayAll::run(Database* db) {
    std::cout << std::endl << "Displaying all nodes and their path: " << std::endl;
    for(struct DBNode* node : db->getAllNodes()) {
        std::cout << db->getPath(node->id) << std::endl;
    }
}