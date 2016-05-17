#include "StaticText.hpp"
#include "graphics.hpp"

using namespace genv;

StaticText::StaticText(int x, int y, int size_x, int size_y, string szoveg,vector<Szin> szin)
    : Widget(x,y,size_x,size_y,szin)
    {
        _szoveg = szoveg;
        _keret=2;
    }
std::string StaticText::adat(){
    return _szoveg;
};
void StaticText::draw(){
    int hezag=8,keret=0;
    if(_selected) gout << color(_szin[1]._r,_szin[1]._g,_szin[1]._b) << move_to(_x,_y) << box(_size_x,_size_y), keret=_keret;
    gout << color(_szin[0]._r,_szin[0]._g,_szin[0]._b) << move_to(_x+keret,_y+keret) << box(_size_x-2*keret,_size_y-2*keret) << color(_szin[2]._r,_szin[2]._g,_szin[2]._b) << move_to(_x+hezag,_y+(_size_y-(gout.cascent()+gout.cdescent()))/2/*+gout.cascent()*/) << text(_szoveg);
}/*
void StaticText::new_szoveg(string ujszoveg){
    _szoveg=ujszoveg;
}
void StaticText::handle(genv::event ev){
    if(ev.type == ev_key){
        int betukod=ev.keycode;
        if(betukod>=32 && betukod<=252 && _size_x>=gout.twidth(_szoveg)+8){
            _szoveg+=betukod;
        }
        else if(betukod==8){
            _szoveg=_szoveg.substr(0,_szoveg.length()-1);
        }
    }
}*/

