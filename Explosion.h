#include "Figure.h"
#include <cmath>
class Explosion: public Figure {
private:
    int minR;
    int maxR;
    int xMaxCoord;
    double curR;
    int inR;
    int inRsq;
    int val;
    int val1;
    double sqR;
    int dx;
    int x0;
    double kSqueeze;
public:
    Explosion(int, int, int, int, int, int);
    vector<vector<int>> kats(vector<vector<int>>);
    int getRad();
    ~Explosion();
};
