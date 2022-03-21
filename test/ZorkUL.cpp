#include <iostream>

using namespace std;
#include "ZorkUL.h"
/*
int main() {
    ZorkUL temp;
    temp.play();
    return 0;
}
*/


ZorkUL::ZorkUL() {
    MainWindow w;
    //w.show();  to put in exe
    map<string,Room *> list_rooms;
    createRooms();
    bool finished = false;

}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i,*_0,*_NULL;


    a = new Room("a");
    a->addItem(new Item("x", 1, 11));
    a->addItem(new Item("y", 2, 22));
    b = new Room("b");
    b->addItem(new Item("xx", 3, 33));
    b->addItem(new Item("yy", 4, 44));
    c = new Room("c");
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");

    _0=new Room("_0");
    _NULL=new Room("_NULL");
//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(_0, d, NULL, NULL);

    _NULL->setExits(NULL, NULL, NULL, NULL);
    _0->setExits(NULL, NULL, f, NULL);

    list_rooms["a"]=a;
    list_rooms["b"]=b;
    list_rooms["c"]=c;
    list_rooms["d"]=d;
    list_rooms["e"]=e;
    list_rooms["f"]=f;
    list_rooms["g"]=g;
    list_rooms["h"]=h;
    list_rooms["i"]=i;

    list_rooms["_0"]=_0;
    list_rooms["_NULL"]=_NULL;


    currentRoom = _0;


    string mapp="         [0]        \n"
                "          |         \n"
                "          |         \n"
                " [h] --- [f] --- [g]\n"
                "          |         \n"
                "          |         \n"
                " [c] --- [a] --- [b]\n"
                "          |         \n"
                "          |         \n"
                " [i] --- [d] --- [e]\n";
}



//  Main play routine.  Loops until end of play.

void ZorkUL::play() {
    w.show();
}

string ZorkUL::printWelcome() {
    return "start \n info for help";
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
string ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
        return "invalid input";
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
        return mapp;
        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        return  "incomplete input";
        }
        else
         if (command.hasSecondWord()) {
            string rep= "you're trying to take " + command.getSecondWord() +"\n";
            int location = currentRoom->isItemInRoom(command.getSecondWord());
            if (location  < 0 )
                rep+= "item is not in room\n";
            else{
                rep+= "item is in room :" "\n" +currentRoom->longDescription();//rajouter la location voir zorktest
                return rep ;}
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }

    else if(commandWord.compare("teleport") == 0){// --------------------------
        teleport(command);

    }
    /*
    {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            return "overdefined input";
        else{finished=true;return "game end";} /**signal to quit*/
    }


    return "error:command not handled";//ne devrait pas apparaitre
}
/** COMMANDS **/
string ZorkUL::printHelp() {
    return "valid inputs are;\n"+parser.showCommands();
}

string ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        return "incomplete input";
    }
    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        return "underdefined input";
    else {
        currentRoom = nextRoom;
        return currentRoom->longDescription() ;
    }
}
string ZorkUL::teleport(Command command ){
    if(command.hasSecondWord())
    {
        if(list_rooms.count(command.getSecondWord())>0){
            currentRoom=list_rooms[command.getSecondWord()];
            return currentRoom->longDescription() ;
        }
        else{return "invalid room";}
    }

    srand((unsigned) time(0));

    map<string,Room *>::iterator it;
    int i=-1;
    int randomNumber = rand() % list_rooms.size();
    it =list_rooms.begin();
    while(it->second==list_rooms["_NULL"] || i< randomNumber ||it->second==currentRoom)
    {
        i=0;
        randomNumber = rand() % list_rooms.size();
        for(it =list_rooms.begin(); i<randomNumber && it != list_rooms.end() ; it++){i++;}

    }
    currentRoom=it->second;
    return currentRoom->longDescription() ;
}
string ZorkUL::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    currentRoom = nextRoom;
    return currentRoom->longDescription();
}



