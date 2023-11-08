#include "Figure.h"
#include <cmath>
class Explosion: public Figure {
private:
    int minR;
    int maxR;
    int xMaxCoord;
    double curR;
    int val;
    int val1;
    double kSqueeze;
public:
    Explosion(int, int, int, int, int, int);
    vector<vector<int>> katsu(vector<vector<int>>, bool); //spawn and widen the circle of explosion
    int getRad();
    ~Explosion();
};
