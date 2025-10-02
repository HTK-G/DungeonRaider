#include <stdio.h>
#include <ncurses.h> // special header for this gaming project
#include <stdlib.h>

typedef struct Player
{
    int xPosition;
    int yPosition;
    int health;
    // Add more later on
} Player; // this gives it an abreviation so we don't need to type "struct Player", just Player

// Function declare here so we can write below main
int screenSetUp();
int mapSetUp();
Player *playerSetUp();
int handleInput(int input, Player *user);
int playerMove(int yPosition, int xPosition, Player *user);
int checkPosition(int y, int x, Player *unit);

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
    refresh();

    return 1;
}

int mapSetUp() // set up the dungeon
{
    mvprintw(13, 13, "--------"); // (y coordinate, x coordinate, "string")
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "--------");

    mvprintw(2, 20, "--------"); // (y coordinate, x coordinate, "string")
    mvprintw(3, 20, "|......|");
    mvprintw(4, 20, "|......|");
    mvprintw(5, 20, "|......|");
    mvprintw(6, 20, "|......|");
    mvprintw(7, 20, "--------");

    mvprintw(10, 40, "------------"); // (y coordinate, x coordinate, "string")
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "------------");

    return 1;
}

Player *playerSetUp()
{
    Player *newPlayer; // pointer uses ->, reference uses .
    newPlayer = malloc(sizeof(Player));

    newPlayer->health = 20;
    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;

    playerMove(14, 14, newPlayer);

    // mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
    // // the end cursor will stop at i + 1 (which is 15)
    // move(newPlayer->yPosition, newPlayer->xPosition); // set back to (cur)

    return newPlayer;
}

int handleInput(int input, Player *user)
{
    int newY;
    int newX;

    switch (input)
    {
    // move up
    case 'w':
    case 'W':
        newY = user->yPosition - 1;
        newX = user->xPosition;
        break;

    // move left
    case 'a':
    case 'A':
        newY = user->yPosition;
        newX = user->xPosition - 1;
        break;

    // move down
    case 's':
    case 'S':
        newY = user->yPosition + 1;
        newX = user->xPosition;
        break;

    // move right
    case 'd':
    case 'D':
        newY = user->yPosition;
        newX = user->xPosition + 1;
        break;

    default:
        break;
    }

    checkPosition(newY, newX, user);

    return 1;
}

int playerMove(int y, int x, Player *user)
{

    mvprintw(user->yPosition, user->xPosition, ".");
    user->yPosition = y;
    user->xPosition = x;
    mvprintw(user->yPosition, user->xPosition, "@");
    move(user->yPosition, user->xPosition); // move our type cursor too

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
        move(unit->yPosition, unit->xPosition);
        return 0;
        break;
    }
}