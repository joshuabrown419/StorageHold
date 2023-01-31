#ifndef GETPATH
#define GETPATH

#include "Command.h"

class GetPath : Command {
    public:
        std::string getName() override;
        void run(Database* db) override;
};

#endif