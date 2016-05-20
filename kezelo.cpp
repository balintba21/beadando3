#include "graphics.hpp"
#include "kezelo.hpp"

using namespace genv;

void P::fajlba_mentes(string fajlnev){
    ofstream ki(fajlnev);
    ki << tabla.size() << " " << tabla[0].size() << " " << kor << endl;
    char ertek=' ';
    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[i].size();j++){
            if(tabla[i][j]._ertek==' ') ertek='-'; else ertek=tabla[i][j]._ertek;
            ki << ertek << " " << tabla[i][j]._nyert << " ";
        }
        ki << endl;
    }
    ki.close();
}

P::P(int meret,int XX,int YY) : meret(XX,YY){
    vector<Amoba_kocka> oszlop;
    for(int i=0;i<meret;i++){
        Amoba_kocka amoba_negyzet(' ',false);
        oszlop.push_back(amoba_negyzet);
    }

    vector<vector<Amoba_kocka>> v;
    ifstream be("adatok.txt");
    if(!be.good()){
        ofstream ki("adatok.txt");
        ki.close();
    }
    else{
        K be_meret(0,0);
        be >> be_meret._x >> be_meret._y >> kor >> ws;
        if(be_meret._x==meret && be_meret._y==meret){
            char c;
            bool nyerte;
            for(int i=0;i<meret;i++){
                v.push_back(oszlop);
            }
            for(int i=0;i<meret && be.good();i++){
                for(int j=0;j<meret && be.good();j++){
                    be >> c >> nyerte >> ws;
                    if(c=='-') c=' ';
                    Amoba_kocka be_an(c,nyerte);
                    v[i][j]=be_an;
                }
            }
        }
    }
    be.close();

    for(int i=0;i<meret;i++){
        tabla.push_back(oszlop);
    }
    if(v.size()==meret && v[0].size()==meret){
        for(int i=0;i<meret;i++){
            for(int j=0;j<meret;j++){
                tabla[i][j]=v[i][j];
            }
        }
    }
    else{
        kor=0;
    }
    nyertes=' ';
    gout.open(XX,YY);

}
void P::uj(int x, int y,char c){
    if(tabla[x][y]._ertek==' ') tabla[x][y]._ertek=c;
}
bool P::allas(int nyero_minimum){
    int max=1,smax=1,omax=1,amax=1;
    for(int i=0;i<tabla.size();i++){
        for(int j=0;j<tabla[0].size();j++){
            if(j<tabla[0].size()-1){
                if(tabla[i][j]._ertek==tabla[i][j+1]._ertek && tabla[i][j]._ertek!=' ') omax++; else omax=1;
                if(max<omax){
                    max=omax;
                }
                if(omax>=nyero_minimum){
                    for(int nyer=0;nyer<omax;nyer++){
                        tabla[i][j+1-nyer]._nyert=true;
                    }
                }
            }
            for(int ii=0;ii<tabla.size()-1;ii++){
                if(tabla[ii][j]._ertek==tabla[ii+1][j]._ertek && tabla[ii][j]._ertek!=' ') smax++; else smax=1;
                if(max<smax){
                    max=smax;
                }
                if(smax>=nyero_minimum){
                    for(int nyer=0;nyer<smax;nyer++){
                        tabla[ii+1-nyer][j]._nyert=true;
                    }
                }
            }
            smax=1;

            for(int m=0;(j+m)<tabla[0].size()-1 && (i+m)<tabla.size()-1;m++){
                if(tabla[i+m][j+m]._ertek==tabla[i+m+1][j+m+1]._ertek && tabla[i+m][j+m]._ertek!=' ') amax++; else amax=1;
                if(max<amax){
                    max=amax;
                }
                if(amax>=nyero_minimum){
                    for(int nyer=0;nyer<amax;nyer++){
                        tabla[i+m+1-nyer][j+m+1-nyer]._nyert=true;
                    }
                }
            }
            amax=1;
            for(int m=0;(j+m)<tabla[0].size()-1 && (i-m)>0;m++){
                if(tabla[i-m][j+m]._ertek==tabla[i-m-1][j+m+1]._ertek && tabla[i-m][j+m]._ertek!=' ') amax++; else amax=1;
                if(max<amax){
                    max=amax;
                }
                if(amax>=nyero_minimum){
                    for(int nyer=0;nyer<amax;nyer++){
                        tabla[i-m-1+nyer][j+m+1-nyer]._nyert=true;
                    }
                }
            }
            amax=1;
        }
        omax=1;
    }

    if(max>=nyero_minimum) return false; else return true;
}
void P::futtatas(){
    while(nyertes!='k'){
        nyertes=jatek();
        for(int i=0;i<tabla.size();i++){
            for(int j=0;j<tabla[0].size();j++){
                tabla[i][j]._ertek=' ';
                tabla[i][j]._nyert=false;
            }
        }
        kor=0;
        if(nyertes==' ') fajlba_mentes("adatok.txt");
    }
}

char P::jatek(){
    int x,y;
    K ujhely(-1,0);
    bool fut=true;
    while(fut && ujhely._y!=-1 && ujhely._y!=-2){
        string uzenet;
        if(kor==tabla.size()*tabla[0].size()){
            uzenet="Megtelt a pálya!";
            Jatek jatek(meret._x,meret._y,tabla,uzenet,false);
            ujhely=jatek.event_loop(meret._x,meret._y);
        }
        else if(allas(5)){
            uzenet="A";
            if(kor%2==0) uzenet+="z X "; else uzenet+="z O ";
            uzenet+="karakter következik.";
            Jatek jatek(meret._x,meret._y,tabla,uzenet,true);
            ujhely=jatek.event_loop(meret._x,meret._y);
            if(ujhely._x>=0 && ujhely._y>=0){
                if(tabla[ujhely._x][ujhely._y]._ertek==' '){
                    kor++;
                    if(kor%2==0){
                        tabla[ujhely._x][ujhely._y]._ertek='O';
                    }
                    else{
                        tabla[ujhely._x][ujhely._y]._ertek='X';
                    }
                }
            }
        }
        else if(!allas(5)){
            uzenet="A";
            if(kor%2==0) uzenet+="z O "; else uzenet+="z X ";
            uzenet+="karakter nyert.";
            Jatek jatek(meret._x,meret._y,tabla,uzenet,false);
            ujhely=jatek.event_loop(meret._x,meret._y);
        }
        fajlba_mentes("adatok.txt");
    }
    if(ujhely._y==-2){
        nyertes=' ';
    }
    else if(ujhely._y==-1){
        nyertes='k';
    }
    return nyertes;
}

