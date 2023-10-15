#include "symbol.h"
#include<vector>
class Line {
private:
    int xCoord;
    int yCoord;
    int length;
    int yMaxCoord;
    int lineColor = 2;
    pair<int, int> xy;
    Symbol* sym = new Symbol();
public:
    Line(int speed, int len, int maxY, int maxX, bool epilFlag) {
        yMaxCoord = maxY;
        length = len;
        xCoord = rand() % (maxX - 2);
        yCoord = 0;
        if (epilFlag) {
            lineColor = rand() % 15 + 1;
        }
    }

    pair<int, int> getLinCoords() {
        xy.first = xCoord;
        xy.second = yCoord;
        return xy;
    }

    vector<pair<int, int>> moveLine() {
        vector<pair<int, int>> backCoords;
        pair<int, int> pc;
        if (yCoord < yMaxCoord) {
            for (int x = xCoord; x < xCoord + 3; x++) {
                if (x % 2 == yCoord % 2) {
                    sym->drawSym(x, yCoord, lineColor);
                    pc.first = x;
                    pc.second = yCoord;
                    backCoords.push_back(pc);
                }
            }
        }
        yCoord++;
        return backCoords;
    }

    void clearTail(vector<vector<int>> permissiveMatrix) {        
        if (yCoord > length && yCoord - length <= yMaxCoord) {
            for (int x = xCoord; x < xCoord + 3; x++) {                
                if (permissiveMatrix[yCoord - length - 1][x] == 1 && (x % 2 == (yCoord - length - 1) % 2)) {
                    sym->clearSym(x, yCoord - length - 1);
                }
                if (yCoord > length + 1) {
                    if (permissiveMatrix[yCoord - length - 2][x] == 0) {
                        sym->clearSym(x, yCoord - length - 2);
                    }
                }
            }
        }            
    }
    ~Line() {
        sym->~Symbol();
    }
};
