#ifndef StaticText_HPP
#define StaticText_HPP

#include "widgets.hpp"
#include "RGB.hpp"
#include <string>
using namespace std;

class StaticText: public Widget
{
    string _szoveg;
    int _keret;
public:
    StaticText(int x, int y, int size_x, int size_y,string szoveg,vector<Szin> szin);
    virtual void draw();
    string adat();/*
    virtual void handle(genv::event ev);
    void new_szoveg(string ujszoveg);*/
};

#endif // StaticText_HPP_INCLUDED

