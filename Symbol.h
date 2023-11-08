#include "windows.h"
#include <iostream>
using namespace std;
class Symbol {
private:
    const char zov[3]{ 'z', 'o', 'v' };
    HANDLE hConsole;
    HANDLE hOutput;
    COORD coord;
public:
    Symbol();
    void gotoxy(int column, int line); //function that can set the cursor to x;y position on the screen
    void drawSym(int, int, int, char); //set the color and draws a random symbol
    void clearSym(int, int); //clears symbol from the screen
};
