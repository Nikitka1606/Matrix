#include "Symbol.h"
#include<vector>
class Line {
private:
    int xCoord;
    int yCoord;
    int length;
    int yMaxCoord;
    int lineColor;
    char epilFlag;
    pair<int, int> xy;
    Symbol* sym = nullptr;
    const int wbr[3]{1, 4, 15};
public:
    Line(int, int, int, char);
    pair<int, int> getLinCoords();
    vector<vector<int>> moveLine(vector<vector<int>>);
    ~Line();
};
