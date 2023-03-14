#include "Database.h"
#include <cstdio>
#include <ostream>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <zmqpp/zmqpp.hpp>

Database::Database(std::string location){
    this->location = location;
}

bool isInt(std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void Database::writeData() {
    std::ofstream id_list_file("./id_list.txt", std::ios::out | std::ios::trunc);
    std::ofstream node_info_file("./node_info.csv", std::ios::out | std::ios::trunc);

    for(auto it = nodeMap.begin(); it != nodeMap.end(); it++){
        id_list_file << it->first << std::endl;

        node_info_file << it->first << ',' << it->second->name << ',' << it->second->parent_id << std::endl;
    }
}

void Database::readData() {
    std::ifstream id_list_file("./id_list.txt");

    const std::string endpoint = "tcp://localhost:2046";

    // initialize the 0MQ context
    zmqpp::context context;

    // generate a push socket
    zmqpp::socket_type type = zmqpp::socket_type::req;
    zmqpp::socket socket (context, type);

    socket.connect(endpoint);

    std::string line;
    while(std::getline(id_list_file, line)) {
        if(line.empty()) break;

        zmqpp::message message;
        message << (line + "|/mnt/Common/code/CS361/StorageHold/node_info.csv");
        socket.send(message);

        std::string buffer;
        socket.receive(buffer);

        std::string name = buffer.substr(0, buffer.find('|'));

        int id = std::atoi(line.c_str());
        int parent_id = std::atoi(buffer.substr(buffer.find('|')+1).c_str());

        DBNode *node = new DBNode();
        node->id = id;
        node->name = name;
        node->parent_id = parent_id;

        nodeMap.emplace(id, node);
        nameMap.emplace(name, id);
    }
}

void Database::addItem(std::string name, int id, std::string path) {
    size_t pos = 0;
    std::string token;

    int parent_id = -1;

    if(nodeMap.count(id) != 0) {
        std::cout << "Node with id " << id << " already exists" << std::endl;
        return;
    }

    if(nameMap.count(name) != 0) {
        std::cout << "Node with name \"" << name << "\" already exists" << std::endl;
        return;
    }

    while ((pos = path.find("/")) != std::string::npos) {
        if(path == "/") break;

        token = path.substr(0, pos);
        path.erase(0, pos + 1);

        if(token.length() == 0) continue;

        if(isInt(token)) {
            if(nodeMap.count(std::atoi(token.c_str())) == 0){
                std::cout << "container \"" << token << "\" does not exist" << std::endl;
                return;
            }
            parent_id = std::atoi(token.c_str());
        } else {
            if(nameMap.count(token) == 0){
                std::cout << "container \"" << token << "\" does not exist" << std::endl;
                return;
            }
            parent_id = nameMap.at(token);
        }
    }

    nameMap.emplace(name, id);

    DBNode* node = new DBNode();
    node->id = id;
    node->name = name;
    node->parent_id = parent_id;

    nodeMap.emplace(id, node);
    std::cout << std::endl;
    printItemInfo(id);
}

void Database::moveItem(int id, std::string& newPath) {
    if(nodeMap.count(id) == 0) {
        std::cout << "Node " << id << " does not exist" << std::endl;
        return;
    }

    std::string nodePath = this->getPath(id);

    if(newPath.find(nodePath) != std::string::npos) {
        std::cout << "Cannot place an item inside of itself" << std::endl;
    }

    size_t pos = 0;
    std::string token;

    int parent_id = -1;

    while ((pos = newPath.find("/")) != std::string::npos) {
      if(newPath == "/") break;

      token = newPath.substr(0, pos);
      newPath.erase(0, pos + 1);

      if(token.length() == 0) continue;

      if(isInt(token)) {
        if(nodeMap.count(std::atoi(token.c_str())) == 0){
          std::cout << "container \"" << token << "\" does not exist" << std::endl;
          return;
        }
        parent_id = std::atoi(token.c_str());
      } else {
        if(nameMap.count(token) == 0){
          std::cout << "container \"" << token << "\" does not exist" << std::endl;
          return;
        }
        parent_id = nameMap.at(token);
      }
    }

    nodeMap.at(id)->parent_id = parent_id;

    std::cout << std::endl;
    printItemInfo(id);
}

void Database::printItemInfo(int id) {
    if(nodeMap.count(id) == 0) {
        std::printf("Node %d does not exist\n", id);
    }

    DBNode* node = nodeMap.at(id);

    std::printf("Node %d, Name: %s, Path: %s\n",
                node->id,
                node->name.c_str(),
                getPath(node->id).c_str());
}

std::string Database::getPath(std::string name){
    if(nameMap.count(name) == 0) {
        return "item does not exist";
    }
    return getPath(nameMap.at(name));
}

std::string Database::getPath(int id) {
    if(id == -1) {
        return "";
    }

    if(nodeMap.count(id) == 0) {
        return "item does not exist";
    }

    return getPath(nodeMap.at(id)->parent_id) + "/" + nodeMap.at(id)->name;
}

std::vector<struct DBNode*> Database::getAllNodes() {
    std::vector<struct DBNode*> nodes;
    for(std::map<int,struct DBNode*>::iterator it = nodeMap.begin(); it != nodeMap.end(); ++it) {
        nodes.push_back(it->second);
    }

    return nodes;
}
