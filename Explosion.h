#include "Figure.h"
class Explosion: public Figure {
private:
    int minR;
    int maxR;
    int xMaxCoord;
    int curR;
public:
    Explosion(int, int, int, int, int, int);
    vector<vector<int>> kats(vector<vector<int>>);
    int getRad();
    ~Explosion();
};
