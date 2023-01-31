#include "Database.h"
#include <string>
#include <iostream>

Database::Database(std::string location){
    this->location = location;
}

void Database::writeData() {

}

void Database::addItem(std::string name, int id, std::string location) {    
    size_t pos = 0;
    std::string token;
    while ((pos = location.find("/")) != std::string::npos) {
        token = location.substr(0, pos);

        std::cout << token << std::endl;
        location.erase(0, pos + 1);
    }

    // nameMap.emplace(name, id);

    // struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    // node->id = id;
}

std::string Database::getPath(std::string name){
    if(nameMap.count(name) == 0) {
        return "item does not exist";
    }
    return getPath(nameMap.at(name));
}

std::string Database::getPath(int id) {
    if(nodeMap.count(id) == 0) {
        return "item does not exist";
    }

    if(nodeMap.at(id)->parent == nullptr) {
        return "/" + nodeMap.at(id)->name;
    }

    return getPath(nodeMap.at(id)->parent->id) + "/" + nodeMap.at(id)->name;
}
