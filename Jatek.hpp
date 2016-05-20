#ifndef JATEK_HPP
#define JATEK_HPP

#include "Ablak.hpp"
#include "StaticText.hpp"
#include "Amobakocka.hpp"

#include <string>

class Jatek: public Ablak
{
    StaticText * kiir1;
    bool _fut;
    vector<Button*> palya;
    vector<int> _betumeret;
public:
    Jatek(int XX,int YY,vector<vector<Amoba_kocka>> tabla,string uzenet,bool fut);
    K event_loop(int XX, int YY);
    void helyem(K hely);
    void uj_jatek();
    void kilepes();
    int magassag(int meret);
    int hossz(int meret,float atlaghosz,string szoveg);
    float aranybecslo(int meret,string tipus,string szoveg);
    int betumeret(float magassag);
};

#endif // JATEK_HPP_INCLUDED
