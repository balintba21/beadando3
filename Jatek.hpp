#ifndef JATEK_HPP
#define JATEK_HPP

#include "Ablak.hpp"
#include "StaticText.hpp"

class Jatek: public Ablak
{
    StaticText * kiir1;
    public:
    Jatek(int XX,int YY,vector<vector<char>> tabla,string uzenet);
    K event_loop(int XX, int YY);
};

#endif // JATEK_HPP_INCLUDED
