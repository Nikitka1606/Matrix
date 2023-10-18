#include "Symbol.h"
void Symbol::gotoxy(int column, int line)
{
    coord.X = column;
    coord.Y = line;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, coord);
}
Symbol::Symbol() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Symbol::drawSym(int x, int y, int color, char epilMode) {
    gotoxy(x, y);
    SetConsoleTextAttribute(hConsole, color);

    if (epilMode == 'Z' || epilMode == 'z') {
        printf("%c", zov[rand() % 3]);
    }
    else {
        printf("%c", rand() % 126 + 63);
    }
}

void Symbol::clearSym(int x, int y) {
    gotoxy(x, y);
    printf("%c", ' ');
}
