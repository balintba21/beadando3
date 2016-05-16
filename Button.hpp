#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widgets.hpp"
#include "RGB.hpp"
#include <string>

using namespace std;

class Button: public Widget
{
    string _felirat;
    bool _felette,_lenyomva;
public:
    Button(int x, int y, int size_x, int size_y,string felirat,vector<Szin> szin);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void action();
    string adat();
    void new_y(int ujszam);
    void new_size_y(int ujszam);
};

#include <functional>
class lambdaButton: public Button{
    function<void()> _f;
public:
    lambdaButton(int x, int y, int size_x, int size_y,string felirat,vector<Szin> szin, function<void()> f);
    virtual void action();
};

#endif // GOMB_HPP_INCLUDED

