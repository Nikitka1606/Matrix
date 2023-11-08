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
    kSqueeze = 0.52;
}

int Explosion::getRad() {
    return curR;
}

vector<vector<int>> Explosion::katsu(vector<vector<int>> permissiveMatrix, bool cardioMode) {
    for (int x = xCoord - curR - 1; x <= xCoord + curR + 1; x++) {
        for (int y = yCoord - curR - 1; y <= yCoord + curR + 1; y++) { //runs through coordinates where the circle may be
            if (x >= 0 && x < xMaxCoord && y >= 0 && y < yMaxCoord) { //in screen check
                if (curR > minR) { //it will do smth if it is not the first call
                    if (cardioMode) { //cardio mode in develop
                        val = pow(xCoord, 2) + pow(y - yCoord - sqrt(abs(x - xCoord)), 2);
                        if (val <= 100) {
                            if (permissiveMatrix[y][x] == 100) sym->clearSym(x, y);
                            permissiveMatrix[y][x] -= 100;
                        }
                    }
                    else{
                        curR--; //it will clear the inner circle
                        val = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR / 1.9, 2); //ellipse equation with squeezed y-axis
                        curR -= 1.5;
                        val1 = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR * kSqueeze, 2); //the same one but do it with smaller radius
                        curR += 2.5;
                        if (val <= 0.9 && val1 >= 0.9) { //find the intersection to draw a perfect circle
                            if (permissiveMatrix[y][x] == 100) sym->clearSym(x, y); //of course, according to the permissive matrix (it works only with explosion circles as not to touch the lines when erasing)
                            permissiveMatrix[y][x] -= 100;
                        }
                    }

                }
                //same thing but draws the symbol anyway
                if (curR <= maxR + 1) {
                    if (cardioMode) {
                        val = pow(xCoord, 2) + pow(y - yCoord - sqrt(abs(x - xCoord)), 2);
                        if (val <= 10) {
                            sym->drawSym(x, y, rand() % 15 + 1, 'n');
                            permissiveMatrix[y][x] += 100;
                        }
                    }
                    else {
                        val = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR / 1.9, 2);
                        curR -= 1.5;
                        val1 = pow(x - xCoord, 2) / pow(curR, 2) + pow(y - yCoord, 2) / pow(curR * kSqueeze, 2);
                        curR += 1.5;
                        if (val <= 0.9 && val1 >= 0.9) {
                            sym->drawSym(x, y, rand() % 15 + 1, 'n');
                            permissiveMatrix[y][x] += 100;
                        }
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