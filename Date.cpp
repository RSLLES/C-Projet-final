#include "Date.hpp"
#include <ctime>
#include <iostream>

Date::Date(int _day, int _month, int _year) : year(_year), day(_day), month(_month) {}

Date::Date(){
    //On récupère la date d'aujourd'hui en utilisant la bibliothèque <ctime>, puis on utilise l'autre constructeur.
    //Enfin, on supprime le pointeur qui ne nous sert plus a rien
    time_t now = time(0);
    tm *ltm = localtime(&now);
    day = ltm->tm_mday;
    month = ltm->tm_mon + 1;
    year = ltm->tm_year + 1900;
    //Il y a un léger décallage à compenser
    delete ltm;
}

void Date::Print()
{
    std::cout << day << "/" << month << "/" << year;
}