#ifndef JATEK_HPP
#define JATEK_HPP

#include "Ablak.hpp"
#include "StaticText.hpp"
#include "Amobakocka.hpp"

class Jatek: public Ablak
{
    StaticText * kiir1;
    bool _fut;
public:
    Jatek(int XX,int YY,vector<vector<Amoba_kocka>> tabla,string uzenet,bool fut);
    K event_loop(int XX, int YY);
    void uj_jatek();
    void kilepes();
};

#endif // JATEK_HPP_INCLUDED
