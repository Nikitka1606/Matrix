#include "Explosion.h"
#include"vector"
class Line: public Figure {
private:
    int length; //line length
    int lineColor; //color of line
    char epilFlag;
    const int wbr[3]{1, 4, 15}; //helps for z mode
public:
    Line(int, int, int, char);
    void moveLine(int (*permissiveMatrix)[122]); //moves line and erase its last symbols according to permissive matrix
    void exuplosion(int (*permissiveMatrix)[122]); //cuts one symbol at the end
    int getLen() const; //gets line length
    ~Line();
};
