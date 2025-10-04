#include <stdio.h>
#include <ncurses.h> // special header for this gaming project
#include <stdlib.h>
#include <time.h> // enable use of random numbers

typedef struct Position
{

    int x;
    int y;

} Position;

typedef struct Player
{
    Position position;
    int health;
    // Add more later on
} Player; // this gives it an abreviation so we don't need to type "struct Player", just Player

typedef struct Room
{

    // int xPosition;
    // int yPosition;
    Position position;
    int height;
    int width;

    // Position doors[4]; // doors are stored as an array os Position structs
    // 0: top 1: bottom 2: left 3: right
    Position **doors; // changed to more volatile form

    // Monster **monsters; // an array for monsters
    // Item **items;       // an array for items

} Room;

typedef struct Monster
{
    int health;

} Monster;

typedef struct Item
{

} Item;

// Function declare here so we can write below main
int screenSetUp();
Room **mapSetUp(); // returns an array of Rooms
Player *playerSetUp();
int handleInput(int input, Player *user);
int playerMove(int yPosition, int xPosition, Player *user);
int checkPosition(int y, int x, Player *unit);

// Room Functions:
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
int connectDoors(Position *doorOne, Position *doorTwo);

int main(int argc, char const *argv[])
{

    Player *user;
    int ch;

    screenSetUp();
    mapSetUp();
    user = playerSetUp();

    // Game loop
    while ((ch = getch()) != 'q')
    {
        // getch(); // get character
        handleInput(ch, user);
    }
    endwin();

    return 0;
}

int screenSetUp()
{

    initscr(); // need ncursor installed and working
    printw("Welcome to the dungeon");
    noecho(); // you can't see what you've typed
    srand(time(NULL));
    refresh();

    return 1;
}

// Set up the dungeon, returns an array of struct Room.
Room **mapSetUp()
{
    Room **rooms;
    rooms = malloc(sizeof(Room *) * 6); // allocate 6 rooms

    // mvprintw(13, 13, "--------");     // (y coordinate, x coordinate, "string")
    // mvprintw(14, 13, "|......|");
    // mvprintw(15, 13, "|......|");
    // mvprintw(16, 13, "|......|");
    // mvprintw(17, 13, "|......|");
    // mvprintw(18, 13, "--------");

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    // mvprintw(2, 20, "--------"); // (y coordinate, x coordinate, "string")
    // mvprintw(3, 20, "|......|");
    // mvprintw(4, 20, "|......|");
    // mvprintw(5, 20, "|......|");
    // mvprintw(6, 20, "|......|");
    // mvprintw(7, 20, "--------");

    rooms[1] = createRoom(2, 20, 6, 8);
    drawRoom(rooms[1]);

    // mvprintw(10, 40, "------------"); // (y coordinate, x coordinate, "string")
    // mvprintw(11, 40, "|..........|");
    // mvprintw(12, 40, "|..........|");
    // mvprintw(13, 40, "|..........|");
    // mvprintw(14, 40, "|..........|");
    // mvprintw(15, 40, "------------");

    rooms[2] = createRoom(10, 40, 6, 12);
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]); // need to change

    return rooms;
}

// This function creates and returns a struct Room
Room *createRoom(int y, int x, int height, int width)
{
    Room *newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    newRoom->doors = malloc(sizeof(Position) * 4);

    // srand(time(NULL));

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = 1 + rand() % (width - 2) + newRoom->position.x; // in range of 0 to width
    newRoom->doors[0]->y = newRoom->position.y;                            // in range of 0 to height

    // bottom door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = 1 + rand() % (width - 2) + newRoom->position.x;
    newRoom->doors[1]->y = newRoom->position.y + newRoom->height;

    // left door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = newRoom->position.x;
    newRoom->doors[2]->y = 1 + rand() % (height - 2) + newRoom->position.y;

    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;
    newRoom->doors[3]->y = 1 + rand() % (height - 2) + newRoom->position.y;

    return newRoom;
}

// Rules for door positions -- 0: top 1: bottom 2: left 3: right
int connectDoors(Position *doorOne, Position *doorTwo)
{
    // 1. check if distance is smaller after moved
    // 2. check for valid position / empty char
    Position temp;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    // use while instead of for loop
    while (1)
    {
        // if (temp.x == doorTwo->x && temp.y == doorTwo->y)
        // {
        //     break;
        // }
        // Go left, cur x - 1
        if ((abs((temp.x - 1) - doorTwo->x) < abs((temp.x) - doorTwo->x)) && mvinch(temp.y, temp.x - 1) == ' ')
        {
            temp.x = temp.x - 1;
            mvprintw(temp.y, temp.x, "#");
        }
        // Go right
        else if ((abs((temp.x + 1) - doorTwo->x) < abs((temp.x) - doorTwo->x)) && mvinch(temp.y, temp.x + 1) == ' ')
        {
            temp.x = temp.x + 1;
            mvprintw(temp.y, temp.x, "#");
        }
        // Go up
        else if ((abs((temp.y - 1) - doorTwo->y) < abs((temp.y) - doorTwo->y)) && mvinch(temp.y - 1, temp.x) == ' ')
        {
            temp.y = temp.y - 1;
            mvprintw(temp.y, temp.x, "#");
        }
        // Go down
        else if ((abs((temp.y + 1) - doorTwo->y) < abs((temp.y) - doorTwo->y)) && mvinch(temp.y + 1, temp.x) == ' ')
        {
            temp.y = temp.y + 1;
            mvprintw(temp.y, temp.x, "#");
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int drawRoom(Room *room)
{
    int y;
    int x;

    // Draw top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y + room->height, x, "-");
    }
    // Draw side walls & floors
    for (y = room->position.y + 1; y < room->position.y + room->height; y++)
    {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
        {

            mvprintw(y, x, ".");
        }
    }

    // Draw Doors
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

    return 1;
}

Player *playerSetUp()
{
    Player *newPlayer; // pointer uses ->, reference uses .
    newPlayer = malloc(sizeof(Player));

    newPlayer->health = 20;
    newPlayer->position.x = 14;
    newPlayer->position.y = 14;

    playerMove(14, 14, newPlayer);

    // mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
    // // the end cursor will stop at i + 1 (which is 15)
    // move(newPlayer->position.y, newPlayer->position.x); // set back to (cur)

    return newPlayer;
}

int handleInput(int input, Player *user)
{
    int newY = user->position.y;
    int newX = user->position.x;

    switch (input)
    {
    // move up
    case 'w':
    case 'W':
        newY = user->position.y - 1;
        newX = user->position.x;
        break;

    // move left
    case 'a':
    case 'A':
        newY = user->position.y;
        newX = user->position.x - 1;
        break;

    // move down
    case 's':
    case 'S':
        newY = user->position.y + 1;
        newX = user->position.x;
        break;

    // move right
    case 'd':
    case 'D':
        newY = user->position.y;
        newX = user->position.x + 1;
        break;

    default:
        break;
    }

    checkPosition(newY, newX, user);

    return 1;
}

int playerMove(int y, int x, Player *user)
{

    mvprintw(user->position.y, user->position.x, ".");
    user->position.y = y;
    user->position.x = x;
    mvprintw(user->position.y, user->position.x, "@");
    move(user->position.y, user->position.x); // move our type cursor too

    return 1;
}

int checkPosition(int newY, int newX, Player *unit)
{
    int space;
    switch (mvinch(newY, newX)) // mvinch
    {
    case '.':
        playerMove(newY, newX, unit);
        return 1;
        break;

    default:
        move(unit->position.y, unit->position.x);
        return 0;
        break;
    }
}