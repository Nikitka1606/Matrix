#include "Explosion.h"
class Line: public Figure {
private:
    int length; //line length
    int lineColor; //color of line
    char epilFlag;
    const int wbr[3]{1, 4, 15}; //helps for z mode
public:
    Line(int, int, int, char);
    MyVector<MyVector<int>> moveLine(MyVector<MyVector<int>>); //moves line and erase its last symbols according to permissive matrix
    MyVector<MyVector<int>> exuplosion(MyVector<MyVector<int>>); //cuts one symbol at the end
    int getLen() const; //gets line length
    ~Line();
};
