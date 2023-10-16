#include<iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<vector>
#include<time.h>
using namespace std;

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, coord);
}

class Symbol {
private:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    void drawSym(int x, int y, int color) {
        for (int s = x; s < x + 3; s++) {
            gotoxy(s, y);
            SetConsoleTextAttribute(hConsole, color);
            if (y % 2 == s % 2) {
                printf("%c", rand() % 126 + 63);
            }
            else {
                printf("%c", ' ');
            }
        }
    }
    void clearSym(int x, int y) {
        for (int i = x; i < x + 3; i++) {
            gotoxy(i, y);
            printf("%c", ' ');
        }
    }
};

class Line {
private:
    int length;
    int xCoord;
    int yMaxCoord;
    int lineColor = 2;
    Symbol* sym = new Symbol();
public:
    int yCoord = 0;
    Line(int speed, int len, int maxY, int maxX, bool epilFlag) {
        yMaxCoord = maxY;
        length = len - 1;
        xCoord = rand() % maxX;
        if (epilFlag) {
            lineColor = rand() % 16 - 1;
        }
    }
    void moveLine() {
        if (yCoord > length) {
            sym->clearSym(xCoord, yCoord - length - 1);
        }
        if (yCoord < yMaxCoord) {
            sym->drawSym(xCoord, yCoord, lineColor);
        }
        yCoord++;

    }
    ~Line() {
        sym->~Symbol();
    }
};

using namespace std;
class Manager {
private:
    int lenLin;
    int heigth;
    int width;
    //int spawnFreq;
    //int spawnsLeft;
    //int counter;
    int freq;
    //int localRand = 0;
    //int countOfSpawns[10];
    int countOfLines;
    bool epilFlag;
    double spawnTime;
    double speed;
    clock_t timeStart;
    clock_t freqTime;
    clock_t speedTime;
    clock_t timeSec;
    vector<Line> Lines;
public:
    Manager(int len, int heigth, int width, int freq, int speed, bool epilFlag) {
        lenLin = len;
        this->heigth = heigth;
        this->width = width;
        this->epilFlag = epilFlag;
        freqTime = 0.0;
        timeStart = 0.0;
        speedTime = 0.0;
        timeSec = 0.0;
        this->freq = freq;
        countOfLines = 0;
        //spawnFreq = freq;
        spawnTime = (double)(1.0 / freq);
        //spawnsLeft = 0;
        //counter = 0;
        this->speed = (double)(1.0 / speed);

    }
    void startLines() {
        timeStart = clock();
        //if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { // #1 рандомизация по частоте, гарантированно выпадает n линий
        //    freqTime = timeStart;                                           // выглядит криво: спавн не аккуратно размазан по окну, а вылезает по нескольку линий за итерацию
        //    if (counter == freq) {                                          // надо сделать один из типов распределения, а не случайное, как вышло здесь.
        //        counter = 0;
        //        spawnsLeft = spawnFreq;
        //        spawnFreq = freq;
        //    }
        //    else {
        //        spawnFreq -= spawnsLeft;
        //        spawnsLeft = rand() % spawnFreq;                            
        //    }
        //    for (int line = 0; line < spawnsLeft; line++) {
        //        Line* ln = new Line(speed, lenLin, heigth, width, epilFlag);
        //        Lines.push_back(*ln);
        //    }
        //    if (counter == 0) {
        //        spawnsLeft = 0;
        //    }
        //    counter++;                                                      //конец #1
        //}

        if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { //#2 более "тупой" метод, но выглядит лучше: спавн более случайный
            freqTime = timeStart;
            if (rand() % 1 / freq == 0) {
                Line* ln = new Line(speed, lenLin, heigth, width, epilFlag);
                Lines.push_back(*ln);
                countOfLines++;
            }
        }                                                                   //конец #2

        if ((double)(timeStart - speedTime) / CLOCKS_PER_SEC >= speed) {
            speedTime = timeStart;
            for (int line = 0; line < Lines.size(); line++) {
                Lines[line].moveLine();
                if (Lines[line].yCoord > heigth + lenLin - 1) {
                    Lines[line].~Line();
                    Lines.erase(Lines.begin() + line);
                }
            }
        }

        //if ((double)(timeStart - timeSec) / CLOCKS_PER_SEC >= 1.1) { //тут я смотрю количесвто линий за секнду - их количесвто соответсвует частоте,
        //    timeSec = timeStart;                                     //так что буду считать метод #2 вполне удачным
        //    gotoxy(0, 0);
        //    printf("%i", countOfLines);
        //    countOfLines = 0;
        //}
    }
};


int main()
{
    int lineFreq = 0;
    int lineVel = 0;
    int lineLength = 0;
    int displayHeigth = 30;
    int displayWidth = 120;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool epilMode = false;
    char EpilMode;

    bool pass = false;
    printf("Matrix: the nachalo\n");
    while (pass == false) {
        printf("Enter the frequency of mind reading [1-30] > ");
        scanf_s("%i", &lineFreq);
        if (lineFreq > 30 || lineFreq < 1) {
            printf("Entered frequency must be in this range: [1-30]\n");
        }
        else {
            pass = true;
        }
    }
    pass = false;

    while (pass == false) {
        printf("Enter the veilocity of mind reading [1-30] > ");
        scanf_s("%d", &lineVel);
        if (lineVel > 30 || lineVel < 1) {
            printf("Entered veilocity must be in this range: [1-30]\n");
        }
        else {
            pass = true;
        }
    }
    pass = false;

    while (pass == false) {
        printf("Enter the length of mind reading [1-30] > ");
        scanf_s("%d", &lineLength);
        if (lineLength > 30 || lineLength < 1) {
            printf("Entered the length must be in this range: [1-30]\n");
        }
        else {
            pass = true;
        }
    }
    pass = false;

    while (pass == false) {
        printf("Do you want to become mad? [Y/N] > ");
        while ((getchar()) != '\n');
        EpilMode = getchar();
        if (EpilMode == 'Y' || EpilMode == 'y') {
            epilMode = true;
        }
        pass = true;
    }
    system("cls");

    hidecursor();
    Manager man(lineLength, displayHeigth, displayWidth, lineFreq, lineVel, epilMode);
    while (true) {
        man.startLines();
        gotoxy(0, 0);
        SetConsoleTextAttribute(hConsole, 15);
    }
}
