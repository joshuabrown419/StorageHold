#ifndef CHECKOUT
#define CHECKOUT

#include "Command.h"
#include "Database.h"
#include <string>

class Checkout : Command {
    public:
        std::string getName() override;
        void run(Database* db) override;
};

#endif