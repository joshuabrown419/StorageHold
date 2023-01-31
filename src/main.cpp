#include <iostream>
#include "Command.h"
#include "GetPath.h"
#include "AddItem.h"
#include "Database.h"
#include "DisplayAll.h"


int main () {
    Database* db = new Database("./db_folder/db.db");
    Command* commands[] = {(Command*) new GetPath(), (Command*) new AddItem(), (Command*) new DisplayAll()};
    
    int selection = 0;
    while(selection != 3) {
        std::cout << std::endl;
        
        std::cout << "Please choose an operation" << std::endl;
        for(int i = 0; i < 3; i++) {
            std::cout << i << ": " << commands[i]->getName() << std::endl;
        }
        std::cout << "3: Quit" << std::endl;

        std::cin >> selection;

        if(selection == 3) continue;

        commands[selection]->run(db);
    }
}
