#include "Explosion.h"
Explosion::Explosion(int x, int y, int minR, int maxR, int yMax, int xMax) {
    xCoord = x;
    yCoord = y;
    this->maxR = maxR;
    this->minR = minR;
    curR = minR;
    yMaxCoord = yMax;
    xMaxCoord = xMax;
    sym = new Symbol();
    kSqueeze = 0.5;
    dx = 0;
}

int Explosion::getRad() {
    return curR;
}

vector<vector<int>> Explosion::kats(vector<vector<int>> permissiveMatrix) {
    if (curR > minR) {
        curR--;
        for (int x = xCoord - curR - 1; x <= xCoord + curR + 1; x++) {
            for (int y = yCoord - curR; y <= yCoord + curR; y++) {
                if (x >= 0 && x < xMaxCoord && y >= 0 && y < yMaxCoord) {
                    kSqueeze = curR / 1.9 / curR;
                    sqR = curR * kSqueeze;
                    val = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(sqR, 2);
                    curR -= 1.5;
                    val1 = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR / 2, 2);
                    curR += 1.5;
                    if (val <= 0.9 && val1 >= 0.9) sym->clearSym(x, y);
                }
            }
        }
        curR++;
    }

    if (curR <= maxR) {
        for (int x = xCoord - curR - 1; x <= xCoord + curR + 1; x++) {
            for (int y = yCoord - curR; y <= yCoord + curR; y++) {
                if (x >= 0 && x < xMaxCoord && y >= 0 && y < yMaxCoord) {
                    kSqueeze = curR / 1.9 / curR;
                    sqR = curR * kSqueeze;
                    val = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(sqR, 2);
                    curR -= 1.5;
                    val1 = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR / 2, 2);
                    curR += 1.5;
                    if (val <= 0.9 && val1 >= 0.9) sym->drawSym(x, y, rand() % 15 + 1, 'n');
                }
            }
        }
    }

    curR++;
    return permissiveMatrix; // IDK should I use it or not
}

Explosion::~Explosion(){
    delete sym;
}