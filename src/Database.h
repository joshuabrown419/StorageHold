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
        std::string* checkout = nullptr;
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

        void moveItem(int id, std::string& newPath);

        void printItemInfo(int id);

        std::string getPath(std::string name);
        std::string getPath(int id);

        void checkout(int id, std::string name);

        std::vector<DBNode*> getAllNodes();

        ~Database();
};

#endif