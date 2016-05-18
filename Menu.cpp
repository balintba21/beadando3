#include "Menu.hpp"
#include "graphics.hpp"
#include "Koordinata.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace genv;
using namespace std;

Menu::Menu(int XX,int YY,vector<vector<string>> menutomb){
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
            kocka = new lambdaButton(x,y,x_meret,y_meret,keret,"Stroke Dimension.ttf",y_meret-2*keret,felirat,gomb_szin,[&,hely](){this->helyem(hely);});
            buttons.push_back(kocka);
        }
    }
};

