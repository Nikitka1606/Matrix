#include "Explosion.h"
class Line: public Figure {
private:
    int length;
    int lineColor;
    char epilFlag;
    const int wbr[3]{1, 4, 15};
public:
    Line(int, int, int, char);
    vector<vector<int>> moveLine(vector<vector<int>>);
    vector<vector<int>> exuplosion(vector<vector<int>>);
    int getLen() const;
    ~Line();
};
