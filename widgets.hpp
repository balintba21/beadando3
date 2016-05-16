#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include "RGB.hpp"

#include <string>
#include <vector>
using namespace std;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
    bool _selected;
    vector<Szin> _szin;
public:
    Widget(int x, int y, int size_x, int size_y,vector<Szin> szin);
    virtual bool is_selected(int mouse_x, int mouse_y) const;
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void selected(bool select);
    virtual void felette(genv::event ev);
    int show_y();
    int show_size_y();
    void add_y(int plusz);
    virtual string adat();
};

#endif
