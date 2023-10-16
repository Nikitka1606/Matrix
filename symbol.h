#include "gotoxy.h"
using namespace std;
class Symbol {
private:
    char zov[3]{ 'z', 'o', 'v' };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    int numberInVec = 0;
    void drawSym(int x, int y, int color, char epilMode) {
        gotoxy(x, y);
        SetConsoleTextAttribute(hConsole, color);
          
        if (epilMode == 'Z' || epilMode == 'z') {
            printf("%c", zov[rand() % 3]);
        }
        else {
            printf("%c", rand() % 126 + 63);
        }
    }

    void clearSym(int x, int y) {
        gotoxy(x, y);
        printf("%c", ' ');
    }
};
