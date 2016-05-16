#include "graphics.hpp"
#include "Gephaz.hpp"
#include "kezelo.hpp"

using namespace genv;

const int XX=1200;
const int YY=600;


int main()
{
    P palya(15,XX,YY);
    char nyert=palya.jatek(XX,YY);
    cout << "A gyoztes karakter: " << nyert << endl;
    return 0;
}
/*
int main()
{
    gout.open(XX,YY);
    Gephaz gephaz(XX,YY);
    return 0;
}*/
