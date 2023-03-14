#ifndef MOVE_ITEM
#define MOVE_ITEM

#include "Database.h"
#include <string>
#include "Command.h"

class MoveItem : Command {
    public:
        std::string getName() override;
        void run(Database* db) override;
};

#endif