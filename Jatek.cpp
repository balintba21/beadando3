#include "Jatek.hpp"
#include "graphics.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace genv;
using namespace std;

void Jatek::uj_jatek(){
}
void Jatek::kilepes(){
    _fut=false;
}

K Jatek::event_loop(int XX, int YY){
    gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
    for (size_t i=0;i<buttons.size();i++) {
        buttons[i]->draw();
    }
    for (size_t i=0;i<widgets.size();i++) {
        widgets[i]->draw();
    }
    gout << refresh;
    event ev;
    bool esemeny=false;
    int focus = -1;
    while(gin >> ev && ev.keycode!=key_escape && !esemeny && _fut){
        for (size_t i=0;i<buttons.size();i++) {
            buttons[i]->handle(ev);
        }
        if(ev.keycode==key_tab){
            if(_key==65547){
                if(focus==0) focus=widgets.size()-1; else focus--;
            }
            else if(focus==widgets.size()-1) focus=0; else focus++;
            for (size_t i=0;i<widgets.size();i++){
                if (i==focus){
                    widgets[i]->selected(true);
                }
                else{
                    widgets[i]->selected(false);
                }
            }
        }
        if (ev.type == ev_mouse && ev.button==btn_left){
            if (focus==-1 || !widgets[focus]->is_selected(ev.pos_x, ev.pos_y)){

                for (size_t i=0;i<buttons.size();i++) {
                    if(buttons[i]->is_selected(ev.pos_x, ev.pos_y)) buttons[i]->action(), esemeny=true;
                }
                bool nincs_focus=true;
                for (size_t i=0;i<widgets.size();i++){
                    if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)){
                        focus = i;
                        widgets[i]->selected(true);
                        nincs_focus=false;
                    }
                    else{
                        widgets[i]->selected(false);
                    }
                }
                if(nincs_focus) focus=-1;
            }
        }

        for(size_t i=0;i<widgets.size();i++){
            widgets[i]->felette(ev);
        }
        if(ev.keycode!=-_key && _key>0 && ev.keycode==0){
            _key_db++;
            if(_key_db>10) ev.keycode=_key;
        }
        else if(ev.keycode>1000 ||ev.keycode<-1000){
            _key=ev.keycode;
            ev.keycode=_key;
            _key_db=1;
        }
        if (focus!=-1) {
            widgets[focus]->handle(ev);
        }
        gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
        for (size_t i=0;i<buttons.size();i++) {
            buttons[i]->draw();
        }
        for (size_t i=0;i<widgets.size();i++) {
            if(i!=focus) widgets[i]->draw();
        }
        if (focus!=-1) {
            widgets[focus]->draw();
        }
        gout << refresh;
    }
    if(ev.keycode==key_escape || !_fut) valasz._y=-1;
    return valasz;
};

Jatek::Jatek(int XX,int YY,vector<vector<Amoba_kocka>> tabla,string uzenet,bool fut){
    _fut=true;
    //gout.load_font("LiberationSans-Regular.ttf",24,true);
    gout.load_font("LiberationSans-Regular.ttf",16,true);
    Szin gomb_keret(220,110,40);
    Szin gomb_aktiv(255,170,30);
    Szin gomb_felette(255,200,40);
    Szin gomb_hatter(255,255,90);
    Szin gomb_nyert(200,100,20);
    Szin gomb_betu(200,90,0);
    Szin gomb_x(60,70,200);
    Szin gomb_o(255,25,0);
    vector<Szin> gomb_szin={gomb_keret,gomb_aktiv,gomb_felette,gomb_hatter,gomb_betu};

    Szin szoveg_hatter(0,0,150);
    Szin szoveg_keret(200,200,250);
    Szin szoveg_szoveg(205,205,255);
    vector<Szin> szoveg_szin={szoveg_hatter,szoveg_keret,szoveg_szoveg};
    int szoveg_magassag=5+gout.cascent()+gout.cdescent()+5;
    /*Szin szam_hatter(0,0,100);
    Szin szam_keret(200,200,250);
    Szin szam_szoveg(205,205,255);
    vector<Szin> szam_szin={szam_hatter,szam_keret,szam_szoveg};
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

    int meret=(min(XX,YY)-(30+szoveg_magassag))/tabla.size();
    int x,y;
    string jel="";
    float keret=meret/10;
    int x_koz=10;
    int y_koz=YY-tabla[0].size()*meret+10+szoveg_magassag;


    kiir1 = new StaticText(10+(meret*tabla[0].size()-gout.twidth(uzenet))/2,10,10+gout.twidth(uzenet)+10,szoveg_magassag,uzenet,szoveg_szin);
    widgets.push_back(kiir1);

   // gout.load_font("LiberationSans-Regular.ttf",meret-2*keret,true);
    float betumeret = meret-2*keret;
    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[i].size();j++){
            jel=tabla[i][j]._ertek;
            bool engedely=false;
            if(tabla[i][j]._ertek=='X') gomb_szin[4]=gomb_x; else if(tabla[i][j]._ertek=='O') gomb_szin[4]=gomb_o; else engedely=true,gomb_szin[4]=gomb_betu;
            if(!fut) engedely=false;
            if(tabla[i][j]._nyert) gomb_szin[3]=gomb_nyert; else gomb_szin[3]=gomb_hatter;
            x=x_koz+i*(meret);
            y=y_koz/2+j*(meret);
            K hely(i,j);
            kocka = new lambdaButton(x,y,meret,meret,keret,"LiberationSans-Regular.ttf",betumeret,engedely,jel,gomb_szin,[&,hely](){this->helyem(hely);});
            buttons.push_back(kocka);
        }
    }
    K hely1(-2,-2);
    gomb_szin[4]=gomb_betu;
    gomb_szin[3]=gomb_hatter;
    kocka = new lambdaButton(10+meret*tabla[0].size()+10,50,300,50,keret,"LiberationSans-Regular.ttf",50-2*keret,true,"Új játék",gomb_szin,[&,hely1](){this->helyem(hely1);});
    buttons.push_back(kocka);

    kocka = new lambdaButton(10+meret*tabla[0].size()+10,110,300,50,keret,"LiberationSans-Regular.ttf",50-2*keret,true,"Kilépés",gomb_szin,[&](){this->kilepes();});
    buttons.push_back(kocka);

};

