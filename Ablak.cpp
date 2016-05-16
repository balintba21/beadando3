#include "Ablak.hpp"
#include "graphics.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace genv;
using namespace std;

void Ablak::helyem(K hely){
    cout << hely._x << " : " << hely._y;
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
    cout << "Rajz kesz" << endl;
    return valasz;
};

Ablak::Ablak(int XX,int YY,vector<vector<char>> tabla){
    Szin gomb_keret(0,0,100);
    Szin gomb_aktiv(0,150,175);
    Szin gomb_felette(0,100,200);
    Szin gomb_hatter(0,0,210);
    vector<Szin> gomb_szin={gomb_keret,gomb_aktiv,gomb_felette,gomb_hatter};
    /*Szin szam_hatter(0,0,100);
    Szin szam_keret(200,200,250);
    Szin szam_szoveg(205,205,255);
    vector<Szin> szam_szin={szam_hatter,szam_keret,szam_szoveg};
    Szin szoveg_hatter(0,0,150);
    Szin szoveg_keret(200,200,250);
    Szin szoveg_szoveg(205,205,255);
    vector<Szin> szoveg_szin={szoveg_hatter,szoveg_keret,szoveg_szoveg};
    Szin kiv_hatter(0,0,50);
    Szin kiv_keret(200,200,250);
    Szin kiv_szoveg(205,205,255);
    Szin lista_hatter(100,100,100);
    Szin lista_szoveg(230,230,230);
    Szin lista_aktiv_hatter(230,230,230);
    Szin lista_aktiv_szoveg(100,100,100);
    vector<Szin> kiv_szin={kiv_hatter,kiv_keret,kiv_szoveg,lista_hatter,lista_szoveg,lista_aktiv_hatter,lista_aktiv_szoveg};
    Szin csuszka_hatter(220,220,220);
    vector<Szin> csuszka_szin={csuszka_hatter};*/

    int meret=(min(XX,YY)-100)/tabla.size();
    int x,y;
    string jel="";

    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[i].size();j++){
            jel=tabla[i][j];
            x=10+i*(meret+2);
            y=10+j*(meret+2);
            K hely(i,j);
            kocka = new lambdaButton(x,y,meret,meret,jel,gomb_szin,[&,hely](){this->helyem(hely);});
            buttons.push_back(kocka);
        }
    }
    cout << "Ablak kesz" << endl;
};
