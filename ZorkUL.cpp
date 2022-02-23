#include <iostream>

using namespace std;
#include "ZorkUL.h"

int main() {
    ZorkUL temp;
    temp.play();
    return 0;
}



ZorkUL::ZorkUL() {

    map<string,Room *> list_rooms;
    createRooms();

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
}



/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
    printWelcome();

    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the ZorkUL game is over.

    bool finished = false;
    while (!finished) {
        // Create pointer to command and give it a command.
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        finished = processCommand(*command);
        // Free the memory allocated by "parser.getCommand()"
        //   with ("return new Command(...)")
        delete command;
    }
    cout << endl;
    cout << "end" << endl;
}

void ZorkUL::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
        cout << "invalid input"<< endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
        cout << "        [0]        " << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
            cout << "you're trying to take " + command.getSecondWord() << endl;
            int location = currentRoom->isItemInRoom(command.getSecondWord());
            if (location  < 0 )
                cout << "item is not in room" << endl;
            else{
                cout << "item is in room" << endl;
                cout << "index number " << + location << endl;
                cout << endl;
                cout << currentRoom->longDescription() << endl;}
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }

    else if(commandWord.compare("teleport") == 0){
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
            cout << "overdefined input"<< endl;
        else
            return true; /**signal to quit*/
    }
    return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
    }
}
void ZorkUL::teleport(Command command ){
    if(command.hasSecondWord())
    {
        if(list_rooms.count(command.getSecondWord())>0){
            currentRoom=list_rooms[command.getSecondWord()];
            cout << currentRoom->longDescription() << endl;
        }
        else{cout << "invalid room" << endl;}
    }
    else{
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
        cout << currentRoom->longDescription() << endl;
    }
}
string ZorkUL::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}



