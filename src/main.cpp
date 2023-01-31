#include <iostream>
#include "Command.h"
#include "GetPath.h"
#include "AddItem.h"
#include "Database.h"


int main () {
    
    Command* commands[] = {(Command*) new GetPath(), (Command*) new AddItem()};
    std::cout << commands[0]->getName() << std::endl;
}
