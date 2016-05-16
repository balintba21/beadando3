#include "Button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int size_x, int size_y, string felirat,vector<Szin> szin)
    : Widget(x,y,size_x,size_y,szin)
    {
        _felirat = felirat;
        _felette=false;
        _lenyomva=false;
    }
std::string Button::adat(){
    return _felirat;
};
void Button::draw(){
    gout << color(_szin[0]._r,_szin[0]._g,_szin[0]._b) << move_to(_x,_y) << box(_size_x,_size_y);
    int g=0,b=210;
    int keret=1;
    if(_lenyomva){
        gout << color(_szin[1]._r,_szin[1]._g,_szin[1]._b);
    }
    else if(_felette){
        gout << color(_szin[2]._r,_szin[2]._g,_szin[2]._b);
    }
    else{
        gout << color(_szin[3]._r,_szin[3]._g,_szin[3]._b);
    }
    gout << move_to(_x+keret,_y+keret) << box(_size_x-2*keret,_size_y-2*keret);
    gout << color(200,200,250) << move_to(_x+(_size_x-gout.twidth(_felirat))/2,_y+(_size_y-(gout.cascent()+gout.cdescent()))/2+gout.cascent()) << text(_felirat);
}
void Button::handle(genv::event ev){
    if(is_selected(ev.pos_x,ev.pos_y)){
        _felette=true;
        if(ev.type==ev_mouse && ev.button==1){
            _lenyomva=true;
        }
    }
    else if(ev.type==ev_mouse){
        _felette=false;
    }
    if(ev.button==-1){
        _lenyomva=false;
    }
}
void Button::new_y(int ujszam){
    _y=ujszam;
}
void Button::new_size_y(int ujszam){
    _size_y=ujszam;
}
void Button::action(){
}

lambdaButton::lambdaButton(int x, int y, int size_x, int size_y, string felirat,vector<Szin> szin, std::function<void()> f)
    : Button (x,y,size_x,size_y,felirat,szin)
{
    _f=f;
}
void lambdaButton::action(){
    _f();
}
