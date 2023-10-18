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
    void gotoxy(int column, int line);
    void drawSym(int, int, int, char);
    void clearSym(int, int);
};
