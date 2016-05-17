#include "Ablak.hpp"
#include "graphics.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace genv;
using namespace std;

void Ablak::helyem(K hely){
    valasz=hely;
}

K Ablak::event_loop(int XX, int YY){
    gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
    for (size_t i=0;i<buttons.size();i++) {
        buttons[i]->draw();
    }
    gout << refresh;
    event ev;
    bool esemeny=false;
    while(gin >> ev && ev.keycode!=key_escape && !esemeny){
        for (size_t i=0;i<buttons.size();i++) {
            buttons[i]->handle(ev);
        }
        if (ev.type == ev_mouse && ev.button==btn_left){
            for (size_t i=0;i<buttons.size();i++) {
                if(buttons[i]->is_selected(ev.pos_x, ev.pos_y)) buttons[i]->action(), esemeny=true;
            }
        }
        gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
        for (size_t i=0;i<buttons.size();i++) {
            buttons[i]->draw();
        }
        gout << refresh;
    }
    if(ev.keycode==key_escape) valasz._y=-1;
    return valasz;
};
