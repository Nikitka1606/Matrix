#include "Manager.h"
Manager::Manager(int len, int height, int width, int freq, int speed, char epilFlag, int minExplR, int maxExplR, int explFreq) {
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

    for (size_t b = 0; b < bombs.size(); b++) {
        timeStart = clock();
        if ((double)(timeStart - bombsTimeDeltas[b]) / CLOCKS_PER_SEC >= 0.5) {
            bombsTimeDeltas[b] = timeStart;
            permissiveMatrix = bombs[b]->kats(permissiveMatrix);
        }
        if (bombs[b]->getRad() > 11) {
            delete bombs[b];
            bombs.erase(bombs.begin() + b);
            bombsTimeDeltas.erase(bombsTimeDeltas.begin() + b);
        }
    }

    for (size_t line = 0; line < Lines.size(); line++) {
        timeStart = clock();
        if ((double)(timeStart - linesTimeDeltas[line]) / CLOCKS_PER_SEC >= speed) {
            linesTimeDeltas[line] = timeStart;

            permissiveMatrix = Lines[line]->moveLine(permissiveMatrix);
            xy = Lines[line]->getCoords();
            if (rand() % freqExpl == 0) {
                permissiveMatrix = Lines[line]->exuplosion(permissiveMatrix);
                Explosion *expl = new Explosion(xy.first + 1, xy.second, minER, maxER, height, width);
                bombs.push_back(expl);
                bombsTimeDeltas.push_back(0.0);
                permissiveMatrix = expl->kats(permissiveMatrix);
            }

            if (xy.second > height + Lines[line]->getLen() || Lines[line]->getLen() < 1) {
                delete Lines[line];
                Lines.erase(Lines.begin() + line);
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
