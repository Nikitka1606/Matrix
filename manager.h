#include "line.h"
#include<time.h>
#include<stdio.h>
using namespace std;
class Manager {
private:
    int lenLin;
    int heigth;
    int width;
    int freq;
    char epilFlag;
    double spawnTime;
    double speed;

    clock_t timeStart;
    clock_t freqTime;

    vector<Line> Lines;
    pair<int, int> xy;
    vector<int> zeroFill;
    vector<vector<int>> permissiveMatrix;
public:
    Manager(int len, int heigth, int width, int freq, int speed, char epilFlag) {        
        lenLin = len;
        this->heigth = heigth;
        this->width = width;
        this->epilFlag = epilFlag;
        this->freq = freq;
        this->speed = (double)(1.0 / speed);
        spawnTime = (double)(1.0 / freq);

        freqTime = 0.0;
        timeStart = 0.0;  

        for (int j = 0; j <= width; j++) {
            zeroFill.push_back(0);
        }
        for (int i = 0; i <= heigth + 1; i++) {
            permissiveMatrix.push_back(zeroFill);
        }
    }
    void startLines() {
        timeStart = clock();

        if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { 
            freqTime = timeStart;
            if (rand() % (31 / freq) == 0) {
                Line* ln = new Line(speed, lenLin, heigth, width, epilFlag);
                Lines.push_back(*ln);
            }
        }

        for (size_t line = 0; line < Lines.size(); line++) {                                                               

            permissiveMatrix = Lines[line].moveLine(permissiveMatrix);

            xy = Lines[line].getLinCoords();
                                
            if (xy.second > heigth + lenLin ) {
                Lines[line].~Line();
                Lines.erase(Lines.begin() + line);
            }                
        }
        /*for (int i = 0; i <= heigth + 1; i++) { //display of permissive Matrix for debug
            for (int j = 0; j < width; j++) {
                gotoxy(j, i+ 31);
                if (permissiveMatrix[i][j] > 0) {                        
                    printf("%i", permissiveMatrix[i][j]);
                }
                else {
                    printf("%c", ' ');
                }
            }
        }*/
    }
};
