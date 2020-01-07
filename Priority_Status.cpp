#include "Priority_Status.hpp"
#include <string>
#include <iostream>
using namespace std;

//Constructeurs
Priority::Priority(int _index) {SetPriority(_index);}
Priority::Priority(string _priority) {SetPriority(_priority);}
Priority::Priority(int _index) : index(NORMAL) {} //Par défaut, on reste en normal

//Méthodes
string Priority::GetPriority() {return list[index];}

void Priority::SetPriority(int _index) {
    //On vérifie si l'index est cohérent, c'est à dire qu'il est bien compris entre 0 et NB_PRIORITY - 1
    //Sinon, on le met à -1, signe d'une erreur
    if (0 <= _index < NB_PRIORITY )
    {
        index = _index;
    }
    else
    {
        index = -1;
    }
};

void Priority::SetPriority(string _priority) {
    int i = 0;
    /* On cherche dans la boucle suivante si _priority correspond bien a un des états possibles d'une priorité.
    Comme toutes les possibilités sont dans list, on itère sur cette dernière, et si jamais l'on trouve une correspondane,
    i prend la valeur de son index. Si l'on ne trouve rien, i aura pour valeur NB_PRIORITY et l'appel final à SetPriority renverra
    une erreure. */
    while (i < NB_PRIORITY){
        if (list[i] == _priority){
            break;
        }
        i++;
    }
    SetPriority(i);
}
