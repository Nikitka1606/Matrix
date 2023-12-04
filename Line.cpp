#include"Line.h"
Line::Line(int len, int maxY, int maxX, char epilFlag) {
    yMaxCoord = maxY;
    length = len;
    xCoord = rand() % (maxX - 2);
    yCoord = -1;
    lineColor = 2;
    this->epilFlag = epilFlag;
    if (epilFlag == 'Y' || epilFlag == 'y') { //if epilepsy mode ON, it will make lines of different color
        lineColor = rand() % 15 + 1;
    }
    /*if (epilFlag == 'Z' || epilFlag == 'z') {
        lineColor = wbr[rand() % 3];
    }*/
    sym = new Symbol();
}

void Line::exuplosion(int (*permissiveMatrix)[122]) {
    if (yCoord > length - 1) {
        for (int x = xCoord; x < xCoord + 3; x++) {
            if (x % 2 == (yCoord - length) % 2) {
                if (permissiveMatrix[yCoord - length][x] % 100 == 1) {
                    sym->clearSym(x, yCoord - length);
                }
                permissiveMatrix[yCoord - length][x]--;
            }
        }
    }
    length--;
    //return permissiveMatrix;
}

int Line::getLen() const{
    return length;
}

void Line::moveLine(int (*permissiveMatrix)[122]) {
    if (yCoord < yMaxCoord) {
        for (int x = xCoord; x < xCoord + 3; x++) {
            if (x % 2 == yCoord % 2) {
                if (epilFlag == 'z' || epilFlag == 'Z'){
                    sym->drawSym(x, yCoord, wbr[(yCoord + 2) % 3], epilFlag);
                }
                else{
                    sym->drawSym(x, yCoord, lineColor, epilFlag);
                }
                permissiveMatrix[yCoord][x]++; //if it draws the symbol it enters this to matrix
            }
        }
    }

    if (yCoord > length - 1) {
        for (int x = xCoord; x < xCoord + 3; x++) {
            if (x % 2 == (yCoord - length) % 2) {
                if (permissiveMatrix[yCoord - length][x] % 100 == 1) { //checks last two values to understand can it erase symbol from screen
                    sym->clearSym(x, yCoord - length);
                }
                permissiveMatrix[yCoord - length][x]--; // if line moves, it subtracts the tail in matrix but may not erase the symbol to not interrupt the other lines. it is the most important logic in this program
            }
        }
    }
    yCoord++;
    //return permissiveMatrix;
}

Line::~Line() {
    delete sym;
}
