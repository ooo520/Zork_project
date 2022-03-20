
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
    string printWelcome();
    string processCommand(Command command);
    string printHelp();
    string goRoom(Command command);
    string teleport(Command command);
    string createItems();
    string displayItems();
    string mapp;
    bool finished ;

public:
    ZorkUL();
    map<string,Room *> list_rooms;
    //void play();
    string go(string direction);
};

#endif /*ZORKUL_H_*/
