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

    fr = 0;

    for (int j = 0; j <= width; j++) {
        zeroFill.push_back(0);
    }
    for (int i = 0; i <= height + 1; i++) {
        permissiveMatrix.push_back(zeroFill);
    }

    sym = new Symbol();
}
void Manager::startLines() {
    timeStart = clock();

    if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) {
        freqTime = timeStart;
        if (rand() % (31 / freq) == 0) {
            Line *ln = new Line(lenLin, height, width, epilFlag);
            Lines.push_back(ln);
            linesTimeDeltas.push_back(0.0);
        }
    }

    /*if (fr == 0) {
        fr++;
        Explosion *expl = new Explosion(50, 15, 2, 6, height, width);
        bombs.push_back(expl);
        sym->gotoxy(0,0);
        printf("%i", fr - 1);
    }

    for (size_t b = 0; b < bombs.size(); b++) {
        if ((double) (timeStart - bombTime) / CLOCKS_PER_SEC >= 0.1) {
            bombTime = timeStart;
            permissiveMatrix = bombs[b]->kats(permissiveMatrix);
            sym->gotoxy(0,0);
            printf("%i", fr - 1);
            fr++;
        }
        if (bombs[b]->getRad() > 6) {
            delete bombs[b];
            bombs.erase(bombs.begin() + b);
        }
    }*/

    for (size_t line = 0; line < Lines.size(); line++) {
        timeStart = clock();
        if ((double)(timeStart - linesTimeDeltas[line]) / CLOCKS_PER_SEC >= speed) {
            linesTimeDeltas[line] = timeStart;

            permissiveMatrix = Lines[line]->moveLine(permissiveMatrix);
            xy = Lines[line]->getCoords();
            if (rand() % 10 == 0) {
                permissiveMatrix = Lines[line]->exuplosion(permissiveMatrix);
                Explosion *expl = new Explosion(xy.first + 1, xy.second, 2, 10, height, width);
                bombs.push_back(expl);
            }

            if (xy.second > height + Lines[line]->getLen() || Lines[line]->getLen() < 1) {
                delete Lines[line];
                Lines.erase(Lines.begin() + line);
            }
        }
    }

    if ((double) (timeStart - bombTime) / CLOCKS_PER_SEC >= 0.5) {
        for (size_t b = 0; b < bombs.size(); b++) {
            if (bombs[b]->getRad() > 10) {
                delete bombs[b];
                bombs.erase(bombs.begin() + b);
            }
            bombTime = timeStart;
            permissiveMatrix = bombs[b]->kats(permissiveMatrix);
        }
    }
    /*for (int i = 0; i <= height + 1; i++) { //display of permissive Matrix for debug
        for (int j = 0; j < width; j++) {
            sym->gotoxy(j, i + 31);
            if (permissiveMatrix[i][j] > 0) {
                printf("%i", permissiveMatrix[i][j]);
            }
            else {
                printf("%c", ' ');
            }
        }
    }*/
}
