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
}

int Explosion::getRad() {
    return curR;
}

vector<vector<int>> Explosion::kats(vector<vector<int>> permissiveMatrix) {
    if (curR > minR){
        curR--;
        for (int x = xCoord - curR; x <= 2 * curR + xCoord; x++){
            for (int y = yCoord - curR; y <= 2 * curR + yCoord; y++){
                if ((x - xCoord) * (x - xCoord) + (y - yCoord) * (y - yCoord) - curR * curR == 0){
                    if (x > 0 && x < xMaxCoord && y > 0 && y < yMaxCoord) {
                        sym->clearSym(x, y);
                        permissiveMatrix[y][x]--;
                    }
                }
            }
        }
        curR++;
    }
    if (curR < maxR) {
        for (int x = xCoord - curR; x <= 2 * curR + xCoord; x++) {
            for (int y = yCoord - curR; y <= 2 * curR + yCoord; y++) {
                if ((x - xCoord) * (x - xCoord) + (y - yCoord) * (y - yCoord) == curR * curR) {
                    if (x > 0 && x < xMaxCoord && y > 0 && y < yMaxCoord) {
                        sym->drawSym(x, y, rand() % 15 + 1, 'n');
                        permissiveMatrix[y][x]++;
                    }
                }
            }
        }
    }
    curR++;
    return permissiveMatrix;
}

Explosion::~Explosion(){
    delete sym;
}