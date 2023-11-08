#include "Manager.h"

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    int lineFreq = 0; //frequency of lines spawn
    int lineVel = 0; //velocity
    int lineLength = 0; //length
    int minExplR; //minimal Explosion radius
    int maxExplR = 0; //max radius
    int explFreq = 0; //explosion frequency
    int displayHeigth = 30;
    int displayWidth = 120;
    char EpilMode;

    bool pass = false;
    printf("Matrix: the prodolzenie\n");
    /*
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
    pass = false;*/
//next bunch of code just take input values correctly
    while (true) {
        try {
            printf("Enter the frequency of mind reading [1-30] > ");
            if (scanf_s("%d", &lineFreq) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (lineFreq < 1 || lineFreq > 30) {
                throw out_of_range("Entered frequency must be in this range: [1-30]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    while (true) {
        try {
            printf("Enter the velocity of mind reading [1-30] > ");
            if (scanf_s("%d", &lineVel) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (lineVel < 1 || lineVel > 30) {
                throw out_of_range("Entered velocity must be in this range: [1-30]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    while (true) {
        try {
            printf("Enter the length of mind reading [1-30] > ");
            if (scanf_s("%d", &lineLength) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (lineLength < 1 || lineLength > 30) {
                throw out_of_range("Entered value must be in this range: [1-30]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    while (true) {
        try {
            printf("Enter minimal radius of explosions [1-10] > ");
            if (scanf_s("%i", &minExplR) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (minExplR < 1 || minExplR > 10) {
                throw out_of_range("Entered value must be in this range: [1-10]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    while (true) {
        try {
            printf("Enter maximum radius of explosions [%i-10] > ", minExplR);
            if (scanf_s("%d", &maxExplR) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (maxExplR < 1 || maxExplR > 10) {
                throw out_of_range("Entered value must be over minimum radius and in this range: [1-10]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    while (true) {
        try {
            printf("Enter frequency of explosions [1-1000] > ");
            if (scanf_s("%d", &explFreq) != 1) {
                while (fgetc(stdin) != '\n');
                throw invalid_argument("Entered value must be integer.");
            }
            if (explFreq < 1 || explFreq > 1000) {
                throw out_of_range("Entered value must in this range: [1-1000]");
            }
            break;
        }
        catch (const invalid_argument &e) {
            fprintf(stderr, "%s\n", e.what());
        }
        catch (const out_of_range &e) {
            fprintf(stderr, "%s\n", e.what());
        }
    }

    printf("Do you want to become mad? [Y/N/Z] > ");
    while ((getchar()) != '\n');
    EpilMode = getchar();

    system("cls");

    hidecursor();
    Manager man(lineLength, displayHeigth, displayWidth, lineFreq, lineVel, EpilMode, minExplR, maxExplR, explFreq);
    while (true) {
        man.startLines();
    }
}
