#include "graphics.hpp"
#include "kezelo.hpp"

using namespace genv;

P::P(int meret,int XX,int YY) : meret(XX,YY){
    vector<char> sor;
    for(int i=0;i<meret;i++){
        sor.push_back(' ');
    }
    for(int i=0;i<meret;i++){
        tabla.push_back(sor);
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
    int max=1,smax=1,omax=1,amax=1;
    for(int j=0;j<tabla[0].size();j++){
        for(int i=1;i<tabla.size();i++){
            if(tabla[i-1][j]==tabla[i][j] && tabla[i][j]!=' ') smax++; else smax=1;
            if(max<smax) max=smax ,nyertes=tabla[i][j];
        }
        smax=1;
        for(int k=j;k<tabla.size()-1;k++){
            if(tabla[k][k+j]==tabla[k+1][k+j+1] && tabla[k][k+j]!=' ') amax++; else amax=1;
            if(max<amax) max=amax ,nyertes=tabla[k][k+j];
        }
        amax=1;
        for(int k=j;k<tabla.size()-1;k++){
            if(tabla[tabla.size()-1-k+j][k]==tabla[tabla.size()-1-k+j-1][k+1] && tabla[tabla.size()-1-k+j][k]!=' ') amax++; else amax=1;
            if(max<amax) max=amax ,nyertes=tabla[tabla.size()-1-k+j][k];
        }
        amax=1;
    }

    for(int i=0;i<tabla.size();i++){
        for(int j=1;j<tabla[i].size();j++){
            if(tabla[i][j-1]==tabla[i][j] && tabla[i][j]!=' ') omax++; else omax=1;
            if(max<omax) max=omax ,nyertes=tabla[i][j];
        }
        omax=1;


        for(int k=i;k<tabla.size()-1;k++){
            if(tabla[k][k-i]==tabla[k+1][k-i+1] && tabla[k][k-i]!=' ') amax++; else amax=1;
            if(max<amax) max=amax ,nyertes=tabla[k][k-i];
        }
        amax=1;
        for(int k=i;k>0;k--){
            if(tabla[k][i-k]==tabla[k-1][i-k+1] && tabla[k][i-k]!=' ') amax++; else amax=1;
            if(max<amax) max=amax ,nyertes=tabla[k][i-k];
            //cout << "(" << k << ":" << i-k << ") " << amax << endl;
        }
        amax=1;
    }
    if(max>=5){
        return false;
    }
    else{
        return true;
    }
}
void P::menu(){
    vector<string> sor={"Uj jatek","Sugo","Kilepes"};
    menutomb.push_back(sor);
    K ujhely(-1,-1);
    while(ujhely._y!=2){
        Menu menu(meret._x,meret._y,menutomb);
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
        }
    }
}

char P::jatek(){
    int x,y;
    K ujhely(-1,0);
    while(allas() && ujhely._y!=-1){
        string uzenet="A";
        if(kor%2==0) uzenet+="z X "; else uzenet+="z O ";
        uzenet+="karakter kovetkezik.";
        /*
        for(int j=0;j<tabla[0].size();j++){
            for(int i=0;i<tabla.size();i++){
                cout << tabla[i][j] << ", ";
            }
            cout << endl;
        }
        */
        /*
        cin >> x >> y;
        if(x<tabla.size() && x>=0 && y<tabla.size() && y>=0){
            uj(x,y,'y');
        }
        else{
            while(x>tabla.size()-1 || x<0 || y>tabla.size()-1 || y<0){
                cout << "Hibas lepes! Lepj ujra:" << endl;
                cin >> x >> y;
            }
        }
        if(allas()){
            for(int j=0;j<tabla[0].size();j++){
                for(int i=0;i<tabla.size();i++){
                    cout << tabla[i][j] << ", ";
                }
                cout << endl;
            }
            cin >> x >> y;
            if(tabla[x][y]==' ' && x<tabla.size() && x>=0 && y<tabla.size() && y>=0){
                uj(x,y,'x');
            }
            else{
                while(tabla[x][y]!=' ' || x>tabla.size()-1 || x<0 || y>tabla.size()-1 || y<0){
                    cout << "Hibas lepes! Lepj ujra:" << endl;
                    cin >> x >> y;
                }
            }
        }*/
        Jatek jatek(meret._x,meret._y,tabla,uzenet);
        ujhely=jatek.event_loop(meret._x,meret._y);
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
    /*
    for(int j=0;j<tabla[0].size();j++){
        for(int i=0;i<tabla.size();i++){
            cout << tabla[i][j] << ", ";
        }
        cout << endl;
    }*/
    return nyertes;
}

