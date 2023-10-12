#include "gotoxy.h"
using namespace std;
class Symbol {
private:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    int numberInVec = 0;
    void drawSym(int x, int y, int color) {
        gotoxy(x, y);
        SetConsoleTextAttribute(hConsole, color);
        printf("%c", rand() % 126 + 63);      
    }

    void clearSym(int x, int y) {
        gotoxy(x, y);
        printf("%c", ' ');
    }
};
