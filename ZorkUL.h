
#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <map>

#include <iostream>
#include <string>
using namespace std;

class ZorkUL {
private:
    Parser parser;
    Room *currentRoom;
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void teleport(Command command);
    void createItems();
    void displayItems();

public:
    ZorkUL();
    map<string,Room *> list_rooms;
    void play();
    string go(string direction);
};

#endif /*ZORKUL_H_*/
