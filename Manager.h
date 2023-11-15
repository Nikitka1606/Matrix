#include "Line.h"
#include "cstdio"
#include "ctime"
class Manager {
private:
    int lenLin; //line length
    int height;
    int width;
    int freq; // line frequency
    int minER; // minimal Explosion radius
    int maxER; // max radius
    int freqExpl; // explosion freq
    char epilFlag; // epilepsy flag
    double spawnTime; //section of time in which it will try to spawn line
    double speed; // lines speed
    bool cardioMode = false;

    clock_t timeStart;
    clock_t freqTime;

    Symbol *sym = nullptr; // works only with projection of permissive matrix

    vector<Line*> Lines; //container with lines pointers
    vector<Explosion*> bombs; //same to the circles of explosion
    pair<int, int> xy;
    vector<int> zeroFill;
    vector<vector<int>> permissiveMatrix; //this matrix will contain data of lines intersections
    vector<double> linesTimeDeltas; //containers with variables that help to determine the moment of move
    vector<double> bombsTimeDeltas; //
public:
    Manager(int, int, int, int, int, char, int, int, int, char);
    void startLines();
};
