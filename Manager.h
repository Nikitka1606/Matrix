#include "Line.h"
#include "cstdio"
#include "ctime"
class Manager {
private:
    int lenLin;
    int height;
    int width;
    int freq;
    int minER;
    int maxER;
    int freqExpl;
    char epilFlag;
    double spawnTime;
    double speed;

    clock_t timeStart;
    clock_t freqTime;
    clock_t bombTime;

    int fr;

    Symbol *sym = nullptr;

    vector<Line*> Lines;
    vector<Explosion*> bombs;
    pair<int, int> xy;
    vector<int> zeroFill;
    vector<vector<int>> permissiveMatrix;
    vector<double> linesTimeDeltas;
    vector<double> bombsTimeDeltas;
public:
    Manager(int, int, int, int, int, char, int, int, int);
    void startLines();
};
