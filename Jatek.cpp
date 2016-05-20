#include "Jatek.hpp"
#include "graphics.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace genv;
using namespace std;

void Jatek::helyem(K hely){
    valasz=hely;
}

void Jatek::uj_jatek(){
    _fut=false;
    valasz._x=-2;
    valasz._y=-2;
}
void Jatek::kilepes(){
    _fut=false;
    valasz._x=-1;
    valasz._y=-1;
}
int Jatek::magassag(int meret){
    int szovegmagassag=ceil(meret*0.90528)+floor(meret*0.21191);
    return szovegmagassag;
}
int Jatek::betumeret(float dobozmagassag){
    int betu_meret=0;
    for(;dobozmagassag>magassag(betu_meret);betu_meret++);
    betu_meret--;
    return betu_meret;
}

int Jatek::hossz(int meret,float atlaghosz/*(közelítő átlag karakter méret a kiírandó szövegeknél)*/,string szoveg){
    int szoveghossz=ceil(float(szoveg.length())*atlaghosz*meret);
    return szoveghossz;
}

float Jatek::aranybecslo(int meret,string tipus,string szoveg){
    gout.load_font(tipus,meret,true);
    return float(gout.twidth(szoveg))/hossz(meret,1,szoveg);
}




K Jatek::event_loop(int XX, int YY){
    gout << color(0,0,0) << move_to(0,0) << box(XX,YY);
    gout.load_font("LiberationSans-Regular.ttf",_betumeret[1],true);
    for (size_t i=0;i<palya.size();i++) {
        palya[i]->draw();
    }
    gout.load_font("LiberationSans-Regular.ttf",_betumeret[0],true);
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
        for (size_t i=0;i<palya.size();i++) {
            palya[i]->handle(ev);
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
                for (size_t i=0;i<palya.size();i++) {
                    if(palya[i]->is_selected(ev.pos_x, ev.pos_y)) palya[i]->action(), esemeny=true;
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
        gout.load_font("LiberationSans-Regular.ttf",_betumeret[1],true);
        for (size_t i=0;i<palya.size();i++) {
            palya[i]->draw();
        }
        gout.load_font("LiberationSans-Regular.ttf",_betumeret[0],true);
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
    if(ev.keycode==key_escape) valasz._y=-1;
    return valasz;
};

Jatek::Jatek(int XX,int YY,vector<vector<Amoba_kocka>> tabla,string uzenet,bool fut){
    _fut=true;
    _betumeret={22,16,22};
    int szovegmagassag=magassag(_betumeret[0]);
    int szoveghossz=hossz(_betumeret[0],0.44,uzenet);

    Szin szoveg_hatter(222,120,30);
    Szin szoveg_keret(220,110,40);
    Szin szoveg_szoveg(255,255,90);
    vector<Szin> szoveg_szin={szoveg_hatter,szoveg_keret,szoveg_szoveg};
    int szoveg_magassag=5+szovegmagassag+5;





    int meret=min((YY-(30+szoveg_magassag)),XX-(30+hossz(_betumeret[2],0.3182,"Új játék")))/tabla.size();
    int x,y;
    string jel="";
    float keret=meret/10;
    int x_koz=10;
    int y_koz=20+szoveg_magassag;


    kiir1 = new StaticText(10+(meret*tabla[0].size()-szoveghossz)/2,10,10+szoveghossz+10,szoveg_magassag,uzenet,szoveg_szin);
    widgets.push_back(kiir1);



    Szin gomb_keret(220,110,40);
    Szin gomb_aktiv(255,170,30);
    Szin gomb_felette(255,200,40);
    Szin gomb_hatter(255,255,90);
    Szin gomb_nyert(200,90,20);
    Szin gomb_betu(200,90,0);
    Szin gomb_x(60,70,200);
    Szin gomb_o(255,25,0);
    vector<Szin> gomb_szin={gomb_keret,gomb_aktiv,gomb_felette,gomb_hatter,gomb_betu};
    _betumeret[1]=betumeret(meret)+1;
    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[i].size();j++){
            jel=tabla[i][j]._ertek;
            bool engedely=false;
            if(tabla[i][j]._ertek=='X') gomb_szin[4]=gomb_x; else if(tabla[i][j]._ertek=='O') gomb_szin[4]=gomb_o; else engedely=true,gomb_szin[4]=gomb_betu;
            if(!fut) engedely=false;
            if(tabla[i][j]._nyert) gomb_szin[3]=gomb_nyert; else gomb_szin[3]=gomb_hatter;
            x=x_koz+i*(meret);
            y=y_koz+j*(meret);
            K hely(i,j);
            kocka = new lambdaButton(x,y,meret,meret,keret,"LiberationSans-Regular.ttf",_betumeret[1],engedely,jel,gomb_szin,[&,hely](){this->helyem(hely);});
            palya.push_back(kocka);
        }
    }


    K hely1(-2,-2);
    gomb_szin[4]=gomb_betu;
    gomb_szin[3]=gomb_hatter;
    keret=2;
    kocka = new lambdaButton(10+meret*tabla[0].size()+10,y_koz,10+hossz(_betumeret[2],0.3182,"Új játék"),10+magassag(_betumeret[2])+10,keret,"LiberationSans-Regular.ttf",50-2*keret,true,"Új játék",gomb_szin,[&](){this->uj_jatek();});
    buttons.push_back(kocka);
    kocka = new lambdaButton(10+meret*tabla[0].size()+10,y_koz+10+magassag(_betumeret[2])+10+10,10+hossz(_betumeret[2],0.364,"Kilépés"),10+magassag(_betumeret[2])+10,keret,"LiberationSans-Regular.ttf",50-2*keret,true,"Kilépés",gomb_szin,[&](){this->kilepes();});
    buttons.push_back(kocka);
};

