#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(int x, int y, int size_x, int size_y,vector<Szin> szin)
{
    _x=x;
    _y=y;
    _size_x=size_x;
    _size_y=size_y;
    _selected=false;
    _szin=szin;
}

std::string Widget::adat(){
    return "-Nincs adat-";
};
void Widget::selected(bool select){
    _selected=select;
};

bool Widget::is_selected(int mouse_x, int mouse_y) const{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}

void Widget::draw(){
}
void Widget::felette(genv::event ev){
}

void Widget::handle(event ev) {
}
int Widget::show_y(){
    return _y;
}
int Widget::show_size_y(){
    return _size_y;
}
void Widget::add_y(int plusz){
    _y+=plusz;
}
