#include "Manager.h"
Manager::Manager(int len, int height, int width, int freq, int speed, char epilFlag) {
    lenLin = len;
    this->height = height;
    this->width = width;
    this->epilFlag = epilFlag;
    this->freq = freq;
    this->speed = (double)(1.0 / speed);
    spawnTime = (double)(1.0 / freq);

    freqTime = 0.0;
    timeStart = 0.0;

    for (int j = 0; j <= width; j++) {
        zeroFill.push_back(0);
    }
    for (int i = 0; i <= height + 1; i++) {
        permissiveMatrix.push_back(zeroFill);
    }
}
void Manager::startLines() {
    timeStart = clock();

    if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) {
        freqTime = timeStart;
        if (rand() % (31 / freq) == 0) {
            Line *ln = new Line(lenLin, height, width, epilFlag);
            Lines.push_back(ln);
            timeDeltas.push_back(0.0);
        }
    }


    for (size_t line = 0; line < Lines.size(); line++) {
        timeStart = clock();
        if ((double)(timeStart - timeDeltas[line]) / CLOCKS_PER_SEC >= speed) {
            timeDeltas[line] = timeStart;
            permissiveMatrix = Lines[line]->moveLine(permissiveMatrix);

            xy = Lines[line]->getLinCoords();

            if (xy.second > height + lenLin) {
                delete Lines[line];
                Lines.erase(Lines.begin() + line);
            }
        }
    }
    /*for (int i = 0; i <= height + 1; i++) { //display of permissive Matrix for debug
        for (int j = 0; j < width; j++) {
            gotoxy(j, i+ 31);
            if (permissiveMatrix[i][j] > 0) {
                printf("%i", permissiveMatrix[i][j]);
            }
            else {
                printf("%c", ' ');
            }
        }
    }*/
}
