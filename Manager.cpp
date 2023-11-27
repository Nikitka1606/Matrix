#include "Manager.h"
Manager::Manager(int len, int height, int width, int freq, int speed, char epilFlag, int minExplR, int maxExplR, int explFreq, char cardioMode) {
    lenLin = len;
    this->height = height;
    this->width = width;
    this->epilFlag = epilFlag;
    this->freq = freq;
    this->speed = (double)(1.0 / speed);
    spawnTime = (double)(1.0 / freq);
    minER = minExplR;
    maxER = maxExplR;
    freqExpl = explFreq;
    timeStart = 0;
    freqTime = 0.0;

    if (cardioMode == 'y' || cardioMode == 'Y') this->cardioMode = true;

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

    if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { //this one checks section of time and spawn lines with a definite chance
        freqTime = timeStart;
        if (rand() % (31 / freq) == 0) {
            Line *ln = new Line(lenLin, height, width, epilFlag);
            Lines.push_back(ln);
            linesTimeDeltas.push_back(0.0);
        }
    }

    for (size_t b = 0; b < bombs.size(); b++) { //runs through bombs container and wide the circles of explosion
        timeStart = clock();
        if ((double)(timeStart - bombsTimeDeltas[b]) / CLOCKS_PER_SEC >= 0.5) { //every 0.5 of sec it wide the circles
            bombsTimeDeltas[b] = timeStart;
            permissiveMatrix = bombs[b]->katsu(permissiveMatrix, cardioMode);
        }
        if (bombs[b]->getRad() > maxER + 2) {
            delete bombs[b];
            bombs.erase(b);
            bombsTimeDeltas.erase(b);
        }
    }

    for (size_t line = 0; line < Lines.size(); line++) { //runs through lines container and moves them
        timeStart = clock();
        if ((double)(timeStart - linesTimeDeltas[line]) / CLOCKS_PER_SEC >= speed) {
            linesTimeDeltas[line] = timeStart;

            permissiveMatrix = Lines[line]->moveLine(permissiveMatrix);
            xy = Lines[line]->getCoords();
            if (rand() % (1001 / freqExpl) == 0) { //if line moves, it can explode with a chance
                permissiveMatrix = Lines[line]->exuplosion(permissiveMatrix);
                Explosion *expl = new Explosion(xy.first + 1, xy.second, minER, maxER, height, width);
                bombs.push_back(expl);
                bombsTimeDeltas.push_back(0.0);
                permissiveMatrix = expl->katsu(permissiveMatrix, cardioMode);
            }

            if (xy.second > height + Lines[line]->getLen() || Lines[line]->getLen() < 1) {
                delete Lines[line];
                Lines.erase(line);
            }
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
