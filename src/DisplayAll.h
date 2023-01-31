#ifndef DISPLAYALL
#define DISPLAYALL

#include "Command.h"

class DisplayAll : Command {
    public:
        std::string getName() override;
        void run(Database* db) override;
};

#endif