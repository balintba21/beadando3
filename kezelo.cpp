#include "graphics.hpp"
#include "kezelo.hpp"

using namespace genv;

P::P(int meret,int XX,int YY) : meret(XX,YY){
    vector<char> oszlop;
    //vector<K> nyero_helyek;
    for(int i=0;i<meret;i++){
        oszlop.push_back(' ');
    }
    for(int i=0;i<meret;i++){
        tabla.push_back(oszlop);
    }
    nyertes=' ';
    gout.open(XX,YY);
    kor=0;
}
void P::uj(int x, int y,char c){
    if(x>tabla.size()-1 || x<0 || y>tabla.size()-1 || y<0) cout << "Kilooog!! " << endl;
    if(tabla[x][y]==' ') tabla[x][y]=c;
}
bool P::allas(){
    nyero_helyek.clear();
    int max=1,smax=1,omax=1,amax=1;
    for(int j=0;j<tabla[0].size();j++){/*
        for(int i=0;i<tabla.size();i++){
            if(tabla[i][j-1]==tabla[i][j] && tabla[i][j]!=' ') omax++; else omax=1;
            if(max<omax) max=omax ,nyertes=tabla[i][j];
            omax=1;
        }*/
        for(int i=0;i<tabla.size()-1;i++){
            if(tabla[i][j]==tabla[i+1][j] && tabla[i][j]!=' ') smax++; else smax=1;
            if(max<smax){
                max=smax;
            }
            if(max>nyero_helyek.size()){
                nyero_helyek.clear();
                for(int nyer=0;nyer<max;nyer++){
                    K ujk1(i+1-nyer,j);
                    nyero_helyek.push_back(ujk1);
                }
            }
        }
        smax=1;
        for(int k=0;k<tabla[0].size()-1;k++){
            if(tabla[j][k]==tabla[j][k+1] && tabla[j][k]!=' ') omax++; else omax=1;
            if(max<omax){
                max=omax;
            }
            if(max>nyero_helyek.size()){
                nyero_helyek.clear();
                for(int nyer=0;nyer<max;nyer++){
                    K ujk1(j,k+1-nyer);
                    nyero_helyek.push_back(ujk1);
                }
            }
        }
        omax=1;

        for(int k=0;k<tabla.size();k++){
            for(int m=0;(j+m)<tabla[0].size()-1 && (k+m)<tabla.size()-1;m++){
                if(tabla[j+m][k+m]==tabla[j+m+1][k+m+1] && tabla[j+m][k+m]!=' ') amax++; else amax=1;
                if(max<amax){
                    max=amax;
                }
                if(max>nyero_helyek.size()){
                    nyero_helyek.clear();
                    for(int nyer=0;nyer<max;nyer++){
                        K ujk1(j+m+1-nyer,k+m+1-nyer);
                        nyero_helyek.push_back(ujk1);
                    }
                }
            }
            amax=1;
            for(int m=0;(j+m)<tabla[0].size()-1 && (k-m)>0;m++){
                if(tabla[j+m][k-m]==tabla[j+m+1][k-m-1] && tabla[j+m][k-m]!=' ') amax++; else amax=1;
                if(max<amax){
                    max=amax;
                }
                if(max>nyero_helyek.size()){
                    nyero_helyek.clear();
                    for(int nyer=0;nyer<max;nyer++){
                        K ujk1(j+m+1-nyer,k-m-1+nyer);
                        nyero_helyek.push_back(ujk1);
                    }
                }
            }
            amax=1;
        }
    }

    if(max>=5){
        for(int ny=0;ny<nyero_helyek.size();ny++){
            cout << nyero_helyek[ny]._x << " : " << nyero_helyek[ny]._y << endl;
        }
        if(nyero_helyek.size()>0){
            for(int ny=0;ny<nyero_helyek.size();ny++){
                tabla[nyero_helyek[ny]._x][nyero_helyek[ny]._y]='L';
            }
        }
        cout << endl;
        return false;
    }
    else{
        return true;
    }
}
void P::menu(){
    vector<string> sor={"Uj jatek","Sugo","Kilepes"};
    menutomb.push_back(sor);
    K ujhely(-2,-2);
    while(nyertes!='k'){
        /*Menu menu(meret._x,meret._y,menutomb);
        ujhely=menu.event_loop(meret._x,meret._y);
        if(ujhely._y==0){
            nyertes=jatek();
            for(int i=0;i<tabla.size();i++){
                for(int j=0;j<tabla[0].size();j++){
                    tabla[i][j]=' ';
                }
            }
        }
        else if(ujhely._y==1){
            cout << "Sugoo" << endl;
        }
        else if(ujhely._y!=2){
            ujhely._y=2;//Esc lenyomaskor
        }*/
        for(int i=0;i<tabla.size();i++){
            for(int j=0;j<tabla[0].size();j++){
                tabla[i][j]=' ';
            }
        }
        kor=0;
        nyertes=jatek();
    }
}

char P::jatek(){
    int x,y;
    K ujhely(-1,0);
    bool fut=true;
    while(fut && ujhely._y!=-1 && ujhely._y!=-2){
        string uzenet;
        if(kor==tabla.size()*tabla[0].size()){
            uzenet="Megtelt a palya!";
            Jatek jatek(meret._x,meret._y,tabla,uzenet);
            ujhely=jatek.event_loop(meret._x,meret._y);
        }
        else if(allas()){
            uzenet="A";
            if(kor%2==0) uzenet+="z X "; else uzenet+="z O ";
            uzenet+="karakter kovetkezik.";
            Jatek jatek(meret._x,meret._y,tabla,uzenet);
            ujhely=jatek.event_loop(meret._x,meret._y);
            if(ujhely._x>=0 && ujhely._y>=0){
                if(tabla[ujhely._x][ujhely._y]==' '){
                    kor++;
                    if(kor%2==0){
                        tabla[ujhely._x][ujhely._y]='O';
                    }
                    else{
                        tabla[ujhely._x][ujhely._y]='X';
                    }
                }
            }
        }
        else if(!allas()){
            uzenet="A";
            if(kor%2==0) uzenet+="z O "; else uzenet+="z X ";
            uzenet+="karakter nyert.";
            Jatek jatek(meret._x,meret._y,tabla,uzenet);
            ujhely=jatek.event_loop(meret._x,meret._y);
        }
    }
    if(ujhely._y==-2){
        nyertes=' ';
    }
    else if(ujhely._y==-1){
        nyertes='k';
    }
    return nyertes;
}

