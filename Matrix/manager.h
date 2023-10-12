#include "line.h"
#include<time.h>
#include<stdio.h>
using namespace std;
class Manager {
private:
    int lenLin;
    int xL;
    int yL;
    int heigth;
    int width;
    int linY;
    int linX;
    int freq;
    int countOfLines;
    int countOfCoords;
    bool epilFlag;
    double spawnTime;
    double speed;

    clock_t timeStart;
    clock_t freqTime;
    clock_t speedTime;
    clock_t timeSec;

    vector<Line> Lines;
    pair<int, int> xy;
    pair<int, int> xyBC;
    vector<pair<int, int>> toClear;
    vector<pair<int, int>> backCoords;
    vector<int> zeroFill;
    vector<vector<int>> permissiveMatrix;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    Manager(int len, int heigth, int width, int freq, int speed, bool epilFlag) {        
        lenLin = len;
        this->heigth = heigth;
        this->width = width;
        this->epilFlag = epilFlag;
        this->freq = freq;
        this->speed = (double)(1.0 / speed);
        spawnTime = (double)(1.0 / freq);

        freqTime = 0.0;
        timeStart = 0.0;
        speedTime = 0.0;
        timeSec = 0.0;        
        countOfLines = 0;     

        for (int j = 0; j < width; j++) {
            zeroFill.push_back(0);
        }
        for (int i = 0; i <= heigth + 1; i++) {
            permissiveMatrix.push_back(zeroFill);
        }
    }
    void startLines() {
        timeStart = clock();
        //if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { // #1 ������������ �� �������, �������������� �������� n �����
        //    freqTime = timeStart;                                           // �������� �����: ����� �� ��������� �������� �� ����, � �������� �� ��������� ����� �� ��������
        //    if (counter == freq) {                                          // ���� ������� ���� �� ����� �������������, � �� ���������, ��� ����� �����.
        //        counter = 0;
        //        spawnsLeft = spawnFreq;
        //        spawnFreq = freq;
        //    }
        //    else {
        //        spawnFreq -= spawnsLeft;
        //        spawnsLeft = rand() % spawnFreq;                            
        //    }
        //    for (int line = 0; line < spawnsLeft; line++) {
        //        Line* ln = new Line(speed, lenLin, heigth, width, epilFlag);
        //        Lines.push_back(*ln);
        //    }
        //    if (counter == 0) {
        //        spawnsLeft = 0;
        //    }
        //    counter++;                                                      //����� #1
        //}

        if ((double)(timeStart - freqTime) / CLOCKS_PER_SEC >= spawnTime) { //#2 ����� "�����" �����, �� �������� �����: ����� ����� ���������
            freqTime = timeStart;
            if (rand() % (31 / freq) == 0) {
                Line* ln = new Line(speed, lenLin, heigth, width, epilFlag);
                Lines.push_back(*ln);
            }
        }              //����� #2

        if ((double)(timeStart - speedTime) / CLOCKS_PER_SEC >= speed) {
            speedTime = timeStart; 

            for (size_t line = 0; line < Lines.size(); line++) {    
                xy = Lines[line].getLinCoords();                                           

                backCoords = Lines[line].moveLine();

                if (xy.second < heigth) {
                    for (size_t i = 0; i < backCoords.size(); i++) {
                        xL = backCoords[i].first;
                        yL = backCoords[i].second;                        
                        permissiveMatrix[yL][xL]++;
                        toClear.push_back(backCoords[i]);
                    }
                    if (backCoords.size() == 2) {
                        toClear[toClear.size() - 2].first += width + 1;
                    }
                }

                Lines[line].clearTail(permissiveMatrix);

                if (xy.second > lenLin - 1) {
                    if (xy.second < heigth + lenLin) {
                        if (toClear[0].first >= width + 1) {
                            toClear[0].first -= width + 1;
                            countOfCoords = 2;
                        }
                        else {
                            countOfCoords = 1;
                        }
                        for (size_t i = 0; i < countOfCoords; i++) {
                            xL = toClear[0].first;
                            yL = toClear[0].second;
                            permissiveMatrix[yL][xL]--;
                            toClear.erase(toClear.begin());
                        }
                    }
                }                
                                
                if (xy.second > heigth + lenLin ) {
                    Lines[line].~Line();
                    Lines.erase(Lines.begin() + line);
                }                
            }

            for (int i = 0; i < heigth; i++) { //��������� ������� ���������� ��� �������� ��������� ��� �������
                for (int j = 0; j < width; j++) {
                    if (permissiveMatrix[i][j] != 0) {
                        gotoxy(j, i + 30);
                        printf("%i", permissiveMatrix[i][j]);
                    }
                    else {
                        gotoxy(j, i + 30);
                        printf("%c", ' ');
                    }
                }
            }
        }
    }
};
