#ifndef KEZELO_HPP_INCLUDED
#define KEZELO_HPP_INCLUDED

#include "Menu.hpp"
#include "Jatek.hpp"
#include "Koordinata.hpp"
#include "Amobakocka.hpp"

#include <vector>
#include <fstream>

using namespace std;

struct P{
    vector<vector<Amoba_kocka>> tabla;
    char nyertes;
    int kor;
    K meret;
    P(int meret,int XX,int YY);
    void uj(int x, int y,char c);
    void futtatas();
    bool allas(int nyero_minimum);
    void fajlba_mentes(string fajlnev);
    char jatek();
};

#endif
