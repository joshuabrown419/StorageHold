#ifndef DATABASE
#define DATABASE

#include <string>
#include <map>

struct Node {
    Node* parent;
    int id;
    std::string name;
};

class Database {
    private:
        std::map<std::string, int> nameMap = std::map<std::string, int>();
        std::map<int, struct Node*> nodeMap = std::map<int, struct Node*>();

        std::string location; 
    public: 
        Database(std::string location);

        void writeData();
        // Name and id should be unique, location should be in the form of "<container_id>/<container_id>"
        void addItem(std::string name, int id, std::string location);

        std::string getPath(std::string name);
        std::string getPath(int id);
};

#endif