#include "Symbol.h"
#include "MyVector.h"
class Figure{
protected:
    int xCoord;
    int yCoord;
    int yMaxCoord;
    pair<int, int> xy;
    Symbol* sym = nullptr;
public:
    pair<int, int> getCoords();
};
