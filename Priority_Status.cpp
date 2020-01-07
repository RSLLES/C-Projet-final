#include "Priority_Status.hpp"
#include <string>
#include <iostream>
using namespace std;

//###########################################
//ListeDETats
//###########################################
ListeDETats::ListeDETats(int _n, string* _liste, int _index) : n(_n), list(_liste), index(_index) {Set(index);}

//Méthodes
string ListeDETats::Get() {
    if (0 <= index && index < n )
    {
        return list[index];
    }
    return "ERREUR";
}

void ListeDETats::Set(int _index) {
    //On vérifie si l'index est cohérent, c'est à dire qu'il est bien compris entre 0 et n - 1
    //Sinon, on le met à -1, signe d'une erreur
    if (0 <= _index  && _index < n )
    {
        index = _index;
    }
    else
    {
        index = -1;
    }
};

void ListeDETats::Set(string _etat) {
    int i = 0;
    /* On cherche dans la boucle suivante si _priority correspond bien a un des états possibles d'une priorité.
    Comme toutes les possibilités sont dans list, on itère sur cette dernière, et si jamais l'on trouve une correspondane,
    i prend la valeur de son index. Si l'on ne trouve rien, i aura pour valeur NB_PRIORITY et l'appel final à SetPriority renverra
    une erreure. */
    while (i < n){
        if (list[i] == _etat){
            break;
        }
        i++;
    }
    Set(i);
}

void ListeDETats::PrintList(){
    for (int i = 0; i < n; i++)
    {
        cout << list[i] << endl;
    }
}


//############################
//Priority
//############################
Priority::Priority() : Priority(0) {}
Priority::Priority(int _index) : ListeDETats(3, new string[3] {"Normal", "Hight", "Low"}, _index){}