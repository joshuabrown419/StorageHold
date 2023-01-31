#include "Database.h"
#include <string>
#include <iostream>
#include <algorithm>

Database::Database(std::string location){
    this->location = location;
}

bool isInt(std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void Database::writeData() {

}

void Database::addItem(std::string name, int id, std::string location) {    
    size_t pos = 0;
    std::string token;

    DBNode* parent = nullptr;

    if(nodeMap.count(id) != 0) {
        std::cout << "Node with id " << id << " already exists" << std::endl;
        return;
    }

    if(nameMap.count(name) != 0) {
        std::cout << "Node with name \"" << name << "\" already exists" << std::endl;
        return;
    }

    while ((pos = location.find("/")) != std::string::npos) {
        if(location == "/") break;

        token = location.substr(0, pos);
        location.erase(0, pos + 1);

        if(token.length() == 0) continue;

        std::cout << token << std::endl;

        if(isInt(token)) {
            if(nodeMap.count(std::atoi(token.c_str())) == 0){
                std::cout << "container \"" << token << "\" does not exist" << std::endl;
                return;
            }
            parent = nodeMap.at(std::atoi(token.c_str()));
        } else {
            if(nameMap.count(token) == 0){
                std::cout << "container \"" << token << "\" does not exist" << std::endl;
                return;
            }
            parent = nodeMap.at(nameMap.at(token));
        }
    }

    nameMap.emplace(name, id);

    DBNode* node = new DBNode();
    node->id = id;
    node->name = name;
    node->parent = parent;

    nodeMap.emplace(id, node);

    std::cout << "Added node " << id << " with name \"" << name << "\" and parent \"" << (parent == nullptr ? "/" : parent->name)  << "\"" << std::endl;
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

std::vector<struct DBNode*> Database::getAllNodes() {
    std::vector<struct DBNode*> nodes;
    for(std::map<int,struct DBNode*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        nodes.push_back(it->second);
    }

    return nodes;
}