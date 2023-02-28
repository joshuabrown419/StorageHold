#ifndef DATABASE
#define DATABASE

#include <string>
#include <map>
#include <vector>

class DBNode {
    public:
        int id;
        int parent_id;
        std::string name;
};

class Database {
    private:
        std::map<std::string, int> nameMap = std::map<std::string, int>();
        std::map<int, struct DBNode*> nodeMap = std::map<int, struct DBNode*>();

        std::string location; 
    public: 
        Database(std::string location);

        void writeData();
        void readData();
        // Name and id should be unique, location should be in the form of "<container_id>/<container_id>"
        void addItem(std::string name, int id, std::string location);

        std::string getPath(std::string name);
        std::string getPath(int id);

        std::vector<struct DBNode*> getAllNodes();
};

#endif