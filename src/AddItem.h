#ifndef ADDITEM
#define ADDITEM

#include "Command.h"

class AddItem : Command {
    public:
        std::string getName() override;
        void run(Database* db) override;
};

#endif