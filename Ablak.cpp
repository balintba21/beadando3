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

Ablak::Ablak(int XX,int YY,vector<vector<char>> tabla){
    gout.load_font("LiberationSans-Regular.ttf",(min(XX,YY)-(2*10)+2)/tabla.size()-4,true);
    Szin gomb_keret(170,30,0);
    Szin gomb_aktiv(255,170,30);
    Szin gomb_felette(255,200,40);
    Szin gomb_hatter(255,255,90);
    Szin gomb_betu(200,200,250);
    Szin gomb_x(60,70,200);
    Szin gomb_o(255,25,0);
    vector<Szin> gomb_szin={gomb_keret,gomb_aktiv,gomb_felette,gomb_hatter,gomb_betu};
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

    int meret=(min(XX,YY)-(2*10))/tabla.size();
    int x,y;
    string jel="";
    float keret=meret/10;

    int x_koz=XX-tabla.size()*meret;
    int y_koz=YY-tabla[0].size()*meret;
    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[i].size();j++){
            jel=tabla[i][j];
            if(tabla[i][j]=='X') gomb_szin[4]=gomb_x; else if(tabla[i][j]=='O') gomb_szin[4]=gomb_o;
            x=x_koz/2+i*(meret);
            y=y_koz/2+j*(meret);
            K hely(i,j);
            kocka = new lambdaButton(x,y,meret,meret,keret,jel,gomb_szin,[&,hely](){this->helyem(hely);});
            buttons.push_back(kocka);
        }
    }
};

Ablak::Ablak(int XX,int YY,vector<vector<string>> menutomb){
    gout.load_font("Stroke Dimension.ttf",80,true);
    Szin gomb_keret(0,0,100);
    Szin gomb_aktiv(0,150,175);
    Szin gomb_felette(0,100,200);
    Szin gomb_hatter(0,0,210);
    Szin gomb_betu(200,200,250);
    vector<Szin> gomb_szin={gomb_keret,gomb_aktiv,gomb_felette,gomb_hatter,gomb_betu};

    int max_meret=0;
    for(int i=0;i<menutomb[0].size();i++){
        if(max_meret<gout.twidth(menutomb[0][i])) max_meret=gout.twidth(menutomb[0][i]);
    }

    int x_meret=10+max_meret+10,y_meret=5+gout.cascent()+gout.cdescent()+5;
    int x,y;
    string felirat="";
    float keret=1;
    int x_koz=XX-menutomb.size()*(x_meret+2)-2;
    int y_koz=YY-menutomb[0].size()*(y_meret+2)-2;
    for(int i=0;i<menutomb.size();i++){
        for(int j=0;j<menutomb[i].size();j++){
            felirat=menutomb[i][j];
            x=x_koz/2+i*(x_meret+2);
            y=y_koz/2+j*(y_meret+2);
            K hely(i,j);
            kocka = new lambdaButton(x,y,x_meret,y_meret,keret,felirat,gomb_szin,[&,hely](){this->helyem(hely);});
            buttons.push_back(kocka);
        }
    }
};
