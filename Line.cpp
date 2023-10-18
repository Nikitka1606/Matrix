#include"Line.h"
Line::Line(int len, int maxY, int maxX, char epilFlag) {
    yMaxCoord = maxY;
    length = len;
    xCoord = rand() % (maxX - 2);
    yCoord = -1;
    lineColor = 2;
    this->epilFlag = epilFlag;
    if (epilFlag == 'Y' || epilFlag == 'y') {
        lineColor = rand() % 15 + 1;
    }
    if (epilFlag == 'Z' || epilFlag == 'z') {
        lineColor = wbr[rand() % 3];
    }
    sym = new Symbol();
}

pair<int, int> Line::getLinCoords() {
    xy.first = xCoord;
    xy.second = yCoord;
    return xy;
}

vector<vector<int>> Line::moveLine(vector<vector<int>> permissiveMatrix) {
    if (yCoord < yMaxCoord) {
        for (int x = xCoord; x < xCoord + 3; x++) {
            if (x % 2 == yCoord % 2) {
                sym->drawSym(x, yCoord, lineColor, epilFlag);
                permissiveMatrix[yCoord][x]++;
            }
        }
    }

    if (yCoord > length - 1) {
        for (int x = xCoord; x < xCoord + 3; x++) {
            if (x % 2 == (yCoord - length) % 2) {
                if (permissiveMatrix[yCoord - length][x] == 1) {
                    sym->clearSym(x, yCoord - length);
                }
                permissiveMatrix[yCoord - length][x]--;
            }
        }
    }
    yCoord++;
    return permissiveMatrix;
}

Line::~Line() {
    delete sym;
}
