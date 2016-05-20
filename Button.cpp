#include "Button.hpp"
#include "graphics.hpp"

using namespace genv;

Button::Button(int x, int y, int size_x, int size_y,float keret,string stilus,float betu_meret,bool engedelyezve, string felirat,vector<Szin> szin)
    : Widget(x,y,size_x,size_y,szin)
    {
        _engedelyezve=engedelyezve;
        _stilus=stilus;
        _felirat = felirat;
        _felette=false;
        _lenyomva=false;
        _keret=keret;
        _betu_meret=betu_meret;
    }
std::string Button::adat(){
    return _felirat;
};
void Button::draw(){
    gout << color(_szin[0]._r,_szin[0]._g,_szin[0]._b) << move_to(_x,_y) << box(_size_x,_size_y);

    if(_lenyomva && _engedelyezve){
        gout << color(_szin[1]._r,_szin[1]._g,_szin[1]._b);
    }
    else if(_felette && _engedelyezve){
        gout << color(_szin[2]._r,_szin[2]._g,_szin[2]._b);
    }
    else{
        gout << color(_szin[3]._r,_szin[3]._g,_szin[3]._b);
    }
    gout << move_to(_x+_keret,_y+_keret) << box(_size_x-2*_keret,_size_y-2*_keret);
    gout << color(_szin[4]._r,_szin[4]._g,_szin[4]._b) << move_to(_x+(_size_x-gout.twidth(_felirat))/2,_y+(_size_y-(gout.cascent()+gout.cdescent()))/2/*+gout.cascent()*//*A másik font miatt*/) << text(_felirat);
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

lambdaButton::lambdaButton(int x, int y, int size_x, int size_y,float keret,string stilus,float betu_meret,bool engedelyezve,  string felirat,vector<Szin> szin, std::function<void()> f)
    : Button (x,y,size_x,size_y,keret,stilus,betu_meret,engedelyezve, felirat,szin)
{
    _f=f;
}
void lambdaButton::action(){
    if(_engedelyezve) _f();
}
