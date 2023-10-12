#include<iostream>
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include "manager.h"
using namespace std;

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

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
    }
}
