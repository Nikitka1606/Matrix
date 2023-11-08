#include "Explosion.h"
class Line: public Figure {
private:
    int length; //line length
    int lineColor; //color of line
    char epilFlag;
    const int wbr[3]{1, 4, 15}; //helps for z mode
public:
    Line(int, int, int, char);
    vector<vector<int>> moveLine(vector<vector<int>>); //moves line and erase its last symbols according to permissive matrix
    vector<vector<int>> exuplosion(vector<vector<int>>); //cuts one symbol at the end
    int getLen() const; //gets line length
    ~Line();
};
