#include "symbol.h"
#include<vector>
class Line {
private:
    int xCoord;
    int yCoord;
    int length;
    int yMaxCoord;
    int lineColor = 2;
    double speed;
    char epilFlag;
    clock_t speedTime;
    clock_t timeStart;
    pair<int, int> xy;
    Symbol* sym = new Symbol();
    
    int wbr[3]{ 1, 4, 15};
    
public:
    Line(double speed, int len, int maxY, int maxX, char epilFlag) {
        yMaxCoord = maxY;
        length = len;
        xCoord = rand() % (maxX - 2);
        yCoord = -1;
        this->epilFlag = epilFlag;
        if (epilFlag == 'Y' || epilFlag == 'y') {
            lineColor = rand() % 15 + 1;
        }    
        if (epilFlag == 'Z' || epilFlag == 'z') {
            lineColor = wbr[rand() % 3];
        }
        speedTime = 0.0;
        this->speed = speed;
    }

    pair<int, int> getLinCoords() {
        xy.first = xCoord;
        xy.second = yCoord;
        return xy;
    }

    vector<vector<int>> moveLine(vector<vector<int>> permissiveMatrix) {
        timeStart = clock();
        if ((double)(timeStart - speedTime) / CLOCKS_PER_SEC >= speed) {
            speedTime = timeStart;
               
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
        }
        return permissiveMatrix;
    }

    ~Line() {
        sym->~Symbol();
    }
};
