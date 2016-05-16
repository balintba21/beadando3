#ifndef KEZELO_HPP_INCLUDED
#define KEZELO_HPP_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

struct P{
    vector<vector<char>> tabla;
    char nyertes;
    P(int meret,int XX,int YY);
    void uj(int x, int y,char c);
    bool allas();
    char jatek(int XX,int YY);
};

#endif
