#include "Amobakocka.hpp"

Amoba_kocka::Amoba_kocka(char ertek,bool nyert){
    _ertek=ertek;
    _nyert=nyert;
}
Amoba_kocka Amoba_kocka::operator=(Amoba_kocka masik){
    _ertek=masik._ertek;
    _nyert=masik._nyert;
    return *this;
}

