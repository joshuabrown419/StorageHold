#include <iostream>
#include "Command.h"
#include "GetPath.h"
#include "AddItem.h"
#include "Database.h"
#include "DisplayAll.h"
#include "MoveItem.h"
#include "Checkout.h"


int main () {
    Database* db = new Database("./db_folder/db.db");
    Command* commands[] = {(Command*) new AddItem(),
                           (Command*) new MoveItem(),
                           (Command*) new Checkout(),
                           (Command*) new GetPath(),
                           (Command*) new DisplayAll()};

    db->readData();
    
    int selection = -1;
    while(selection != 0) {
        std::cout << std::endl;
        
        std::cout << "Please choose an operation" << std::endl;
        std::cout << "0: Quit" << std::endl;
        for(int i = 1; i < 6; i++) {
            std::cout << i << ": " << commands[i-1]->getName() << std::endl;
        }

        std::cin >> selection;

        if(selection == 0) continue;

        commands[selection - 1]->run(db);
    }
}
