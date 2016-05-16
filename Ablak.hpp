#ifndef ABLAK_HPP_INCLUDED
#define ABLAK_HPP_INCLUDED

#include "widgets.hpp"
#include "Button.hpp"
#include "Koordinata.hpp"

#include <vector>
#include <string>
#include <fstream>

struct Ablak{
    int _key=0,_key_db=0;
    vector<Widget*> widgets;
    vector<Button*> buttons;
    lambdaButton * kocka;
    K valasz;

    void helyem();
    K event_loop(int XX, int YY);
    Ablak(int XX,int YY,vector<vector<char>> tabla);
};

#endif
