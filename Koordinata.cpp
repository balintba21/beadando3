#include "Koordinata.hpp"

K::K(int x, int y){
    _x=x;
    _y=y;
}
K::K(){}
bool K::operator==(K masik){
    if(_x==masik._x && _y==masik._y) return true;else false;
}

