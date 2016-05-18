#ifndef KEZELO_HPP_INCLUDED
#define KEZELO_HPP_INCLUDED

#include "Menu.hpp"
#include "Jatek.hpp"
#include "Koordinata.hpp"

#include <iostream>
#include <vector>

using namespace std;

struct P{
    vector<vector<char>> tabla;
    vector<vector<string>> menutomb;
    vector<K> nyero_helyek;
    char nyertes;
    int kor;
    K meret;
    P(int meret,int XX,int YY);
    void uj(int x, int y,char c);
    void menu();
    bool allas();
    char jatek();
};

#endif
