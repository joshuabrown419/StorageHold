#ifndef COMMAND
#define COMMAND

#include <string>
#include "Database.h"

class Command {
    public:
        virtual std::string getName() = 0;
        virtual void run(Database* db) = 0;
};

#endif